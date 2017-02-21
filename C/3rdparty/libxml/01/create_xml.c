/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2016-01-19 18:28:28
* Last modified: 2016-01-20 13:41:25
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


int main(int argc, char **argv)
{
	xmlDocPtr pdoc = NULL;			//指向xml文档对象的指针
	xmlNodePtr proot_node = NULL;	//指向 XML 的节点对象（根节点和子节点都是一样的）
	xmlNodePtr pnode1 = NULL, sonpnode2 = NULL;

	pdoc = xmlNewDoc(BAD_CAST "1.0");	//创建一个xml新文档对象

	proot_node = xmlNewNode(NULL, BAD_CAST "根节点");	//创建root节点
	xmlNewProp(proot_node, BAD_CAST "mykey1", BAD_CAST "myvalue1");	//给一个节点增添属性
	xmlNewProp(proot_node, BAD_CAST "mykey2", BAD_CAST "myvalue2");
	xmlDocSetRootElement(pdoc, proot_node);		//设置 XML 文档对象的根节点为proot_node，只有一个根节点

	pnode1 = xmlNewNode(NULL, BAD_CAST "子节点1");	//创建pnode1 子节点
	xmlNewChild(pnode1, NULL, BAD_CAST "子子节点1", BAD_CAST "子子节点1的内容");	//指定一个节点，会创建这个节点的子节点。这样不需要使用 xmlNewNode 创建一个节点，再使用 xmlAddChild 添加到其父节点中
	xmlAddChild(proot_node, pnode1);		//添加子节点到 root 节点

	sonpnode2 = xmlNewNode(NULL, BAD_CAST "子子节点2");
	xmlAddChild(pnode1, sonpnode2);
	xmlAddChild(sonpnode2, xmlNewText(BAD_CAST "子子节点2的内容"));	//xmlNewText 创建一个描述节点
	
	xmlNewTextChild(proot_node, NULL, BAD_CAST "子节点2", BAD_CAST "子节点2的内容");
	xmlNewTextChild(proot_node, NULL, BAD_CAST "子节点3", BAD_CAST "子节点3的内容");

	xmlSaveFormatFileEnc("./test.xml", pdoc, "UTF-8", 1);	//保存 xml 为文件

	//释放资源
	xmlFreeDoc(pdoc);	//释放xml对象
	xmlCleanupParser();	//清理
	xmlMemoryDump();	//清理

	return 0;
}

