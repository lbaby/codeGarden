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

        time_t stamp;           //��ǰ

        string prefix;

        string flag;
        FILE *fp;
        const int seconds_per_log;  //������дһ����־�ļ�
} ;


#endif /*LOG_FILE_H_*/
