/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-10 03:17:41
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "c_map.h"


struct key {
	int k;
};

int key_comparer(value_type x, value_type y)
{
	return ((struct key *)x)->k - ((struct key *)y)->k;
}

c_pair pair_ary[] = { { 0, 0 } };

int main(int argc, char **argv)
{
	c_map map;
	struct key *pkey = malloc(sizeof(struct key));

	pair_ary[0].first = pkey;
	c_map_create(&map, key_comparer);
	c_map_insert(&map, &pair_ary[0]);
	c_map_destroy(&map);

	free(pkey);


	return 0;
}

