#include <do_sum.h>

const size_t load_factor = 62;  //for memory mange
const size_t max_load_min =   24 *  60 ;


pos_info_t pvalue_list [pos_key_max];
pos_info_t pdir_list [pos_key_max];
pos_info_t pfile_list [pos_key_max];
pos_info_t pkey_list [pos_key_max];
pos_info_t pcheckpos_list [pos_key_max];

size_t feelimit;

static size_t mm_factor;


//adjust the memory so that keep the balance of memory usage
void mem_adjust(idx_map_t *idx, size_t mem_lmt)
{
        idx_map_t::iterator mem_itr = idx->begin();
        unsigned long long memsum = 0;

        while (mem_itr != idx->end()) {
                memsum += mem_itr->second.data->mem_sum() * _kb_mem_units;
                //adjust the access count
                if ( ( mem_itr->second.count ) < mm_factor) {
                        mem_itr->second.count  = 0;
                } else {
                        mem_itr->second.count -= mm_factor;
                }
                ++mem_itr;

        }


        if (memsum > mem_lmt ) {

#ifdef DEBUG_PRINT_L3
                printf("adjust memory at mem: %lld\n", memsum );
#endif



                vector<lru_t> lru_v;
                mem_itr = idx->begin();
                while (mem_itr != idx->end()) {
                        lru_t lru_node ;
                        lru_node.count = mem_itr->second.count;
                        lru_node.idx = mem_itr->first;
                        lru_v.push_back(lru_node);
                        ++ mem_itr;
                }

                size_t remove_count = lru_v.size() * (100 - load_factor)  / 100;
                lru_less lless;
                sort  (lru_v.begin(), lru_v.end(),  lless);
                mylog->write("memadjust,delete %lld nodes\n", remove_count);
                for (size_t i = 0; i < remove_count; ++i ) {
                        idx_map_t:: iterator  del_itr = idx->find(lru_v[i].idx);
#ifdef DEBUG_PRINT_L3
                        printf("delete %s@%lld\n", lru_v[i].idx.c_str() , (uint64_t)lru_v[i].count );
#endif


                        delete del_itr->second.data;
                        idx->erase(del_itr);

                }
        }
}

//make the file index for the data
const string &mk_file_idx(string *cur_file_idx, const char *line_buf)
{

        char dir_key[line_max];

        char file_key[line_max];

        extract_key(dir_key, line_buf, pdir_list);
        extract_key(file_key, line_buf, pfile_list);
        *cur_file_idx = dir_key;

        *cur_file_idx += "/";
        *cur_file_idx += file_key;
#ifdef DEBUG_PRINT_L3
        printf("mk_file_idx:%s\n", cur_file_idx->c_str());
#endif
        return *cur_file_idx;

}

//make the data index for the data
const char *  mk_dup_key(char  *dup_key, const char *line_buf)
{
        extract_key(dup_key, line_buf, pkey_list);
#ifdef DEBUG_PRINT_L3
        printf("mk_dup_key:%s\n", dup_key);
#endif
        return dup_key;
}


const htable<char> &load_idx(htable<char> * h, const string f)
{
        FILE *fp = fopen(f.c_str(), "r");
        if (!fp) {
                string msg("load_idx:can not open file:");
                msg += f;
                msg += ":";
                msg += strerror(errno);
                throw runtime_error(msg);
        }
        char vec_buf[key_max]={0};
        find_visitor<char> fvi(vec_buf, mem_layout);
        char buf[line_max + 1];
        while (fgets(buf, line_max  +1, fp)) {
                size_t len = strlen(buf);

                if (buf [ len -1 ] == '\n') {
                        buf [ len -1 ] = 0;
                }

                idx_to_pkey(vec_buf, buf);

                update_node(h, vec_buf, fvi);


        }

        fclose(fp);
        mylog->write("load_idx,index %s loaded \n", f.c_str());
        return *h;

}

//app
const vector<string> & vwrite(const string &f, const vector<string> &vs)
{
        FILE * fp = fopen(f.c_str(), "w");
        if (!fp) {
                string msg = f;
                msg +=": appendat:can not open the file";
                throw invalid_argument(msg);
        }
#ifdef DEBUG_PRINT_L3
        printf("append:%s\n", f.c_str());
#endif
        for (size_t i = 0; i < vs.size(); ++i) {
                fputs(vs[i].c_str() , fp);
                fputc('\n', fp);
        }

        if (fclose(fp) < 0) {
                string msg = f;
                msg +=": appendat:can not close the file";
                throw runtime_error(msg);
        }

        return vs;

}


//do the index weed up and record the transaction
//first , find the file index for the data
//second  , weed out the duplicate records

//if the index does not resident in memory
//check if it is exist in the disk file
//load it from file if it is


//before we load the index , do memory usage check
//if run out of memory limitation, release
void do_weed(idx_map_t *idx, trans_info_t *trans_log, const string &f)
{

        size_t fc = 0;
        size_t ec = 0;

        string fname = config::conf_inputdir + "/" + f;

        string tmpname = config::conf_tmpdir + "/" + f ;

        char tbs[16];
        full_time_str(tbs, time(0));

        //for memory mangment
        if (!mm_factor) {

                size_t total_node = atol(config::conf_maxmem.c_str());
                total_node *= max_mem_unit;
                total_node /= key_max *atol(config::conf_records_per_node.c_str() ) ;

                mm_factor =atol(config::conf_records_per_node.c_str() )  / total_node;

                mylog->write("runtime mm_factor:%llu\n", (int64_t)mm_factor);
#ifdef DEBUG_PRINT_L3

#endif
        }
        if (mm_factor== 0) {
                mm_factor = 1;
        }

        FILE *fpin = fopen(fname.c_str(), "r");
        if (!fpin) {
                string msg= "can not open:" + fname;
                msg += ":";
                msg += strerror(errno);
                throw runtime_error(msg);
        }

        FILE *fptmp = fopen(tmpname.c_str(), "w");
        if (!fptmp) {
                string msg= "can not open:" + tmpname;
                msg += ":";
                msg += strerror(errno);
                throw runtime_error(msg);
        }


        size_t records_per_node = atoi(config::conf_records_per_node.c_str() );
        size_t max_mem = atol(config::conf_maxmem.c_str()) ;
        max_mem *= max_mem_unit;

        char dup_key[key_max];

        find_visitor<char> fv(dup_key, mem_layout);

        string prev_file_idx;
        map<string, vector<string> > :: iterator prev_trans_itr;
        idx_map_t::iterator prev_idx_itr;


        vector <string> verr ;
        string cur_file_idx;
        char line_buf[line_max+1];
        while (fgets(line_buf, line_max + 1, fpin)) {
                string cur_file_idx;
                map<string, vector<string> > :: iterator cur_trans_itr;
                idx_map_t::iterator cur_idx_itr;

                char checkkey[line_max];
                extract_key(checkkey, line_buf, pcheckpos_list);
                if (strcmp(checkkey, config::conf_checkkey.c_str() ) ) {
                        fputs(line_buf, fptmp);
                        ++fc;
                        continue;
                }
                //make the file index
                mk_file_idx(&cur_file_idx, line_buf);
                //make the duplicate key for record
                mk_dup_key(dup_key, line_buf);
                char value_key[key_max] ;
                extract_key(value_key, line_buf, pvalue_list);
                *pkey_data(dup_key) = atol(value_key);

                //do previous cache check
                if (cur_file_idx == prev_file_idx) {
                        cur_trans_itr = prev_trans_itr;
                        cur_idx_itr = prev_idx_itr;
                } else {//no cache node found , we need a new node
                        cur_idx_itr = idx->find(cur_file_idx);

                        cur_trans_itr = trans_log->idx_map.find(cur_file_idx);
                        if (cur_trans_itr == trans_log->idx_map.end()) {
                                vector<string> vs;
                                cur_trans_itr = trans_log->idx_map.insert(
                                                        map<string, vector<string> >::value_type(cur_file_idx, vs)
                                                ).first;
                        }

                        if (cur_idx_itr == idx->end()) {//this file index does not resident in memory
                                mem_adjust(idx, max_mem); //do the MM( memory management)

                                data_node_t dn;
                                dn.count = records_per_node;
                                dn.data = new htable<char>(records_per_node,
                                                           vector <int>(1, 0));
                                dn.data->set_layout(mem_layout);
                                cur_idx_itr = idx->insert(idx_map_t::value_type(cur_file_idx, dn)).first;

                                //check if it exist in the disk file
                                string idx_disk_file = config::conf_idxdir + "/" + cur_file_idx;
                                if (access(idx_disk_file.c_str(), F_OK) == 0) { // the index resident in the disk
                                        load_idx(cur_idx_itr->second.data, idx_disk_file);
                                }

                                // note , if we get a new index node,  there may be the node out of synchronize
                                //load it to memory too
                                if (cur_trans_itr->second.size()) {
                                        char vec_buf[key_max]={0};
                                        find_visitor<char> fvi(vec_buf, mem_layout);

                                        vector<string>::const_iterator vitr = cur_trans_itr->second.begin();
                                        while (vitr !=  cur_trans_itr->second.end()) {
                                                memset(vec_buf, 0 ,sizeof(vec_buf));
                                                idx_to_pkey(vec_buf, vitr->c_str() );
                                                update_node(cur_idx_itr->second.data, vec_buf, fvi);
                                                ++vitr;
                                        }

                                }

                        }


                        //update the cache node
                        prev_trans_itr = cur_trans_itr;
                        prev_idx_itr = cur_idx_itr;
                        prev_file_idx = cur_file_idx;
                }

                //do the duplicate check
                fv.reset();



                update_node(cur_idx_itr->second.data, dup_key, fv);
                ++ cur_idx_itr->second.count;


                ++fc;
                if (*pkey_data(fv.field(0)) > feelimit) {
                        char feebuf[24] = {0};
                        sprintf(feebuf, "%lld:", *pkey_data(fv.field(0)));
                        string es = feebuf;
                        es += line_buf;
                        verr.push_back(es);
                        ++ec;
                } else { //a passed record
                        char dup_key_str[key_max];
                        pkey_to_idx(dup_key_str, dup_key);
#ifdef DEBUG_PRINT_L3
                        printf("idx:%s\n", dup_key_str);
#endif
                        fputs(line_buf, fptmp);
                        cur_trans_itr->second.push_back(dup_key_str);
                }

        }

        fclose(fptmp);
        fclose(fpin);


        //record the transaction file :

        map<string, vector<string> >:: const_iterator citr ;
        for (citr  = trans_log->idx_map.begin(); citr != trans_log->idx_map.end(); ++citr) {
                string fname = config::conf_idxdir + "/" + citr -> first;
                unsigned long long  flen = 0;
                if ( access( fname.c_str(), F_OK) == 0) { //not exist in the disk
                        flen = file_size(fname);
                }
                char buf[64];
                sprintf(buf, "%llu", (uint64_t)flen);
                string trun_cmd = truncate_cmd + cmd_separator + fname + cmd_separator +buf;
                trans_log->trans_cmd.push_back(trun_cmd);
        }

        string fcmd;
        if (config::conf_is_backup == "yes") {
                fcmd= mv_cmd + cmd_separator + fname + cmd_separator + config::conf_bakdir + "/" +f;
                trans_log->trans_cmd.push_back(fcmd);
        }

        if (verr.size()) {
                string errname = config::conf_tmpdir + "/" + f + ".err";
                vwrite(errname, verr);
                fcmd= mv_cmd + cmd_separator + errname + cmd_separator + config::conf_errdir + "/" + f + ".err";

                trans_log->trans_cmd.push_back(fcmd);
        }


        if (file_size(tmpname)) {
                fcmd= mv_cmd + cmd_separator + tmpname + cmd_separator + config::conf_outdir + "/" + f;
                //size_t fl = fcmd.length();
                //fcmd.replace(fl - 4, 4, ".chk");
                trans_log->trans_cmd.push_back(fcmd);
        } else {
                fcmd= rm_cmd + cmd_separator + tmpname;
                trans_log->trans_cmd.push_back(fcmd);

        }



        char tbe[16];
        full_time_str(tbe, time(0));
        mylog->write("%s,%s,%llu,%llu,%llu,%llu,%llu,%s,%s,%s\n"
                     , "ProcInfo"
                     , f.c_str()
                     , (uint64_t)fc
                     , (uint64_t)(fc - ec)
                     , (uint64_t)ec
                     , (uint64_t) 0
                     , (uint64_t) file_size(fname)
                     , tbs
                     , tbe
                     , config::conf_inputdir.c_str()
                    );

}



//app
const vector<string> & append_idx(const string &f, const vector<string> &idx)
{
        string::size_type slash = f.rfind('/');
        string dir_name = f.substr(0, slash );

        if ( access (dir_name.c_str(), F_OK) != 0) {
#ifdef DEBUG_PRINT_L3
                printf("mkdir:%s\n", dir_name.c_str());
#endif
                if (mkdir(dir_name.c_str(), DIR_PERMIT_MODE) < 0) {
                        string msg = dir_name;
                        msg += "can not mkdir : ";
                        msg += strerror(errno);
                        throw runtime_error(msg);
                }
        }

        FILE * fp = fopen(f.c_str(), "a+");
        if (!fp) {
                string msg = f;
                msg +=": appendat:can not open the file";
                throw invalid_argument(msg);
        }
#ifdef DEBUG_PRINT_L3
        printf("append:%s\n", f.c_str());
#endif
        for (size_t i = 0; i < idx.size(); ++i) {
                fputs(idx[i].c_str() , fp);
                fputc('\n', fp);
        }

        if (fclose(fp) < 0) {
                string msg = f;
                msg +=": appendat:can not close the file";
                throw runtime_error(msg);
        }

        return idx;

}


