/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-10 02:33:44
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "c_map.h"



c_pair pairs[3];
//= {
//	{ &keys[0], &values[0] },
//	{ &keys[1], &values[1] },
//	{ &keys[2], &values[2] },
//};


static inline int int_comparer(void * x, void * y)
{
    return *(int *)(x) - *(int *)(y);
}

int create_with_insert_unique(c_pmap thiz)
{
	int values[] = { 
		8,	/* 0 */
		3,	/* 1 */
		8,	/* 2 */
	};

	int keys[] = { 
		12,	/* 0 */	
		4,	/* 1 */	
		71,	/* 2 */
	};
	
//	{ &keys[0], &values[0] },
//	{ &keys[1], &values[1] },
//	{ &keys[2], &values[2] },
	pairs[0].first = &keys[0];
	pairs[0].second = &values[0];
	pairs[1].first = &keys[1];
	pairs[1].second = &values[1];
	pairs[2].first = &keys[2];
	pairs[2].second = &values[2];

	int i = 0;

	for(i = 0; i < sizeof(keys)/sizeof(int); i++) {
		c_map_insert(thiz, &pairs[i]);
	}

	print_map(thiz);
	rprint_map(thiz);

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

#if 0
	target = c_map_find(thiz, &keys[0]);

	printf("key =  %d     value = %d\n", *(int*)(((c_ppair)ITER_REF(target))->first),\
										 *(int*)(((c_ppair)ITER_REF(target))->second) );
#endif

	int key = 71;
	target = c_map_find(thiz, &key);
	printf("key =  %d     value = %d\n", *(int*)(((c_ppair)ITER_REF(target))->first),\
										 *(int*)(((c_ppair)ITER_REF(target))->second) );

	key = 4;
	target = c_map_find(thiz, &key);
	printf("key =  %d     value = %d\n", *(int*)(((c_ppair)ITER_REF(target))->first),\
										 *(int*)(((c_ppair)ITER_REF(target))->second) );

}


int main(int argc, char **argv)
{
	c_map map;

	c_map_create(&map, int_comparer);

	create_with_insert_unique(&map);
#if 0
	printf("------print_map-------\n");
	print_map(&map);
	printf("------rprint_map-------\n");
	rprint_map(&map);


	printf("------find_map-------\n");
#endif
	test_find_erase(&map);

	test_clear(&map);  //测试c_map_clear()

	c_map_destroy(&map);



	return 0;
}














