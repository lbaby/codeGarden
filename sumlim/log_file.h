#ifndef LOG_FILE_H_
#define LOG_FILE_H_

#include <stl_conf.h>

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>

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


#endif /*LOG_FILE_H_*/
