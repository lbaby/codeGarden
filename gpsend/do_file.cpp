#include <errno.h>
#include <string.h>


#include <gpsend.h>

#include <gp.h>

#include <unistd.h>

#include <datafile.h>


//trim the spaces on the right end of str;
const char *trimsp(char *s)
{
        char *nsp =NULL;
        char *rs =s;
        const char sp=' ';
        while (*s ) {
                if (*s == sp) {
                        if (!nsp) {
                                nsp = s;
                        }
                } else {
                        nsp = NULL;
                }
                ++s;
        }

        if (nsp) {
                *nsp= '\0';
        }

        return rs;
}



void do_mv(const string &cmd)
{


        if (cmd.substr(0, mv_cmd.length()) == mv_cmd) {
#ifdef DEBUG_PRINT_L3
                puts("do mv");
#endif
                string::size_type stsrc  = cmd.find(mv_cmd) + mv_cmd.length() + 1;
                string::size_type stdst = cmd.substr(stsrc).find(mv_direct) + mv_cmd.length() + 1+ 2;
                string::size_type  srclen = stdst - stsrc - 2   ;
                const string & src = cmd.substr(stsrc, srclen);
                const string & dst = cmd.substr(stdst);
                int n = rename(src.c_str(), dst.c_str());
                //return errno;
#ifdef DEBUG_PRINT_L3
                printf("mv:%s->%s\n", src.c_str(), dst.c_str() );
#endif
                if (n < 0) {

                        string msg = "can not rename :";
                        msg += src;
                        msg += " to ";
                        msg += dst;
                        msg += ":";
                        msg += strerror(errno);
                        throw runtime_error(msg);
                }
        }
}

void do_rm(const string &cmd)
{

        if (cmd.substr(0, rm_cmd.length()) == rm_cmd) {
                int n = unlink(cmd.substr( cmd.find(' ') + 1).c_str());
                //return errno;
#ifdef DEBUG_PRINT_L3
                printf("rm->%s\n", cmd.substr( cmd.find(' ') + 1).c_str() );
#endif
                if (n < 0) {
                        string msg = cmd.substr( cmd.find(' ') + 1);
                        msg += ":can not remove:";
                        msg += strerror(errno);
                        throw runtime_error(msg);
                }
        }

}

time_t str_to_sec(const string & tstr)
{

        time_t cur = time(0);
        struct tm *t = localtime(&cur);

        t->tm_year  = atoi(tstr.substr(0, 4).c_str()) - 1900;
        t->tm_mon  = atoi(tstr.substr(4, 2).c_str())  - 1;
        t->tm_mday = atoi(tstr.substr(6, 2).c_str()) ;
        t->tm_hour = atoi(tstr.substr(8, 2).c_str()) ;
        t->tm_min  = atoi(tstr.substr(10, 2).c_str()) ;
        t->tm_sec  = atoi(tstr.substr(12, 2).c_str()) ;
        return mktime(t);

}




void redo(timer_arg_t *ta)
{
#ifdef DEBUG_PRINT_L3
        printf("redo on %d\n", ta->file_stamp);
#endif

        flist_t rf;
        if (!ls_dir(&rf, config::tmp_dir.c_str(), redo_name_pattern.c_str(),2)) {
                mylog->write("can not redo:%s\n", strerror(errno));
                exit(3);
        }

        if (rf.size()) {


                string fname = config::tmp_dir + "/" + rf[0];
                FILE *fp = fopen(fname.c_str(), "r");
                if (!fp) {
                        mylog->write("redo:%s:can not read:%s\n", fname.c_str(), strerror(errno));
                        exit(4);

                }

                char line_buf[line_max];
                while (fgets(line_buf, line_max, fp)) {
                        size_t len = strlen(line_buf);
                        if (line_buf[len -1] == '\n') {
                                line_buf[len -1] = 0;
                        }

                        ta->redo_cmd.push_back(line_buf);
                }
                fclose(fp);

                vector<string>::iterator itr = ta->redo_cmd.begin();
                while (itr != ta->redo_cmd.end()) {
                        try {
                                do_mv(*itr);
                        } catch (...) {

                        }
                        ++itr;
                }


                itr = ta->redo_cmd.begin();
                while (itr != ta->redo_cmd.end()) {
                        try {
                                do_rm(*itr);
                        } catch (...) {

                        }
                        ++itr;
                }
                ta->redo_cmd.clear();

                //FIX: 一个不能完全保证事务处理的BUG
                rf.clear();
                if (!ls_dir(&rf, config::tmp_dir.c_str(), redo_name_pattern.c_str(),2)) {
                        mylog->write("can not redo:%s\n", strerror(errno));
                        exit(3);
                }

                //注意，事务记录文件名也会被更改
                string base_tim =
                        rf[0].substr(redo_name_pattern.length() -1 , 8 );
                const string &fno = rf[0].substr(redo_name_pattern.length() -1+8 );
                base_tim += "000000"; //HHMISS
                //ta ->file_stamp =  str_to_sec(base_tim);
#ifdef DEBUG_PRINT_L3

                char time_buf[16];
                full_time_str(time_buf, ta ->file_stamp);

                printf("stamp is:%s\n ",time_buf );
#endif
                ta ->file_stamp =  str_to_sec(base_tim) +
                                   atoi(fno.c_str())*minutes_per_file*60  ;


#ifdef DEBUG_PRINT_L3
                printf("redo %s:%s\n", base_tim.c_str(), fno.c_str());

                full_time_str(time_buf, ta ->file_stamp);

                printf("stamp is:%s\n ",time_buf );
#endif

        } else {
                time_t t = time(0);
                ta->file_stamp = t - t % (minutes_per_file*60) ;

                //从当前事务开始

                last_count(ta);

                finish_trans(ta);

                next_count(ta);

        }

        ta->timer_stamp = ta->file_stamp;

#ifdef DEBUG_PRINT_L3
        printf("redo ok %d\n", ta->file_stamp);
#endif

}





static bool is_out_of_date(const string &f)
{
        time_t t = time(0);
        //index format:
        // pro_name
        string st = f.substr(pro_name.length()+1, 14);
        time_t ft  = str_to_sec(st);

        return ft - t > index_time_out;
}







void finish_file(timer_arg_t *ta)
{
#ifdef DEBUG_PRINT_L3
        printf("finish file on %d\n", ta->file_stamp);
#endif

        string sfx = out_suffix(ta->file_stamp );
        char obuf[64];
        sprintf(obuf, out_name_fmt.c_str(), sfx.c_str());
        string oname = obuf;



        string ft = config::tmp_dir + "/"+ oname;
        string fo = config::output_dir + "/"+ oname;

        string fcmd = mv_cmd + " "+ ft + mv_direct + fo;
        ta->redo_cmd.push_back(fcmd);

#ifdef DEBUG_PRINT_L3
        printf("done file on %d :%s\n", ta->file_stamp, fcmd.c_str());
#endif


        //can not be called until next file finished
        ta->timer_stamp = ta->file_stamp + minutes_per_file*60;


}

void next_count(timer_arg_t *ta)
{
#ifdef DEBUG_PRINT_L3
        printf("next file on %d\n", ta->file_stamp);
#endif


        ta->file_stamp +=  minutes_per_file*60 ;

        ta->timer_stamp = ta->file_stamp ;
}

void last_count(timer_arg_t *ta)
{
#ifdef DEBUG_PRINT_L3
        printf("next file on %d\n", ta->file_stamp);
#endif



        ta->file_stamp -=  minutes_per_file*60 ;

}






void truncate_file(const string &f)
{
        char tmp[128] ;
        srandom(time(0));
        long r = random();
        sprintf(tmp, ".%ld", r);
        string nn = f + tmp;

        FILE *fp =  fopen(nn.c_str(), "w");
        if (!fp) {
                string msg ("truncate:") ;
                msg += f ;
                msg += " can not write:" ;
                msg += strerror(errno);
                throw runtime_error(msg);
        }

        fclose(fp);

        if (rename(nn.c_str(), f.c_str()) < 0) {
                string msg ("truncate:") ;
                msg += f ;
                msg += " can not rename:" ;
                msg += strerror(errno);
                throw runtime_error(msg);
        }


}

void do_trans(timer_arg_t *ta)
{
#ifdef DEBUG_PRINT_L3
        printf("do trans on %d\n", ta->file_stamp);
#endif


        char buf[256 ] ;


        sprintf(buf, redo_name_fmt.c_str(), out_suffix(ta->file_stamp ).c_str());
        string fo = config::tmp_dir +"/"+ buf;

        string fpre = config::tmp_dir +"/" + "predo" + buf;

        FILE *fp = fopen(fpre.c_str(), "w");

        string msg;
        if (!fp) {
                msg = fpre;
                msg += ": can not write:";
                msg += strerror(errno);
                throw runtime_error(msg);
        }


        //下一个文件

        sprintf(buf, redo_name_fmt.c_str(),
                out_suffix(ta->file_stamp +minutes_per_file *60 ).c_str());

        string next_trans_file = config::tmp_dir +"/"+ buf;


        string tran_cmd = "mv " + fo + "->" +  next_trans_file;
        ta->redo_cmd.push_back(tran_cmd);


        vector<string>::const_iterator itr= ta->redo_cmd.begin();
        while (itr != ta->redo_cmd.end()) {
                fprintf(fp, "%s\n" ,itr->c_str());
                ++ itr;
        }
        fclose(fp);
        tran_cmd = "mv " + fpre + "->" +  fo;
        do_mv(tran_cmd);

        //clear all the input filename that have done
        done_file.clear();
#ifdef DEBUG_BREAK
        exit(0);
#endif

        for_each(ta->redo_cmd.begin(),
                 ta->redo_cmd.end(),
                 do_mv);

        for_each(ta->redo_cmd.begin(),
                 ta->redo_cmd.end(),
                 do_rm);

        //we have done one transaction , the redo command is now
        ta->redo_cmd.clear();


        ta->timer_stamp = ta->file_stamp  + minutes_per_file*60;

}



void finish_trans(timer_arg_t *ta)
{
#ifdef DEBUG_PRINT_L3
        printf("finish trans on %d\n", ta->file_stamp);
#endif


        char buf[256 ] ;

        sprintf(buf, redo_name_fmt.c_str(),
                out_suffix(ta->file_stamp+minutes_per_file *60  ).c_str());
        string fo = config::tmp_dir +"/"+ buf;

        truncate_file(fo);

        ta->timer_stamp = ta->file_stamp  + minutes_per_file*60;
}



int do_check(const char *line, chklist_t const &ck )
{

        for (size_t n = 0; n < ck.size(); ++ n) {
                if (!regexec(&ck[n].re, line, (size_t) 0, NULL, 0)) {
                        return ck[n].eno;
                }
        }

        return 0;

}


void do_file(timer_arg_t *ta)
{
#ifdef DEBUG_PRINT_L3
        printf("do file on %d\n", ta->file_stamp);
#endif

        char line_buf[line_max] ;
        char ck_buf[line_max];

        //check rule for msrn.dat and h01234.dat
        //

        compara msrn_cmp = { 0, &what_operation((char*)"eq") };
        compara msrn_cmp1 = { 1, &what_operation((char*)"ge") };
        compara msrn_cmp2 = { 2, &what_operation((char*)"lt") };

        vector<compara> cr_msrn;
        cr_msrn.push_back(msrn_cmp);
        cr_msrn.push_back(msrn_cmp1);
        cr_msrn.push_back(msrn_cmp2);


        char msrn_buf[128];

        find_visitor<char> fv_msrn(msrn_buf, ta->msrn->get_layout(), cr_msrn);


        const lo_t &l = ta->msrn->get_layout();






        flist_t fl;
        if (!ls_dir(&fl, config::input_dir.c_str(), config::file_pattern.c_str(), -1 ) ) {
                string msg;
                msg = config::input_dir ;
                msg += ": can not list :";
                msg += strerror(errno);
                throw msg;
        }



        for (size_t i = 0 ;i  < fl.size(); ++ i) {
                if (done_file.find(fl[i]) != done_file.end()) {
                        continue;
                }
                done_file.insert(fl[i]);
                //已处理文件列表
                string fname = config::input_dir + "/" + fl[i];


                FILE *fp = fopen(fname.c_str(), "r");
                if (!fp) {
                        string msg;
                        msg = fname ;
                        msg += ": can not read :";
                        msg += strerror(errno);
                        throw msg;
                }

                string cmd = mv_cmd;
                cmd += " ";
                cmd += fname;
                cmd += mv_direct;
                cmd += config::bak_dir + "/" + fl[i];

                ta->redo_cmd.push_back(cmd);

                string ferr= config::tmp_dir + "/" + fl[i] + ".err";
                FILE *fperr = fopen(ferr.c_str(), "w");
                if (!fperr) {
                        string msg;
                        msg =  ferr ;
                        msg += ": can not write :";
                        msg += strerror(errno);
                        throw msg;
                }


                size_t line_total = 0;
                size_t line_ok = 0;
                size_t line_err = 0;

                string max_date ;
                while ( fgets(line_buf, line_max, fp) ) {
                        char ob[1024] ;

                        if (strncmp(line_buf + offsetof(ismgraw_t, cdr_type), "01", sizeof("01")-1 )) {//only SMT are needed
                                continue;
                        }
                        ismgraw_t i_t;
                        char serv_code[sizeof(i_t.serv_code) + 1] = {0};
                        char db[16] = {0};

                        memcpy(serv_code, line_buf + offsetof(ismgraw_t, serv_code),sizeof(i_t.serv_code) );
                        memcpy(db, line_buf + offsetof(ismgraw_t, apply_t),sizeof(i_t.apply_t) );

                        trimsp(serv_code);
                        trimsp(db);
                        strcpy(msrn_buf + l[0].pos, serv_code);
                        strcpy(msrn_buf + l[1].pos, db);
                        strcpy(msrn_buf + l[2].pos, db);
                        fv_msrn.reset();
                        ta->msrn->find(msrn_buf).accept(fv_msrn);


                        if (!fv_msrn.done()) {//servcode not no config
                                continue;
                        }
                        ++ line_total;
                        gp_fmt(ob, line_buf);



                        fputs(ob, ta->fout);

                        line_ok++;
                        ++ta->fc;
                }

                mylog->write("ProcInfo,%s,%d,%d,%d\n",
                             fl[i].c_str(),
                             line_total,
                             line_ok,
                             line_err);
                if (line_err) {
                        cmd = mv_cmd;
                        cmd += " ";
                        cmd += ferr;
                        cmd += mv_direct;
                        cmd += config::err_dir + "/" + fl[i] + ".err";
                        ta->redo_cmd.push_back(cmd);
                } else {
                        cmd = rm_cmd;
                        cmd += " ";
                        cmd += ferr;
                        ta->redo_cmd.push_back(cmd);
                }


                line_total = 0;
                line_ok = 0;
                line_err = 0;

                fclose(fp);
                fclose(fperr);





        }

        //根据文件号调用
        ta->timer_stamp = ta->file_stamp;
}


void open_out(timer_arg_t *ta)
{

        ta->msrn->load();

        if (ta->fout) {
                fprintf(stderr, "WARNING:reopen \n");
        }

        string sfx = out_suffix(ta->file_stamp);
        char obuf[64] ;
        sprintf(obuf, out_name_fmt.c_str(), sfx.c_str());
        string oname = obuf;

        string ft = config::tmp_dir + "/"+ oname;


        ta->fout = fopen(ft.c_str(), "w");

        if (!ta->fout) {
                string msg;
                msg = ft + ":can not open:" ;
                msg += strerror(errno);
                throw runtime_error(msg);
        }

        ta->max_date = "";
        ta->min_date = "";
        ta->feesum = 0;
        ta->fc = 0;

        //根据文件号调用
        ta->timer_stamp = ta->file_stamp  ;
}






void close_out(timer_arg_t *ta)
{
        if (ta->fout) {
                fclose(ta->fout);
                ta->fout = 0;
                ta->fc = 0;
        }

        ta->timer_stamp = ta->file_stamp  + minutes_per_file*60;
}


void write_header(timer_arg_t *ta)
{
        char tbuf[16] ;
        full_time_str(tbuf, ta->file_stamp);
        fprintf(ta->fout,
                "10"
                "%-10.10s"
                "%-8.8s"
                "%-10.10s"
                "%03d"
                "%-20.20s"
                "%-14.14s"
                "01"
                "%-126.126s"
                "\r\n",
                "46000371",
                "",
                "46000000",
                file_count( ta->file_stamp ),
                "",
                tbuf,
                "");
#ifdef DEBUG_PRINT_L3
        printf("open out  on %ld\n", file_count( ta->file_stamp ) );
#endif

        //本次文件超时调用
        ta->timer_stamp = ta->file_stamp  ;
}

void write_tail(timer_arg_t *ta)
{

        char tbuf[16] ;
        full_time_str(tbuf, ta->file_stamp);
        fprintf(ta->fout,
                "90"
                "%-10.10s"

                "%-8.8s"
                "%-10.10s"

                "%03d"
                "%09d"
                "%-153.153s"
                "\r\n",
                "46000000",
                "",
                "46000371",

                file_count( ta->file_stamp ),
                ta->fc,

                "");

        //下次文件超时调用
        ta->timer_stamp = ta->file_stamp  + minutes_per_file*60;

}


//YYYYMMDDHHMISS
int file_count(time_t t)
{

        t -= timezone;
        const int files_per_day = 24*60/minutes_per_file
                                  + (24*60)%minutes_per_file ;

        size_t fn =  ( t % (files_per_day*minutes_per_file*60) )
                     / (minutes_per_file *60)  + 1;

        return ( fn + files_per_day -1 ) % files_per_day;
}


string out_suffix(time_t file_stamp)
{

        char tbuf[16] = {0};

        full_time_str(tbuf,file_stamp);
        tbuf[8] = 0;
        string sfx = tbuf ;

        sprintf(tbuf, "%03d", file_count(file_stamp));

        sfx += tbuf;
        return sfx;
}

void copy_file(const char *from, const char *to)
{

}

