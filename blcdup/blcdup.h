#ifndef WEEDUP_H_
#define WEEDUP_H_

#include <stl_conf.h>
#include <toolkits.h>
#include <log_file.h>

#define EDUP "E302"
#define DIR_PERMIT_MODE (S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH) //775

const string trans_log_prefix(".transaction");
const string trans_suffix_first(".append_index_processs");
const string trans_suffix_second(".file_output_process");

const string prog_prefix("blcdup");

enum { key_max=1024, max_mem_unit=1024*1024 };


extern lo_t mem_layout;
typedef struct data_node {
        htable<char> *data;
        uint64_t count; //access count

}data_node_t;

typedef struct file_cache{
	vector<string> cache;
	string file;

}file_cache_t;

typedef
map<string, file_cache_t >  fcache_map_t;
typedef struct trans_info {
        vector<string> trans_cmd;
        fcache_map_t idx_map;
}trans_info_t;




typedef map<string ,  data_node_t> idx_map_t;

enum {max_file_per_time = 1024};
enum {pos_key_max=256};
extern pos_info_t pkey_list [pos_key_max];
extern pos_info_t pdir_list [pos_key_max];
extern pos_info_t pfile_list [pos_key_max];



extern log_file *mylog;




namespace config
{
extern string conf_logdir;
extern string conf_progid;

extern string conf_inputdir;
extern string conf_tmpdir;
extern string conf_outdir;
extern string conf_errdir;
extern string conf_idxdir;

extern string conf_bakdir;
extern string conf_pattern;

extern string conf_sleep_time;

extern string conf_is_backup;
extern string conf_is_daemon;
extern string conf_maxmem;

extern string conf_dirpos;
extern string conf_filepos;
extern string conf_keypos;
extern string conf_valuepos;
extern string conf_presort;

extern string conf_records_per_node;

}



const vector<string> & vappdend_idx(const string &f, const vector<string> &idx);

#endif /*WEEDUP_H_*/
