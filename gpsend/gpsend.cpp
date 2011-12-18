
#include <gpsend.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <fnmatch.h>
#include <stdarg.h>
#include <stdlib.h>

#include <algorithm>




static bool need_terminated;

void signal_TERM(int signalFlag)
{
        signal(SIGTERM,SIG_IGN);
        need_terminated = true;
#ifdef DEBUG_PRINT_L3
        puts("TERM signal catched");
#endif
}


bool need_exit(const string &s)
{
        if (need_terminated) {
                return need_terminated;
        }

        int erno_bak = errno;
        if (!access(s.c_str(), F_OK)) {
                need_terminated = true;
#ifdef DEBUG_PRINT_L3
                printf("%s:exist, and remove it\n", s.c_str());
#endif
                unlink(s.c_str());
        } else {//会设置全局错误标记
                errno = erno_bak;
        }

        return need_terminated;
}


flist_t *ls_dir(flist_t *fl, const char *path, const char *pattern,
                unsigned int max_file=64)
{
        DIR *dir = opendir(path);
        if (!dir) {
                return 0;
        }

        dirent *de;

        size_t i = 0;
        while ( (de = readdir(dir)) && (i <= max_file)) {
                //文件名是否匹配
                if (fnmatch(pattern, de->d_name, 0) ) {
                        continue;
                }
                string name = path;
                name += "/";
                name += de->d_name;
                struct stat fstatus;
                if (stat(name.c_str(), &fstatus) == -1) {

                        closedir(dir);
                        return 0;
                }

                if (S_ISREG(fstatus.st_mode) ) {//是一个普通文件 ，添加到文件列表
                        fl->push_back(de->d_name);
                        ++i;
                }//if S_ISREG


        }// while readdir
        closedir(dir);

        return fl;
}

//YYYYMMDDHH24MISS
char *full_time_str(char  *tstr, time_t t)
{
        struct tm * tm;
        tm=localtime(&t);
        sprintf(tstr,"%04d%02d%02d%02d%02d%02d",
                tm->tm_year+1900,
                tm->tm_mon+1,
                tm->tm_mday,
                tm->tm_hour,
                tm->tm_min,
                tm->tm_sec);

        return tstr;
}

//the log file resolution rate is DAY(24*60*60 seconds)
log_file::log_file(const string &pre,const string &arg_flag, int arg_day)
                :prefix(pre), seconds_per_log(arg_day*24*60*60),flag(arg_flag)
{

        tzset();

        fp = 0;
        time_t t = time(0) - timezone;
        stamp = (t/seconds_per_log ) *seconds_per_log ;

        open();


}

FILE *log_file::open(void)
{

        char buf[16] = {0};
        full_time_str(buf, stamp);
        buf[8]  = 0;


        string fname = prefix + flag +"_" + buf + ".log";
        if (fp) {
                fclose(fp);
                fp = 0;
        }
        fp = fopen(fname.c_str(), "a+");

        if (!fp) {
                fprintf(stderr, "%s:can not open in a+ mode :%s\n",
                        fname.c_str(), strerror(errno));
                exit(errno);
        }
        return fp;
}


void log_file::write(const char *fmt, ...)
{
        char buf[16];
        time_t t = time(0) - timezone ; //NOTE : this is the local time
        if (t -stamp >= seconds_per_log) {
                stamp = (t/(seconds_per_log) )*seconds_per_log;
                open();
        }


        full_time_str(buf, t);
        fputs(buf, fp);
        fputs(":", fp);

        va_list args;
        va_start(args,fmt);
        vfprintf(fp, fmt,args);
        va_end(args);
        fflush(fp);
}




conf_t *read_conf(conf_t *conf,const char *conf_name,
                  const string &pro_prefix)
{
        FILE *fp = fopen(conf_name, "r");
        if (!fp) {
                return 0;
        }

        char line_buf[line_max];
        while (fgets(line_buf, line_max, fp)) {
                //ignore the remark part
                char *p = strchr(line_buf, remark_op);
                if (p) {
                        *p = 0;
                }

                //not a valid key/value pair
                if (!strchr(line_buf, conf_op)) {
                        continue;
                }
                //not a key for the program
                if (strncmp(pro_prefix.c_str(),line_buf, pro_prefix.length())) {
                        continue;
                }



                char key[line_max/4];
                char value[line_max/4];
                sscanf(line_buf, "%[^=]=%s", key, value);
                trimsp(key);
                trimsp(value);


                if (conf->find(string(key)) ==conf->end() ) {
                        conf->insert(conf_t::value_type(key, value));
                }
        }
        fclose(fp);
        return conf;
}



void set_conf(const conf_t &conf)
{

        using namespace config;

        string pro_prefix = pro_name + ".";

        typedef struct conf_pair_t {
                string key;
                string *value;
        } conf_pair_t;

        conf_pair_t cp[] = {
                {
                        pro_prefix + "inputPath",
                        &input_dir
                },
                {
                        pro_prefix + "outputPath",
                        &output_dir
                },
                {
                        pro_prefix + "tmpPath",
                        &tmp_dir
                },
                {
                        pro_prefix + "bakPath",
                        &bak_dir
                },
                {
                        pro_prefix + "logPath",
                        &log_dir
                },
                {
                        pro_prefix + "errorPath",
                        &err_dir
                },
                {
                        pro_prefix + "filePattern",
                        &file_pattern
                }	,
                {
                        pro_prefix + "sleepTime",
                        &sleep_time
                },
                {
                        pro_prefix + "runFlag",
                        &run_flag
                },
                {
                        pro_prefix + "procID",
                        &proc_id
                },
                {
                        pro_prefix + "datapath",
                        &datapath
                }

        };

#ifdef DEBUG_PRINT_L3
        printf("sizeof(cp):sizeof(cp[0])= %d:%d\n",sizeof(cp),sizeof(cp[0]) );
#endif

        for (size_t i = 0 ; i < sizeof(cp) / sizeof(cp[0]) ; ++ i) {
                conf_t::const_iterator itr = conf.find(cp[i].key);
                if ( itr == conf.end()) {
                        string msg("Can not find config key: ");
                        msg += cp[i].key;
                        throw( *new runtime_error(msg));
                }
                *cp[i].value = itr->second;
        }

}




//void  run_daemon(void)
//{
//int i;
//pid_t pid;
//if((pid = fork()) > 0)	exit(0);
//
//sleep(1);
//setsid();
//signal(SIGHUP,SIG_IGN);
//if( (pid = fork()) > 0)	exit(0);
//sleep(1);
//
//for(i = 0; i < 3; i++){
//	close(i);
//	}
//}

void do_sleep(timer_arg_t *ta)
{
        static int st =atoi(config::sleep_time.c_str());
        time_t t = time(0);

        //no sleep while not done any thing
        if (t - ta->file_stamp > minutes_per_file *60) {
                return ;
        }

        if (st >  t - ta->file_stamp) {
                sleep (t - ta->file_stamp);
        } else {
                sleep (st);
        }
}


struct  do_action {
        timer_arg_t *ta;
        time_t curr;  //超时时间
        void operator () (timer &tmr) {
                if (tmr.time_out(curr)) {
                        tmr.action(ta);
                        tmr.set_stamp(ta->timer_stamp );
                }

        }
} ;

namespace config
{
string input_dir;
string output_dir;
string tmp_dir;
string err_dir;
string index_dir;
string bak_dir;
string proc_id;
string run_flag;
string sleep_time;
string log_dir;
string file_pattern;
string datapath;

}


void build_chk_rule(chklist_t *ck, const string &ckf)
{
        FILE *fck = fopen(ckf.c_str(), "rt");
        if (!fck) {
                throw runtime_error("can not open check rule file");
        }

        char line_buf[1024];

        while (fgets(line_buf, sizeof(line_buf), fck)) {
                char enostr [ 128 ] = {0};
                char restr [512] = {0};
                sscanf (line_buf, "%128[^:]:%511[^\n]", enostr, restr);
#ifdef DEBUG_PRINT_L3
                fprintf(stderr, "dump re file:\n");
                printf("%s:%s\n", enostr, restr);
#endif
                chkrule_t cr;
                cr.eno = atoi(enostr);
                int i = 0;
                if (i = regcomp(&cr.re, restr, REG_EXTENDED|REG_NOSUB)) {
                        char ermsg[256];
                        string ts;
                        ts = "Invalid regular expression: ";
                        regerror(i, &cr.re, ermsg, sizeof ermsg);
                        ts += ermsg;
                        throw invalid_argument(ts.c_str());
                }

                ck->push_back(cr);
        }

        fclose(fck);

}





#ifdef MODULE_TEST


int main(int argc, char *argv[])
{

        flist_t fl;
        ls_dir(&fl, ".", "*.cpp");

        if (fl.size()) {
                for (size_t i=0; i < fl.size(); ++ i) {
                        printf("%s\n", fl[i].c_str());
                }
        }

        log lf("test", "XXX", 1);
        lf.write("this is a test:%d\n", 123456);
        conf_t conf;
        if (read_conf(&conf, "a.conf", "this" ) != &conf) {
                puts("can not read");
                exit(1);
        }



        conf_t::const_iterator itr = conf.begin();

        puts("read:");
        for (;itr != conf.end(); ++itr) {
                printf("%s|%s|\n", itr->first.c_str(), itr->second.c_str());
        }


}

#else

conf_t conf;
log_file *mylog;

set<string> done_file;



/******************************************************************************
* 整个的调用序列如下：
当前文件点：0
每个文件时长：1
当前时间点：1
1 超时
------------------------------
1 写文件尾 （下次超时时间:下一文件点  2）
1 关闭文件   (下次超时时间:下一文件点 2）
1 处理事务  （下次超时时间:下一文件点 2）
1 完成事务   (下次超时时间:下一文件点 2）

1下一个文件点 (下次超时时间:本文件点 2）
1 打开文件       (下次超时时间:本文件点 2）
1 写文件头      (下次超时时间:本文件点 2 ）
1 写文件体


1.5  写文件体

2 超时：
-------------------
2写文件尾 （下次超时时间:下一文件点  3）
2 关闭文件   (下次超时时间:下一文件点 3）
2 处理事务  （下次超时时间:下一文件点 3）
2 完成事务   (下次超时时间:下一文件点 3）

2下一个文件点 (下次超时时间:本文件点3）
2 打开文件       (下次超时时间:本文件点3）
2 写文件头      (下次超时时间:本文件点 3 ）
2 写文件体

2.1 写文件体
2.2写文件体

*******************************************************************************
*/

int main(int argc, char *argv[])
{

        if (argc < 2) {
                fprintf(stderr, "usage: %s cfg\n", argv[0]);
                exit(0);
        }

        read_conf(&conf, argv[1], pro_name);
        try {
                set_conf(conf);

        } catch (exception &e) {
                fprintf(stderr, "%s\n", e.what());
                exit(2);
        }

#ifdef DEBUG_PRINT_L3
        puts(config:: input_dir.c_str());
        puts(config:: output_dir.c_str());
        puts(config:: tmp_dir.c_str());
        puts(config:: err_dir.c_str());
        puts(config:: index_dir.c_str());
        puts(config:: bak_dir.c_str());
        puts(config:: proc_id.c_str());
        puts(config:: run_flag.c_str());
        puts(config:: sleep_time.c_str());
        puts(config:: log_dir.c_str());
        puts(config:: file_pattern.c_str());
#endif
        string logname = config::log_dir + "/" + pro_name;
        mylog = new log_file(logname, "0" + config::proc_id,1 );


        signal(SIGTERM,signal_TERM);






        timer_arg_t timer_arg;

        redo (&timer_arg);

        timer_vector_t timer_vect;




        string msrn_name = config::datapath + "/" +"gpservcode.dat";

        timer_arg.msrn = new datafile(msrn_name.c_str());




        open_out(&timer_arg);
        write_header(&timer_arg);

        do_file(&timer_arg);
        timer_vect.push_back(timer(10, minutes_per_file*60, write_tail));//写文件尾
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);//

        timer_vect.push_back(timer(20, minutes_per_file*60, close_out));//关闭文件
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);


        //完成一个上发文件
        timer_vect.push_back(timer(30, minutes_per_file*60, finish_file));
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);



        timer_vect.push_back(timer(60, minutes_per_file*60, do_trans));//开始事务
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);

        timer_vect.push_back(timer(70, minutes_per_file*60, finish_trans));//完成事务
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);



        //下一个时间点
        timer_vect.push_back(timer(100, minutes_per_file*60, next_count));
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);


        //打开文件
        timer_vect.push_back(timer(110, minutes_per_file*60, open_out));
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);

        //写头记录
        timer_vect.push_back(timer(120, minutes_per_file*60, write_header));
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);



        timer_vect.push_back(timer(130, 0, do_file));//处理输入, 实时处理
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);


        timer_vect.push_back(timer(1000, 0, do_sleep));//没有文件时sleep
        timer_vect[timer_vect.size() - 1].set_stamp(timer_arg.timer_stamp);


        //注意：必须对事务排序以得到正确的执行序列
        //从小到大排列(less<T>)，对应优先级数字
        sort(timer_vect.begin(), timer_vect.end());



        //设定查重关键字长度,使用冲值卡序列号作为关键字





        do_action action;
        action.ta = &timer_arg;

        string stop_file_name = config::tmp_dir
                                +"/"+pro_name + stop_file_suffix;

        while (!need_exit(stop_file_name)) {

                //call the function with priority and time out setting
                //if time out , the function called in priority order,
                //the execute sequence is definite

                //all the function can decide what time they should be called on the next time
                //by set the timer_arg.timer_stamp dynamically
                time_t t = time(0);
                action.curr = t;
                try {
                        for_each(timer_vect.begin(),
                                 timer_vect.end(), action);
                } catch (const exception &e) {
                        mylog->write(e.what());
                        delete mylog;

                        exit(errno);
                }



        }



        return 0;

}



#endif
