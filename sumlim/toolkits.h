#ifndef TOOLKITS_H_
#define TOOLKITS_H_


#include <stl_conf.h>

#include <errno.h>
#include <dirent.h>
#include <fnmatch.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define extract_key(d, s, p)\
	do{\
		int _i_n = 0;\
		while((p)[_i_n].len) {\
			memcpy( (d)+ (p)[_i_n].tag_len, (s) + (p)[_i_n].pos, (p)[_i_n].len );\
			++ _i_n;\
		}\
		 *((d)+ (p)[_i_n - 1].tag_len + (p)[_i_n -1].len) = 0;\
		 int _ix_n = (p)[_i_n - 1].tag_len + (p)[_i_n -1].len -1;\
			 while( ( (_ix_n  ) >= 0) && isspace((d) [ _ix_n ]) ) {\
				 (d) [ _ix_n]  = 0;\
				 -- _ix_n;\
			 }\
	}while(0)




const char conf_op = '=';
const char remark_op = '#';
const string mv_cmd("mv");
const string rm_cmd("rm");
const string truncate_cmd("truncate");


const char cmd_separator = ':';


typedef map <const string,const string> conf_t; //ÅäÖÃÏîÖµ: key->value


//layout infomation for data chunk:
//pos : position of the chunk
//len : length of the chunk
typedef struct layout {
        int pos;
        size_t len;
        bool operator == (const layout &arg) const {
                return   (len == arg.len) && (pos == arg.pos);
        }

        bool operator > (const layout &arg) const {
                return   (len > arg.len) ;
        }

        bool operator < (const layout &arg) const {
                return    (len < arg.len) ;
        }

        layout():pos(0),len(0) {}

}
layout_t;

typedef struct pos_info {
        size_t tag_len;
        size_t pos;
        size_t len;
} pos_info_t;



//note:vector is used as an array
typedef vector<layout> lo_t;

pos_info_t *lo_to_pkey(pos_info_t *pkey, lo_t const &l );


enum {line_max = 1024, mem_units=1024};


size_t findchr(const char *s, char c, size_t pos= 0);

const lo_t & decide_layout(lo_t &l,
                           const char *str,
                           const char separator);

const char *do_layout(char *s, const lo_t &l);

const char *trimsp(char *s);

void do_rm(const string &cmd);
void do_truncate(const string &cmd);
void do_mv(const string &cmd);

time_t str_to_sec(const string & tstr) ;

conf_t *read_conf(conf_t *conf,const char *conf_name);


void redo(vector<string> const &cmd) ;

char *full_time_str(char  *tstr, time_t t);

typedef vector<string> flist_t;

flist_t *ls_dir(flist_t *fl, const char *path, const char *pattern,
                unsigned int max_file=1024);

void write_trans_file(const string &f, const vector<string> &cv);

inline const string
query_conf(string *value,  const conf_t &conf, const string &key)
{
        conf_t::const_iterator itr = conf.find(key);
        if (itr == conf.end()) {
                string ermsg("can not found config : ");
                ermsg += key;
                throw invalid_argument(ermsg);
        }

        return *value = itr->second;
}

size_t inline file_size(string const & fn)
{
        struct stat fs;
        if (stat(fn.c_str(), &fs) < 0) {
                string msg("file_size:stat:can not stat :");
                msg += fn;
                msg += ":";
                msg += strerror(errno);
                throw invalid_argument(msg);

        }

        return fs.st_size;
}


const char lo_sep = '|';
const char ft_sep = '-';

lo_t *parse_layout(lo_t *l, const string &s);


#endif /*TOOLKITS_H_*/
