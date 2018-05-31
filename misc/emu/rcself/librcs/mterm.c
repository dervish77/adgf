#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#ifdef UNIX
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#endif
#ifdef MSDOS
#include <dos.h>
#include <conio.h>
#endif
#ifdef WIN32
#include <wtypes.h>
#include <winbase.h>
#endif

#include "librcs.h"

void rcs_output(char* Buffer)
{
  printf("%s",Buffer);
}

void rcs_input(char* Buffer)
{
  Buffer[0]='\0';
  gets(Buffer);
}

int rcs_inkey() {
#ifdef MSDOS
  int key;
  if (kbhit()) {
    key= getch();
    if (key != 0) return key;
    key=getch();
    switch (key) {
      case 72:key=MTERM_UP; break;
      case 80:key=MTERM_DOWN; break;
      case 75:key=MTERM_LEFT; break;
      case 77:key=MTERM_RIGHT; break;
      default:key+=256;
      }
    return key;
    }
#endif
#ifdef UNIX
  int           c;
  fd_set         rfds;
  struct timeval tv;
  tv.tv_sec=0;
  tv.tv_usec=0;
  FD_ZERO(&rfds);
  FD_SET(0,&rfds);
  c=select(1,&rfds,NULL,NULL,&tv);
  if (c!=0) c=fgetc(stdin);
  tv.tv_sec=0;
  tv.tv_usec=0;
  FD_ZERO(&rfds);
  FD_SET(0,&rfds);
  if (c==27 && select(1,&rfds,NULL,NULL,&tv)!=0) {
    c=fgetc(stdin);
    if (c==91 && select(1,&rfds,NULL,NULL,&tv)!=0) {
      c=fgetc(stdin);
      switch (c) {
        case 65:c=MTERM_UP; break;
        case 66:c=MTERM_DOWN; break;
        case 68:c=MTERM_LEFT; break;
        case 67:c=MTERM_RIGHT; break;
        default:c+=256;
        }

      } else ungetc(c,0);
    }
  return c;
#endif
  return 0;
  }

void rcs_clrScr()
{
#ifdef MSDOS
  clrscr();
#endif
#ifdef UNIX
  rcs_output("\E[H\E[2J");
#endif
}

void rcs_delay(int sec)
{
#ifdef WIN32
  Sleep(sec*1000);
#endif
#ifdef UNIX
  sleep(sec);
#endif
#ifdef MSDOS
  sleep(sec);
#endif
}

void rcs_gotoXY(int x,int y)
{
#ifdef MSDOS
  gotoxy(x,y);
#endif
#ifdef UNIX
  char XBuffer[10];
  char YBuffer[10];
  char Buffer[20];
  sprintf(XBuffer,"%d",x);
  sprintf(YBuffer,"%d",y);
  strcpy(Buffer,"\E["); strcat(Buffer,YBuffer); strcat(Buffer,";");
  strcat(Buffer,XBuffer); strcat(Buffer,"H");
  rcs_output(Buffer);
#endif
}

#ifdef UNIX
int rcs_getTerm(rcs_Termio* term) {
  if (tcgetattr(0,term)!=0) return -1;
  return 0;
  }

int rcs_setTerm(rcs_Termio* term) {
  if (tcsetattr(0,TCSANOW,term)!=0) return -1;
  return 0;
  }

int rcs_echoOn(rcs_Termio* term) {
  term->c_lflag |= ECHO;
  if (tcsetattr(0,TCSANOW,term)!=0) return -1;
  return 0;
  }

int rcs_echoOff(rcs_Termio* term) {
  setbuf(stdin,NULL);
  term->c_lflag &= ~ECHO;
  if (tcsetattr(0,TCSANOW,term)!=0) return -1;
  return 0;
  }

int rcs_buffered(rcs_Termio* term) {
  term->c_lflag |= ICANON;
  if (tcsetattr(0,TCSANOW,term)!=0) return -1;
  return 0;
  }

int rcs_unBuffered(rcs_Termio* term) {
  term->c_lflag &= ~ICANON;
  if (tcsetattr(0,TCSANOW,term)!=0) return -1;
  return 0;
  }
#endif

