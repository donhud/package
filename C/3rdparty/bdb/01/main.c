/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2016-03-03 18:04:11
* Last modified: 2016-03-03 18:44:58
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <db.h>

typedef struct customer {
	int		c_id;
	char	name[10];
	char	address[20];
	int		age;
}CUSTOMER;


void print_error(int ret);
void init_DBT(DBT *key, DBT *data);


int main(int argc, char **argv)
{
	DB				*dbp;
	DBT				key, data;
	u_int32_t		flags;
	int				ret;
	char			*fruit = "apple";
	int				number = 15;
	int				key_cust_c_id = 1;
	CUSTOMER		cust;

	cust.c_id = 1;
	strncpy(cust.name, "javer", 9);
	strncpy(cust.address, "chengdu", 19);
	cust.age = 32;

	/* 创建数据库句柄 */
	ret = db_create(&dbp, NULL, 0);
	print_error(ret);

	/* 创建数据库标志 */
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, "single.db", NULL, DB_BTREE, flags, 0);	//创建一个名为single.db的数据库，使用B+树访问算法，本段代码演示对简单数据类型的处理
	print_error(ret);

	init_DBT(&key, &data);
	/* 分别对关键字和数据赋值和规定长度 */
	key.data = fruit;
	key.size = strlen(fruit) + 1;
	data.data = &number;
	data.size = sizeof(int);
	ret = dbp->put(dbp, NULL, &key, &data, DB_NOOVERWRITE);	//把记录写入数据库中，不允许覆盖关键字相同的记录
	print_error(ret);

	dbp->sync(dbp, 0);	//手动把缓存中的数据刷新到硬盘文件中，实际上在关闭数据库时，数据会被自动刷新

	init_DBT(&key, &data);
	key.data = fruit;
	key.size = strlen(fruit) + 1;
	ret = dbp->get(dbp, NULL, &key, &data, 0);		//从数据库中查询关键字为apple的记录
	print_error(ret);
	printf("The number = %d\n", *(int *)(data.data));	//特别要注意数据结构DBT的字段data为void *型，所以在对data赋值和取值时，要做必要的类型转换。

//_______________________________________
	if(dbp != NULL) {
		dbp->close(dbp, 0);
	}
	ret = db_create(&dbp, NULL, 0);
	print_error(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, "complex.db", NULL, DB_HASH, flags, 0);	//创建一个名为single.db的数据库，使用B+树访问算法，本段代码演示对简单数据类型的处理
	print_error(ret);

	init_DBT(&key, &data);
	/* 分别对关键字和数据赋值和规定长度 */
	key.data = &cust.c_id;
	key.size = sizeof(int);
	data.data = &cust;
	data.size = sizeof(CUSTOMER);
	ret = dbp->put(dbp, NULL, &key, &data, DB_NOOVERWRITE);	//把记录写入数据库中，不允许覆盖关键字相同的记录
	print_error(ret);

	memset(&cust, 0, sizeof(CUSTOMER));

	key.data = &key_cust_c_id;
	key.size = sizeof(int);
	data.data = &cust;
	data.ulen = sizeof(CUSTOMER);
	data.flags = DB_DBT_USERMEM;
	ret = dbp->get(dbp, NULL, &key, &data, 0);		//从数据库中查询关键字为apple的记录
	print_error(ret);
	printf("c_id = %d name = %s address = %s age = %d\n", cust.c_id, cust.name, cust.address, cust.age);
	



	if(dbp != NULL) {
		dbp->close(dbp, 0);
	}


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




