#include "elf.h"

void hexOutWrite(byte value) {
  int i;
  i=value>>4;
  if (i>=0 && i<4) {
    hexDisp[i].number=value&15;
    til311Paint(&hexDisp[i],display,hexOutWindow);
    }
  }

void hexOutEvent(rcs_Event event) {
  rcs_GC gc;
  int    i;
  if (event.type == EVENT_EXPOSE) {
    gc=rcs_openGC(display,hexOutWindow);
    rcs_copyArea(display,hexOutBuffer,hexOutWindow,gc,0,0,178,102,0,0);
    rcs_closeGC(display,gc);
    for (i=0;i<4;i++) til311Paint(&hexDisp[i],display,hexOutWindow);
    }
  }

