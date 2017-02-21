/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-12-26 00:41:27
* Last modified: 2016-02-05 18:00:38
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libwebsockets.h"





int main(int argc, char **argv)
{
	//server url will be http://localhost:9000
	int								port = 9000;
	const char						*interface = NULL;
	struct libwebsocket_context		*context;

	//we're not using ssl
	const char						*cert_path = NULL;
	const char						*key_path = NULL;

	//no special options
	int								opts = 0;







	return 0;
}





static int callback_http(struct libwebsocket_context *context,\
						 struct libwebsocket *wsi,\
						 enum libwebsocket_callback_reasons reason,\
						 void *user,\
						 void *in,\
						 size_t len)
{
	switch(reason) {
		case LWS_CALLBACK_CLIENT_WRITEABLE:
			printf("connection established\n");
		case LWS_CALLBACK_HTTP: 
			char *requested_uri = (char *)in;
			printf("requested URI: %s\n", requested_uri);

			if(strcmp(requested_uri, "/") == 0) {
				void *universal_response = "Hello, world!";
				libwebsocket_write(wsi, universal_response, strlen(universal_response), LWS_WRITE_HTTP);
				break;
			} else {
				char cwd[1024];
				char *resource_path;
				if(getcwd(cwd, sizeof(cwd)) != NULL) {
					// allocate enough memory for the resource path
					resource_path = malloc(strlen(cwd) + strlen(requested_uri));
					sprintf(resource_path, "%s%s", cwd, requested_uri);
					printf("resource path: %s\n", resource_path);
					
					char *extension = strrchr(resrouce_path, '.');
					char *mime;

					// choose mime type based on the file extension
					if(extension == NULL) {
						mime = "text/plain";
					} else if (strcmp(extension, ".png") == 0) {
						mime = "image/png";
					} else if (strcmp(extension, ".jpg") == 0) {
						mime = "image/jpg";
					} else if (strcmp(extension, ".gif") == 0) {
						mime = "image/gif";
					} else if (strcmp(extension, ".html") == 0) {
						mime = "text/html";
					} else if (strcmp(extension, ".css") == 0) {
						mime = "text/css";
					} else {
						mime = "text/plain";

						libwebsockets_serve_http_file(wsi, resource_path, mime);
					}
				}

				libwebsocket_close_and_free_session(context, wsi, LWS_CLOSE_STATUS_NORMAL);
				break;
			}

		default:
			printf("unhandled callback\n");
			break;

	}

	return 0;
}
















