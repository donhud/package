/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-10 12:11:26
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cstl/cmap.h"


typedef struct _user {
	int n_first;
	int n_second;
}user_t;

static void _user_init(const void *cpv_input, void *pv_output)
{
	((user_t *)cpv_input)->n_first = 0;
	((user_t *)cpv_input)->n_second = 0;
	*(bool_t *)pv_output = true;
}

static void _user_destroy(const void *cpv_input, void *pv_output)
{
	((user_t *)cpv_input)->n_first = 0;
	((user_t *)cpv_input)->n_second = 0;
	*(bool_t *)pv_output = true;
}

static void _user_copy(const void *cpv_first, const void *cpv_second, void *pv_output)
{
	((user_t *)cpv_first)->n_first = ((user_t *)cpv_second)->n_first;
	((user_t *)cpv_first)->n_second = ((user_t *)cpv_second)->n_second;
	*(bool_t *)pv_output = true;
}

static void _user_less(const void *cpv_first, const void *cpv_second, void *pv_output)
{
	*(bool_t *)pv_output = \
		((user_t *)cpv_first)->n_first < ((user_t *)cpv_second)->n_first ? true :false;
}


static int make_map(map_t *thiz)
{
	pair_t			*ppair_p = create_pair(char *, user_t);
	user_t			tmp;

	if(NULL == ppair_p) {
		return -1;
	}
	pair_init(ppair_p);

	tmp.n_first = 1;
	tmp.n_second = 2;
	pair_make(ppair_p, "ab", &tmp);
	map_insert(thiz, ppair_p);

	tmp.n_first = 10;
	tmp.n_second = 20;
	pair_make(ppair_p, "ae", &tmp);
	map_insert(thiz, ppair_p);

	tmp.n_first = 100;
	tmp.n_second = 200;
	pair_make(ppair_p, "ad", &tmp);
	map_insert(thiz, ppair_p);

	pair_destroy(ppair_p);
}


int main(int argc, char *argv)
{
	type_register(user_t, _user_init, _user_copy, _user_less, _user_destroy);

	map_t			*pmap_m1 = create_map(char *, user_t);
	pair_t			*ppair_p = create_pair(char *, user_t);
	map_iterator_t	it_m;
	
	if(NULL == pmap_m1 || NULL == ppair_p) {
		printf("create map or pair error!\n");
		return -1;
	}

	map_init(pmap_m1);
	pair_init(ppair_p);


	make_map(pmap_m1);


#if 1

	printf("The first element of m1 is %s\n",\
			(char *)pair_first(iterator_get_pointer(map_begin(pmap_m1))));
	printf("The first element of m1 is %d\n",\
			((user_t *)pair_second(iterator_get_pointer(map_begin(pmap_m1))))->n_first );

	it_m = map_begin(pmap_m1);
	it_m = iterator_next(it_m);

	printf("The first element of m1 is %s\n",\
			(char *)pair_first(iterator_get_pointer(it_m)));
	printf("The first element of m1 is %d\n",\
			((user_t *)pair_second(iterator_get_pointer(it_m)))->n_first);

#endif

	map_destroy(pmap_m1);
	pair_destroy(ppair_p);

	return 0;
}













