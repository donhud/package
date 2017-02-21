/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2016-03-03 18:04:11
* Last modified: 2016-03-04 10:55:17
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <db.h>


void print_error(int ret);
void init_DBT(DBT *key, DBT *data);


int main(int argc, char **argv)
{
	DB_ENV			*dbenv = NULL;
	DB				*dbp = NULL;
	DBT				key, data;
	u_int32_t		env_flags, flags;
	int				ret;
	int				recv_max;

	ret = db_env_create(&dbenv, 0);
	print_error(ret);
	env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB | DB_THREAD;
	dbenv->set_errfile(dbenv, stderr);
	dbenv->set_cachesize(dbenv, 0, 1024*1024*1, 1);
	ret = dbenv->open(dbenv, "./", env_flags, 0);
	print_error(ret);
	


	/* 创建数据库句柄 */
	ret = db_create(&dbp, dbenv, 0);
	print_error(ret);
	
	dbp->set_errpfx(dbp, "\nBerkeley DB: ");

	/* 创建数据库标志 */
	flags = DB_CREATE | DB_THREAD;
	ret = dbp->open(dbp, NULL, "single.db", NULL, DB_BTREE, flags, 0664);	//创建一个名为single.db的数据库，使用B+树访问算法，本段代码演示对简单数据类型的处理
	print_error(ret);

	init_DBT(&key, &data);
	key.data = "MAXRCVNUM";
	key.size = sizeof("MAXRCVNUM");
	data.flags = DB_DBT_MALLOC;	//multithread , the same as following ?
#if 0
	data.data = &recv_max;
	data.size = sizeof(int);
#endif

	ret = dbp->get(dbp, NULL, &key, &data, 0);
	print_error(ret);
	printf("recv_max = %d\n", *((int *)data.data ));

	
	free(data.data);



	if(dbp != NULL) {
		dbp->close(dbp, 0);
	}

	dbenv->close(dbenv, 0);


	return 0;
}








void print_error(int ret)		//DB的函数执行完成后，返回0代表成功，否则失败
{
	if(ret != 0) {
		printf("ERROR: %s\n", db_strerror(ret));
	}
}

void init_DBT(DBT *key, DBT *data)
{
	memset(key, 0, sizeof(DBT));
	memset(data, 0, sizeof(DBT));
}




