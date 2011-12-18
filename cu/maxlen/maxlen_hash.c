/*
 * maxlen_hash.c:find  10  largest length string, hash method
 *
 *  Created on: 2009-3-4
 *      Author: ly
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_MAX 2048
#define BUF_MAX (LEN_MAX*2)
#define ONUM 10

#define RET_OK 0
#define RET_FAIL -1
#define RET_WARN_OVER_FLOW 0x2
#define RET_WARN_EXISTS 0x4

typedef struct line_info {
	const char *s; /*string */
	size_t line_no; /*line number of string*/
} line_info_t;


/* store the string to array[length]
 * hash algorithm : string length is the key
 * return value : RET_OK : string is accepted
 *                RET_FAIL: string can not be unacceptable(too large)
 *                RET_WARN_OVER_FLOW: string length is larger than  LEN_MAX  but accepted
 *                RET_WARN_EXISTS: some string in this length number had hold the hash position
 * */
int mark_line(line_info_t *line, const char *s, size_t len , size_t lno) {


	if (len > BUF_MAX - 2) {/* the last element used for error detecting */
		return RET_FAIL;
	}

	int ret = 0;
	if (len > LEN_MAX) {
		ret |= RET_WARN_OVER_FLOW;
	}

	if (line[len].s) {/* some line already hold the position   */
		/* just return a warinig*/
		ret |= RET_WARN_EXISTS;

	} else {/* a new length for this length number*/

		line[len ].s = s;
		line[len ].line_no = lno;
	}

	return ret;

}

int main(void)
{
	line_info_t li[BUF_MAX]  = {0};
	char *s = (char *)malloc(BUF_MAX*BUF_MAX * sizeof(char) );
	if(!s ){
		fprintf(stderr, "No enough memory , I'm exiting\n");
		exit(-1);
	}

	size_t p = 0;



	size_t lc = 0;
	/*first, the result data area used as a temporary buffer */
	while(fgets(s + p, BUF_MAX, stdin)){
		/*trim '\n' of line */
		size_t len = strlen(s+p);
		if(s[ p + len -1 ] == '\n'){
			s[p + len - 1] = 0;
			--len;
		}
		++lc;

		int ret = mark_line(li, s +p, len, lc);

		/* second, the temporary buffer will be stored if it's valid */
		if( (ret == RET_OK )|| (! (RET_WARN_EXISTS&ret))){
			/*input should be store*/
			p += len +1;
			if(p + BUF_MAX >  (BUF_MAX*BUF_MAX * sizeof(char)) ){
				fprintf(stderr, "invalid input , exceed  MAX buffer length,line:%u\n", lc);
				exit(-1);
			}
		}else {
			if(ret == RET_FAIL){
				fprintf(stderr, "invalid input , exceed  MAX buffer length,line:%u\n", lc);
				exit(-1);
			}
		}



	}

	int i = 0;
	int n =0;
	for (i =BUF_MAX-2  ; i >= 0; --i ){
		if(li[i].s){
		printf("%d:%u:%s\n", i, li[i].line_no , li[i].s);
		++n;
		if(n >= ONUM){
			break;
		}
		}

	}

	return 0;

}



