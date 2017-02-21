/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-11-06 05:11:09
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cmap.h"


typedef struct _min_element_t {
	int id;
	int a;
} min_element_t;


int char_min_get_map_2(map_iterator_t *pit_m, char **key, void **value);
min_element_t *char_min_element_find_value_2(map_t *thiz, char *key);
int char_min_insert_map_2(map_t *thiz, char *key, void *value);



int main(int argc, char *argv)
{
	map_t *map = create_map(char * , void *);
	map_iterator_t it_m;

	map_init(map);
	int i = 0;

	min_element_t *tmp = malloc( sizeof(min_element_t)*10 );
	memset(tmp, 0, sizeof(min_element_t)*10);
	for(i = 0; i < 10; i++) {
		tmp[i].id = i;
	}
	
	if(NULL == char_min_element_find_value_2(map, "123")) {
		char_min_insert_map_2(map, "123", tmp);
	}
	char_min_insert_map_2(map, "hello", tmp);


	min_element_t *_info_1 = char_min_element_find_value_2(map, "123");
	min_element_t *_info_2 = char_min_element_find_value_2(map, "hello");
	printf("tmp = %d\n", tmp);
	printf("_info_1 = %d\n", _info_1);
	printf("_info_2 = %d\n", _info_2);


	for(i = 0; i < 10; i++) {
		printf("_info_1[%d] = %d\n", i, _info_1[i].id);
	}


	for(i = 0; i < 10; i++) {
		printf("_info_2[%d] = %d\n", i, _info_2[i].id);
	}


	char *key = NULL;
	min_element_t *value = NULL;
	it_m = map_begin(map);
			
	char_min_get_map_2(&it_m, &key, &value);
	printf("key = %s\n", key);
	printf("value[0].id %d\n", value[0].id);


	it_m = iterator_next(it_m);
	char_min_get_map_2(&it_m, &key, &value);
	printf("key = %s\n", key);
	printf("value[0].id %d\n", value[0].id);




	return 0;
}




//-------------------------------------------------------------------------------------------------------------

/*
 *	获取map中的一项数据
 * */
int element_get_map(map_iterator_t *pit_m, void **key, void **value)
{
	if(NULL == pit_m || NULL == key || NULL == value) {
		//_LOG_ERR("pit_m , key or value is NULL!\n");
		return -1;
	}
	//strcpy( key, (char *)pair_first(iterator_get_pointer(*pit_m)) );
	//memcpy( value, sizeof(highlight_info_t), (highlight_info_t *)(iterator_get_pointer(*pit_m)) );
	*key = (void *)pair_first(iterator_get_pointer(*pit_m));
	*value = (void *)pair_second(iterator_get_pointer(*pit_m));

	return 0;
}



int element_insert_map(map_t *thiz, pair_t *ppair_p, void *key, void *value)
{
	map_iterator_t	it_m;

	if(NULL == ppair_p) {
		//_LOG_ERR("create_pair err!\n");
		return -1;
	}

	if(NULL == key || NULL == value || NULL == thiz) {
		//_LOG_DBG("key or value = NULL\n");
		return -1;
	}

	pair_make(ppair_p, key, value);
	it_m = map_insert(thiz, ppair_p);
	if( iterator_equal(it_m, map_end(thiz)) ) {
		//_LOG_DBG("insert %s err!\n", key);
		//pair_destroy(ppair_p);
		return -1;
	}

	return 0;
}

void *element_find_value_map(map_t *thiz, const void *key)
{
	if(NULL == thiz || NULL == key) {
		return NULL;
	}

	map_iterator_t it_m = map_find(thiz, key);

	if( iterator_equal(it_m, map_end(thiz)) ) {
		return NULL;
	}
	return (void *)pair_second(iterator_get_pointer(it_m));
}





//min_element_t 数组
//======================================================================================================
/*
 *	获取map中的一项数据
 * */
int char_min_get_map_2(map_iterator_t *pit_m, char **key, void **value)
{
	if(NULL == pit_m || NULL == key || NULL == value) {
		//_LOG_ERR("pit_m , key or value is NULL!\n");
		return -1;
	}
	
	*key = (void *)pair_first(iterator_get_pointer(*pit_m));
	*value = *(void **)pair_second(iterator_get_pointer(*pit_m));

	//return element_get_map(pit_m, key, value);
	return 0;
}


min_element_t *char_min_element_find_value_2(map_t *thiz, char *key)
{
	if(NULL == thiz || NULL == key) {
		return NULL;
	}


	map_iterator_t it_m = map_find(thiz, key);

	if( iterator_equal(it_m, map_end(thiz)) ) {
		return NULL;
	}
	return *(min_element_t **)pair_second(iterator_get_pointer(it_m));
}

int char_min_insert_map_2(map_t *thiz, char *key, void *value)
{
	pair_t			*ppair_p = create_pair(char *, void *);
	map_iterator_t	it_m;

	if(NULL == ppair_p) {
		//_LOG_ERR("create_pair err!\n");
		return -1;
	}

	if(NULL == key || NULL == value) {
		//_LOG_DBG("key or value = NULL\n");
		return -1;
	}

	pair_init(ppair_p);
	//-----------------
	element_insert_map(thiz, ppair_p, key, value);

	pair_destroy(ppair_p);

	return 0;
}
//======================================================================================================








