#ifndef OLYVC_H_
#define OLYVC_H_


#include <vector>



#include <string>
#include <map>
#include <set>

#include <stdio.h>
#include <signal.h>

#include <stdexcept>

#include <stdlib.h>
#include <algorithm>

#include <sys/types.h>
#include <regex.h>

#include <datafile.h>

#ifdef _USING_NAMESPACE_STD
using namespace std;
#endif

typedef struct chkrule {
        int eno;
        regex_t re;
}chkrule_t;

typedef vector<chkrule_t> chklist_t;


//一个上发文件 所需要的参数
typedef struct timer_arg_t {

        FILE *fout;

        size_t fc;
        size_t feesum;
        string max_date;
        string min_date;

        datafile *msrn;

        chklist_t chk;
        vector<string> redo_cmd; // 事务处理的命令

        time_t file_stamp;             //上次输出文件的时间点
        time_t timer_stamp;       //用来计时调用的时间点
        timer_arg_t() {
                feesum = 0;

                fout = 0;
                fc = 0;
                file_stamp = 0;
                timer_stamp = 0;
        }

} timer_arg_t  ;




typedef map <const string,const string> conf_t; //配置项值: key->value



conf_t *read_conf(conf_t *conf,const char *conf_name,
                  const string &pro_prefix);


char *full_time_str(char *tstr, time_t t);

class log_file
{
public:
        log_file(const string &pre, const string &arg_flag, int arg_day);
        void write(const char *fmt, ...);
        ~log_file() {
                if (fp) {
                        fclose(fp);
                        fp = 0;
                }
        }
private:
        FILE *open(void);

        time_t stamp;           //当前

        string prefix;

        string flag;
        FILE *fp;
        const int seconds_per_log;  //多少天写一个日志文件
} ;







//超时需要调用的函数
//根据优先级就可以决定它们的调用顺序
//超时设置：
//完成一个上发文件：2小时(7200秒):优先级：-1 最高
//处理一个文件：实时(0秒):优先级: 10
//合并索引文件：1天(24*3600):优先级：1000
//事务处理：2小时:优先级：0
//
//
typedef void (*action_t)(timer_arg_t *);

class timer
{

public:
        timer(int pro, int to,  action_t ac ) {
                act = ac;

                m_time_out=to;
                priority = pro;
        }


        bool time_out(time_t  t) {

#ifdef DEBUG_PRINT_L3
                printf("priority:%d,timer:time_out:t=%d: stamp = %d: m_time_out = %d: timeout = %d \n",
                       priority,t, stamp, m_time_out, t - stamp >= m_time_out);

#endif
                return t - stamp >= m_time_out;

        }

        time_t set_stamp(time_t t) {
                return stamp = t;
        }

        bool operator < (const timer& arg) const {
                return this->priority < arg.priority;
        }

        void action(timer_arg_t *arg) {
                act(arg);
        }

private:
        time_t stamp;   //上次的处理时间
        int priority;  //优先级，越小级别越高，负数最高
        int m_time_out;
        action_t act;


};

namespace config
{
extern string input_dir;
extern string output_dir;
extern string tmp_dir;
extern string err_dir;
extern string index_dir;
extern string bak_dir;
extern string proc_id;
extern string run_flag;
extern string sleep_time;
extern string log_dir;
extern string file_pattern;
extern string datapath;
}

typedef vector<timer> timer_vector_t;


typedef vector<string> flist_t;

flist_t * ls_dir(flist_t *fl, const char *dir,
                 const char *pattern, unsigned int n);

extern set<string> done_file;





const size_t minutes_per_file = 30;//多长时间需要输出一个文件
const string pro_name("gpsend");

const size_t index_time_out = 3*30*24*60*60;
const size_t line_max = 1024;
const char conf_op = '=';
const char remark_op = '#';
const string stop_file_suffix(".stop");
const string mv_cmd("mv");
const string rm_cmd("rm");
const string mv_direct("->");

const string pre_redo_name_fmt(pro_name + ".break." + "%s");
const string redo_name_fmt("." + pro_name + ".break." + "%s");
const string redo_name_pattern("." + pro_name + ".break." + "*");

const string out_name_fmt("BSMS%s.371");
const string out_name_pattern("BSMS*.371");

const string pre_index_name_fmt("pre" + pro_name + "%s" +".idx");
const string index_name_fmt(pro_name + ".%s" +".idx");

const string index_name_pattern(pro_name + ".*" +".idx");



extern conf_t conf;
extern log_file *mylog;

void  redo(timer_arg_t *ta);


void finish_trans(timer_arg_t *ta);
void do_trans(timer_arg_t *ta);
void next_count(timer_arg_t *ta);
void last_count(timer_arg_t *ta);

void finish_file(timer_arg_t *ta);
void do_file(timer_arg_t *ta);
void combin_index(timer_arg_t *ta);

void do_mv(const string &cmd);



void write_header(timer_arg_t *ta);

void write_tail(timer_arg_t *ta);
void open_out(timer_arg_t *ta);



void close_out(timer_arg_t *ta);

int file_count(time_t t);
string out_suffix(time_t ta);

const char *trimsp(char *s);

#endif /*OLYVC_H_*/
