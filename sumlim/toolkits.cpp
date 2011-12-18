#include <toolkits.h>
#include <stdio.h>



size_t findchr(const char *s, char c, size_t pos)
{
        size_t l = 0;
        while (*(s+pos +l)) {
                if (*(s + pos +l) == c) {
                        break;
                }
                ++l;
        }

        return pos +l;

}




//add to every layout's end a '\0'
const char *do_layout(char *s, const lo_t &l)
{
        for (size_t i = 0; i < l.size(); i++) {
                *(s + l[i].pos + l[i].len -1 ) = '\0';
        }
        return s;
}



const lo_t & decide_layout(lo_t &l,
                           const char *str,
                           const char separator='|')
{
        size_t len = strlen(str);
        layout lo;
        size_t pos = 0;

        do {

                lo.pos = pos;
                size_t np =findchr(str,separator, pos);
                lo.len = np -pos  +1 ;
                pos = np + 1;
                l.push_back(lo);
        } while (pos < len);

        if (len == pos) {
                lo.pos = pos;
                lo.len = pos -len +1 ;
                l.push_back(lo);
        }


        return l;

}

//trim the spaces on the right end of str;
const char *trimsp(char *s)
{
        char *nsp =NULL;
        char *rs =s;
        while (*s ) {
                if (isspace(*s)) {
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




//rename a file
//syntax:
//mv:old_name:new_name
void do_mv(const string &cmd)
{

        if (cmd.substr(0, mv_cmd.length()) == mv_cmd) {
#ifdef DEBUG_PRINT_L3
                puts("do mv");
#endif
                lo_t l;
                decide_layout(l, cmd.c_str(), cmd_separator);
                const string & src = cmd.substr( l[1].pos , l[1].len -1);
                const string & dst = cmd.substr(l[2].pos);
                int n = rename(src.c_str(), dst.c_str());
                //return errno;
#ifdef DEBUG_PRINT_L3
                printf("mv:%s:%s\n", src.c_str(), dst.c_str() );
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


//first rename from old name to random one
//second: remove the second one
//syntax:
//rm:filename
void do_rm(const string &cmd)
{


        if (cmd.substr(0, rm_cmd.length()) == rm_cmd) {
#ifdef DEBUG_PRINT_L3
                printf("do_rm:%s\n", cmd.c_str());
#endif
                lo_t l;
                decide_layout(l, cmd.c_str(), cmd_separator);
                string fname = cmd.substr(l[1].pos);

//                char rand_suffix[128];
//                srand(time(0));
//                sprintf(rand_suffix, ".%d", rand());
//
//                string rname = fname;
//                rname += rand_suffix;
//
//#ifdef DEBUG_PRINT_L3
//                printf("rm:%s\n", fname.c_str());
//#endif
//                if (rename(fname.c_str(), rname.c_str()) < 0) {
//
//                        string msg = fname;
//                        msg += ":can not rename before delete:";
//                        msg += strerror(errno);
//                        throw runtime_error(msg);
//                }
//
//
//                int n = unlink(rname.c_str());
                int n = unlink(fname.c_str());
                //return errno;

                if (n < 0) {
                        string msg = cmd.substr(l[1].pos);
                        msg += ":can not remove:";
                        msg += strerror(errno);
                        throw runtime_error(msg);
                }
        }

}

//syntax :
//truncate:file:100

void do_truncate(const string &cmd)
{

#ifdef DEBUG_PRINT_L3
        printf("do_truncate:%s\n", cmd.c_str());
#endif
        if (cmd.substr(0, truncate_cmd.length()) == truncate_cmd) {
                lo_t l;
                decide_layout(l, cmd.c_str(), cmd_separator);
                string fname = cmd.substr(l[1].pos,  l[1].len -1);
                string pos = cmd.substr(l[2].pos);
                size_t p = atol(pos.c_str());
#ifdef DEBUG_PRINT_L3
                printf("%s:%s", fname.c_str(), pos.c_str());
#endif
                if (truncate(fname.c_str(), p) < 0) {
                        string msg = fname;
                        msg += "can not truncate: ";
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



void redo(vector<string> const &cmd)
{

        size_t i = 0;

        while (i < cmd.size()) {



                try {
                        do_mv(cmd[i]);
                } catch (exception &e) {
#ifdef DEBUG_PRINT_L3
                        printf("%s:not found:%s\n", cmd[i].c_str(), e.what() );
#endif

                }
                try {
                        do_rm(cmd[i]);
                } catch (exception &e) {
#ifdef DEBUG_PRINT_L3
                        printf("%s:not found:%s\n", cmd[i].c_str(), e.what() );
#endif

                }

                ++i;

        }

}



void write_trans_file(const string &f, const vector<string> &cv)
{
        string::size_type p = f.rfind('/');

        string tmp_name("./") ;
        if (p != string::npos ) {
                tmp_name= f.substr(0, p);  // path name with slash(/)
        }
        tmp_name += "tran_tmp_file.";

        char buf[64];
        srand(time(0));
        sprintf(buf, "%d", rand());

        tmp_name += buf;

        FILE *fptmp = fopen(tmp_name.c_str(), "w");

        if (!fptmp) {
                string msg = "write_trans_file:can not open tmp file:";
                msg += tmp_name;
                msg += " : ";
                msg += strerror(errno);
                throw runtime_error(msg);
        }

        size_t i = 0;
        while ( i < cv.size()) {
                fputs( cv[i].c_str(), fptmp);
                fputc( '\n', fptmp);
                ++i;
        }


        fclose(fptmp);


        if ( rename(tmp_name.c_str(), f.c_str() )  < 0) {
                string msg = "write_trans_file:rename tmp file:";
                msg += tmp_name;
                msg += " : ";
                msg += strerror(errno);
                throw runtime_error(msg);
        }



}




conf_t *read_conf(conf_t *conf,const char *conf_name)
{
        FILE *fp = fopen(conf_name, "r");
        if (!fp) {
                string ermsg ("can not open file :");
                ermsg += conf_name;
                ermsg += " ";
                ermsg += strerror(errno);
                throw invalid_argument(ermsg);
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


flist_t *ls_dir(flist_t *fl, const char *path, const char *pattern,
                unsigned int max_file)
{
        DIR *dir = opendir(path);
        if (!dir) {
                string msg("ls_dir:can not open  dir:");
                msg += path;
                msg += ":";
                msg += strerror(errno);
                throw invalid_argument(msg);
        }

        dirent *de;

        fl->clear();

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

                        string msg("ls_dir:can not stat:");
                        msg += name;
                        msg += ":";
                        msg += strerror(errno);
                        throw invalid_argument(msg);
                }

                if (S_ISREG(fstatus.st_mode) ) {//是一个普通文件 ，添加到文件列表
                        fl->push_back(de->d_name);
                        ++i;
                }//if S_ISREG


        }// while readdir
        closedir(dir);

        return fl;
}


//parse the layout information
//format is1-3|4-5|6-7|9-11

lo_t *parse_layout(lo_t *l, const string &s)
{

        string::size_type p = 0;
        string::size_type tp = 0;

        do {
                //find a '-' in string
                tp = s.find(ft_sep, p);
                if (tp == string::npos) {//there must 1 '-' in string at least
                        string msg="Invalid argument:";
                        msg += s;
                        throw invalid_argument(msg);
                }
                //extract 'A' from A-B|C-D
                string from = s.substr(p, tp-p );
#ifdef DEBUG_PRINT_L3
                printf("from:%d->%d=%s\n", p, tp, from.c_str());
#endif
                string to;
                p = tp+1;

                //find | in A-B|C-D from 'B'
                //and extract B from A-B|C-D  , B is between -B|
                tp = s.find(lo_sep, p);
                if (tp == string::npos) {
                        to = s.substr(p);
                } else {
                        to = s.substr(p, tp-p );
                }
#ifdef DEBUG_PRINT_L3
                printf("from:%d->%d=%s\n", p, tp, to.c_str());
                printf("%s-%s\n", from.c_str(), to.c_str());
#endif
                //next section
                p = tp +1;
                if (atoi(from.c_str()) > atoi(to.c_str() )) {
                        string msg="Invalid argument:";
                        msg += from;
                        msg += "-";
                        msg += to;
                        msg += "from position must smaller than  to position ";
                        throw invalid_argument(msg);
                }
                layout_t lay;
                lay.pos = atoi(from.c_str()) -1;
                lay.len = atoi(to.c_str()) - atoi(from.c_str()) + 1;


                l->push_back(lay);

        } while (tp != string::npos);

        return l;

}


pos_info_t *lo_to_pkey(pos_info_t *pkey, lo_t const &l )
{
        size_t pos = 0;
        size_t n = 0;
        while (n < l.size()) {
                pkey[n].pos = l[n].pos;
                pkey[n].len = l[n].len;
                pkey[n].tag_len = pos;
                pos += l[n].len;
                ++n;
        }
        return pkey;
}
