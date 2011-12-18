/*
 * 事务记录包括：在作事务时的索引记录，需要发布的文件等。
 * 输入->内存索引-> 事务临时记录==>发布一阶段事务->追 加索引==>发布第二段事务 ->输出文件==>完成事务
 * ==>部分是原子操作，可保证事务性
 * 重作： 如果是第一阶段的事务 ，将事务记录中的索引恢复就可以了
 * 重作：如果是第二阶段的事务，将事务记录中的文件输出就行了
 */
#include <sumlim.h>

#include <signal.h>
#include <do_sum.h>

namespace config
{
string conf_logdir;
string conf_progid;

string conf_inputdir;
string conf_tmpdir;
string conf_outdir;
string conf_errdir;
string conf_idxdir;

string conf_bakdir;
string conf_pattern;

string conf_sleep_time;

string conf_is_backup;
string conf_is_daemon;
string conf_maxmem;

string conf_records_per_node;

string conf_dirpos;
string conf_filepos;
string conf_keypos;
string conf_valuepos;
string conf_checkpos;
string conf_checkkey;
string conf_feelim;


}

#ifdef DEBUG_PRINT_L3
void print_lo(const lo_t &l)
{
        size_t n = 0;
        while (n < l.size()) {
                printf("%d-%d\n", l[n].pos, l[n].len);
                ++n;
        }
}

void print_pk(const pos_info_t *p)
{
        size_t i = 0;
        while (p[i].len) {
                printf("%d:%d:%d\n", p[i].tag_len, p[i].pos, p[i].len);
                ++i;
        }
}
#endif

lo_t mem_layout;

static bool need_terminated;

void signal_TERM(int signalFlag)
{
        signal(SIGTERM, SIG_IGN);
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


const
vector <string> & read_cmd_file(vector <string> *vs, const string &f)
{
        FILE *fp = fopen(f.c_str(), "r");
        char lbuf[line_max + 1];

        if (!fp) {

                sprintf(lbuf, "can not open transaction file:%s:%s\n", f.c_str(),
                        strerror(errno) );
                throw runtime_error(lbuf);
        }

        while (fgets(lbuf, line_max + 1, fp)) {
                size_t len = strlen(lbuf);
                if (lbuf[len -1 ] == '\n') {
                        lbuf[len - 1 ] = 0;
                }
                vs->push_back(lbuf);

        }
        fclose(fp);

        return *vs;
}

void roll_back(vector<string> const &cmd)
{
        size_t i = 0;

        while (i < cmd.size()) {
                do_truncate(cmd[i]);

                ++i;
        }
}



void set_conf(const conf_t &conf)
{

        query_conf(&config::conf_logdir, conf, prog_prefix +".logPath");
        query_conf(&config::conf_inputdir, conf, prog_prefix +".inputPath");
        query_conf(&config::conf_outdir, conf, prog_prefix +".outputPath");
        query_conf(&config::conf_tmpdir, conf, prog_prefix +".tmpPath");
        query_conf(&config::conf_errdir, conf, prog_prefix +".errorPath");
        query_conf(&config::conf_idxdir, conf, prog_prefix +".indexPath");
        query_conf(&config::conf_bakdir, conf, prog_prefix +".bakPath");
        query_conf(&config::conf_pattern, conf, prog_prefix +".filePattern");

        query_conf(&config::conf_dirpos, conf, prog_prefix +".dirPos");
        query_conf(&config::conf_filepos, conf, prog_prefix +".filePos");
        query_conf(&config::conf_keypos, conf, prog_prefix +".keyPos");
        query_conf(&config::conf_valuepos, conf, prog_prefix +".valuePos");
        query_conf(&config::conf_checkpos, conf, prog_prefix +".checkPos");
        query_conf(&config::conf_checkkey, conf, prog_prefix +".checkKey");
        query_conf(&config::conf_feelim, conf, prog_prefix +".feeLimit");

        query_conf(&config::conf_is_backup, conf, prog_prefix +".backup");
//	query_conf(&config::conf_is_daemon, conf, prog_prefix +".daemon");
        query_conf(&config::conf_progid, conf, prog_prefix +".progID");
        query_conf(&config::conf_sleep_time, conf, prog_prefix +".sleepTime");
        query_conf(&config::conf_maxmem, conf, prog_prefix +".maxmem");
        query_conf(&config::conf_records_per_node, conf, prog_prefix +".recordsPerNode");

#ifdef DEBUG_PRINT_L3
        printf("dirPos=%s\n", config::conf_dirpos.c_str());
        printf("filePos=%s\n", config::conf_filepos.c_str());
        printf("keyPos=%s\n", config::conf_keypos.c_str());
        printf("valuePos=%s\n", config::conf_valuepos.c_str());
        printf("conf_checkpos=%s\n", config::conf_checkpos.c_str());
        printf("conf_checkkey=%s\n", config::conf_checkkey.c_str());
        printf("conf_feelim=%s\n", config::conf_feelim.c_str());
        puts(">-=end of conf dump=-<");
#endif
}

void init_conf(const char *argv)
{
        using namespace config;
        conf_t conf;
        read_conf(&conf, argv);
        set_conf(conf);

        memset(pdir_list, 0, sizeof(pos_info_t)*pos_key_max);
        memset(pfile_list, 0, sizeof(pos_info_t)*pos_key_max);
        memset(pkey_list, 0, sizeof(pos_info_t)*pos_key_max);
        memset(pvalue_list, 0, sizeof(pos_info_t)*pos_key_max);
        memset(pcheckpos_list, 0, sizeof(pos_info_t)*pos_key_max);

        lo_t l;
        parse_layout(&l, conf_dirpos);
        lo_to_pkey(pdir_list, l);
#ifdef DEBUG_PRINT_L3
        print_lo(l);
        print_pk(pdir_list);
#endif
        l.clear();

        parse_layout(&l, conf_filepos);
        lo_to_pkey(pfile_list, l);
#ifdef DEBUG_PRINT_L3
        print_lo(l);
        print_pk(pfile_list);
#endif
        l.clear();

        parse_layout(&l, conf_keypos);
        lo_to_pkey(pkey_list, l);
#ifdef DEBUG_PRINT_L3
        print_lo(l);
        print_pk(pkey_list);
#endif

        int n = 0;
        while (n < pos_key_max) {
                if (pkey_list[n].len && pkey_list[n+1].len) {

                } else {
                        break;
                }

                n++;
        }
        layout _mem_layout;
        _mem_layout.pos = 0;
        _mem_layout.len =pkey_list[n].tag_len + pkey_list[n].len + 1;

#ifdef DEBUG_PRINT_L3
        printf("!!!memlayout:%d\n", _mem_layout.len);
#endif

        mem_layout.push_back(_mem_layout);
        _mem_layout.pos = pkey_list[n].tag_len + pkey_list[n].len + 1;
        _mem_layout.len =sizeof(data_t); //using long long type
        mem_layout.push_back(_mem_layout);

        l.clear();

        parse_layout(&l, conf_valuepos);
        lo_to_pkey(pvalue_list, l);
#ifdef DEBUG_PRINT_L3
        print_lo(l);
        print_pk(pvalue_list);
#endif
        l.clear();

        parse_layout(&l, conf_checkpos);
        lo_to_pkey(pcheckpos_list, l);
#ifdef DEBUG_PRINT_L3
        print_lo(l);
        print_pk(pcheckpos_list);
#endif
        l.clear();

#ifdef DEBUG_PRINT_L3
        char pstr__ []= "123|1238576";
        char sstr__[124] = {0};
        char dstr__[124] = {0};
        idx_to_pkey(dstr__, pstr__);
        puts(pstr__);
        printf("%s|%lld", dstr__,*reinterpret_cast<data_t*>( dstr__ + mem_layout[1].pos));
        pkey_to_idx(sstr__, dstr__);

        puts(sstr__);

#endif

        feelimit = atol(conf_feelim.c_str());

}

log_file *mylog;

int main(int argc, char *argv[])
{

        if (argc != 2) {
                fprintf(stderr, "usage:%s config\n", argv[0]);
                exit(1);
        }


        try {

                init_conf(argv[1]);
        } catch (const exception &e) {
                fprintf(stderr, "%s", e.what());
                exit(1);
        }





        signal(SIGTERM, signal_TERM);

        mylog = 0;
        try {
                mylog = new log_file(config::conf_logdir +"/" + prog_prefix, config::conf_progid, 1 );
        } catch ( exception &e) {
                fprintf(stderr, "can not open log:%s", e.what());
                exit(1);
        }

        //查找 第一段事 务记录是否存在
        string trans_log_pattren_first = trans_log_prefix + trans_suffix_first;
        string trans_log_pattren_second = trans_log_prefix + trans_suffix_second;
        try {

                string trans_log_name = config::conf_logdir + "/" + trans_log_pattren_first;

                if (access(trans_log_name.c_str(), F_OK) == 0) {
#ifdef DEBUG_PRINT_L1
                        fprintf(stderr, "found : transaction file first\n");

#endif
                        //the first process transaction exist , we need truncate the index that effected by writing index
                        vector<string> p1;

                        read_cmd_file(&p1, trans_log_name);
                        roll_back(p1);
                        string rcmd = rm_cmd;
                        rcmd += cmd_separator;
                        rcmd += trans_log_name;
                        do_rm(rcmd);
                } else {
                        //the second process trasnaction exist , we need redo the move and rm for this transaction
                        trans_log_name = config::conf_logdir + "/" + trans_log_pattren_second;
                        if (access(trans_log_name.c_str(), F_OK) == 0) {
#ifdef DEBUG_PRINT_L1
                                fprintf(stderr, "found : transaction file: second\n");
#endif

                                vector<string> p2;

                                read_cmd_file(&p2, trans_log_name);
                                redo(p2);
                                if (access(trans_log_name.c_str(), F_OK) == 0) {
                                        string rcmd = rm_cmd;
                                        rcmd += cmd_separator;
                                        rcmd += trans_log_name;
                                        do_rm(rcmd);
                                }
                        }
                }
        } catch (exception &e) {
                mylog->write("error detected:%s\n", e.what());
                exit(1);
        }

        string trans_log_name_first = config::conf_logdir + "/"
                                      + trans_log_pattren_first;
        string trans_log_name_second = config::conf_logdir + "/"
                                       + trans_log_pattren_second;

        string stop_file = config::conf_tmpdir + "/" + prog_prefix + ".stop";



        try {
                idx_map_t idx_map;

                while (!need_exit(stop_file)) {
                        flist_t fl;
                        ls_dir(&fl, config::conf_inputdir.c_str(), config::conf_pattern.c_str());

                        trans_info_t trans_log;
                        for (int i = 0; i < fl.size(); ++i) {
                                do_weed(&idx_map, &trans_log, fl[i]); //do weed up operation
                        }


                        //write the transaction file log before we write the index
                        write_trans_file(trans_log_name_first, trans_log.trans_cmd);

                        //append the index from the file
                        map<string, vector<string> >::iterator itr;
                        for (itr = trans_log.idx_map.begin(); itr !=  trans_log.idx_map.end() ;++itr) {
                                if (itr->second.size()) {
#ifdef DEBUG_PRINT_L1
                                        printf("do append %s:\n", itr->first.c_str());
#endif
                                        string idx_file_name = config::conf_idxdir + "/" + itr->first;
                                        append_idx(idx_file_name, itr->second);
                                }
                        }
#ifdef DEBUG_PRINT_L1
                        puts("end of firstly transaction process");
#endif

                        //finish the firstly transaction :
                        //entering
                        if ( rename(trans_log_name_first.c_str(),trans_log_name_second.c_str() ) < 0) {
                                throw runtime_error("can not do the secondary transaction");
                        }

                        //the secondary transaction is move file or remove file
                        size_t cc =0;
                        while (cc < trans_log.trans_cmd.size()) {
                                do_mv(trans_log.trans_cmd[cc]);
                                do_rm(trans_log.trans_cmd[cc]);
                                ++cc;
                        }

                        //clear the transaction log cmd since I have finished it
                        trans_log.trans_cmd.clear();
                        trans_log.idx_map.clear();

                        //remove the secondary transaction log file
                        string rm_trans_cmd = rm_cmd + cmd_separator;
                        rm_trans_cmd += trans_log_name_second;
                        do_rm(rm_trans_cmd);

//			need_terminated = true;
                        if (fl.size() == 0) {
//				need_terminated = true;
                                sleep(atoi(config::conf_sleep_time.c_str()));
                        }

                }
        } catch (exception &e) {
                mylog->write("error detected:%s\n", e.what());
                delete mylog;
                exit(1);
        }

        delete mylog;
        return 0;
}


