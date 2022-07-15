#include <librcs.h>
#include "elf.h"

#define CYCLE 25000

void v1870_redraw();

void v1870_o3(byte value) {
  v1870.reg3 = value;
  v1870_redraw();
  }

void v1870_o5(byte value) {
  v1870.reg5 = v1870.addr;
  v1870_redraw();
  }

void v1870_o6(byte value) {
  v1870.reg6 = (v1870.addr & 0x7ff);
  }

void v1870_o7(byte value) {
  v1870.reg7 = (v1870.addr & 0x7ff);
  v1870_redraw();
  }

void v1870_cycle() {
  v1870.cycle --;
  if (v1870.cycle <= 0) {
    v1870.cycle = CYCLE;
    cdp1802Int(&cpu);
    }
  }

void v1870_configure(char* arg) {
  use1870 = 'Y';
  outPorts[2].out = v1870_o3;
  outPorts[4].out = v1870_o5;
  outPorts[5].out = v1870_o6;
  outPorts[6].out = v1870_o7;
  }

V1870 v1870_init() {
  int i;
  V1870 ret;
  for (i=0; i<2024; i++) ret.cram[i] = 0;
  for (i=0; i<2048; i++) ret.pram[i] = 0;
  ret.reg3 = 0;
  ret.reg5 = 0;
  ret.reg6 = 0;
  ret.cycle = CYCLE;
  return ret;
  }

void v1870_event(rcs_Event event) {
  if (event.type == EVENT_EXPOSE) {
    v1870_redraw();
    }
  }

byte v1870_read(word addr) {
  if (addr >= 0xf400 && addr < 0xf800) return v1870.cram[addr - 0xf400];
  if (addr >= 0xf800 && addr <= 0xffff) return v1870.pram[addr - 0xf800];
  return 255;
  }

void v1870_drawLine(int x,int y,byte v,byte pcb) {
  int i;
  int clr;
  rcs_GC fore;
  rcs_GC back;
  if ((v1870.reg5 & 0x80) == 0) y *= 2;
  fore = rcs_openGC(display,v1870Window);
  back = rcs_openGC(display,v1870Window);
  switch (v1870.reg3 & 7) {
    case 0:rcs_namedForeground(display,back,"black"); break;
    case 1:rcs_namedForeground(display,back,"green"); break;
    case 2:rcs_namedForeground(display,back,"blue"); break;
    case 3:rcs_namedForeground(display,back,"cyan"); break;
    case 4:rcs_namedForeground(display,back,"red"); break;
    case 5:rcs_namedForeground(display,back,"yellow"); break;
    case 6:rcs_namedForeground(display,back,"magenta"); break;
    case 7:rcs_namedForeground(display,back,"white"); break;
    }
  clr = 0;
  switch (v1870.reg3 & 0x60) {
    case 0x00:if (v & 0x40) clr += 4;
              if (v & 0x80) clr += 2;
              if (pcb) clr += 1;
              break;
    case 0x20:if (v & 0x40) clr += 4;
              if (pcb) clr += 2;
              if (v & 0x80) clr += 1;
              break;
    case 0x40:if (pcb) clr += 4;
              if (v & 0x40) clr += 2;
              if (v & 0x80) clr += 1;
              break;
    case 0x60:if (pcb) clr += 4;
              if (v & 0x40) clr += 2;
              if (v & 0x80) clr += 1;
              break;
    }
  switch (clr) {
    case 0:rcs_namedForeground(display,fore,"black"); break;
    case 1:rcs_namedForeground(display,fore,"green"); break;
    case 2:rcs_namedForeground(display,fore,"blue"); break;
    case 3:rcs_namedForeground(display,fore,"cyan"); break;
    case 4:rcs_namedForeground(display,fore,"red"); break;
    case 5:rcs_namedForeground(display,fore,"yellow"); break;
    case 6:rcs_namedForeground(display,fore,"magenta"); break;
    case 7:rcs_namedForeground(display,fore,"white"); break;
    }
  v <<= 2;
  for (i=0; i<6; i++) {
    if (v & 128) {
      rcs_drawPoint(display,v1870Window,fore,x,y);
      if ((v1870.reg5 & 0x80) == 0) {
        rcs_drawPoint(display,v1870Window,fore,x,y+1);
        }
      if ((v1870.reg3 & 0x80) != 0x80) {
        rcs_drawPoint(display,v1870Window,fore,x+1,y);
        if ((v1870.reg5 & 0x80) == 0) {
          rcs_drawPoint(display,v1870Window,fore,x+1,y+1);
          }
        }
      } else {
      rcs_drawPoint(display,v1870Window,back,x,y);
      rcs_drawPoint(display,v1870Buffer,back,x,y);
      if ((v1870.reg5 & 0x80) == 0) {
        rcs_drawPoint(display,v1870Window,back,x,y+1);
        }
      if ((v1870.reg3 & 0x80) != 0x80) {
        rcs_drawPoint(display,v1870Window,back,x+1,y);
        if ((v1870.reg5 & 0x80) == 0) {
          rcs_drawPoint(display,v1870Window,back,x+1,y+1);
          }
        }
      }
    x++;
    if ((v1870.reg3 & 0x80) != 0x80) x++;
    v <<= 1;
    }
  rcs_closeGC(display,fore);
  rcs_closeGC(display,back);
  }

void v1870_drawChar(int x,int y,byte v) {
  int i;
  int a;
  int l;
  byte pcb;
  pcb = (v & 0x80) ? 1 : 0;
  if ((v1870.reg3 & 0x10) == 0x10) return;
v &= 0x7f;
  if ((v1870.reg3 & 0x80) != 0x80) x *= 2;
  l = ((v1870.reg5 & 0x8) == 0x8) ? 9 : 8;
  a = v * 16;
  for (i=0; i<l; i++) {
    v1870_drawLine(x,y,v1870.cram[a],pcb);
    a++;
    y++;
    }
  }

void v1870_write(word addr,byte v) {
  int i;
  int l;
  int a;
  int x,y;
  word ac;
  int m;
  m = ((v1870.reg3 & 0x80) == 0x80) ? 40 : 20;
  l = ((v1870.reg5 & 0x8) == 0x8) ? 9 : 8;
/*  if (v1870.reg5 & 1 && (addr - 0xf800 != v1870.reg6) &&
      addr >= 0xf400 && addr <=0xffff) { */
  if (addr >= 0xf400 && addr < 0xf800) {
    if ((v1870.reg5 & 1) == 1) {
      addr -= 0xf400;
      addr &= 0xf;
      ac = v1870.reg6;
      addr += (v1870.pram[ac]) * 16;
      v1870.cram[addr] = v;
    for (i=0; i<960; i++)
      if (v1870.pram[i] == v1870.pram[ac]) {
        x = (i % m) * 6;
        y = (i / m) * l;
        v1870_drawChar(x,y,v1870.pram[i]);
        }
      return;
      }
    addr -= 0xf400;
    v1870.cram[addr] = v;
    for (i=0; i<960; i++)
      if ((v1870.pram[i] & 0x3f) == (addr / 16)) {
        x = (i % m) * 6;
        y = (i / m) * l;
        v1870_drawChar(x,y,v1870.pram[i]);
        }
    return;
    }
  if (addr >= 0xf800 && addr <= 0xffff) {
if (v1870.reg5 & 1 && (addr - 0xf800 != v1870.reg6)) return;
    addr = addr - 0xf800;
    v1870.pram[addr] = v;
    a = addr - v1870.reg7;
    if (a < 0) a += 960;
    x = (a % m) * 6;
    y = (a / m) * l;
    v1870_drawChar(x,y,v);
    }
  }

void v1870_redraw() {
  int i;
  int s;
  int m;
  int l;
  int x,y;
  int a;
  rcs_GC gc;
  if ((v1870.reg3 & 0x10) == 0x10) {
    gc = rcs_openGC(display,v1870Window);
    rcs_namedForeground(display,gc,"black");
    rcs_drawFilledBox(display,v1870Window,gc,0,0,240,216);
    rcs_closeGC(display,gc);
    return;
    }
  m = ((v1870.reg3 & 0x80) == 0x80) ? 40 : 20;
  i = ((v1870.reg5 & 0x80) == 0x80) ? 12 : 24;
  l = ((v1870.reg5 & 0x8) == 0x8) ? 9 : 8;
  s = m * i;
s=960;
  a = v1870.reg7;
  if (a<0) a = 0;
  for (i=0; i<s; i++) {
    x = (i % m) * 6;
    y = (i / m) * l;
    v1870_drawChar(x,y,v1870.pram[a]);
    a++;
    if (a>=40*24) a = 0;
    }
  }

