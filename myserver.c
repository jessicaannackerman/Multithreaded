#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>
#include <signal.h>
#include "myserver.h"

static pthread_t newthread;

void createClientServiceThread(void* parameters){
    SockInfo newsockinfo = (SockInfo) parameters;
    int success;
    char buffer[256];

    printf("In CLIENT SERVER therad: %i\n",newsockinfo->sockfd);
    success = write(newsockinfo->sockfd, "CONNECTED TO SERVER, READY FOR COMMANDS\n", 18);
    if(success < 0){
        error("ERROR WRITING TO SOCKET\n");
    }
    bzero(buffer,256);
    success = read(newsockinfo->sockfd, buffer, 255);
    printf("%s", buffer);
    if(success < 0){
        error("ERROR READING FROM SOCKET\n");
    }
    close(newsockinfo->sockfd);
    pthread_exit(NULL);
}

void sessionAcceptorThread(void* parameters){
     uargs a = (uargs)parameters;//this is argc and argv

     //THIS IS THE TCP/IP STUFF
     int sockfd, newsockfd, portno, clilen;
     struct sockaddr_in serv_addr, cli_addr;


     //MAKES SURE THERE WAS SOMETHING PASSED IN
     if (a->argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         pthread_exit(NULL);
     }
    //

    //MADES THE SOCKET
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        error("ERROR opening socket");
    }
    //


    //BINDS THE SOCKET AND THE SERVER ADDRESS
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(a->argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
    //
    int numconnections = 0;
    pthread_t threads[SOMAXCONN]; //SOMAXCONN is the maximum number of threads that can be connected 
    int thread_ids[SOMAXCONN];

    while(numconnections < SOMAXCONN){
     listen(sockfd,SOMAXCONN);
     clilen = sizeof(cli_addr);
     SockInfo newsockinfo = malloc(sizeof(SockInfo));
     newsockinfo->sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockinfo->sockfd < 0) {
          error("ERROR on accept");
    }

    //THIS CREATES A NEW THREAD FOR EVERY CONNECTION THAT IS ACCEPTED
    thread_ids[numconnections] = pthread_create( &threads[numconnections],
    NULL, (void *)createClientServiceThread, (void*)newsockinfo);
    numconnections++; 
}
    close(sockfd);
    pthread_join(threads[numconnections], NULL); //suspends execution of calling thread until target thread terminates
    pthread_exit(NULL);
}


int main(int argc, char** argv){
    pthread_t thread;
    int created, i;
    uargs arguments = malloc(sizeof(uargs));
    arguments->argc = argc;
    arguments->argv = argv;

    created = pthread_create(&thread, NULL, (void*)sessionAcceptorThread, (void*) arguments);

    if(created != 0){
        printf("pthread_create FAILED\n");
        return 0;
    }

    pthread_join(thread,NULL);
    return 0; 
}