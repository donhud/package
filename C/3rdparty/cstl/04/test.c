/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-31 11:15:54
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cmap.h"

int main(int argc, char *argv)
{
	map_t *pmap_stocks = create_map(char * ,int);
	map_iterator_t it_pos, n_it;
	if(pmap_stocks == NULL) {
		return -1;
	} else {
		map_init(pmap_stocks);
	}

	*(int*)map_at(pmap_stocks, "Google") = 834;
	*(int*)map_at(pmap_stocks, "IBM") = 431;
	*(int*)map_at(pmap_stocks, "Apple") = 557;
	*(int*)map_at(pmap_stocks, "MS") = 691;
	*(int*)map_at(pmap_stocks, "Oracle") = 670;
	//map_insert()

#if 0
	for(it_pos = map_begin(pmap_stocks), n_it = iterator_next(it_pos);\
			!iterator_equal(n_it, map_end(pmap_stocks));\
			it_pos = n_it, n_it = iterator_next(it_pos)) {

		char *tmp = (char*)pair_first((pair_t*)iterator_get_pointer(it_pos));

		if(!strcmp(tmp, "Google") || !strcmp(tmp, "MS")) {
			//pre_it = pre

			map_erase_pos(pmap_stocks, it_pos);
		}

	}
	....
#else 

	//------------------------------------注意此处遍历并删除map中的元素
	for(it_pos = map_begin(pmap_stocks); !iterator_equal(it_pos, map_end(pmap_stocks));) {

		char *tmp = (char*)pair_first((pair_t*)iterator_get_pointer(it_pos));

		n_it = it_pos;
		it_pos = iterator_next(it_pos);

		if(!strcmp(tmp, "Google") || !strcmp(tmp, "MS")) {
			map_erase_pos(pmap_stocks, n_it);
		}

	}



#endif



	printf("\n");

	for(it_pos = map_begin(pmap_stocks); !iterator_equal(it_pos, map_end(pmap_stocks)); it_pos = iterator_next(it_pos)) {

		printf("stock:%s\tprice:%d\n",
				(char*)pair_first((pair_t*)iterator_get_pointer(it_pos)),
				*(int*)pair_second((pair_t*)iterator_get_pointer(it_pos)));
	}
	printf("\n");
	


	return 0;
}











