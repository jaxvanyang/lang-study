/**
 * echoservert_pre.c - Concurrent echo server based on prethreading
 */

#include "csapp.h"
#include "sbuf.h"

#define kThreads 4
#define kSbufSize 16

static void init_echo_cnt();
void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf;
static long byte_cnt;
static sem_t mutex;

int main(int argc, char **argv) {
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	pthread_t tid;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	listenfd = Open_listenfd(argv[1]);

	sbuf_init(&sbuf, kSbufSize);
	for (int i = 0; i < kThreads; ++i)
		Pthread_create(&tid, NULL, thread, NULL);

	while (1) {
		clientlen = sizeof(struct sockaddr_storage);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		sbuf_insert(&sbuf, connfd);
	}
}

void *thread(void *vargp) {
	Pthread_detach(pthread_self());
	while (1) {
		int connfd = sbuf_remove(&sbuf);
		echo_cnt(connfd);
		Close(connfd);
	}
}

static void init_echo_cnt() {
	Sem_init(&mutex, 0, 1);
	byte_cnt = 0;
}

void echo_cnt(int connfd) {
	size_t n;
	char buf[MAXLINE];
	rio_t rio;
	static pthread_once_t once = PTHREAD_ONCE_INIT;

	Pthread_once(&once, init_echo_cnt);
	Rio_readinitb(&rio, connfd);
	while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
		P(&mutex);
		++byte_cnt;
		printf("server recieved %ld (%ld total) byte on fd %d\n",
				n, byte_cnt, connfd);
		V(&mutex);
		Rio_writen(connfd, buf, n);
	}
}
