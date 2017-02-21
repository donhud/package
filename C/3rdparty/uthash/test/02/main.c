/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2016-01-06 03:15:20
* Last modified: 2016-01-06 03:59:17
************************************************************************/

#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct packet {
	int					key;	//这个是用来做hash的key值
	char				msg[10];

	UT_hash_handle		hh;
} packet_t;

int main(int argc, char **argv)
{
	packet_t	*pkt, *tmp, *hash_packet = NULL;
	int i;
		
	printf("hash count = %d\n", HASH_COUNT(hash_packet));


	//--------------------------------------------------------------------
	for(i = 0; i < 10; i++) {	/*往hash中添加节点*/

		HASH_FIND_INT(hash_packet, &i, tmp);

		if (NULL == tmp) {
			pkt = (packet_t *)malloc(sizeof(packet_t));
			pkt->key = i;
			sprintf(pkt->msg, "i = %d", i);

			HASH_ADD_INT(hash_packet, key, pkt);
		}
	}
	printf("hash count = %d\n", HASH_COUNT(hash_packet));


	//--------------------------------------------------------------------
	i = 5;
	HASH_FIND_INT(hash_packet, &i, tmp);	/*通过key查找*/
	if(NULL != tmp) {
		printf("key = %d: %s\n", i, tmp->msg);
	}
	printf("hash count = %d\n", HASH_COUNT(hash_packet));


	//--------------------------------------------------------------------
	for(tmp = hash_packet; NULL != tmp; tmp = tmp->hh.next) {	/*遍历这个hash表*/
		printf("%d = > %s\n", tmp->key, tmp->msg);
	}

	
	//--------------------------------------------------------------------
	for(i = 0; i < 3; i++) {	/*删除节点*/
		HASH_FIND_INT(hash_packet, &i, tmp);
		if(NULL != tmp) {
			HASH_DEL(hash_packet, tmp);
			free(tmp);
		}
	}
	printf("hash count = %d\n", HASH_COUNT(hash_packet));



	return 0;
}








