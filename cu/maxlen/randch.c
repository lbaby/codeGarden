/*
 * randch.c:to generate random lines
 *
 *  Created on: 2009-3-4
 *      Author: ly
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_CH (5000*1024) /*5000 line as default */
int main(int argc, char *argv[]) {
	const char chtable[] = {
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz1234567890"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz12345"
		"\n" };

	int max_ch = MAX_CH;
	if (argc >= 2) {
		max_ch = atoi(argv[1]);
	}

	if (max_ch <= 0) {
		max_ch = MAX_CH;
	}

	char ch = 0;
	int i = 0;

	size_t sl = strlen(chtable);

	srandom(time(0));
	while (i < max_ch) {
		ch = chtable[random() % sl];
		putchar(ch);
		++i;
	}

	if (ch != '\n') {
		putchar('\n');
	}
	return 0;
}
