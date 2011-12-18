#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct footprint {
	size_t x; /* X coordinate in matrix */
	size_t y; /* Y coordinate */
	size_t cnt;/* current count for padding */
} footprint_t;

/* processing work path padding from left to right(lr)
 * return value : the count of pad action
 * */
int pad_lr(size_t **matrix, footprint_t * cur_foot, size_t n) {
	int pad_cnt = 0;

	while (cur_foot -> y < n - 1) {
		if (matrix[cur_foot->x][cur_foot -> y + 1]) {
			/* the position has been padded ,and pad cycle will end now */
			break;
		}
		++cur_foot -> y;
		++cur_foot -> cnt;
		matrix[cur_foot->x][cur_foot -> y] = cur_foot -> cnt;
		++pad_cnt;
#ifdef DEBUG_PRINT_L3
		fprintf(stderr, "pad_lr:pad m[%u][%u] with %u\n"
				,cur_foot->x, cur_foot->y, cur_foot->cnt );
#endif
	}

	return pad_cnt;

}

/* processing work path padding from up to down(ud)
 * return value : the count of pad action
 * */
int pad_ud(size_t **matrix, footprint_t * cur_foot, size_t n) {
	int pad_cnt = 0;

	while (cur_foot -> x < n - 1) {
		if (matrix[cur_foot->x + 1][cur_foot -> y]) {
			/* the point has been padded ,and pad cycle will end now */
			break;
		}
		++cur_foot -> x;
		++cur_foot -> cnt;
		matrix[cur_foot->x][cur_foot -> y] = cur_foot -> cnt;
		++pad_cnt;
#ifdef DEBUG_PRINT_L3
		fprintf(stderr, "pad_ud:pad m[%u][%u] with %u\n"
				,cur_foot->x, cur_foot->y, cur_foot->cnt );
#endif
	}

	return pad_cnt;

}

/* processing work path padding from right to left  (rl)
 * return value : the count of pad action
 * */
int pad_rl(size_t **matrix, footprint_t * cur_foot, size_t n) {
	int pad_cnt = 0;

	while (cur_foot -> y > 0) {
		if (matrix[cur_foot->x][cur_foot -> y - 1]) {
			/* the point has been padded ,and pad cycle will end now */
			break;
		}
		--cur_foot -> y;
		++cur_foot -> cnt;
		matrix[cur_foot->x][cur_foot -> y] = cur_foot -> cnt;
#ifdef DEBUG_PRINT_L3
		fprintf(stderr, "pad_rl:pad m[%u][%u] with %u\n"
				,cur_foot->x, cur_foot->y, cur_foot->cnt );
#endif
		++pad_cnt;
	}

	return pad_cnt;

}

/* processing work path padding from down to up(du)
 * return value : the count of pad action
 * */
int pad_du(size_t **matrix, footprint_t * cur_foot, size_t n) {
	int pad_cnt = 0;


	while (cur_foot -> x > 0) {
		if (matrix[cur_foot->x - 1][cur_foot -> y]) {
			/* the point has been padded ,and pad cycle will end now */
			break;
		}
		--cur_foot -> x;
		++cur_foot -> cnt;
		matrix[cur_foot->x][cur_foot -> y] = cur_foot -> cnt;
		++pad_cnt;
#ifdef DEBUG_PRINT_L3
		fprintf(stderr, "pad_du:pad m[%u][%u] with %u\n"
				,cur_foot->x, cur_foot->y, cur_foot->cnt );
#endif
	}

	return pad_cnt;

}

/* pad a matrix
 * action:
 * 00 LR-> 01
 * ^         |
 * |        ud
 * du        |
 * 10 <- rl-11
 * return value : dummy
 *
 */

int pad_matrix(size_t **matrix, footprint_t * cur_foot, size_t n) {
	int p = 1;/* there was a pad action already ^_^*/
	while (p) {/* do pad action until there is no pad can be done*/

		p = 0;
		p += pad_lr(matrix, cur_foot, n);
		p += pad_ud(matrix, cur_foot, n);
		p += pad_rl(matrix, cur_foot, n);
		p += pad_du(matrix, cur_foot, n);

	}

	return 0;
}

int del_matrix(size_t **matrix, size_t n) {
	size_t x = 0;
	while (x < n) {
		free(matrix[x++]);
	}

	free(matrix);

	return 0;
}
/* allocate  and initialize the matrix
 * return value : -1  no enough memory
 *                 0 success
 */

int mk_matrix(size_t ***matrix, size_t n) {
	*matrix = (size_t **) malloc(n * sizeof(size_t **));
	if (!*matrix) {
		return -1;
	}

	size_t **m = *matrix;
	size_t x = 0;

	while (x < n) {
		m[x] = (size_t *) malloc(n * sizeof(size_t));
		if (!m[x]) {
			if (x) {
				/* x array */
				del_matrix(m, x);
			}

			return -1;
		}
		memset(m[x], 0, n * sizeof(size_t));
		++x;

	}

	return 0;
}


/*
 * print the matrix in a beautiful style
 * return value : dummy
 */
int print_matrix(size_t **matrix, size_t n) {
	size_t total = n * n;
	size_t num_len = 0;
	while (total) {
		total /= 10;
		++num_len;
	}

	/* make output string format first */
	char str_format[64];
	sprintf(str_format, "%%%uu ", num_len);
	size_t x = 0;
	while (x < n) {
		size_t y = 0;
		while (y < n) {
			printf(str_format, matrix[x][y]);
			++y;
		}
		putchar('\n');

		++x;
	}

	return 0;

}

int main(void) {

	char buf[64];
	while (fgets(buf, sizeof(buf) , stdin)) {
		size_t **m;
		int n = atoi(buf);

		if (n <= 0) {
			fprintf(stderr, "Invalid input:%s", buf);
			continue;
		}

		if (mk_matrix(&m, n) < 0) {
			fprintf(stderr, "Can not make matrix with input :%s\n", buf);
			continue;
		}
		footprint_t f;
		f.x = 0;
		f.y = 0;
		f.cnt = 1;
		m[0][0] = 1;

		pad_matrix(m, &f, n);
		print_matrix(m, n);
		del_matrix(m, n);
	}

}

