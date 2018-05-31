#include "librcs.h"

int rcs_clip(int* x1,int* y1,int* x2,int* y2,int lx,int ly,int hx,int hy) {
  int i,dx,dy;
  if (*x1>=lx && *x2>=lx && *x1<=hx && *x2<=hx &&
      *y1>=ly && *y2>=ly && *y1<=hy && *y2<=hy) return 1;
  if ((*x1<lx && *x2<lx) || (*x1>hx && *x2>hx) ||
      (*y1<ly && *y2<ly) || (*y1>hy && *y2>hy)) return 0;
  if (*x1==*x2) {
    if (*y1<ly) *y1=ly; else if (*y1>hy) *y1=hy;
    if (*y2<ly) *y2=ly; else if (*y2>hy) *y2=hy;
    return 1;
    }
  if (*y1==*y2) {
    if (*x1<lx) *x1=lx; else if (*x1>hx) *x1=hx;
    if (*x2<lx) *x2=lx; else if (*x2>hx) *x2=hx;
    return 1;
    }
  if (*x2<*x1) {
    i=*x1; *x1=*x2; *x2=i;
    i=*y1; *y1=*y2; *y2=i;
    }
  dx=*x2-*x1; dy=*y2-*y1;
  if (*x2>hx) { *y2-=(*x2-hx)*dy/dx; *x2=hx; }
  if (*x1<lx) { *y1-=(*x1-lx)*dy/dx; *x1=lx; }
  if (dx<0) dx=-dx;
  if (dy<0) dy=-dy;
  if (*y2>hy) { *x2-=(*y2-hy)*dx/dy; *y2=hy; }
  if (*y2<ly) { *x2-=(ly-*y2)*dx/dy; *y2=ly; }
  if (*y1>hy) { *x1+=(*y1-hy)*dx/dy; *y1=hy; }
  if (*y1<ly) { *x1+=(ly-*y1)*dx/dy; *y1=ly; }
  if (*x1<lx || *x1>hx || *x2<lx || *x2>hx ||
      *y1<ly || *y1>hy || *y2<ly || *y2>hy) return 0;
  return 1;
  }

  
