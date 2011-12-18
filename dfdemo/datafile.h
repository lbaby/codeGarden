#ifndef DATAFILE_H_
#define DATAFILE_H_


#include <string>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include <vector>

#include <htable.h>


#ifdef _USING_NAMESPACE_STD
using namespace std;
#endif





class datafile
{
public:
        datafile(const char * const name,
                 const char sep='|'):fname(name),separator(sep),data(NULL)
        {
#ifdef DYNAMIC_LOAD
                load_time =0;
#endif

                isloaded = false;

        }


        hnode <char> &
        find(char *s)
        {
                if(!isloaded) {
                        throw runtime_error("can not search the data before you load it");
                }
                //we assume that the layout is the same as our htable
                return data->find(hnode<char>(s));
        }

        ~datafile()
        {
                delete data;
        }

        const vector<layout_t>
        &get_layout(void)const
        {
                return l;
        }

        char get_separator(void)
        {
                return separator;
        }

        void load(void);

private:
        string fname;


#ifdef DYNAMIC_LOAD

        time_t load_time;
#endif

        const char separator;
        htable<char> *data;
        vector<layout> l;
        bool isloaded;

};

struct comparestr
{
	  virtual bool operator ()
	 (const char *str1, const char *str2, size_t n)
	{
		return false;
	}
	virtual ~comparestr(){}
	
};
	
typedef struct compara
{
	size_t pos;
	comparestr *comp;
} compara_t;

typedef vector<compara_t> compara_list_t;

struct strlt:public comparestr
{
		virtual bool operator () (const char *str1, const char *str2, size_t n)
	{
		//puts("lt");
		return strncmp(str1,str2,n) < 0;
	}
};

struct streq:public comparestr
{
		bool operator () (const char *str1, const char *str2, size_t n)
	{
		//puts("eq");
		return !strncmp(str1,str2,n);
	}
};

struct strgt:public comparestr
{
	
			bool operator () (const char *str1, const char *str2, size_t n)
	{
		//puts("gt");
		return strncmp(str1,str2,n)>0;
		
	}
};


struct strle:public comparestr
{
	
			bool operator () (const char *str1, const char *str2, size_t n)
	{
		//puts("gt");
		return strncmp(str1,str2,n)>=0;
		
	}
};

struct strge:public comparestr
{
	
			bool operator () (const char *str1, const char *str2, size_t n)
	{
		//puts("gt");
		return strncmp(str1,str2,n)>=0;
		
	}
};


struct strne:public comparestr
{
	
			bool operator () (const char *str1, const char *str2, size_t n)
	{
		//puts("gt");
		return strncmp(str1,str2,n);
		
	}
};



static streq _strcompare_default;

static compara _compara_default = 
{
	0,
	dynamic_cast<comparestr *> (&_strcompare_default)
};
	
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
                        :isdone(false),str(s),l(al),para(df)
        {}

        virtual void visit(char  *t)
        {


                if(!t) {
                        return;
                }
                 //isdone = true;
                 bool found = true;
                for (size_t ck = 0; ck < para.size(); ++ck) {
                //	puts("visit");
                
                        if( (*para[ck].comp)( t + l[para[ck].pos].pos,str +l[para[ck].pos].pos, l[para[ck].pos].len-1)) {
                                //isdone = true;
                              /*
                                printf("OK::comp:%s:%s:%d\n", 
                                str +l[para[ck].pos].pos,
                                t + l[para[ck].pos].pos,
                                 l[para[ck].pos].len-1);*/
                                 
                        }else{
                        	//isdone = false;
                        	//break;
                        	//printf("fial:%s-%s\n", str +l[para[ck].pos].pos, t + l[para[ck].pos].pos);
                        	
                        	/*
                        	printf("FAILcomp:%s:%s:%d\n", 
                                str +l[para[ck].pos].pos,
                                t + l[para[ck].pos].pos,
                                 l[para[ck].pos].len-1);
                                 break;
                                 */
                        	found = false;
                        }

                }
                
                if(found){
                	data.push_back(t);
                }

               // 	isdone = data.size();
        }

void print(void)
{
        //int m = l.back().len + l.back().pos;
        vector <char  *> ::const_iterator itr;
        for(itr = data.begin(); itr != data.end(); ++itr) {
                
                for(size_t i = 0; i < l.size(); ++i) {
                	if(i){
                		putchar('|');
                	}
                        printf(*itr +l[i].pos);
                }
                putchar('\n');
        }
}


        virtual bool done(void)
        {
                return isdone;
        }
        
        void reset(void)
        {
        	isdone = false;
        	data.clear();
        }
        
private:
        char  *str;
        vector <layout_t> l;
        vector <char  *> data;
         compara_list_t para;
        bool isdone;

};







const lo_t & decide_layout(lo_t &l,
                           const char *str,
                           const char separator);

const char *format_layout(char *ns, lo_t nl,
                          char *os, lo_t ol);

const char *do_layout(char *s, const lo_t &l);



const lo_t  combin_layout(const lo_t &a, const lo_t &b);
const char *trimsp(char *s);


#endif /*DATAFILE_H_*/
