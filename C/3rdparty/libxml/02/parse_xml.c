/*************************************************************************
* File Name: parse_xml.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2016-01-20 13:55:16
* Last modified: 2016-01-20 14:34:12
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(int argc, char **argv)
{
	xmlDocPtr	pdoc = NULL;
	xmlNodePtr proot = NULL, curNode = NULL;
	char *psfilename = "../01/test.xml";
	int n = 0;

	xmlKeepBlanksDefault(0);	//注意此处作用
	pdoc = xmlReadFile(psfilename, "UTF-8", XML_PARSE_RECOVER);
	if(NULL == pdoc) {
		printf("open file %s err!\n", psfilename);
		return -1;
	}

	proot = xmlDocGetRootElement(pdoc);		//获取 xml 文档对象的根节对象
	if(NULL == proot) {
		printf("error: %s not root node\n", psfilename);
		return -1;
	}
	
	if(xmlStrcmp(proot->name, BAD_CAST "根节点") != 0) {	//判断根节点是否正确
		printf("错误文档!\n");
		return -1;
	}

	if(xmlHasProp(proot, BAD_CAST "mykey1") && xmlHasProp(proot, BAD_CAST "mykey2") ) {	//如果相应的属性存在
		xmlChar *szAttr1 = xmlGetProp(proot, BAD_CAST "mykey1");
		xmlChar *szAttr2 = xmlGetProp(proot, BAD_CAST "mykey2");
		printf("szAttr1 = %s\tszAttr2 = %s\n", szAttr1, szAttr2);
	}

	curNode = proot->xmlChildrenNode;

	while(NULL != curNode) {

		printf("%d = %s\n", n++, curNode->name);

		curNode = curNode->next;
	}



	xmlFreeDoc(pdoc);
	xmlCleanupParser();


	return 0;
}











