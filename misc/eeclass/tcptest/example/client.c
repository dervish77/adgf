/********************************************************
*
* client program example
*
* File:   client.c 	
*
* Rev 0   3/6/94   Originated
*
* Author: Brian Lingard
*
* Usage:  client <remote host> <port>
*
*	where host = name of machine (ex. tif686)
*	      port = numeric name of service (ex. 50001)
*
* Unix Compile string:	cc client.c -O -o client -lsocket -lnsl
*
*********************************************************/


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>

#define MSGLEN 10

int s;                     /* connected socket descriptor */

struct hostent *hp;        /* pointer to host info for remote host */
struct servent *sp;        /* pointer to service information */

long timevar;              /* contains time returned by time() */
char *ctime();             /* declare time formatting routine */

struct sockaddr_in myaddr_in;    /* for local socket address */
struct sockaddr_in peeraddr_in;  /* for peer socket address */

main(argc,argv)
   int argc;
   char *argv[];
{
   int addrlen, i, j;
   char buf[MSGLEN];           /* message buffer of MSGLEN chars */
   
   if (argc != 3) {
      fprintf(stderr,"Usage:  %s <remote host> <port>\n", argv[0]);
      exit(1);
   }
   
   memset ((char *)&myaddr_in, 0, sizeof(struct sockaddr_in));
   memset ((char *)&peeraddr_in, 0, sizeof(struct sockaddr_in));
   
   peeraddr_in.sin_family = AF_INET;
   
   hp = gethostbyname(argv[1]);
   if (hp == NULL) {
      fprintf(stderr,"%s: %s not found in /etc/hosts\n",argv[0],argv[1]);
      exit(1);
   }
   peeraddr_in.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
   
   peeraddr_in.sin_port = atoi(argv[2]);  /* server's port number */
   
   s = socket(AF_INET, SOCK_STREAM, 0);   /* create socket */
   if (s == -1) {
      perror(argv[0]);
      fprintf(stderr,"%s: unable to create socket\n",argv[0]);
      exit(1);
   }
   
   if (connect(s, (struct sockaddr *)&peeraddr_in, sizeof(peeraddr_in)) == -1) {
      perror(argv[0]);
      fprintf(stderr,"%s: unable to connect to remote\n",argv[0]);
      exit(1);
   }
   
   addrlen = sizeof(struct sockaddr_in);  /* get addr of this end */
   if (getsockname(s, (struct sockaddr *)&myaddr_in, &addrlen) == -1) {
      perror(argv[0]);
      fprintf(stderr,"%s: unable to read socket address\n", argv[0]);
      exit(1);
   }
   
   time(&timevar);
   printf("Connected to %s on port %u at %s\n",      
                     argv[1], ntohs(myaddr_in.sin_port), ctime(&timevar));
   
   sleep(5);   /* simulate preliminary processing */
   
   for (i=1; i<=5; i++){               /* send request to server */
      *buf = i;
      if (send(s, buf, MSGLEN, 0) != MSGLEN) {
         fprintf(stderr,"%s: Connection aborted on error ", argv[0]);
         fprintf(stderr,"on send number %d\n", i);
         exit(1);
      }
   }
   
   if (shutdown(s, 1) == -1) {         /* shutdown connection */
      perror(argv[0]);
      fprintf(stderr,"%s: unable to shutdown socket\n",argv[0]);
      exit(1);
   }
   
   while (i = recv(s, buf, MSGLEN, 0)) {   /* receive results from server */
      if (i == -1) {
         perror(argv[0]);
         fprintf(stderr,"%s: error reading result\n", argv[0]);
         exit(1);
      }
      while (i < MSGLEN) {
         j = recv(s, &buf[i], MSGLEN-i, 0);
         if (j == -1) {
            perror(argv[0]);
            fprintf(stderr,"%s: error reading result\n", argv[0]);
            exit(1);
         }
         i += j;
      }
      printf("Received result number %d\n", *buf);
   }
   
   time(&timevar);
   printf("All done at %s",ctime(&timevar));
}
            
