#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <event.h>

void accept_cb(int fd, short events, void *arg);
void socket_read_cb(int fd, short events, void *arg);
int tcp_server_init(int port, int listen_num);


int main(int argc, char **argv)
{
	int listener = tcp_server_init(9999, 10);
	if(-1 == listener) {
		perror("tcp_server_init error\n");
		return -1;
	}

	struct event_base *base = event_base_new();

	//添加监听客户端请求连接事件，即监听listener
	struct event *ev_listen = event_new(base, listener, EV_READ | EV_PERSIST, accept_cb, base);
	event_add(ev_listen, NULL);	//超时时间（struct timeval *类型的，NULL表示无超时设置）

	//启动循环，这样才能开始处理发生的事件，循环将一直持续，直到不再有需要关注的事件，或者遇到event_loopbreak()/event_loopexit()函数
	event_base_dispatch(base);

	return 0;
}

//绑定到event的回调函数accept_cb():
//fd:监听的文件描述符
//evnts:event类型及属性
//arg:即传递给event_new的最后一个参数
void accept_cb(int fd, short events, void *arg)
{
	evutil_socket_t sockfd;
	struct sockaddr_in client;
	socklen_t len;

	sockfd = accept(fd, (struct sockaddr *)&client, &len);
	
	evutil_make_socket_nonblocking(sockfd);

	printf("accept a client %d", sockfd);

	struct event_base *base = (struct event_base *)arg;

	//仅仅是为了动态创建一个event结构体
	struct event *ev = event_new(NULL, -1, 0, NULL, NULL);

	//将动态创建的结构体作为event的回调参数
	event_assign(ev, base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, (void *)ev);

	event_add(ev, NULL);
}

void socket_read_cb(int fd, short events, void *arg)
{
	char msg[1024] = {0};
	struct event *ev = (struct event *)arg;
	int len = read(fd, msg, sizeof(msg)-1);
	if(len <= 0) {
		printf("some error happen when read\n");
		close(event_get_fd(ev));
		return ;
	}

	msg[len] = '\0';
	printf("recv the client msg: %s", msg);

	char reply_msg[4096] = "I have recvieced the msg: ";
	strcat(reply_msg, msg);
	write(fd, reply_msg, strlen(reply_msg));

}

typedef struct sockaddr SA;
int tcp_server_init(int port, int listen_num)
{
	int errno_save;
	evutil_socket_t listener;
	
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == listener) {
		return -1;
	}
	
	//允许多次绑定同一个地址，要用在socket和bind之间
	evutil_make_listen_socket_reuseable(listener);

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(port);

	if(bind(listener, (SA*)&sin, sizeof(sin)) < 0) {
		goto error;
	}

	if(listen(listener, listen_num) < 0) {
		goto error;
	}

	//跨平台的统一接口，将套接子设置为非阻塞状态
	evutil_make_socket_nonblocking(listener);

	return listener;

error:
	errno_save = errno;
	evutil_closesocket(listener);
	errno = errno_save;

	return -1;
}







