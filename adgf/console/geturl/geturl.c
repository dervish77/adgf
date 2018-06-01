/******************************************************************************

  Get URL test program.

    File:	geturl.c

    Author:	Brian Lingard
	
    Date:	02/16/96

******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif   /* INADDR_NONE */


#define ERROR 0
#define BUF_SIZE 4096

#include <errno.h>
//extern int  errno;


unsigned long   inet_addr();


/* errexit - print an error message and exit */

#include <stdarg.h>

static int
errexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}

/*
 * Get the data at a URL and return it.
 *
 * Called is responsible for calling 'free' on
 * returned *data.
 *
 * Returns 0 is something wrong.
 * 
 * BUG: no timeouts and doesn't check all error returns
 */
size_t 
getURLbyParts( void** data, char* machine, int port, char* file )
{
   struct hostent *he;
   struct servent *se;
   struct protoent *pe;
   struct sockaddr_in sin;
   int sock;
   int bytes;
   char buf[BUF_SIZE];
   char* results = 0;
   size_t size;
   int newSize;


   /* BUG: use malloc, but freeing after error is a problem */
   char getString[2048]; 


#ifdef _USE_BSD
   bzero((char *)&sin, sizeof(sin));
#else
   memset((char *)&sin, 0, sizeof(sin));
#endif

   sin.sin_family = AF_INET;
   sin.sin_port = port;

   data = 0;
#ifdef _USE_BSD
   if ( he = gethostbyname(machine) )
      bcopy(he->h_addr, (char *)&sin.sin_addr, he->h_length);
#else
   if ( he = gethostbyname(machine) )
      memcpy((char *)&sin.sin_addr, he->h_addr, he->h_length);
#endif
   else if ( (sin.sin_addr.s_addr = inet_addr(machine)) == INADDR_NONE )
      errexit("getURLbyParts: Can't get \"%s\" host entry\n", machine);


   if ( (pe = getprotobyname("tcp")) == 0)
      errexit("getURLbyParts: Can't get \"%s\" protocol entry\n", "tcp");


   sock = socket(he->h_addrtype, SOCK_STREAM, pe->p_proto);
   if (sock < 0)
      errexit("Can't create socket: %s\n", strerror(errno));

#ifdef _DEBUG
   fprintf(stderr, "getURLbyParts: sock = %d\n", sock);
#endif


/*
   sin.sin_family = he->h_addrtype;
   if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
      errexit("getURLbyParts: Can't bind to %d port: %s\n", port, 
						strerror(errno));
*/

#ifdef _USE_BSD
   bcopy(he->h_addr, &sin.sin_addr, he->h_length);
#else
   memcpy(&sin.sin_addr, he->h_addr, he->h_length);
#endif

   se = getservbyname("telnet", "tcp");

   sin.sin_port = port;
   if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
      errexit("getURLbyParts: Can't connect to %s.%s: %s\n", machine, port, 
						strerror(errno));

   /* send GET message to http */
   sprintf(getString, "GET %s\n", file);
   if ( write( sock, getString, strlen(getString) != strlen(getString) ) )
   {
      return ERROR;
   }

#ifdef _DEBUG
   fprintf(stderr, "getURLbyParts: sent %s to http\n", getString);
#endif

   /* get data */
   size = 0;
   results = 0;
   while( (bytes = read(sock,buf,BUF_SIZE)) > 0) 
   {
      newSize = size + bytes;
      results = realloc( results, newSize );
      assert( results );

#ifdef _USE_BSD
      bcopy( buf, results + size, bytes );
#else
      memcpy(results + size, buf, bytes);
#endif

      size += bytes;
   }

   *data = (void*)results;

   return size;
}

/* Get the data at a URL and return it.
 *
 * Called is responsible for calling 'free' on
 * returned *data.
 *
 * url must be of the form http://machine-name[:port]/file-name
 *
 * Returns 0 is something wrong.
 */
size_t 
getURL( void** data, char* url )
{
   char* s;
   size_t size;
   char* machine;
   int machineLen; /* length of machine name */
   int port;
   char* file = 0;
   char* http = "http://";
   int httpLen = strlen( http );

#ifdef _DEBUG
   fprintf(stderr, "getURL: url = %s\n", url);
#endif

   if ( !url ) 
   {
      return ERROR;
   }

   if ( strncmp( http, url, httpLen) ) 
   {
      return 0;
   }

   /* get the machine name */
   for( s = url + strlen(http) + 1; *s && (*s != ':') && (*s != '/'); s++ );

   machineLen = s - url;
   machineLen -= httpLen;
   machine = (char*)malloc( machineLen + 1 ); assert( machine );
   strncpy( machine, url + httpLen, machineLen );

#ifdef _DEBUG
   fprintf(stderr, "getURL: machine = %s\n", machine);
#endif

   /* get port number */
   if ( *s == ':' ) 
   {
      port = atoi( ++s );
      while( *s && (*s != '/') )
      s++;
   } 
   else 
   {
      port = 80;
   }

#ifdef _DEBUG
   fprintf(stderr, "getURL: port = %d\n", port);
#endif

   /* get the file name */
   if ( *s == '/' ) 
      file = s;
   else
      file = "/";

#ifdef _DEBUG
   fprintf(stderr, "getURL: file = %s\n", file);
#endif

   size = getURLbyParts( data, machine, port, file );

   free( machine );

   return size;
}

int main( int argc, char** argv )
{
   char* url = argv[1];
   void* data;
   size_t size;

#ifdef _DEBUG
   fprintf(stderr, "main: url = %s\n", argv[1]);
#endif

   size = getURL( &data, url );

   if (size > 0)
   {
      printf("data at url is:\n");
      printf("%s\n", data);
   }

   exit(0);
}

