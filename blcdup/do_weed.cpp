#include <do_weed.h>

const size_t load_factor = 62;  //for memory mange
const size_t max_load_min =   24 *  60 ;
const size_t cache_max_percent = 20;  // 10% total  memory max usage  per file cache
	                                   //(because of STL memory management strategy,  this num can not be precise one)



static size_t mm_factor;

const fcache_map_t&
cache_write(const string &dir,  fcache_map_t *fm)
{
	fcache_map_t::iterator itr = fm->begin();
	while(itr != fm->end()){
		if (itr ->second.cache.size()) {

			if (!itr->second.file.length()) { // the file is first time to synchronize to disk
				itr -> second.file = dir;
				string wname = itr->first;
				string::size_type slash = wname.find('/');

				while (slash != string::npos) {
					wname.replace(slash, 1, ",");
					slash = wname.find('/');
				}

				itr -> second.file += "/";
				itr -> second.file += wname;

				vwritef(itr->second.file, itr->second.cache, "w");
			} else {
				vwritef(itr->second.file, itr->second.cache, "a+");
			}
#ifdef DEBUG_PRINT_L3
			printf("cache file:%s\n", itr->second.file.c_str());
#endif

			itr->second.cache.clear(); // release the memory
		}
		++itr;
	}

	return *fm;
}

const
vector <string> & vreadf(vector <string> *vs, const string &f)
{
        FILE *fp = fopen(f.c_str(), "r");
        char lbuf[line_max + 1];

        if (!fp) {

                sprintf(lbuf, "can not open transaction file:%s:%s\n", f.c_str(),
                        strerror(errno) );
                throw runtime_error(lbuf);
        }

        while (fgets(lbuf, line_max + 1, fp)) {
                size_t len = strlen(lbuf);
                if (lbuf[len -1 ] == '\n') {
                        lbuf[len - 1 ] = 0;
                }
                vs->push_back(lbuf);

        }
        fclose(fp);

        return *vs;
}


const vector<string> & vwritef(const string &f, const vector<string> &idx, const string &mode)
{
        FILE * fp = fopen(f.c_str(), mode.c_str());
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




//adjust the memory so that keep the balance of memory usage
void mem_adjust(idx_map_t *idx, uint64_t mem_lmt)
{
        idx_map_t::iterator mem_itr = idx->begin();
        uint64_t memsum = 0;

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

                uint64_t remove_count = lru_v.size() * (100 - load_factor)  / 100;
                lru_less lless;
                sort  (lru_v.begin(), lru_v.end(),  lless);
                mylog->write("memadjust,delete %lld nodes\n", remove_count);
                for (size_t i = 0; i < remove_count; ++i ) {
                        idx_map_t:: iterator  del_itr = idx->find(lru_v[i].idx);
#ifdef DEBUG_PRINT_L3
                        printf("delete  memory node %s@%lld\n", lru_v[i].idx.c_str() , (uint64_t)lru_v[i].count );
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
        return *cur_file_idx;

}

//make the data index for the data
const char *  mk_dup_key(char  *dup_key, const char *line_buf)
{
	extract_key(dup_key, line_buf, pkey_list);
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

        char buf[line_max + 1];
        while (fgets(buf, line_max + +1, fp)) {
                size_t len = strlen(buf);
                if (buf [ len -1 ] == '\n') {
                        buf [ len -1 ] = 0;
                }

                h->insert(hnode<char>((char *)buf) );
        }

        fclose(fp);
#ifdef DEBUG_PRINT_L3
        mylog->write("load_idx,index %s loaded \n", f.c_str());
#endif
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

        uint64_t fc = 0;
        uint64_t ec = 0;

        string fname = config::conf_inputdir + "/" + f;

        string tmpname = config::conf_tmpdir + "/" + f + ".chk";

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


        uint64_t records_per_node = atoi(config::conf_records_per_node.c_str() );
        uint64_t max_mem = atol(config::conf_maxmem.c_str()) ;
        max_mem *= max_mem_unit;

        char dup_key[key_max];
        find_visitor<char> fv(dup_key, mem_layout);

        string prev_file_idx;
        fcache_map_t :: iterator prev_trans_itr;
        idx_map_t::iterator prev_idx_itr;

        uint64_t sync_count = 0;
        vector <string> verr ;
        string cur_file_idx;
        char line_buf[line_max+1];
        while (fgets(line_buf, line_max + 1, fpin)) {
                string cur_file_idx;
                fcache_map_t :: iterator cur_trans_itr;
                idx_map_t::iterator cur_idx_itr;

                //make the file index
                mk_file_idx(&cur_file_idx, line_buf);
                //make the duplicate key for record
                mk_dup_key(dup_key, line_buf);

                //do previous cache check
                if (cur_file_idx == prev_file_idx) {
                        cur_trans_itr = prev_trans_itr;
                        cur_idx_itr = prev_idx_itr;
                } else {//no cache node found , we need a new node
                        cur_idx_itr = idx->find(cur_file_idx);

                        cur_trans_itr = trans_log->idx_map.find(cur_file_idx);
                        if (cur_trans_itr == trans_log->idx_map.end()) {
                        	file_cache_t fc;
                                cur_trans_itr = trans_log->idx_map.insert(
                                		fcache_map_t::value_type(cur_file_idx, fc)
                                                ).first;
                        }

                        if (cur_idx_itr == idx->end()) {//this file index does not resident in memory
                                mem_adjust(idx, max_mem); //do the MM( memory management)

                                if(
                                		  (fc-ec-sync_count)  * 100 * mem_layout[0].len  > max_mem* cache_max_percent
                                		 ){
                                	cache_write(config::conf_tmpdir,  & trans_log->idx_map);
                               	mylog->write("cache_write:on records: %llu, mem:%llu,maxmem,%llu\n",
                                			fc-ec-sync_count, (fc-ec-sync_count) *mem_layout[0].len, max_mem);
                               	sync_count += fc-ec-sync_count;

                                }
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
                                if (cur_trans_itr->second.cache.size()) {
                                        vector<string>::const_iterator vitr = cur_trans_itr->second.cache.begin();
                                        while (vitr !=  cur_trans_itr->second.cache.end()) {
                                                char vec_buf[key_max];
                                                vitr->copy(vec_buf, key_max);
                                                cur_idx_itr->second.data->insert(hnode<char>(vec_buf));
                                                ++vitr;
                                        }

                                }
                                if(cur_trans_itr->second.file.length()){
                                	load_idx(  cur_idx_itr->second.data, cur_trans_itr->second.file);
                                }

                        }


                        //update the cache node
                        prev_trans_itr = cur_trans_itr;
                        prev_idx_itr = cur_idx_itr;
                        prev_file_idx = cur_file_idx;
                }

                //do the duplicate check
                fv.reset();
                size_t hpos = hashstr(dup_key)%cur_idx_itr->second.data->size();
                cur_idx_itr->second.data->at(hpos).accept(fv);
                ++ cur_idx_itr->second.count;


                ++fc;
                if (!fv.done()) {
                        cur_idx_itr->second.data->insert(hpos, hnode<char>(dup_key));
                        cur_trans_itr->second.cache.push_back(dup_key);
                        fputs(line_buf, fptmp);
                } else { //duplicate record
                        string es = EDUP;
                        es += line_buf;
                        verr.push_back(es);
                        ++ec;
                }

        }

        fclose(fptmp);
        fclose(fpin);


        //record the transaction file :

        map<string, file_cache_t >:: const_iterator citr ;
        for (citr = trans_log->idx_map.begin(); citr != trans_log->idx_map.end(); ++citr) {
		string fname = config::conf_idxdir + "/" + citr -> first;
		unsigned long long flen = 0;
		if (access(fname.c_str(), F_OK) == 0) { //not exist in the disk
			flen = file_size(fname);
		}
		char buf[64];
		sprintf(buf, "%llu", (uint64_t) flen);
		string trun_cmd = truncate_cmd + cmd_separator + fname + cmd_separator
				+ buf;
		trans_log->trans_cmd.push_back(trun_cmd);
		if (citr->second.file.length()) {// there is some index data synchronize to disk, remove it
			string rmtmp = rm_cmd;
			rmtmp += cmd_separator;
			rmtmp += citr->second.file;
			trans_log->trans_cmd.push_back(rmtmp);
		}
	}

        string fcmd;
        if (config::conf_is_backup == "yes") {
                fcmd= mv_cmd + cmd_separator + fname + cmd_separator + config::conf_bakdir + "/" +f;
                trans_log->trans_cmd.push_back(fcmd);
        }

        if (verr.size()) {
                string errname = config::conf_tmpdir + "/" + f + ".dup";
                vwrite(errname, verr);
                fcmd= mv_cmd + cmd_separator + errname + cmd_separator + config::conf_errdir + "/" + f;
                size_t fl = fcmd.length();

                fcmd.replace(fl - 4, 4, ".dup");
                trans_log->trans_cmd.push_back(fcmd);
        }


        if (file_size(tmpname)) {
                fcmd= mv_cmd + cmd_separator + tmpname + cmd_separator + config::conf_outdir + "/" + f;
                size_t fl = fcmd.length();
                string::size_type dot = f.rfind('.');
                                if(dot == string::npos){
                                	fcmd += ".chk";
                                }else
                                	if(dot ==  (fl -4) ){
                                		fcmd.replace(fl - 4, 4, ".chk");

                                }else{
                                	fcmd += ".chk";
                                }


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


