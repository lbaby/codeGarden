/*
 * maxlen_seq.c: find  10 largest length string, sequence search method
 *
 *  Created on: 2009-3-4
 *      Author: ly
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_MAX 2048
#define BUF_MAX (LEN_MAX*2)

#define RET_OK 0
#define RET_WARN_EXISTS 0x4
#define TOP_NUM 10

typedef struct line_info {
	const char *s; /*string */
	size_t len; /* length of string */
	size_t line_no; /*line number of string*/
} line_info_t;

/* store the string to array[length]
 * hash algorithm : string length is the key
 * return value : RET_OK : string is accepted
 *                RET_WARN_EXISTS: some string in this length number had hold the hash position
 * */
int mark_line(line_info_t *line, const char *s, size_t len, size_t lno) {

	int ret = 0;
	int i = 0;
	line_info_t *min_line = line;

	/* let's look for a min length string */
	for (i = 0; (i < TOP_NUM) && line[i].s; ++i) {
		if (len == line[i].len) {
			/* do not accept a duplicate length */
			ret |= RET_WARN_EXISTS;
			break;
		} else if ((line[i].len < min_line->len)) {
			min_line = line + i;
		}

	}


	if (ret == RET_OK) {
		min_line = line[i];
		min_line->s = s;
		min_line->len = len;
		min_line->line_no = lno;
	}
	return ret;
}

int main(void) {
	line_info_t li[TOP_NUM] = { 0 };
	char *s = (char *) malloc(BUF_MAX*BUF_MAX * sizeof(char) );
	if(!s ) {
		fprintf(stderr, "No enough memory , I'm exiting\n");
		exit(-1);
	}

	size_t p = 0;

	size_t lc = 0;
	/*first, the result data area used as a temporary buffer */
	while(fgets(s + p, BUF_MAX, stdin)) {
		/*trim '\n' of line */
		size_t len = strlen(s+p);
		if(s[ p + len -1 ] == '\n') {
			s[p + len - 1] = 0;
			--len;
		}
		++lc;

		int ret = mark_line(li, s +p, len, lc);

		/* second, store the valid string from input */
		if( ret == RET_OK ) {
			/*input should be store*/
			p += len +1;
			if(p + BUF_MAX> (BUF_MAX*BUF_MAX * sizeof(char)) ) {
				fprintf(stderr,"invalid input , exceed  MAX buffer length,line:%u\n", lc);
				exit(-1);
			}
		}

	}

	int i = 0;
	int n =0;
	line_info_t * prev_max_line = 0;
	line_info_t * cur_max_line = 0;

	/*print the array in reverse length order */
	for (i =0  ; (i <  TOP_NUM )&& li[i].s; ++i ){
		int x = 0;
		for(x  = 0;  (x < TOP_NUM ) && li[x].s ; ++x){

			if(cur_max_line){
			if(cur_max_line->len > li[x].len){
				continue;
			}
			}
			if(prev_max_line){
			if(li[x].len > prev_max_line->len){
				continue;
			}
			}
			cur_max_line = li +x;
		}

		if(!cur_max_line)
		{
			break;
		}

		printf("%d:%u:%s\n", cur_max_line->len, cur_max_line->line_no , cur_max_line->s);

		prev_max_line = cur_max_line;
		cur_max_line = 0;

	}

	return 0;

}

