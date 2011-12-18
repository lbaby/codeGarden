/*
 * sieve.c
 *
 *  Created on: 2009-4-24
 *      Author: of
 */

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef uint32_t mygoal_t ;
#define NUM_PER_BYTE 20  /* 20 number in one byte */
#define BIT_PER_BYTE 8
#define NUM_WIDTH 4 /* 4 number per line */
#define INVALID_BIT_ID  ((size_t)-1)


		/*
		 * offset:
		 * 3=1 + 2
		 * 7=3 + 4
		 * 9=7 + 2
		 * 11=9 + 2
		 * and so on
		 */
const uint8_t offset_table[BIT_PER_BYTE]={
		2,4,2,2,
		2,4,2,2
};

/* value for 1-20 with compress :*/
const mygoal_t bit_value_table [BIT_PER_BYTE] ={
	1,3,7,9,11,13,17,19
};


/* a bit location map to byte for 20 */
const size_t bit_location [NUM_PER_BYTE ] ={
INVALID_BIT_ID,0,INVALID_BIT_ID,1,INVALID_BIT_ID,INVALID_BIT_ID,INVALID_BIT_ID,2,INVALID_BIT_ID,3,
INVALID_BIT_ID,4,INVALID_BIT_ID,5,INVALID_BIT_ID,INVALID_BIT_ID,INVALID_BIT_ID,6,INVALID_BIT_ID,7
};


const mygoal_t goal_default = (1000*1000*1000); /*  one billion as default */
const size_t page_size = (1024*4-16);
const uint8_t mask_table [8] ={
		0x1, 0x2, 0x4,0x8,0x10,0x20,0x40,0x80
};


/*
 * memory :
 * entry:
 * ------
 * e -> page 1
 * e -> page 2
 * e -> page 3
 *  ...
 * e -> page total
 *
 * ------
 * page is  array of byte
 */

/*
 * the bit map of first byte:
 * 0 0 0 1 0   0   0
 * ------------------
 * 1 3 7 9 11 13 17
 */

/* To allocate many memory page , so that I can get a BIG one in total */
typedef struct mem_entry {
	uint8_t **entry;  /* Bit map page  entry */
	size_t size;
}mem_entry_t;


/*
 * The  Bit can be located uniquely by following information :
 * entry :identify the page(a byte array)
 * byte : byte in the page
 * bit: bit in the byte
 * bit_value: the value 1-20 according to bit_id and so on
 */
typedef struct bit_addr{
	size_t entry_id ; /* page entry in the memory  (0 - page_total-1)*/
	size_t byte_id ;  /* byte in the array ( 0 - page_size -1) */
	size_t bit_id ;   /* bit in the byte (0 - sizeof(uint8_t)*8-1)*/

	/*
	 * used to store raw value instead of  a bit offset
	 * and do addition
	 */
	size_t bit_value;
}bit_addr_t;

/*
 * set a bit address from  a number
 *
 * number can be generated from bit location:
 * number = entry_id * page_size *NUM_PER_BYTE
 * + byte_id *NUM_PER_BYTE
 * + bit_value_table[bit_id]
 */
#ifdef set_addr
#undef set_addr
#endif



#define set_addr(addr_, prod_)\
	do{\
		(addr_).entry_id = (prod_ ) /  (page_size * NUM_PER_BYTE);\
		(addr_).byte_id  = ( (prod_)  % (page_size * NUM_PER_BYTE) )  / NUM_PER_BYTE;\
		(addr_).bit_id   = bit_location[ (addr_).bit_value = ( (prod_)%NUM_PER_BYTE ) ];\
	}while(0)




#ifdef add_addr
#undef add_addr
#endif
/* add right address to left one , with carry */
#define add_addr(lv_, rv_)\
	do{\
		(lv_).bit_value += (rv_).bit_value;\
		if((lv_).bit_value >= NUM_PER_BYTE){\
			(lv_).bit_value -= NUM_PER_BYTE;\
			(lv_).byte_id ++;\
			if( (lv_).byte_id >= (page_size )){\
				(lv_).byte_id -= (page_size );\
				(lv_).entry_id ++;\
			}\
		}\
		(lv_).bit_id = bit_location[ (lv_).bit_value];\
		(lv_).byte_id += (rv_).byte_id;\
		if( (lv_).byte_id >= (page_size )){\
			(lv_).byte_id -= (page_size );\
			(lv_).entry_id ++;\
		}\
		if((rv_).entry_id){(lv_).entry_id += (rv_).entry_id;}\
	}while(0)


#define next_addr(lv_)\
	do{\
		(lv_).bit_id += 1;\
		if((lv_).bit_id >= (BIT_PER_BYTE)){\
			(lv_).bit_id -= (BIT_PER_BYTE );\
			(lv_).byte_id ++;\
			if( (lv_).byte_id >= (page_size )){\
				(lv_).byte_id -= (page_size );\
				(lv_).entry_id ++;\
			}\
		}\
	}while(0)


/* get entry's memory and zero it */
mem_entry_t *make_entry(mem_entry_t *m, size_t page_total)
{
	m->entry =  (uint8_t **)malloc(page_total * sizeof(uint8_t *));
	if(!m->entry){
		return NULL;
	}

	size_t  i = 0;
	for(i=0; i < page_total; ++i){
		m->entry[i] = (uint8_t *)malloc(page_size*sizeof(uint8_t));
		if(!m->entry[i]){
			break;
		}
		memset(m->entry[i], 0, page_size*sizeof(uint8_t));
	}

	if( i != page_total ){/* no enough memory */
		while(i > 0){
			--i;
			free(m->entry[i]);
		}

		free(m->entry);

		return NULL;
	}

	m->size = page_total;
	return m;
}

void free_entry(mem_entry_t *m)
{
	size_t i  = 0;
	for( i = 0; i  < m->size ; i++){
		free(m->entry[i]);
	}

	free(m->entry);

}

mem_entry_t *sieve(mem_entry_t *m, mygoal_t goal)
{

	mygoal_t s_goal = (mygoal_t)sqrt(goal);

	size_t lbit_id = 1;
	mygoal_t lfactor;
	for(lfactor = 3; lfactor <= s_goal +1 ;){
		/*
		 * multiplication can implement as addition :
		 * 7*3 = (3+4)*3
		 * = 3*3 + 4*3
		 *
		 */

		mygoal_t prod = lfactor * lfactor;
		bit_addr_t cur_addr={0};

		/* set current address in the entry*/
		set_addr(cur_addr, prod);

		/* build a addr_factor_table table for addition */
		bit_addr_t addr_factor_table [4] = {0};

		bit_addr_t bit_addr_by_2 = {0};
		mygoal_t prod_by2 = lfactor *2;
		set_addr(bit_addr_by_2 , prod_by2);

		bit_addr_t bit_addr_by_4 = {0};
		mygoal_t prod_by4 = lfactor *4;
		set_addr(bit_addr_by_4 , prod_by4);

		addr_factor_table[ 2 -1 ] = bit_addr_by_2;
		addr_factor_table[ 4 -1 ] = bit_addr_by_4;

		mygoal_t rfactor = lfactor;
		size_t rbit_id = lbit_id;
		mygoal_t rgoal = goal/lfactor;

		while(rfactor <= rgoal ){
			uint8_t *non_prime_byte  =   m->entry [cur_addr.entry_id] + cur_addr.byte_id;
			if(cur_addr.bit_id == INVALID_BIT_ID){
				fprintf(stderr,"panic:fatal: factor=%llu \n", rfactor);
				exit(1);
			}


			if(!(mask_table[cur_addr.bit_id] & *non_prime_byte)){/* the bit not set yet */
				/* let's set the bit */
				*non_prime_byte |= 	mask_table[cur_addr.bit_id];

			}

			/*next factor */
			rfactor += offset_table[rbit_id];


			/* next address */
			/*
			 * 3*7 = 3*(3 + 4)
			 *     = 3*3 + 4*3
			 * with our bit address algorithm,
			 *  I can evaluate result of multiple with
			 *  address addition
			 */

			add_addr(cur_addr, addr_factor_table[offset_table[rbit_id] -1 ]);
			rbit_id++;
			if(rbit_id == BIT_PER_BYTE){
				rbit_id = 0;
			}

		}
		lfactor += offset_table[lbit_id++];
		if(lbit_id == BIT_PER_BYTE){
			lbit_id = 0;
		}

	}

}



void print_prime(mem_entry_t *m, mygoal_t goal)
{
	size_t width= 0;
	mygoal_t g = goal;
	while(g){
		width ++;
		g/=10;
	}

	char format[32] ;
	sprintf(format, "%%%ullu "); /* %8llu" */

	/* how many primes in this line */
	size_t np = 1;
	mygoal_t first_prime = 2;
	printf(format, first_prime);

	size_t j = 0;
	mygoal_t i = 3;/* from 3 7 9 ... 11 ... */
	bit_addr_t cur_addr;
	set_addr(cur_addr, i);

	while (i <= goal) {
		uint8_t *prime_byte = m->entry[cur_addr.entry_id] + cur_addr.byte_id;

		if (!(mask_table[cur_addr.bit_id] & *prime_byte)) {/* we found a prime! */
			printf(format, i);
			np++;
			if (np == NUM_WIDTH) {
				np = 0;
				putchar('\n');
			}
		}
		/*next number */
		i += offset_table[cur_addr.bit_id];
		/* next address */

		next_addr(cur_addr);
	}
	if (np){
		putchar('\n');
	}


}

int main(int argc, char *argv[])
{


	mygoal_t mygoal =0;
		mygoal = goal_default;
	int is_print = 0;

	if( argc == 2){
		if(argv[1][0] == 'p'){
			is_print  = 1;
		}else if(argv[1][0] == 'n'){
			is_print  = 0;
		}else{
			printf("usage:\n"
					"\t %s p\n"
					"\t %s prime_range p|n\n",argv[0],argv[0]);
			exit(1);
		}

	}else if(argc == 3 ){
		mygoal = atoll(argv[1]);
		if(mygoal <= 0){
			fprintf(stderr, "invalid argument:%s\n", argv[1]);
			exit(1);
		}

		if(argv[2][0] == 'p'){
			is_print  = 1;
		}else if(argv[2][0] == 'n'){
			is_print  = 0;
		}else{
			printf("usage:\n"
					"\t %s p\n"
					"\t %s prime_range p|n\n",argv[0],argv[0]);
			exit(1);
		}

	}else{
		printf("usage:\n"
				"\t %s p\n"
				"\t %s prime_range p|n\n",argv[0],argv[0]);
		exit(1);
	}

	size_t entry_size = mygoal / (page_size * NUM_PER_BYTE)  + ( mygoal%page_size != 0);

	mem_entry_t m;
	if(make_entry(&m,entry_size) == NULL){
		fprintf(stderr, "no enough memory\n");
		exit(1);
	}


	sieve(&m, mygoal);
	if(is_print){
		print_prime(&m,mygoal);
	}
	free_entry(&m);

	return 0;
}

