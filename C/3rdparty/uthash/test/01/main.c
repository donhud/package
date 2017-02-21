/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2016-01-06 03:15:20
* Last modified: 2016-01-06 03:24:37
************************************************************************/

#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct example_user_t {
	int					id;
	int					cookie;
	UT_hash_handle		hh;
} example_user_t;

int main(int argc, char **argv)
{
	int i;
	example_user_t *user, *users = NULL;

	srand((unsigned int)time(NULL));

	for(i = 0; i < 10; i++) {
		user = malloc(sizeof(example_user_t));
		if(NULL == user) {
			exit(-1);
		}
		user->id = rand() % 100;
		user->cookie = i * i;
		HASH_ADD_INT(users, id, user);
	}

	for(user = users; user != NULL; user=(example_user_t *)(user->hh.next)) {
		printf("user %d, cookie %d\n", user->id, user->cookie);
	}



	return 0;
}








