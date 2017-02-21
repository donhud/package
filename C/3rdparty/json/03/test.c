/*************************************************************************
* File Name: test.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-09 04:01:26
* Last modified: 2015-10-29 14:16:28
************************************************************************/

#include <stdio.h>
#include "libjson.h"

int main(int argc, char **argv)
{
	int i = 5;
	//JSONNODE *n = json_new(JSON_NODE);
	JSONNODE *n = json_new(JSON_ARRAY);
	json_set_name(n, "sell");
	
	while (i--) {
		JSONNODE *tmp = json_new(JSON_NODE);
		json_push_back(tmp, json_new_i("volume_1", 123));
		json_push_back(tmp, json_new_i("volume_2", 123));
		json_push_back(tmp, json_new_i("volume_3", 123));
		json_push_back(tmp, json_new_i("volume_4", 123));

		json_push_back(n, tmp);
	}
	

	json_char *jc = json_write_formatted(n);
	printf("%s\n", jc);



	json_free(jc);
	json_delete(n);

	return 0;
}

