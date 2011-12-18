#ifndef DO_WEED_H_
#define DO_WEED_H_

#include <toolkits.h>
#include <htable.h>
#include <sumlim.h>

typedef uint64_t data_t;

enum {pos_key_max=256};
extern pos_info_t pvalue_list [pos_key_max];
extern pos_info_t pdir_list [pos_key_max];
extern pos_info_t pfile_list [pos_key_max];
extern pos_info_t pkey_list [pos_key_max];
extern pos_info_t pcheckpos_list [pos_key_max];

typedef struct lru {
        size_t count ;
        string idx  ;
}lru_t;

typedef struct lru_less {
        bool operator () ( const lru_t &a,  const lru_t &b ) const {
                return a.count < b.count;
        }
}lru_less_t;

typedef struct trans_info {
        vector<string> trans_cmd;
        map<string, vector<string> > idx_map;
}trans_info_t;



typedef struct data_node {
        htable<char> *data;
        size_t count; //access count

}data_node_t;

typedef map<string ,  data_node_t> idx_map_t;

extern lo_t mem_layout;
extern size_t feelimit;

void do_weed(idx_map_t *idx, trans_info_t *trans_log, const string &f) ;
const vector<string> & append_idx(const string &f, const vector<string> &idx);


inline data_t *  pkey_data(char *pkey)
{
        return reinterpret_cast<data_t*>(pkey + mem_layout[1].pos)	;
}

inline const data_t *  const  pkey_data(const char *pkey)
{
        return reinterpret_cast<const data_t*>(pkey + mem_layout[1].pos)	;
}

inline char *pkey_to_idx(char *idx,const  char *pkey)
{
        memcpy(idx, pkey, mem_layout[0].len);
#ifdef DEBUG_PRINT_L3
        printf ("pk-idx:%d\n", mem_layout[0].len);
#endif
        char line_buf[line_max] ;
        sprintf(line_buf , "%c%lld", lo_sep, *pkey_data(pkey));

        strcat(idx, line_buf);

        return idx;
}



inline  char *idx_to_pkey(char *pkey, const char *idx)
{
        size_t n = 0;
        while (idx[n] ) {
                if ( ( pkey[n]  = idx[n]) != lo_sep) {
                        n++;
                } else {
                        pkey[n] = 0;
                        n++;
                        break;
                }
                

        }
        *pkey_data(pkey)
        = atol(idx +n);


        return pkey;
}

inline char *add_pkey(char *pkey, const char *padd)
{
        *pkey_data(pkey)
        +=
                *pkey_data(padd);

        return pkey;

}

#define update_node( _ht_, _pk_, _fv_)\
	do{\
        _fv_.reset();\
         size_t _hpos_ = hashstr(_pk_)%(_ht_)->size();\
         (_ht_)->at(_hpos_).accept(_fv_);\
         if(_fv_.done()){\
        	 add_pkey(_fv_.field(0), _pk_);\
         }else{\
        	 (_ht_)->insert(_pk_);\
        	 (_ht_)->at(_hpos_).accept(_fv_);\
         }\
         }while(0)



#endif /*DO_WEED_H_*/
