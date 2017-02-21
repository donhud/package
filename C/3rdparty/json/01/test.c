/*************************************************************************
* File Name: test.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-09 04:01:26
* Last modified: 2015-10-12 03:30:42
************************************************************************/

#include <stdio.h>
#include "libjson.h"

int main(int argc, char **argv)
{
	JSONNODE *n = json_new(JSON_NODE);

	json_push_back(n, json_new_a("RootA", "Hello world"));

	JSONNODE *c = json_new(JSON_NODE);
	json_set_name(c, "ArrayOfNumbers");

	json_push_back(c, json_new_i("first", 16));
	json_push_back(c, json_new_i("second", 42));
	json_push_back(c, json_new_i("third", 128));

	json_push_back(n, c);

	json_char *jc = json_write_formatted(n);
	printf("%s\n", jc);

	printf("----\n");


	json_free(jc);
	json_delete(n);

	return 0;
}

