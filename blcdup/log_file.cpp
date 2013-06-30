#include <log_file.h>
#include <toolkits.h>

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
                fprintf(stderr, "%s:can not open in a+ mode : %s\n",
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


        full_time_str(buf, time(0));
        fputs(buf, fp);
        fputc(',', fp);

        va_list args;
        va_start(args,fmt);
        vfprintf(fp, fmt,args);
        va_end(args);
        fflush(fp);
}

