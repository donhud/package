/*************************************************************************
* File Name: test.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-09 04:01:26
* Last modified: 2015-10-09 22:17:18
************************************************************************/

#include <stdio.h>
#include "libjson.h"

typedef struct _regster {
	char platid[50];
	char platname[50];
	char platip[50];
	char ostype[50];
	char osver[50];
	char username[50];
	char keyserial[50];
	char org[50];
	char mc_addr[50];
}register_t;


void make_register_req_js(const char *platid, const char *platname, const char *platip,\
							const char *mc_addr, char *buf, int buf_size)
{
	JSONNODE *n = json_new(JSON_NODE);

#if 0
	JSONNODE *c = json_new(JSON_ARRAY);
	json_set_name(c, "ArrayOfNumbers");
	json_push_back(c, json_new_i(NULL, 16));
	json_push_back(c, json_new_i(NULL, 42));
	json_push_back(c, json_new_i(NULL, 128));
	json_push_back(n, c);
#endif

	json_push_back(n, json_new_a("platid", platid));
	json_push_back(n, json_new_a("platname", platname));
	json_push_back(n, json_new_a("platip", platip));
	json_push_back(n, json_new_a("ostype", "centos"));
	json_push_back(n, json_new_a("osver", "linux"));
	json_push_back(n, json_new_a("username", ""));
	json_push_back(n, json_new_a("keyserial", ""));
	json_push_back(n, json_new_a("org", "6313264"));
	json_push_back(n, json_new_a("mc_addr", mc_addr));

	json_char *jc = json_write_formatted(n);
	strncpy(buf, jc, buf_size);

	json_free(jc);
	json_delete(n);
}


static void parse_reg_json(JSONNODE *n, register_t *reg)
{
	if(NULL == n) {
		return ;
	}

	JSONNODE_ITERATOR i = json_begin(n);

	while(i != json_end(n)) {
		if(*i == NULL) {
			return ;
		}
		if(json_type(*i) == JSON_ARRAY || json_type(*i) == JSON_NODE) {
			parse_reg_json(*i, reg);
		}

		json_char *node_name = json_name(*i);
		if(strcmp(node_name, "platid") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->platid, node_value, sizeof(reg->platid));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "platname") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->platname, node_value, sizeof(reg->platname));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "platip") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->platip, node_value, sizeof(reg->platip));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "ostype") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->ostype, node_value, sizeof(reg->ostype));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "osver") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->osver, node_value, sizeof(reg->osver));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "username") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->username, node_value, sizeof(reg->username));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "keyserial") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->keyserial, node_value, sizeof(reg->keyserial));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "org") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->org, node_value, sizeof(reg->org));
			json_free(node_value);
			json_free(node_name);
		} else if(strcmp(node_name, "mc_addr") == 0) {
			json_char *node_value = json_as_string(*i);
			strncpy(reg->mc_addr, node_value, sizeof(reg->mc_addr));
			json_free(node_value);
			json_free(node_name);
		}

		i++;

	}

}


int parse_register_req_js(const char *buf, register_t *reg)
{
	JSONNODE *n = json_parse(buf);
	
	if(NULL == n){
		perror("json_parse");
		return -1;
	} 

	parse_reg_json(n, reg);

	json_delete(n);

	return 0;
}


int main(int argc, char **argv)
{
	char buffer[1024] = { 0 };
	register_t reg;
	memset(&reg, 0, sizeof(reg));

	//----------------创建json字符串
	make_register_req_js("98945343", "darkblue-PC", "192.168.1.101", "00:0C:29:B1:7A:62", buffer, sizeof(buffer));

	printf("buffer = %s\n", buffer);


	//----------------解析json字符串
	parse_register_req_js(buffer, &reg);

	printf("reg.platid = %s\n", reg.platid);
	printf("reg.platname = %s\n", reg.platname);
	printf("reg.platip = %s\n", reg.platip);
	printf("reg.ostype = %s\n", reg.ostype);
	printf("reg.osver = %s\n", reg.osver);
	printf("reg.username = %s\n", reg.username);
	printf("reg.keyserial = %s\n", reg.keyserial);
	printf("reg.org = %s\n", reg.org);
	printf("reg.mc_addr = %s\n", reg.mc_addr);
	
	return 0;
}



