/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-10 09:37:35
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cstl/cmap.h"

static int make_map(map_t *thiz)
{
	pair_t				*ppair_p = create_pair(int, int);
	if( NULL == ppair_p ) {
		return -1;
	}

	pair_init(ppair_p);

	pair_make(ppair_p, 2, 20);
	map_insert(thiz, ppair_p);
	pair_make(ppair_p, 3, 30);
	map_insert(thiz, ppair_p);

	pair_destroy(ppair_p);
}

int main(int argc, char *argv)
{
	map_t				*pmap_m1 = create_map(int, int);
	pair_t				*ppair_p = create_pair(int, int);
	map_iterator_t		it_m;

	if( NULL == pmap_m1 || NULL == ppair_p ) {
		return -1;
	}
	pair_init(ppair_p);
	map_init(pmap_m1);


	*(int *)map_at(pmap_m1, 1) = 10;
	make_map(pmap_m1);


	printf("The keys of the mapped elements are:");
	for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m)) {
		printf(" %d", *(int *)pair_first(iterator_get_pointer(it_m)));
	}
	printf("\n");

	printf("The values of the mapped elements are:");
	for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m)) {
		printf(" %d", *(int *)pair_second(iterator_get_pointer(it_m)));
	}
	printf("\n");

	
	*(int *)map_at(pmap_m1, 2) = 40;
	map_at(pmap_m1, 5);


	printf("The keys of the mapped elements are:");
	for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m)) {
		printf(" %d", *(int *)pair_first(iterator_get_pointer(it_m)));
	}
	printf("\n");

	printf("The values of the mapped elements are:");
	for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m)) {
		printf(" %d", *(int *)pair_second(iterator_get_pointer(it_m)));
	}
	printf("\n");



	pair_destroy(ppair_p);
	map_destroy(pmap_m1);

	return 0;
}













