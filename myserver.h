#ifndef SERVER_H_
#define SERVER_H_

struct userargs{
	int argc;
	char **argv;
};
typedef struct userargs* uargs;

struct sockinfo{
	int sockfd;
};
typedef struct sockinfo* SockInfo;

#endif