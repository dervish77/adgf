#include <stdio.h>
#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h>
#include <termios.h>
#endif

#ifdef UNIX
struct termios term,old;

void openterm() {
  if (tcgetattr(0,&term)!=0) printf("Error getting term data\n");
  old=term;
  }

void closeterm() {
  if (tcsetattr(0,TCSANOW,&old)!=0) printf("Could not set term\n");
  }

void echoon() {
  term.c_lflag|=ECHO;
  if (tcsetattr(0,TCSANOW,&term)!=0) printf("Could not set term\n");
  }

void echooff() {
  term.c_lflag&=~ECHO;
  if (tcsetattr(0,TCSANOW,&term)!=0) printf("Could not set term\n");
  }

void unbuffered() {
  term.c_lflag&=~ICANON;
  term.c_cc[VMIN]=0;
  term.c_cc[VTIME]=0;
  if (tcsetattr(0,TCSANOW,&term)!=0) printf("Could not set term\n");
  }

void buffered() {
  term.c_lflag|=ICANON;
  if (tcsetattr(0,TCSANOW,&term)!=0) printf("Could not set term\n");
  }

int inkey() {
  char           c;
  fd_set         rfds;
  struct timeval tv;
  tv.tv_sec=0;
  tv.tv_usec=0;
  FD_ZERO(&rfds);
  FD_SET(0,&rfds);
  c=select(1,&rfds,NULL,NULL,&tv);
  if (c!=0) c=fgetc(stdin);
  return c;
  }

main() {
  char c;
  int  flag;
  char buffer[100];

  setbuf(stdout,NULL);
/*  setbuf(stdin,NULL); */
  openterm();
  echooff();
  unbuffered();
  flag=0;
  while (flag==0) {
/*    c=inkey(); */
    c=fgetc(stdin);
    if (c>0) printf("%d\n",c);
    if (c==27) flag=1;
    }
  closeterm();
  }
#endif
