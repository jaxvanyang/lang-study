/**
 * echoservers.c - Concurrent echo server driven by event
 */

#include "csapp.h"

typedef struct {
	int maxfd;
	fd_set read_set, ready_set;
	int nready, maxi;	// High water index into client array
	int clientfd[FD_SETSIZE];
	rio_t clientrio[FD_SETSIZE];
} pool_t;

size_t byte_cnt = 0;	// Counts total bytes received by server

void init_pool(int listenfd, pool_t *p);
void add_client(int connfd, pool_t *p);
void check_clients(pool_t *p);

int main(int argc, char **argv) {
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;

	static pool_t pool;
	
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	listenfd = Open_listenfd(argv[1]);
	init_pool(listenfd, &pool);

	while (1) {
		pool.ready_set = pool.read_set;
		pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

		// If listening descriptor ready, add new client to pool
		if (FD_ISSET(listenfd, &pool.ready_set)) {
			clientlen = sizeof(struct sockaddr_storage);
			connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
			add_client(connfd, &pool);
		}

		// Echo a text line from each ready connected descriptor
		check_clients(&pool);
	}
}

void init_pool(int listenfd, pool_t *p) {
	// Initially, there are no connected descriptors
	p->maxi = -1;
	for (int i = 0; i < FD_SETSIZE; ++i) {
		p->clientfd[i] = -1;
	}

	// Initially, listenfd is the only member of select read set
	p->maxfd = listenfd;
	FD_ZERO(&p->read_set);
	FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool_t *p) {
	p->nready--;	// Uncount listenfd
	int i;
	for (i = 0; i < FD_SETSIZE; ++i) {
		if (p->clientfd[i] < 0) {
			// Add connected descriptor to the pool
			p->clientfd[i] = connfd;
			Rio_readinitb(&p->clientrio[i], connfd);

			// Add the descriptor to descriptor set
			FD_SET(connfd, &p->read_set);

			// Update max descriptor and pool high water mark
			if (connfd > p->maxfd)
				p->maxfd = connfd;
			
			if (i > p->maxi)
				p->maxi = i;
			break;
		}
	}
	if (i == FD_SETSIZE)
		app_error("add_client error: Too many clients");
}

void check_clients(pool_t *p) {
	size_t n;
	int i, connfd;
	char buf[MAXLINE];
	rio_t rio;

	for (i = 0; i <= p->maxi && p->nready > 0; ++i) {
		connfd = p->clientfd[i];
		rio = p->clientrio[i];

		// If the descriptor is ready, echo a text line from it
		if (connfd > 0 && FD_ISSET(connfd, &p->ready_set)) {
			p->nready--;
			if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
				byte_cnt += n;
				printf("Server received %ld (%ld total) bytes on fd %d\n",
						n, byte_cnt, connfd);
				Rio_writen(connfd, buf, n);
			} else {	// EOF detected, remove descriptor from pool
				Close(connfd);
				FD_CLR(connfd, &p->read_set);
				p->clientfd[i] = -1;
			}
		}
	}
}
