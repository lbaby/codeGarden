#include <htable.h>
#include <string.h>
#include <time.h>
#include <string>







#ifdef _HTABLE_MAIN

int main(void)
{
        htable<char>  h(120000);
        layout_t l1 ;
        layout_t l2 ;
        l1.pos = 0;
        l1.len = 6;
        l2.pos = 6;
        l2.len = 3;

        vector<layout_t> ll;
        ll.push_back(l1);
        ll.push_back(l2);

        h.set_layout(ll);




        int i ;

        char l[9] = {
                            't','t','\0','t','0','\0', '^','_','^'};
        find_visitor<char> f(l, ll);
        for( i = 0 ; i < 10000; i ++) {


                sprintf(l, "%05d", i);
                h.insert(l, ll);
                hnode<char> hn(l);
                hnode<char> &p = h.find(hn);
                p.accept(f);
        }

        //f.print();

        /*
        	layout_t l3 ;
        	layout_t l4 ;
        	l3.pos = 0;
        	l3.len = 5;
        	l4.pos = 5;
        	l4.len = 3;
        	
        	vector<layout_t> la;
        	la.push_back(l3);
        	la.push_back(l4);
        	char l[9] = {
        		't','t','t','t','t','t', '^','_','^'};
         
        		for( i = 0 ; i < 10000; i ++){
        			sprintf(l, "%04d", i);
        	h.insert(l, la);
        		hnode<char> hn(l);
        	hnode<char> &p = h.find(hn);
        		p.accept(f);
        	}
        	//if(f.done()){
        		f.print();
        	//}
        	 * 
        	/*
        	 */

        htable<char>  hh(10000);
        layout_t l3;
        layout_t l4;
        l3.pos = 0;
        l3.len = 7;
        l4.len  = 7;
        l4.pos = 7;
        vector<layout_t> lb;
        lb.push_back(l3);
        lb.push_back(l4);

        hh.set_layout(lb);


        hh = h;

        find_visitor<char> ff(l, lb);
        for( i = 0 ; i < 10000; i ++) {

                sprintf(l, "%05d", i);
                hnode<char> hn(l);
                hnode<char> &p = hh.find(hn);
                p.accept(ff);

        }

        ff.print();



}

#endif
