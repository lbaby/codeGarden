#ifndef HTABLE_H
#define HTABLE_H


#include <stl_conf.h>

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _INCLUDE_STDINT_H
#include <stdint.h>
#endif

#ifdef _REGEXP_MATCH
#include <regex.h>
#include <fnmatch.h>
#endif

#include <toolkits.h>


const size_t _kb_mem_units = 1024;

//To find a data member with your need
//a visitor ,    visitor pattern ,
//refer to <<Design pattern>> for   visitor section
template <class T>
class hashvisitor
{
public:
        virtual bool done(void) {
                return false;
        }

        virtual void visit(T *t) =0;
        virtual ~hashvisitor() {}

};



//hash function for a string
//NOTE: this fuction and following ones is from SGI's STL library
inline size_t hashstr(const char* s)
{
        unsigned long h = 0;
        for ( ; *s; ++s) {
                h = 5*h + *s;
        }

        return size_t(h);
}

template <class _Key>
struct hash { }
;


template<>
struct hash<const char *> {
        size_t operator ()(const char *s)const {
                return (hashstr(s));
        }
};

template<>
struct hash<char *> {
        size_t operator ()(char *s)const {
                return (hashstr(s));
        }
};



//prime list , for hash table's size
//
enum { num_primes = 32 };

static const unsigned long
prime_list[num_primes] = {
        1543ul,     6151ul,     12289ul,    24593ul,   36939ul,
        49157ul,    61633ul,    75751ul,    98317ul,   115959ul,
        135137ul,   151511ul,   172127ul,   196613ul,  238999ul,
        260001ul,   290353ul,   355157ul,   393241ul,  589999ul,
        786433ul,   1158889ul,  1572869ul,  2280807ul, 3145739ul,
        4791111ul,  6291469ul,  12582917ul, 25165843ul,50331653ul,
        100663319ul,201326611ul
};


//layout for data
//data member's are organized with a chunk of data,
//every data member's size can change with need
//
enum {num_layout = 13};
static const size_t layout_list [ num_layout] = {
        1, 2, 3, 5,
        8, 13, 21, 34,
        55,89,144,233,377
};



size_t proper_layout(const size_t n);

//note:hash node does not manage data memory itself
//he just point to an exist memory region
//obversely , the node is a link list node
template <class T>
class hnode
{

public :
        hnode( T* v=NULL):m_value(v),m_next(NULL) {}

        //accept a visitor's visit with invoke visitor's member function :vistit()
        virtual void accept(hashvisitor<T> &v) {

                hnode<T> *p = this;

                while ( (! v.done() )&& p ) {
                        if (!p->m_value) {
                                break;
                        }

                        v.visit(p->m_value);
                        p = p->m_next;

                }
        }



        T * value(void) const {
                return m_value;
        }

        //return the tail node of this link list
        hnode<T>* back(void) {
                hnode<T>* p = this;
                while (p->m_next) {
                        p= p->m_next;
                }
                return p;
        }

        const hnode<T> &
        set_next(hnode<T > * h) {
                m_next = h;
                return *h;
        }

        T * set_value(T* v) {
                return m_value = v;

        }

        virtual ~hnode() {}



private:

        T *m_value;
        hnode<T> *m_next;
};



const size_t extra_divisor = 8;

//this htable can only used to search for data
//therefore , there is no way to deleting
//template: HF , a hash functor(or a function object) for the class T, refer to
template <class T, class HF=hash<T *> >
class htable
{
public:

        htable(size_t n, const vector<int> &arg_hfield  )
                        :_m_size(n),base(NULL),data(),hfield(arg_hfield) {
                size_t i;
                for (i = 0 ; i < num_primes; i++) {
                        if (n <= prime_list[i]) {
                                break;
                        }
                }
                _m_size =  ( i == num_primes) ? prime_list[i-1]:prime_list[i];

                base = new hnode<T> [_m_size];
                extra_size = _m_size/extra_divisor;
                if (!extra_size) {
                        extra_size = 1;
                }
        }


        ~htable() {
                purge();
        }

        void purge(void);

        const hnode<T> &insert(const hnode<T> &h);
        const  hnode<T> & insert(T *h, const vector<layout_t> &l);
        const  hnode<T> &  insert(size_t pos , const hnode<T> &hn);
        hnode<T> &find(const hnode<T> &h);



        void set_layout(const vector <layout_t> &l) {

                data_layout = l;

                chunksz = data_layout[data_layout.size() -1] . pos + data_layout[data_layout.size() -1].len;
                data.ptr = new uint8_t [_m_size * chunksz];
                memset(data.ptr, 0, chunksz * extra_size);


        }

        const vector <layout_t> & get_layout(void) const {
                return data_layout;
        }

        htable & operator = ( htable & h);


        htable(const htable & h) {
                *this = h;
        }

        size_t chunk_size(void) {
                return chunksz;
        }



        const vector<int>& get_hfield(void) {
                return hfield ;
        }
        typedef struct pool_info {
                uint8_t *ptr;
                size_t count;
                pool_info ():ptr(NULL), count(0) {}
        }
        data_pool_t ;

        unsigned long mem_sum() const {
                //data + link list
                return  (_m_size + (1 + base_pool.size())*extra_size ) * chunksz /_kb_mem_units ;
        }

        size_t size(void) const {
                return _m_size;
        }

        const  hnode <T> & operator [](size_t n)  const {
                return base[n];
        }

        hnode <T> & at (size_t n) {
                return base[n];
        }


private:


        size_t h(const hnode<T> &hn)

        {

                if (!hfield.size()) {
                        return  ( hf (hn.value()) ) %_m_size;
                }
                size_t hval  = 0;
                for (int i = 0 ; i < hfield.size(); i ++) {
                        hval = hval *5 + hf(
                                       reinterpret_cast<T *>
                                       (reinterpret_cast<uint8_t *>( hn.value() )+

                                        data_layout[ hfield[i] ].pos)

                               );
#ifdef DEBUG_PRINT_L3
                        printf("h:%s@%d\n", reinterpret_cast<T *>
                               (reinterpret_cast<uint8_t *>( hn.value() )+
                                data_layout[ hfield[i] ].pos), i);
#endif
                }
                return hval % _m_size;
        }
        vector<int> hfield; //hash value is extract from this key
        HF hf; //hash function
        size_t extra_size ;
        //for overflow's extra data
        vector <layout_t> data_layout; //
        size_t _m_size;//the length of hash table
        size_t chunksz;

        vector<size_t> base_pool_count;//for hnode's pool count

        hnode<T> *base;

        data_pool_t data;


        vector<hnode<T> *> base_pool;//memory pool for overflow
        vector<data_pool_t> data_pool;//data pool for memory manage

};

//an implement for copy construtor
template <typename T>
class copy_visitor:public hashvisitor<T>
{
public:
        copy_visitor(htable <T> *const to,const vector<layout_t> &lo )
                        :ht(to),l(lo) {}

        virtual void visit(T *t) {
                ht->insert(t, l);

        }


private:
        vector <layout_t> l;
        htable <T> *ht;

};



//
template<typename T ,class HF >
void htable<T,  HF >::purge(void)
{
        delete []base;
        base = NULL;
        delete []data.ptr;
        data.ptr = NULL;
        data.count = 0;
        size_t i;
        for ( i = 0 ; i < base_pool.size(); ++i) {
                delete []base_pool[i];

        }
        base_pool.clear();

        for ( i = 0 ; i < data_pool.size(); ++i) {
                delete []data_pool[i].ptr;
        }
        data_pool.clear();
}



//when you resize the chunk , you get a new hash table
//set the layout, then copy the data from argument

//NOTE:this hashtable act as an auto_ptr, when you copy the data
//from one  ptr, the ptr is purged.
template<typename T ,class HF >
htable<T, HF>
& htable<T, HF>::operator = ( htable<T, HF> & ht)
{
        if (this == & ht) {
                return *this;
        }

        //necessary check
        if (data_layout.empty() || ht.data_layout.empty() ) {
                throw logic_error("Please set data layout before you use  this hash table");
        }

        if (data_layout.size() < ht.data_layout.size()) {
                throw out_of_range("Please specific a bigger data(or equal) chunk num than the old one");
        }
        size_t i;
        for ( i = 0; i < ht.data_layout.size(); i ++) {
                if (data_layout[i].len < ht.data_layout[i].len) {
                        throw out_of_range("Please specific a bigger  chunk size than the old one");
                }
        }
        //do the copy action with copy visitor
        copy_visitor<T> cv(this, ht.get_layout());
        hfield = ht.hfield;
        //note: we have copy all the node  in the link list
        for ( i = 0 ; i < ht.size ; i ++) {
                if (ht.base[i].value()) {
                        ht.base[i].accept(cv);
                }
        }



        return *this;
}


//function to perform  core insert operation
//first , look for a node to arrange the inserted node
//second, find a proper data area for  storage
template<typename T ,class HF >

const
hnode<T> &
htable<T, HF>::insert(const hnode<T> &hn)
{

        size_t pos = h(hn);
        return insert(pos, hn);
}


//function to perform  core insert operation
//first , look for a node to arrange the inserted node
//second, find a proper data area for  storage
template<typename T ,class HF >

const
hnode<T> &
htable<T, HF>::insert(size_t pos , const hnode<T> &hn)
{


        hnode<T> *insert_point = base + pos;
        hnode<T> *insert_node = NULL;
        T * dat;

        //the find operation do like this:
        //look for a node that is free in  the base
        //then look for a free node position in the pool
        //if find operation on the above failed
        //and new a pool

        if (insert_point->value()) {//there is one element hold the position
                //ok , let's look for the extra pool to put the hnode
                insert_point=insert_point->back();

                //get a node on overflow data area
                size_t pool;
                for (pool = 0 ; pool < base_pool_count.size(); ++ pool) {
                        if (base_pool_count[pool] < extra_size) {
                                break;
                        }
                }

                if (pool == base_pool_count.size()) {//all the pool is full
                        //let's get new one
                        hnode<T> *p = new hnode<T> [extra_size];
                        base_pool.push_back(p);
                        base_pool_count.push_back(0);
                }
                insert_node = base_pool[pool] + (base_pool_count[pool] ++);

        } else {//the position is empty()
                insert_node = insert_point;

        }


        if (data.count == _m_size) {//data
                //look for a memory area in data area
                size_t data_pool_pos;
                for (data_pool_pos = 0; data_pool_pos < data_pool.size(); ++data_pool_pos) {
                        if (this->data_pool[data_pool_pos].count  <=  extra_size -1) {
                                break;
                        }
                }
                //full data area
                if (data_pool_pos == data_pool.size()) {
                        data_pool_t dp;
                        dp.ptr = new uint8_t [chunksz * extra_size];
                        memset(dp.ptr, 0, chunksz * extra_size);
                        data_pool.push_back(dp);
                }

                dat = reinterpret_cast<T* >
                      (
                              data_pool[data_pool_pos].ptr
                              + chunksz *   ( data_pool[data_pool_pos].count++)
                      );
        } else {
                dat = reinterpret_cast<T * >
                      (
                              data.ptr
                              + chunksz *   ( data.count++)
                      );
        }

        memcpy(dat, hn.value(), chunksz);
        insert_node->set_value(dat);

#ifdef DEBUG_PRINT_L3
        for (size_t i = 0; i < data_layout.size(); ++i) {
                if (i) {
                        putchar('|');
                }
                printf(dat +data_layout[i].pos);
        }
        putchar('\n');
#endif    // DEBUG_PRINT_L1

        if (insert_node != insert_point) {
                insert_point->set_next(insert_node);
        }

        return *insert_node;
}




//a call level interface for insert operation
template<typename T ,class HF >

const
hnode<T> &

htable<T, HF>::insert(T *t, const vector<layout_t> &l)
{
        if (data_layout.size() <l.size()) {
                throw out_of_range("Please specific a bigger data(or equal) chunk num than the old one");
        }
        size_t i;

        for (i = 0; i < l.size(); i ++) {
                if (data_layout[i].len < l[i].len) {
                        throw out_of_range("Please specific a bigger  chunk size than the old one");
                }
        }
        if (l == data_layout) {
                return insert(hnode<T>(t));
        }

        uint8_t * tmp = new uint8_t[chunksz];

        for (i = 0 ; i < l.size(); i++) {
                memcpy(tmp+data_layout[i].pos, reinterpret_cast<uint8_t *>(t) + l[i].pos, l[i].len);
        }

        const hnode<T> &hn =  insert(hnode<char>((char*)tmp));
        delete []tmp;
        return hn;

}


//NOTE: find method only return the first node of the link list
template<typename T ,class HF>
hnode<T> &
htable<T , HF>::find( const hnode<T> &hn)
{
        return base[ h(hn) ];
}




struct comparestr {
        virtual bool operator ()
        (const char *str1, const char *str2, size_t n) {
                return false;
        }
        virtual ~comparestr() {}

};

typedef struct compara {
        size_t pos;
        comparestr *comp;
} compara_t;

typedef vector<compara_t> compara_list_t;

struct strlt:public comparestr {
        virtual bool operator () (const char *str1, const char *str2, size_t n) {

                return strncmp(str1,str2,n) < 0;
        }
};

struct streq:public comparestr {
        bool operator () (const char *str1, const char *str2, size_t n) {

                return !strncmp(str1,str2,n);
        }
};


struct strcaseeq:public comparestr {
        bool operator () (const char *str1, const char *str2, size_t n) {

                return !strncasecmp(str1,str2,n);
        }
};

struct strgt:public comparestr {

        bool operator () (const char *str1, const char *str2, size_t n) {

                return strncmp(str1,str2,n)>0;

        }
};


struct strle:public comparestr {

        bool operator () (const char *str1, const char *str2, size_t n) {

                return strncmp(str1,str2,n)<=0;

        }
};



struct nz_streq:public comparestr {

        bool operator () (const char *str1, const char *str2, size_t n) {

                return !*str2 || !strncmp(str1,str2,n);

        }
};



struct strge:public comparestr {

        bool operator () (const char *str1, const char *str2, size_t n) {
                //puts("gt");
                return strncmp(str1,str2,n)>=0;

        }
};


struct strne:public comparestr {

        bool operator () (const char *str1, const char *str2, size_t n) {
                //puts("gt");
                return strncmp(str1,str2,n);

        }
};



static streq _strcompare_default;

static compara _compara_default = {
        0,
        dynamic_cast<comparestr *> (&_strcompare_default)
};




#ifdef _REGEXP_MATCH
struct strfnmatch:public comparestr {

        bool operator () (const char *pattern, const char *str, size_t n) {
                return !fnmatch(pattern,str,0);

        }
};


struct strregexp:public comparestr {

        bool operator () (const char *pattern, const char *str, size_t n) {

                regex_t re;

                int i = 0;
                if (  i = regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB)) {
                        char ermsg[256] ;
                        string ts;
                        ts = "Invalid regular expression: ";
                        regerror(i,&re,ermsg,sizeof ermsg);
                        ts += ermsg;
                        throw invalid_argument(ts.c_str());
                }

                bool ret = regexec(&re, str, (size_t) 0, NULL, 0);
                regfree(&re);
                return !ret;

        }


};


#endif

static compara_list_t _compara_list_default(1, _compara_default);
template <typename T>
class find_visitor :public hashvisitor<T>
        {};




template <>
class find_visitor <char> :public hashvisitor<char>
{
public:
        find_visitor
        (char  *s
         , const vector<layout_t> &al
         ,const compara_list_t &df=_compara_list_default)
                        :isdone(false),str(s),l(al),para(df) {}

        virtual void visit(char  *t) {


                if (!t) {
                        return;
                }
#ifdef PARA_CHECK
                for (size_t i = 0; i < para.size(); ++i) {
                        if (para[i].pos +1 > l.size()) {
                                char ermsg[512];
                                sprintf(ermsg, "parameter out of range on file:%s,line:%u "
                                        ", parameter: %u, and file's layout :%u "
                                        ,__FILE__
                                        ,__LINE__
                                        ,para[i].pos
                                        ,l.size());
                                throw out_of_range(ermsg);
                        }

                }
#endif
                //isdone = true;
                bool found = true;
                for (size_t ck = 0; ck < para.size(); ++ck) {
                        //	puts("visit");

                        if ( (*para[ck].comp)(str +l[para[ck].pos].pos,   t + l[para[ck].pos].pos,l[para[ck].pos].len-1)) {
                                //isdone = true;
#ifdef DEBUG_PRINT_L2
                                printf("OK::comp:%s:%s:%d\n",
                                       str +l[para[ck].pos].pos,
                                       t + l[para[ck].pos].pos,
                                       l[para[ck].pos].len-1);
#endif

                        } else {
                                //isdone = false;
                                //break;
                                //printf("fial:%s-%s\n", str +l[para[ck].pos].pos, t + l[para[ck].pos].pos);
#ifdef DEBUG_PRINT_L2
                                printf("FAILcomp:%s:%s:%d\n",
                                       str +l[para[ck].pos].pos,
                                       t + l[para[ck].pos].pos,
                                       l[para[ck].pos].len-1);
#endif
                                found = false;
                                break;

                        }

                }


                if (found) {
                        data.push_back(t);
                        isdone =true;
                }

                // 	isdone = data.size();
        }

        void print(void) {
                //int m = l.back().len + l.back().pos;
                vector <char  *> ::const_iterator itr;
                for (itr = data.begin(); itr != data.end(); ++itr) {

                        for (size_t i = 0; i < l.size(); ++i) {
                                if (i) {
                                        putchar('|');
                                }
                                printf(*itr +l[i].pos);
                        }
                        putchar('\n');
                }
        }


        virtual bool done(void) {
                return isdone;//data.size();
        }

        void reset(void) {
                isdone = false;
                data.clear();
        }

        char *field(size_t n) {
                return data[0] + l[n].pos;
        }

        const char *set_buf(char *s) {
                return str = s;
        }

        const lo_t & set_layout(const lo_t &arg_l) {
                return l = arg_l;
        }

        const lo_t & get_layout(void) {
                return l;
        }

        vector <char *> * all_match(void) {
                return &data;
        }
private:
        char  *str;
        vector <layout_t> l;
        vector <char  *> data;
        compara_list_t para;
        bool isdone;

};







#endif /*HTABLE_H*/
