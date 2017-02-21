/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-10 11:04:59
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cstl/cmap.h"

static int make_map(map_t *thiz)
{
	pair_t			*ppair_p = create_pair(char *, int);

	if(NULL == ppair_p) {
		return -1;
	}
	pair_init(ppair_p);

	pair_make(ppair_p, "ab", 0);
	map_insert(thiz, ppair_p);
	pair_make(ppair_p, "ae", 1);
	map_insert(thiz, ppair_p);
	pair_make(ppair_p, "ad", 4);
	map_insert(thiz, ppair_p);

	pair_destroy(ppair_p);
}


int main(int argc, char *argv)
{
	map_t			*pmap_m1 = create_map(char *, int);
	pair_t			*ppair_p = create_pair(char *, int);
	map_iterator_t	it_m;
	
	if(NULL == pmap_m1 || NULL == ppair_p) {
		return -1;
	}

	map_init(pmap_m1);
	pair_init(ppair_p);


	make_map(pmap_m1);

#if 1

	printf("The first element of m1 is %s\n",\
			(char *)pair_first(iterator_get_pointer(map_begin(pmap_m1))));
	printf("The first element of m1 is %d\n",\
			*(int *)pair_second(iterator_get_pointer(map_begin(pmap_m1))));

	it_m = map_begin(pmap_m1);
	it_m = iterator_next(it_m);

	printf("The first element of m1 is %s\n",\
			(char *)pair_first(iterator_get_pointer(it_m)));
	printf("The first element of m1 is %d\n",\
			*(int *)pair_second(iterator_get_pointer(it_m)));

#endif

	map_destroy(pmap_m1);
	pair_destroy(ppair_p);

	return 0;
}













