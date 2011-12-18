
//test code for base kits
#include "toolkits.h"


int main(void)
{
        lo_t l ;
        pos_info_t p[255] = {0};

        char buf[1024];
        while (fgets(buf ,sizeof(buf), stdin )) {
                parse_layout(&l, string(buf));
                size_t n  = 0;
                while (n < l.size()) {
                        printf("%d-%d\n", l[n].pos, l[n].len);
                        ++n;
                }


        }
        lo_to_pkey(p, l);

        size_t i = 0;
        while (p[i].len) {
                printf("%d:%d:%d\n", p[i].tag_len, p[i].pos, p[i].len);
                ++i;
        }

        char *s="1234567890   ";

        char d[255] = {0};

        extract_key(d, s, p);

        printf("^%s$\n",d );


}
