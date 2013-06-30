#ifndef DO_WEED_H_
#define DO_WEED_H_

#include <blcdup.h>

//#define extract_key(d, s, p, n)\
//	do{\
//		int _i_n = 0;\
//		for (_i_n = 0; _i_n < (n); ++_i_n) {\
//			memcpy( (d)+ (p)[_i_n].tag_len, (s) + (p)[_i_n].pos, (p)[_i_n].len );\
//		}\
//		 *((d)+ (p)[_i_n - 1].tag_len + (p)[_i_n -1].len) = 0;\
//		 int _ix_n = (p)[_i_n - 1].tag_len + (p)[_i_n -1].len -1;\
//			 while( ( (_ix_n  ) >= 0) && isspace((d) [ _ix_n ]) ) {\
//				 (d) [ _ix_n]  = 0;\
//				 -- _ix_n;\
//			 }\
//	}while(0)



typedef struct lru {
        uint64_t count ;
        string idx  ;
}lru_t;

typedef struct lru_less {
        bool operator () ( const lru_t &a,  const lru_t &b ) const {
                return a.count < b.count;
        }
}lru_less_t;


void do_weed(idx_map_t *idx, trans_info_t *trans_log, const string &f) ;

const
vector <string> & vreadf(vector <string> *vs, const string &f);
const vector<string> & vwritef(const string &f, const vector<string> &idx, const string &mode);
#endif /*DO_WEED_H_*/
