/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-10 08:41:12
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cstl/cmap.h"

static int make_map_1(map_t *thiz)
{
	pair_t				*ppair_p = create_pair(int, int);
	if( NULL == ppair_p ) {
		return -1;
	}

	pair_init(ppair_p);

	pair_make(ppair_p, 1, 10);
	map_insert(thiz, ppair_p);
	pair_make(ppair_p, 2, 30);
	map_insert(thiz, ppair_p);
	pair_make(ppair_p, 3, 30);
	map_insert(thiz, ppair_p);

	pair_destroy(ppair_p);
}

static int make_map_2(map_t *thiz)
{
	pair_t				*ppair_p = create_pair(int, int);
	if( NULL == ppair_p ) {
		return -1;
	}

	pair_init(ppair_p);

	pair_make(ppair_p, 4, 40);
	map_insert(thiz, ppair_p);
	pair_make(ppair_p, 5, 50);
	map_insert(thiz, ppair_p);
	pair_make(ppair_p, 6, 60);
	map_insert(thiz, ppair_p);

	pair_destroy(ppair_p);
}
int main(int argc, char *argv)
{
	map_t				*pmap_m1 = create_map(int, int);
	map_t				*pmap_m2 = create_map(int, int);
	pair_t				*ppair_p = create_pair(int, int);
	map_iterator_t		it_m;

	if( NULL == pmap_m1 || NULL == pmap_m2 || NULL == ppair_p ) {
		return -1;
	}
	pair_init(ppair_p);
	map_init(pmap_m1);
	map_init(pmap_m2);

	make_map_1(pmap_m1);

	make_map_2(pmap_m2);


	printf("m1 = ");
	for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m)) {
		printf(" <%d, %d>", \
				*(int *)pair_first(iterator_get_pointer(it_m)),\
				*(int *)pair_second(iterator_get_pointer(it_m)));
	}
	printf("\n");

	map_assign(pmap_m1, pmap_m2);

	printf("m1 = ");
	for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m)) {
		printf(" <%d, %d>", \
				*(int *)pair_first(iterator_get_pointer(it_m)),\
				*(int *)pair_second(iterator_get_pointer(it_m)));
	}
	printf("\n");
	

	pair_destroy(ppair_p);
	map_destroy(pmap_m1);
	map_destroy(pmap_m2);

	return 0;
}













