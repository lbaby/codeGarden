#ifndef WEEDUP_H_
#define WEEDUP_H_

#include <stl_conf.h>
#include <toolkits.h>
#include <log_file.h>
#include <do_sum.h>


#define DIR_PERMIT_MODE (S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH) //775

const string trans_log_prefix(".transaction");
const string trans_suffix_first(".append_index_processs");
const string trans_suffix_second(".file_output_process");

const string prog_prefix("sumlim");

enum { key_max=128, max_mem_unit=1024*1024 };


extern lo_t mem_layout;





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

extern string conf_records_per_node;

extern string conf_dirpos;
extern string conf_filepos;
extern string conf_keypos;
extern string conf_valuepos;
extern string conf_checkpos;
extern string conf_checkkey;
extern string conf_feelim;
}



#endif /*WEEDUP_H_*/
