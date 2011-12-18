#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <stdexcept>


#ifdef _USING_NAMESPACE_STD
using namespace std;
#endif

#ifdef _NEED_STDINT
#include <stdint.h>
#endif

#include <stdio.h>




//To find a data member with your need
template <class T>
class hashvisitor
{
public:
        virtual bool done(void)
        {
                return false;
        }

        virtual void visit(T *t) =0;
        virtual ~hashvisitor(){}

};



//hash function for a string
//
inline size_t hashstr(const char* s)
{
        unsigned long h = 0;
        for ( ; *s; ++s) {
                h = 5*h + *s;
        }

        return size_t(h);
}

template <class _Key>
struct hash
        { }
;


template<>
struct hash<const char *>
{
        size_t operator ()(const char *s)const
        {
                return (hashstr(s));
        }
};

template<>
struct hash<char *>
{
        size_t operator ()(char *s)const
        {
                return (hashstr(s));
        }
};



//prime list , for hash table's size
//
enum { num_primes = 28 };

static const unsigned long prime_list[num_primes] =
        {
                53ul,         97ul,         193ul,       389ul,       769ul,
                1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
                49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
                1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
                50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
                1610612741ul, 3221225473ul, 4294967291ul
        };


//layout for data
//data member's are organized with a chunk of data,
//every data member's size can change with need
//
enum {num_layout = 13};
static const size_t layout_list [ num_layout] =
        {
                1, 2, 3, 5,
                8, 13, 21, 34,
                55,89,144,233,377
        };



size_t proper_layout(const size_t n);

//note:hash node does not manage data memory itself
//he just point an exist memory region
//obversely , the node is a link list node
template <class T, class HF=hash<T* > >
class hnode
{

public :
        hnode( T* v=NULL):m_value(v),m_next(NULL)
        {}

        virtual void accept(hashvisitor<T> &v)
        {

                hnode<T> *p = this;

                while ( (! v.done() )&& p ) {
                        if(!p->m_value) {
                                break;
                        }

                        v.visit(p->m_value);
                        p = p->m_next;
                        
                }
        }

        size_t hashvalue(void) const
        {
                return hf(m_value);
        }

        T * value(void) const
        {
                return m_value;
        }


        hnode<T>* back(void)
        {
                hnode<T>* p = this;
                while(p->m_next) {
                        p= p->m_next;
                }
                return p;
        }

        const hnode<T> &
        set_next(hnode<T > * h)
        {
                m_next = h;
                return *h;
        }

        T * set_value(T* v)
        {
                return m_value = v;

        }
        
        virtual ~hnode(){}

private:
        HF hf;
        T *m_value;
        hnode<T> *m_next;
};


//layout infomation for data chunk:
//
typedef struct layout
{
        int pos;
        size_t len;
        bool operator == (const layout &arg) const
        {
                return  (pos == arg.pos) && (len == arg.len);
        }

        bool operator > (const layout &arg) const
        {
                return  (pos > arg.pos) ;
        }

        bool operator < (const layout &arg) const
        {
                return  (pos < arg.pos) ;
        }

        layout():pos(0),len(0)
        {}

}
layout_t;

typedef vector<layout> lo_t;




//this htable can only used to search for data
//never delete any data!

template <class T>
class htable
{
public:

        htable(size_t n):size(n),base(NULL),data()
        {
                size_t i;
                for(i = 0 ; i < num_primes; i++) {
                        if(n <= prime_list[i]) {
                                break;
                        }
                }
                size =  (i == num_primes) ? prime_list[i-1]:prime_list[i];
                base = new hnode<T> [size];
                extra_size = size/4;
        }


        ~htable()
        {
                purge();
        }

        void purge(void);

        const hnode<T> &insert(const hnode<T> &h);
        const  hnode<T> & insert(T *h, const vector<layout_t> &l);
        hnode<T> &find(const hnode<T> &h);



        void set_layout(const vector <layout_t> &l)
        {
                /*
                size_t addn = 0;
                for(size_t i  = 0 ; i < l.size(); i++){
                	layout_t nl;
                	nl.pos += addn;
                	nl.len = proper_layout(l[i].len);
                	
                	addn += nl.len -l[i].len;
                	nl.pos += l[i].pos;
                	data_layout.push_back( nl );
                }*/
                data_layout = l;

                chunksz = data_layout[data_layout.size() -1] . pos + data_layout[data_layout.size() -1].len;
                data.ptr = new uint8_t [size * chunksz];
                memset(data.ptr, 0, chunksz * extra_size);


        }

        const vector <layout_t> & get_layout(void) const
        {
                return data_layout;
        }

        htable & operator = ( htable & h);


        htable(const htable & h)
        {
                *this = h;
        }

        typedef struct pool_info
        {
                uint8_t *ptr;
                size_t count;
                pool_info ():ptr(NULL), count(0)
                {}
        }
        data_pool_t ;

private:


        size_t h(size_t n)const

        {
                //printf("%d:%d\n", n, n%size);
                return n%size;
        }
        size_t extra_size ;
        //for overflow's extra data
        vector <layout_t> data_layout; //
        size_t size;//the length of hash table
        size_t chunksz;

        vector<size_t> base_pool_count;//for hnode's pool count

        hnode<T> *base;

        data_pool_t data;


        vector<hnode<T> *> base_pool;//memory pool for overflow
        vector<data_pool_t> data_pool;//data pool for memory manage

};

template <typename T>
class copy_visitor:public hashvisitor<T>
{
public:
        copy_visitor(htable <T> *const to,const vector<layout_t> &lo )
                        :ht(to),l(lo)
        {}

        virtual void visit(T *t)
        {
                ht->insert(t, l);

        }


private:
        vector <layout_t> l;
        htable <T> *ht;

};



//
template<typename T>
void htable<T>::purge(void)
{
        delete []base;
        base = NULL;
        delete []data.ptr;
        data.ptr = NULL;
        data.count = 0;
        size_t i;
        for( i = 0 ; i < base_pool.size(); ++i) {
                delete []base_pool[i];

        }
        base_pool.clear();

        for( i = 0 ; i < data_pool.size(); ++i) {
                delete []data_pool[i].ptr;
        }
        data_pool.clear();
}



//when you resize the chunk , you get a new hash table
//set the layout, then copy the data from argument
//NOTE:this hashtable act as an auto_ptr, when you copy the data
//from one  ptr, the ptr is purged.
template<typename T>
htable<T>
& htable<T>::operator = ( htable<T> & ht)
{
        if(this == & ht) {
                return *this;
        }

        //necessary check
        if(data_layout.empty() || ht.data_layout.empty() ) {
                throw logic_error("Please set data layout before you use  this hash table");
        }

        if(data_layout.size() < ht.data_layout.size()) {
                throw out_of_range("Please specific a bigger data(or equal) chunk num than the old one");
        }
        size_t i;
        for( i = 0; i < ht.data_layout.size(); i ++) {
                if(data_layout[i].len < ht.data_layout[i].len) {
                        throw out_of_range("Please specific a bigger  chunk size than the old one");
                }
        }


        copy_visitor<T> cv(this, ht.get_layout());

        //note: we have copy all the node --including
        for ( i = 0 ; i < ht.size ; i ++) {
                if(ht.base[i].value()) {
                        ht.base[i].accept(cv);
                }
        }



        return *this;
}



template<class  T>
const
hnode<T> &
htable<T>::insert(const hnode<T> &hn)
{

        size_t pos = h(hn.hashvalue());
        hnode<T> *insert_point = base + pos;
        hnode<T> *insert_node = NULL;
        T * dat;

        if(insert_point->value()) {//there is one element hold the position
                //ok , let's look for the extra pool to put the hnode
                insert_point=insert_point->back();

                //get a node on overflow data area
                size_t pool;
                for(pool = 0 ; pool < base_pool_count.size(); ++ pool) {
                        if(base_pool_count[pool] < extra_size) {
                                break;
                        }
                }

                if(pool == base_pool_count.size()) {//all the pool is full
                        //let's get new one
                        hnode<T> *p = new hnode<T> [extra_size];
                        base_pool.push_back(p);
                        base_pool_count.push_back(0);
                }
                insert_node = base_pool[pool] + (base_pool_count[pool] ++);

        } else {//the position is empty()
                insert_node = insert_point;

        }


        if(data.count == size) {//data
                //look for a memory area in data area
                size_t data_pool_pos;
                for(data_pool_pos = 0; data_pool_pos < data_pool.size(); ++data_pool_pos) {
                        if(this->data_pool[data_pool_pos].count  <=  extra_size -1) {
                                break;
                        }
                }
                //full data area
                if(data_pool_pos == data_pool.size()) {
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

        if(insert_node != insert_point) {
                insert_point->set_next(insert_node);
        }

        return *insert_node;
}



template<class  T>
const
hnode<T> &

htable<T>::insert(T *t, const vector<layout_t> &l)
{
        if(data_layout.size() <l.size()) {
                throw out_of_range("Please specific a bigger data(or equal) chunk num than the old one");
        }
        size_t i;

        for(i = 0; i < l.size(); i ++) {
                if(data_layout[i].len < l[i].len) {
                        throw out_of_range("Please specific a bigger  chunk size than the old one");
                }
        }
        if(l == data_layout) {
                return insert(hnode<T>(t));
        }

        uint8_t * tmp = new uint8_t[chunksz];

        for(i = 0 ; i < l.size(); i++) {
                memcpy(tmp+data_layout[i].pos, reinterpret_cast<uint8_t *>(t) + l[i].pos, l[i].len);
        }

        const hnode<T> &hn =  insert(hnode<char>((char*)tmp));
        delete []tmp;
        return hn;

}

template<class T>
hnode<T> &
htable<T>::find( const hnode<T> &hn)
{
        return base[ h(hn.hashvalue()) ];
}





#endif /*HASH_TABLE_H*/
