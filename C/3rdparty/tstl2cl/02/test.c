/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-09 12:28:10
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "c_map.h"


static int values[] = 
{ 
	8,	/* 0 */
	3,	/* 1 */
	8,	/* 2 */
	4,	/* 3 */
	3,	/* 4 */
	8,	/* 5 */
	5,	/* 6 */
	43,	/* 7 */
	994,	/* 8 */
	32,	/* 9 */
	6,	/* 10 */
	9,	/* 11 */
	3,	/* 12 */
	7,	/* 13 */
	7,	/* 14 */
	32,	/* 15 */
	8,	/* 16 */
	2,	/* 17 */
	343 	/* 18 */
};

static int keys[] = 
{ 
	12,	/* 0 */	
	4,	/* 1 */	
	71,	/* 2 */
	2,	/* 3 */
	90,	/* 4 */
	99,	/* 5 */
	30,	/* 6 */
	61,	/* 7 */
	29,	/* 8 */
	84,	/* 9 */
	6,	/* 10 */
	97,	/* 11 */
	3,	/* 12 */
	8,	/* 13 */
	54,	/* 14 */
	78,	/* 15 */
	9,	/* 16 */
	16,	/* 17 */
	62,	/* 18 */
};

static c_pair pairs[] =
{
	{ &keys[0], &values[0] },
	{ &keys[1], &values[1] },
	{ &keys[2], &values[2] },
	{ &keys[3], &values[3] },
	{ &keys[4], &values[4] },
	{ &keys[5], &values[5] },
	{ &keys[6], &values[6] },
	{ &keys[7], &values[7] },
	{ &keys[8], &values[8] },
	{ &keys[9], &values[9] },
	{ &keys[10], &values[10] },
	{ &keys[11], &values[11] },
	{ &keys[12], &values[12] },
	{ &keys[13], &values[13] },
	{ &keys[14], &values[14] },
	{ &keys[15], &values[15] },
	{ &keys[16], &values[16] },
	{ &keys[17], &values[17] },
	{ &keys[18], &values[18] }
};


static inline int int_comparer(void * x, void * y)
{
    return *(int *)(x) - *(int *)(y);
}

int create_with_insert_unique(c_pmap thiz)
{
	int i = 0;

	for(i = 0; i < sizeof(keys)/sizeof(int); i++) {
		c_map_insert(thiz, &pairs[i]);
	}

	return 0;
}

int print_map(c_pmap pt)
{
	c_iterator iter = c_map_begin(pt);
	c_iterator end = c_map_end(pt);

	for(; !ITER_EQUAL(iter, end); ITER_INC(iter)) {
		printf( "key = %d, value = %d\n", \
				*(int *)((c_ppair)ITER_REF(iter))->first,\
				*(int *)((c_ppair)ITER_REF(iter))->second );
	}

	return 0;
}

int rprint_map(c_pmap pt)
{
	c_reverse_iterator iter = c_map_rbegin(pt);
	c_reverse_iterator end = c_map_rend(pt);

	for(; !ITER_EQUAL(iter, end); ITER_INC(iter)) {
		printf( "key = %d, value = %d\n", \
				*(int *)((c_ppair)ITER_REF(iter))->first,\
				*(int *)((c_ppair)ITER_REF(iter))->second );
	}

	return 0;
}

int test_clear(c_pmap thiz)
{
	c_iterator begin, end;
	c_reverse_iterator rbegin, rend;

	c_map_clear(thiz);
	begin = c_map_begin(thiz);
	end = c_map_end(thiz);
	rbegin = c_map_rbegin(thiz);
	rend = c_map_rend(thiz);

	printf("size = %d\n", c_map_size(thiz));
	
	if(ITER_EQUAL(begin, end) && ITER_EQUAL(rbegin, rend)) {
		printf("begin = end\nrbegin = rend\n");
	}
	
	//printf("keys[0] = %d\n", keys[0]);

	return 0;
}

int test_find_erase(c_pmap thiz)
{
	c_iterator target, end = c_map_end(thiz);

	target = c_map_find(thiz, &keys[0]);

	printf("key =  %d     value = %d\n", *(int*)(((c_ppair)ITER_REF(target))->first),\
										 *(int*)(((c_ppair)ITER_REF(target))->second) );


	int key = 97;

	target = c_map_find(thiz, &key);

	printf("key =  %d     value = %d\n", *(int*)(((c_ppair)ITER_REF(target))->first),\
										 *(int*)(((c_ppair)ITER_REF(target))->second) );

	key = 90;

	target = c_map_find(thiz, &key);

	printf("key =  %d     value = %d\n", *(int*)(((c_ppair)ITER_REF(target))->first),\
										 *(int*)(((c_ppair)ITER_REF(target))->second) );

}


int main(int argc, char **argv)
{
	c_map map;

	c_map_create(&map, int_comparer);

	create_with_insert_unique(&map);

	printf("------print_map-------\n");
	print_map(&map);
	printf("------rprint_map-------\n");
	rprint_map(&map);


	test_find_erase(&map);

	test_clear(&map);  //测试c_map_clear()

	c_map_destroy(&map);



	return 0;
}














