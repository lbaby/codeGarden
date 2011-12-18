
#include <datafile.h>

comparestr &what_op(char *method)
{
        static streq eq;
        static strlt lt;
        static strgt gt;
        static strge ge;
        static strle le;
        static strne ne;

        if(!strcmp(method, "eq")) {
                return eq;
        } else if (!strcmp(method, "lt")) {
                return lt;
        } else if (!strcmp(method, "ne")) {
                return ne;
        } else if (!strcmp(method, "ge")) {
                return ge;
        } else if (!strcmp(method, "gt")) {
                return gt;
        } else if (!strcmp(method, "le")) {
                return le;
        } else {
                string e;
                e="can not find:";
                e+= method;
                e+="may be a bad operator";
                throw invalid_argument(e);
        }
}

void usage(void)
{
        printf (
                "used to search data file that spearated by '|'\n"
                "usage:\n"
                "    dfdemo file field operator data \n"
                "eg:dfdemo vpmn.dat 2 gt 200706\n"
                "the line on the last means that you search vpmn.dat,\n"
                "you want the 2nd data field greater than 200706 \n"
                "then ,you should input the key data with stardand input \n"
        );
}

int main(int argc, char *argv[])
{
        if(argc < 2) {
                usage();
                exit(0);
        }
        
        if( ((argc - 2) %3 )  && (argc !=2)) {
                usage();
                exit(0);
        }
        datafile adat(argv[1]);
        char s[1024] = {0};
        adat.load();
        compara_list_t chkrule;
        compara base = {
                               0,
                               &what_op("eq")
                       };

        chkrule.push_back(base);

        int n = 0;
        for (n = 2 ; n < argc; ) {
                compara comp;
                comp.pos = atoi(argv[n]) -1;
                comp.comp = &what_op(argv[n+1]);
                strcpy(s + adat.get_layout()[comp.pos].pos, argv[n+2]);
                chkrule.push_back(comp);
                n += 3;
        }




        find_visitor<char> f(s,adat.get_layout(), chkrule);
        char buf[1024];
        while(fgets(buf, sizeof(buf), stdin)) {
                f.reset();
                buf[strlen(buf) -1] = '\0';
                if(!buf[0]){
                	continue;
                }
                trimsp(buf);
                strcpy(s, buf);
                adat.find(s).accept(f);
                f.print();
        }
        

        
        return 0;

}




