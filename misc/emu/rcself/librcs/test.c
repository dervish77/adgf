#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

main() {
  Display *d;
  d=XOpenDisplay(":0.0");
  printf("%d\n",(&d)->default_screen);
  XCloseDisplay(d);
  }

