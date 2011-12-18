/*
 * pep.c:print environment  variable "PATH" 's  content
 *       this code can work in win32 and *NIX with different compile option
 *
 *  Created on: 2009-2-26
 *      Author: ly
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_ENV_VAR "PATH"
#define NEW_PATH_DELIMITER '\n'

#ifdef WIN32
#define PATH_DELIMITER ';'
#else
#define PATH_DELIMITER ':'
#endif

/*
 * replace the character oc to nc in string s
 * return value:pointer address of s
 */
char * replace_ch(char * s, char oc, char nc) {
	char * bs = s;
	while (*s) {
		if (*s == oc) {
			*s = nc;
		}
		++s;
	}

	return bs;
}

int main(void) {
	char *pe = getenv(MY_ENV_VAR);
	char *vpe = malloc(strlen(pe) + 1);
	if (!vpe) {
		fprintf(stderr, "No enough memory, I'm exiting");
		exit(1);
	}
	strcpy(vpe, pe);

	replace_ch(vpe, PATH_DELIMITER,NEW_PATH_DELIMITER);
	printf("%s\n", vpe);
	free(vpe);
	return 0;
}

