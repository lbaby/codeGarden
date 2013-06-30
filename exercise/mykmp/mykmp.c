#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define psn(n)\
	do{\
		int __N_SP = 0;\
		while(__N_SP ++< (n)){\
			putchar(' ');\
		}\
	}while(0)

/*
 * mykmp.c
 *
 *  Created on: 2009-8-18
 *      Author: of
 */

size_t kmp_search(char *s, char *p, size_t *idx) {
	size_t sl = strlen(s);
	size_t pl = strlen(p);
	size_t ml = 0;

	size_t pos = 0;
	while (pos <= sl - pl ) {/* do KMP match */
		while (s[pos] == p[ml]) { /* if match , update the current match length */
//			puts(s);
//			psn( (pos-ml ));
//			puts(p);
//			printf("%d:%d\n\n",pos, ml );
			ml++;
			pos++;

			if (ml == pl) {
				goto match;
			}
		}
		/* encounter a no match
		 * so , what's the current match length?
		 * just ask index
		 * */

		while (ml && (p[pos] != p[ml + 1])) {
			ml = idx[ml];
		}
		if(ml){
			ml++;
		}


		pos++;

	}

	return -1;
	match: return pos - pl;

}

size_t *kmp_idx(size_t *idx, char *p) {
	size_t pl = strlen(p);

	idx[0] = 0;
	size_t pos = 1;
	size_t ml = 0;
	while (pos < pl) {
		/*
		 * so , let's  look for a prefix as sub string
		 */
		if (p[ml] == p[pos]) {
			ml++;

		} else {

			/*
			 * if mismatch , look for another bounder
			 * is current match the  previous match pattern?
			 */
			do{
				ml = idx[ml - 1];
			}
			while ( ( ml > 0) && (  p[pos] != p[ml   ] ) );



		}
		idx[pos++] = ml;

	}

	return idx;

}

void print_idx(char *s,size_t *idx, size_t n) {
	size_t i = 0;
	while (i < n) {

		printf("%c:%d\n", s[i],idx[i]);
		i++;
	}
}

int main(int argc, char * argv[])

{

	//	char *s = "cmp_annual_conference_announce";
	//	char *p = "announce";

	char *s = argv[2];
	char *p = argv[1];

	size_t *idx = (size_t *) malloc(strlen(p) * sizeof(int));

//	kmp_idx(idx, p);
	print_idx(p,idx, strlen(p));
	size_t pn = kmp_search(s, p, idx);
	if(pn != (size_t ) -1){
	printf("%d:%s\n", pn, pn + s);
	}
	free(idx);

}
