/********************************************************
*
* Remote calling client test program. (using rcmd)
*
* File:   rcmdtest.c
*
* Rev 0.0  02/02/96  Originated
*
* Author: Brian Lingard
*
* Usage:  rcmdtest <host>
*
*	where <host> - remote system host name (i.e. tif686)
*
* Notes:  Remote uses 'rcmd' to remotely execute a command
*         on another system.  The user can pass a list of
*         arguments to the remote command.
*
*********************************************************/

/* This program accesses the TCP service rexecd on a remote host */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN		128

#define HOST_NAME_LEN	20
typedef char HOST_NAME_T[HOST_NAME_LEN];


static char *cliuname = "lingard";
static char *servuname = "lingard";

static char *cmdpath = "/home/hki020hk/lingard/misc/ee/class/tcptest/remote/";


/*  pr_inet
 *
 *  print each internet address in dotted decimal notation
 */
void
pr_inet( char **listptr, int length)
{
   struct in_addr *ptr;

   while ( (ptr = (struct in_addr *) *listptr++) != NULL )
   {
      printf("%s,", inet_ntoa(*ptr));
   }
}



/*  main program
 */
int
main(argc, argv)
   int   argc;
   char  *argv[];
{
   char 		*host;
   char 		arg_string[LINELEN];
   char 		cmd_string[LINELEN];

   int 			sockfd1, sockfd2;
   struct hostent	*phe;    /* pointer to host information entry */
   struct servent	*pse;    /* pointer to service information entry */

   register char 	*ptr;

   char			**ahost;

   HOST_NAME_T		host_name;
   char			*host_ptrs[5];


   /*  extract host argument from command line 
    */
   switch (argc) {
      case 2:
         host = argv[1];
         break;
      default:
         fprintf(stderr, "usage: %s <host>\n\n", argv[0]);
         exit(1);
   }


   /*  get user input string
    */
   printf("\nEnter a command string (i.e. test 1 2<cr>):\n");
   printf("=> ");
   fgets( arg_string, LINELEN, stdin );

   strcpy( cmd_string, cmdpath);
   strcat( cmd_string, arg_string);

   /*  get remote port for shell service 
    */
   if ( (pse = getservbyname("shell", "tcp") ) == NULL)
   {
      fprintf(stderr, "error: shell/tcp unknown service\n\n");
      exit(1);
   }

   printf("\ngot remote port for shell service - %d\n", pse->s_port);

   /*  map host name to IP address, allowing for dotted decimal
    */
   if ( (phe = gethostbyname(host)) == NULL )
   {
      fprintf(stderr, "error: can't get host entry for - %s\n\n", host);
      exit(1);
   }

   printf("\nmapped host name (%s) to IP address (", phe->h_name);
   pr_inet( phe->h_addr_list, phe->h_length );
   printf(")\n");

   host_ptrs[0] = host;
   host_ptrs[1] = (char *)NULL;

   ahost = (char **)&host_ptrs;


   /*  execute command string remotely using rcmd
    */
   sockfd1 = rcmd( ahost, 			/* ahost */
			pse->s_port, 		/* remport */
			cliuname, 		/* cliuname */
			servuname, 		/* servuname */
			cmd_string, 		/* cmd */
			&sockfd2 );		/* sockfd2 */

   printf("\ngot sockfd1 = %d, sockfd2 = %d\n", sockfd1, sockfd2);

   if ( sockfd1 < 0 )
   {
      fprintf(stderr, "error: rcmd failed\n\n");
      exit(1);
   }

   printf("\nsent - %s - successfully!\n", arg_string);

   exit(0);
}
      
     
