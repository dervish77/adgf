/* cubeclient.c - cubeclient, main */

/* this program sends commands via TCP to a remote host */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define LINELEN      128

#include "tcplib.h"



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



/* sendcommand -- send command and receive response */
int
sendcommand(host, port, command)
   char *host;
   char *port;
   char *command;
{
   char  buf[LINELEN+1];        /* buffer for one line of text */
   char  *sbuf;
   int   s, n;                  /* socket, read count */
   int   outchars, inchars;     /* characters sent and received */
   long  timevar;
   
   s = connectTCP(host, port);	           /* connect to server machine */

   fprintf(stdout,"\nconnected to %s.%s\n\n", host, port);

/* send command to remote host */
   sbuf = strcpy(buf, command);  /* copy command to send buffer */
   sbuf[LINELEN] = '\0';         /* insure line null-terminated */
   outchars = strlen(sbuf);
   time(&timevar);
   fprintf(stdout,"command sent: %s at %s", command, ctime(&timevar));
   (void) write(s, sbuf, outchars);

/* read it back -- server just echos command sent */
   for (inchars = 0; inchars < outchars; inchars+=n ) {
      n = read(s, &buf[inchars], outchars - inchars);
      if (n < 0)
         errexit("socket read failed: %s\n", sys_errlist[errno]);
   }
   time(&timevar);
   fprintf(stdout,"command received: %s at %s", buf, ctime(&timevar));

   if (shutdown(s, 2) == -1)     /* shutdown connection in both directions */
      errexit("shutdown failed: %s\n", sys_errlist[errno]);
   if (close(s) == -1)           /* close connection to server machine */
      errexit("close failed: %s\n", sys_errlist[errno]);
}

/* menu() -- prints menu, waits for choice, returns command string */
int
menu(command)
   char *command;
{ 
   int choice, done=0, stopflag=0;
   char data[LINELEN];

   while (!done) {
      printf("\nCommand Menu:\n");
      printf("   1. start\n");
      printf("   2. send\n");
      printf("   3. solve\n");
      printf("   4. stop\n");
      printf("   5. exit program\n");
      printf("enter choice #: ");
      scanf("%d",&choice);

      switch(choice) {
         case 1:
            sprintf(command, "start");
            done = 1;
            break;
         case 2:
            printf("\nenter data to be sent: ");
            scanf("%s",&data);
            sprintf(command, "send %s", data);
            done = 1;
            break;
         case 3:
            sprintf(command, "solve");
            done = 1;
            break;
         case 4:
            sprintf(command, "stop");
            done = 1;
            stopflag = 1;
            break;
         case 5:
            sprintf(command, "");
            done = 1;
            stopflag = 2;
            break;
         default:
            printf("\ninvalid choice entered, re-enter\n\n");
            break;
      }
   }
   return(stopflag);
}

/* main - TCP client for cube service example */
int
main(argc, argv)
   int   argc;
   char  *argv[];
{
   char  *host = "localhost";    /* host to use if none supplied */
   char  *port;                  /* default service port */
   int   doneflag=0;
   char  command[LINELEN];
   
   switch (argc) {
      case 3:
         host = argv[1];
         port = argv[2];
         break;
      default:
         fprintf(stderr, "usage: cubeclient <host> <port>\n");
         exit(1);
   }

   while (doneflag == 0) {
      doneflag = menu(command);            /* print menu and get choice */
      if (doneflag != 2)
         sendcommand(host, port, command); /* send command choice */
   }
   exit(0);
}
      
     
