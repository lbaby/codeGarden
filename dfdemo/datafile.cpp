
#include <datafile.h>



void datafile::load(void)
{
        struct stat dstat;

#ifdef DYNAMIC_LOAD

        stat(fname.c_str(), &dstat);
        isloaded = dstat.st_mtime <= load_time;
        delete data;
        data = 0;

#endif

        if(isloaded) {
                return;
        }

        stat(fname.c_str(), &dstat);

        FILE *fp = fopen(fname.c_str(), "rt");
        if(!fp) {
                string e;
                e="can not open" + fname;
                throw runtime_error(e);
        }

        char buf[1024]= {0};

        while(fgets(buf, sizeof(buf), fp)) {
                if(buf[0] != '#') {
                        break;
                }
        }
        //let's decide the data layout
        //oo:estimate the lines in the file

        size_t lsz = strlen(buf);
        size_t lcount = 1;
        if(lsz){
         lcount = (size_t)(dstat.st_size/lsz);//
        }
        

        size_t len = strlen(buf);
        if(buf[len -1] == '\n') {
                buf[len-1] = '\0';
        }

        data = new htable<char>(lcount);
        decide_layout(l, buf,separator);
        data->set_layout(l);

        do {
                if(buf[0] == '#') {
                        continue;
                }

                size_t len = strlen(buf);
                if(buf[len -1] == '\n') {
                        buf[len-1] = '\0';
                }
                lo_t nl;
                decide_layout(nl, buf,separator);
                do_layout(buf,nl);
                trimsp(buf);
                /*
                if(nl.size() > l.size() ) {
                        //do not accept different format in one file
                        throw runtime_error("invalid file format");
                }*/

                if(nl > l) {
                        htable<char> *nd = new htable<char>(lcount);
                        char xbuf[1024] = {0};
                        
                        lo_t cl = combin_layout(nl, l);
                        format_layout(xbuf,cl, buf, nl);
                        nd->set_layout(cl);
                        *nd = *data;
                        l = cl;
                        delete data;
                        data = nd;
                        data->insert(hnode<char>(xbuf));

      
                } else if(nl < l) {
                        char nbuf[1024] = {0} ;
                        format_layout(nbuf, l, buf,nl);
                        data->insert(hnode<char>(nbuf));
                                       } else {
                        data->insert(hnode<char>(buf));
                }
                memset(buf, 0, sizeof(buf));

        } while(fgets(buf, sizeof(buf), fp));

        //before we store the data
        //we must set the layout


        fclose(fp);
#ifdef DYNAMIC_LOAD
        load_time  = dstat.st_mtime  ;
#endif
        isloaded = true;


}



size_t proper_layout(size_t n)
{
        size_t i;
        for ( i = 0; i < num_layout; i ++) {
                if(layout_list[i] >= n) {
                        break;
                }
        }

        if(i == num_layout) {
                throw invalid_argument("can not find a proper layout:please enlarge your max layout limit");
        }

        return layout_list[i];
}

const char *trimsp(char *s)
{
        char *nsp =NULL;
        char *rs =s;
        const char sp=' ';
        while(*s ) {
                if(*s == sp) {
                        if(!nsp) {
                                nsp = s;
                        }
                } else {
                        nsp = NULL;
                }
                ++s;
        }

        if(nsp) {
                *nsp= '\0';
        }

        return rs;
}

const lo_t  combin_layout(const lo_t &a, const lo_t &b)
{
        lo_t l;
        if(a.size() > b.size()) {
                l = a;
                for (size_t i = 0 ; i < b.size() ; i ++) {
                        if(l[i].len < b[i].len) {
                                l[i].len = b[i].len;
                        }
                        if(l[i].pos < b[i].pos) {
                                l[i].pos = b[i].pos;
                        }
                }
                	
        } else {
        	
                l = b;
                for (size_t i = 0 ; i < a.size() ; i ++) {
                        if(l[i].len < a[i].len) {
                                l[i].len = a[i].len;
                        }
                        if(l[i].pos < a[i].pos) {
                                l[i].pos = a[i].pos;
                        }
                }
        }

        return l;


}

size_t findchr(const char *s, char c, size_t pos= 0)
{
        size_t l = 0;
        while(*(s+pos +l)) {
                if(*(s + pos +l) == c) {
                        break;
                }
                ++l;
        }

        return pos +l;

}


const char *format_layout(char *ns, lo_t nl,
                          char *os, lo_t ol)
{

        for(size_t i = 0 ; i < ol.size(); i++) {
                memcpy(ns+nl[i].pos, os + ol[i].pos, ol[i].len);
        }

	return ns;
}

const char *do_layout(char *s, const lo_t &l)
{
        for (size_t i = 0; i < l.size(); i++) {
                *(s + l[i].pos + l[i].len -1 ) = '\0';
        }
        return s;
}


const lo_t & decide_layout(lo_t &l,
                           const char *str,
                           const char separator='|')
{
        size_t len = strlen(str);
        layout lo;
        size_t pos = 0;

        do {

                lo.pos = pos;
                size_t np =findchr(str,separator, pos);
                lo.len = np -pos  +1 ;
                pos = np + 1;
                l.push_back(lo);
        } while(pos < len);

        if(len == pos) {
                lo.pos = pos;
                lo.len = pos -len +1 ;
                l.push_back(lo);
        }


        return l;

}




#ifdef _DATAFILE_MAIN

int main(void)
{
        datafile adat("vpmn.dat");
        char s[1024] = {0};
        adat.load();
        compara_list_t chkrule;
        streq eq;
        strlt lt;
        strgt gt;
         compara p0 = {
        	0,
        	dynamic_cast<comparestr *> (&eq)
        };
        
          compara p1 = {
        	1,
        	dynamic_cast<comparestr *> (&lt)
        };
        
        
            compara p2 = {
        	2,
        	dynamic_cast<comparestr *> (&gt)
        };
        
                    compara p3 = {
        	5,
        	dynamic_cast<comparestr *> (&gt)
        };
        
                            compara p4 = {
        	6,
        	dynamic_cast<comparestr *> (&lt)
        };
        
        
        
        chkrule.push_back(p0);
        chkrule.push_back(p1);
        chkrule.push_back(p2);
        chkrule.push_back(p3);
        chkrule.push_back(p4);
        
        strcpy(s + adat.get_layout()[0].pos, "13607612280");
        strcpy(s + adat.get_layout()[1].pos, "SG");
        strcpy(s + adat.get_layout()[2].pos, "D");
        strcpy(s + adat.get_layout()[5].pos, "20070803235959");
        strcpy(s + adat.get_layout()[6].pos, "20070803235959");
        
        printf("%d:%d\n", adat.get_layout()[1].pos, adat.get_layout()[2].pos);
        find_visitor<char> f(s,adat.get_layout(), chkrule);
        
        adat.find(s).accept(f);
        f.print();
        
        /*printf("search:");
        while(fgets(s, sizeof(s), stdin)) {
                adat.load();
                printf("search:");
                if(s[strlen(s) -1] == '\n') {
                        s[strlen(s) -1] = '\0';
                }
                find_visitor<char> f(s,adat.get_layout());
                adat.find(s).accept(f);
                f.print();
                printf("search:");
                memset(s, 0 , sizeof(s));
        }
*/

}



#endif
