/* cubeserver2.c - handlecommand, main */

#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

#include "tcplib.h"

#define QLEN         5     /* maximum connection queue length */
#define BUFSIZE      4096

int reaper();



/* errexit - print an error message and exit */

#include <varargs.h>

static int
errexit( format, va_alist)
char *format;
va_dcl
{
   va_list args;
   va_start(args);
   _doprnt(format, args, stderr);
   va_end(args);
   exit(1);
}


/* main - iterative TCP server for cubeserver service */
int
main(argc, argv)
   int   argc;
   char  *argv[];
{
   char     *port;               /* service name or port number */
   struct   sockaddr_in fsin;    /* the address of a client */
   int      alen;                /* length of client's address */
   int      msock;               /* master server socket */
   int      ssock;               /* slave server socket */
   FILE     *logfile;
   
   switch (argc) {
      case 2:
         port = argv[1];
         break;
      default:
         fprintf(stderr, "usage: cubeserver2 <port>\n");
         exit(1);
   }

   logfile = fopen("logcmd.out", "w");
   
   msock = passiveTCP(port, QLEN);
   
   (void) signal(SIGCHLD, reaper);    /* cleanup zombies */
   
   while (1) {
      alen = sizeof(fsin);
      ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
      if (ssock < 0) {
         if (errno == EINTR)
            continue;
         errexit("accept: %s\n", sys_errlist[errno]);
      }
      (void) handlecommand(ssock, logfile);
      (void) close(ssock);
   }
}


/* handlecommand - echo commands received */
int
handlecommand(fd, logfile)
   int fd;
   FILE *logfile;
{
   char  buf[BUFSIZE];
   int   cc;
   
   cc = read(fd, buf, sizeof(buf));                 /* read command */
   if (cc < 0)
      errexit("echo read: %s\n", sys_errlist[errno]);
   logcmd(logfile, buf);
   printf("server: command received %s\n",buf);
   if (write(fd, buf, cc) < 0)                     /* echo command */
      errexit("echo write: %s\n", sys_errlist[errno]);

   return 0;
}


/* logcmd() - log commands recieved in log file */
int
logcmd(logfile, cmd)
   FILE *logfile;
   char *cmd;
{
   long timevar;

   time(&timevar);
   fprintf(logfile,"%s received at %s", cmd, ctime(&timevar));
   return 0;
}


/* reaper - clean up zombie children */
int
reaper()
{
/*
   union wait  status;
*/
   
/*
   while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0) 
   {

   }
*/
}
