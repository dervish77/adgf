/********************************************************
*
* server program example
*
* File:   server.c 	
*
* Rev 0   3/6/94   Originated
*
* Author: Brian Lingard
*
* Usage:  server <port>
*
*	where port = numeric name of service (ex. 50001)
*
* Unix Compile string:	cc server.c -O -o server -lsocket -lnsl
*
*********************************************************/


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <netdb.h>

#define MSGLEN 10

int s;                        /* connected socket descriptor */
int ls;                       /* listen socket descriptor */

struct hostent *hp;           /* pointer to host info for remote host */
struct servent *sp;           /* pointer to service informaion */

long timevar;
char *ctime();

struct linger linger;         /* allow a lingering, graceful close; */
                              /* used when setting SO_LINGER */

struct sockaddr_in myaddr_in;    /* for local socket address */
struct sockaddr_in peeraddr_in;  /* for peer socket address */

main(argc,argv)
   int argc;
   char *argv[];
{
   int addrlen;
   
   if (argc != 2) {
      fprintf(stderr,"Usage: %s <port>\n",argv[0]);
      exit(1);
   }
   
   memset((char *)&myaddr_in, 0, sizeof(struct sockaddr_in));
   memset((char *)&peeraddr_in, 0, sizeof(struct sockaddr_in));
   
   myaddr_in.sin_family = AF_INET;
   myaddr_in.sin_addr.s_addr = INADDR_ANY;
   
   myaddr_in.sin_port = atoi(argv[1]);    /* assign service port */
   
   ls = socket(AF_INET, SOCK_STREAM, 0);  /* create listen socket */
   if (ls == -1) {
      perror(argv[0]);
      fprintf(stderr,"%s: unable to create listen socket\n", argv[0]);
      exit(1);
   }
   
   if (bind(ls, (struct sockaddr *)&myaddr_in, sizeof(myaddr_in)) == -1) {
      perror(argv[0]);
      fprintf(stderr,"%s: unable to bind listen address\n", argv[0]);
      exit(1);
   }
   
   if (listen(ls, 5) == -1) {
      perror(argv[0]);
      fprintf(stderr,"%s: unable to listen on socket\n",argv[0]);
      exit(1);
   }
   
   setpgrp();  /* disassociate parent's terminal from child process */
   
   switch(fork()) {
      case -1:             /* unable to fork for some reason */
         perror(argv[0]);
         fprintf(stderr, "%s:unable to fork daemon\n",argv[0]);
         exit(1);
      case 0:              /* child process comes here */
         close(stdin);
         close(stderr);
         signal(SIGCLD, SIG_IGN);   /* prevent accumulation of zombies */
         for(;;) {
            addrlen = sizeof(struct sockaddr_in);
            s = accept(ls, (struct sockaddr *)&peeraddr_in, &addrlen); /* wait for connection */
            if (s == -1) exit(1);
            switch(fork()) {
               case -1:       /* can't fork, just exit */
                  exit(1);
               case 0:        /* child process comes here */
                  server();
                  exit(0);
               default:       /* daemon process comes here */
                  close(s);
            }
         }
      default:             /* parent process comes here */
         exit(0);
   }
} /* end of main */


/* server() -- handle individual connection */
server()
{
   int reqcnt = 0;         /* keeps count of number of requests */
   char buf[MSGLEN];           /* use MSGLEN byte messages */
   char *inet_ntoa();
   char *hostname;         /* points to remote host's name string */
   int len, len1;
   
   close(ls);         /* close listen socket inherited from daemon */
   
   hp = gethostbyaddr((char *)&peeraddr_in.sin_addr, 
                         sizeof(struct in_addr), peeraddr_in.sin_family);
                         
   if (hp == NULL) {
      hostname = inet_ntoa(peeraddr_in.sin_addr);
   }
   else {
      hostname = hp->h_name;
   }
   
   time(&timevar);
   printf("Startup from %s port %u at %s",hostname,
                        ntohs(peeraddr_in.sin_port), ctime(&timevar));
   
   linger.l_onoff = 1;
   linger.l_linger = 1;
   if (setsockopt(s, SOL_SOCKET, SO_LINGER, (const char *)&linger, sizeof(linger)) == -1){
      printf("Connection with %s aborted on error\n",hostname);
      exit(1);
   }
   
   while (len = recv(s, buf, MSGLEN, 0)) {
      if (len == -1) {  /* error from recv */
         printf("Connection with %s aborted on error\n",hostname);
         exit(1);
      }
      while (len < MSGLEN) {
         len1 = recv(s, &buf[len], MSGLEN-len, 0);
         if (len == -1) {
            printf("Connection with %s aborted on error\n",hostname);
            exit(1);
         }
         len += len1;
      }
      
      reqcnt++;
      sleep(1);      /* simulate processing by server */
      if (send(s, buf, MSGLEN, 0) != MSGLEN) {
         printf("Connection with %s aborted on error\n",hostname);
         exit(1);
      }
   }
   close(s);   /* no more requests, close socket with lingering */
   
   time(&timevar);
   printf("Completed %s port %u, %d requests, at %s]n",
            hostname, ntohs(peeraddr_in.sin_port),reqcnt,ctime(&timevar));
} /* end of server() */
   
