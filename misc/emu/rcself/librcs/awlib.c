#ifdef X
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#endif
#include "librcs.h"

#ifdef WIN32
rcs_Display disp;

int _rcs_isBitmap(rcs_Window w) {
  int i;
  if (disp.numPixmaps==0) return FALSE;
  for (i=0;i<disp.numPixmaps;i++)
    if (disp.pixmapIDs[i]==w) return TRUE;
  return FALSE;
  }

LRESULT CALLBACK rcs_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
		case WM_DESTROY:PostQuitMessage(0);
			              break;
	  default:return DefWindowProc(hWnd, message, wParam, lParam);
    }
  return 0;
  }

void rcs_initWin32(HINSTANCE hInstance) {
	WNDCLASSEX wcex;
  disp.hInstance=hInstance;
  strcpy(disp.className,"rcsawlib");
  disp.numPixmaps=0;
  disp.pixmapIDs=NULL;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)rcs_WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= disp.className;
	wcex.hIconSm		= NULL;

	RegisterClassEx(&wcex);
  }
#endif

void rcs_setWindowName(rcs_Display* d,rcs_Window w,char* name) {
#ifdef X
  XTextProperty text;
  XStringListToTextProperty(&name,1,&text);
  XSetWMName(d,w,&text);
#endif
#ifdef WIN32
  SetWindowText(w,name);
#endif
  }

#ifdef X
void rcs_background(rcs_Display* d,rcs_GC gc,
                    unsigned long red,unsigned long green,unsigned long blue) {
  XColor clr;
  clr.red=red; clr.green=green; clr.blue=blue;
  XAllocColor(d,DefaultColormap(d,DefaultScreen(d)),&clr);
  XSetBackground(d,gc,clr.pixel);
#endif
#ifdef WIN32
void rcs_background(rcs_Display* d,rcs_GC gc,
                    unsigned long red,unsigned long green,unsigned long blue) {
  gc->background=RGB(red,green,blue);
#endif
  }

void        rcs_closeDisplay(rcs_Display* display) {
#ifdef X
  XCloseDisplay(display);
#endif
  }

void rcs_closeFont(rcs_Display* d,rcs_Font font) {
#ifdef X
  XUnloadFont(d,font);
#endif
#ifdef WIN32
  DeleteObject(font);
#endif
  }

void rcs_closeGC(rcs_Display* d,rcs_GC gc) {
#ifdef X
  XFreeGC(d,gc);
  XFlush(d);
#endif
#ifdef WIN32
  free(gc);
#endif
  }

void rcs_closeWindow(rcs_Display* d,rcs_Window win) {
#ifdef X
  XDestroyWindow(d,win);
  XFlush(d);
#endif
#ifdef WIN32
  DestroyWindow(win);
#endif
  }

void rcs_copyArea(rcs_Display* d,rcs_Window src,rcs_Window dest,rcs_GC gc,
                  int sx,int sy,int w,int h,int dx,int dy) {
#ifdef X
  XCopyArea(d,src,dest,gc,sx,sy,w,h,dx,dy);
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HDC ddc;
  if (_rcs_isBitmap(src)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,src);
    } else dc=GetDC(src);
  if (_rcs_isBitmap(dest)==TRUE) {
    ddc=CreateCompatibleDC(0);
    SelectObject(ddc,dest);
    } else ddc=GetDC(dest);
  BitBlt(ddc,dx,dy,w,h,dc,sx,sy,SRCCOPY);
  if (_rcs_isBitmap(src)==TRUE) DeleteDC(dc);
    else ReleaseDC(src,dc);
  if (_rcs_isBitmap(dest)==TRUE) DeleteDC(ddc);
    else ReleaseDC(dest,ddc);
#endif
  }

rcs_Pixmap rcs_createPixmap(rcs_Display* d,rcs_Window win,int x,int y) {
  rcs_Pixmap ret;
#ifdef X
  XWindowAttributes attr;
  XGetWindowAttributes(d,win,&attr);
  ret=XCreatePixmap(d,win,x,y,attr.depth);
#endif
#ifdef WIN32
  HBITMAP    bitmap;
  HDC        dc;
  dc=GetDC(win);
  bitmap=CreateCompatibleBitmap(dc,x,y);
  ReleaseDC(win,dc);
  ret=(rcs_Pixmap)bitmap;
  if (disp.numPixmaps == 0) disp.pixmapIDs=(rcs_Window*)malloc(sizeof(rcs_Window));
    else disp.pixmapIDs=(rcs_Window*)realloc(disp.pixmapIDs,(sizeof(rcs_Window))*(disp.numPixmaps+1));
  disp.pixmapIDs[disp.numPixmaps++]=ret;
#endif
  return ret;
  }

rcs_Window  rcs_createWindow(rcs_Display* d,rcs_Window parent,
                             int x,int y,int width,int height) {
  rcs_Window ret;
#ifdef X
  unsigned long mask;
  XSetWindowAttributes attr;
  attr.background_pixel=WhitePixel(d,DefaultScreen(d));
  mask=CWBackPixel;
  ret=XCreateWindow(d,parent,x,y,width,height,0,
                       CopyFromParent,
                       CopyFromParent,
                       CopyFromParent,
                       mask,&attr);
  XSelectInput(d,ret,ExposureMask | ButtonPressMask | ButtonReleaseMask |
               ButtonMotionMask | KeyPressMask | KeyReleaseMask |
               StructureNotifyMask);
#endif
#ifdef WIN32
  ret = CreateWindow(d->className, "rcsawlib", WS_OVERLAPPEDWINDOW,
      x, y, width, height, NULL, NULL, d->hInstance, NULL);
#endif
  return ret;
  }

void rcs_drawCircle(rcs_Display* d,rcs_Window win,rcs_GC gc,
                   int x,int y,int w,int h) {
#ifdef X
  XDrawArc(d,win,gc,x,y,w,h,0,23040);
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HPEN pen;
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
  pen=CreatePen(PS_SOLID,0,gc->foreground);
  pen=(HPEN)SelectObject(dc,pen);
  Arc(dc,x,y,x+w,y+h,x+w/2,y,x+w/2,y);
  pen=(HPEN)SelectObject(dc,pen);
  DeleteObject(pen);
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif
  }

void rcs_drawFilledBox(rcs_Display* d,rcs_Window win,rcs_GC gc,
                  int x,int y,int w,int h) {
#ifdef X
  XFillRectangle(d,win,gc,x,y,w,h);
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HPEN pen;
  HBRUSH brush;
  RECT rect;
  rect.top=y;
  rect.left=x;
  rect.bottom=y+h;
  rect.right=x+w;
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
  pen=CreatePen(PS_SOLID,0,gc->foreground);
  brush=CreateSolidBrush(gc->foreground);
  pen=(HPEN)SelectObject(dc,pen);
  FillRect(dc,&rect,brush);
  pen=(HPEN)SelectObject(dc,pen);
  DeleteObject(pen);
  DeleteObject(brush);
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif
  }

void rcs_drawFilledCircle(rcs_Display* d,rcs_Window win,rcs_GC gc,
                   int x,int y,int w,int h) {
#ifdef X
  XFillArc(d,win,gc,x,y,w,h,0,23040);
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HPEN pen;
  HBRUSH brush;
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
  pen=CreatePen(PS_SOLID,0,gc->foreground);
  brush=CreateSolidBrush(gc->foreground);
  brush=(HBRUSH)SelectObject(dc,brush);
  pen=(HPEN)SelectObject(dc,pen);
  Ellipse(dc,x,y,x+w,y+h);
  brush=(HBRUSH)SelectObject(dc,brush);
  pen=(HPEN)SelectObject(dc,pen);
  DeleteObject(pen);
  DeleteObject(brush);
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif
  }

void rcs_drawLine(rcs_Display* d,rcs_Window win,rcs_GC gc,
                  int x1,int y1,int x2,int y2) {
#ifdef X
  XDrawLine(d,win,gc,x1,y1,x2,y2);
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HPEN pen;
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
  pen=CreatePen(PS_SOLID,0,gc->foreground);
  pen=(HPEN)SelectObject(dc,pen);
  MoveToEx(dc,x1,y1,NULL);
  LineTo(dc,x2,y2);
  pen=(HPEN)SelectObject(dc,pen);
  DeleteObject(pen);
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif
  }

void rcs_drawBox(rcs_Display* d,rcs_Window win,rcs_GC gc,
                  int x,int y,int w,int h) {
#ifdef X
  XDrawRectangle(d,win,gc,x,y,w,h);
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HPEN pen;
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
  pen=CreatePen(PS_SOLID,0,gc->foreground);
  pen=(HPEN)SelectObject(dc,pen);
  MoveToEx(dc,x,y,NULL);
  LineTo(dc,x+w,y);
  LineTo(dc,x+w,y+h);
  LineTo(dc,x,y+h);
  LineTo(dc,x,y);
  pen=(HPEN)SelectObject(dc,pen);
  DeleteObject(pen);
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif
  }

void rcs_drawPoint(rcs_Display* d,rcs_Window win,rcs_GC gc,int x,int y) {
#ifdef X
  XDrawPoint(d,win,gc,x,y);
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HPEN pen;
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
  pen=CreatePen(PS_SOLID,0,gc->foreground);
  pen=(HPEN)SelectObject(dc,pen);
  MoveToEx(dc,x,y,NULL);
  LineTo(dc,x+1,y);
  pen=(HPEN)SelectObject(dc,pen);
  DeleteObject(pen);
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif
  }

void rcs_drawString(rcs_Display* d,rcs_Window win,rcs_GC gc,int x,int y,
                    char* buffer) {
#ifdef X
  XDrawString(d,win,gc,x,y,buffer,strlen(buffer));
  XFlush(d);
#endif
#ifdef WIN32
  HDC dc;
  HPEN pen;
  RECT rect;
  int  height;
  rect.top=y;
  rect.left=x;
  rect.bottom=20;
  rect.right=20;
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
  pen=CreatePen(PS_SOLID,0,gc->foreground);
  pen=(HPEN)SelectObject(dc,pen);
  SelectObject(dc,gc->font);
  SetBkColor(dc,gc->background);
  SetTextColor(dc,gc->foreground);
  SetBkMode(dc,TRANSPARENT);
  height=DrawText(dc,buffer,strlen(buffer),&rect,DT_CALCRECT);
  rect.top-=height;
  DrawText(dc,buffer,strlen(buffer),&rect,DT_TOP);
  pen=(HPEN)SelectObject(dc,pen);
  DeleteObject(pen);
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif
  }

void rcs_foreground(rcs_Display* d,rcs_GC gc,
                    unsigned long red,unsigned long green,unsigned long blue) {
#ifdef X
  XColor clr;
  clr.red=red; clr.green=green; clr.blue=blue;
  XAllocColor(d,DefaultColormap(d,DefaultScreen(d)),&clr);
  XSetForeground(d,gc,clr.pixel);
#endif
#ifdef WIN32
  gc->foreground=RGB(red,green,blue);
#endif
  }

void rcs_closePixmap(rcs_Display* d,rcs_Pixmap p) {
#ifdef X
  XFreePixmap(d,p);
#endif
#ifdef WIN32
  int i,j;
  DeleteObject(p);
  i=0;
  while (i<disp.numPixmaps) {
    if (disp.pixmapIDs[i]==p) {
      for (j=i;j<disp.numPixmaps-2;j++)
        disp.pixmapIDs[j]=disp.pixmapIDs[j+1];
      return;
      }
    i++;
    }
#endif
  }

void rcs_hideWindow(rcs_Display* d,rcs_Window win) {
#ifdef X
  XUnmapWindow(d,win);
  XFlush(d);
#endif
#ifdef WIN32
  ShowWindow(win,SW_HIDE);
#endif
  }

void rcs_lowerWindow(rcs_Display* d,rcs_Window win) {
#ifdef X
  XLowerWindow(d,win);
  XFlush(d);
#endif
  };

void rcs_moveWindow(rcs_Display* d,rcs_Window win,int x,int y) {
#ifdef X  
  XMoveWindow(d,win,x,y);
  XFlush(d);
#endif
#ifdef WIN32
  RECT rect;
  GetClientRect(win,&rect);
  MoveWindow(win,x,y,rect.right,rect.bottom,TRUE);
#endif
  }

void rcs_namedForeground(rcs_Display* d,rcs_GC gc,char* color) {
#ifdef X
  XColor clr,exact;
  XAllocNamedColor(d,DefaultColormap(d,DefaultScreen(d)),color,
                   &clr,&exact);
  XSetForeground(d,gc,clr.pixel);
#endif
#ifdef WIN32
  int red,green,blue;
  rcs_namedColor(color,&red,&green,&blue);
  gc->foreground=RGB(red,green,blue);
#endif
  }

void rcs_namedBackground(rcs_Display* d,rcs_GC gc,char* color) {
#ifdef X
  XColor clr,exact;
  XAllocNamedColor(d,DefaultColormap(d,DefaultScreen(d)),color,
                   &clr,&exact);
  XSetBackground(d,gc,clr.pixel);
#endif
#ifdef WIN32
  int red,green,blue;
  rcs_namedColor(color,&red,&green,&blue);
  gc->background=RGB(red,green,blue);
#endif
  }

void rcs_setWindowBackground(rcs_Display* d,rcs_Window w,char* color) {
#ifdef X
  XColor clr,exact;
  XAllocNamedColor(d,DefaultColormap(d,DefaultScreen(d)),color,
                   &clr,&exact);
  XSetWindowBackground(d,w,clr.pixel);
#endif
#ifdef WIN32
#endif
  }

rcs_Display *rcs_openDisplay(char* display_name) {
#ifdef X
  return XOpenDisplay(display_name);
#endif
#ifdef WIN32
  return &disp;
#endif
  }

rcs_Font rcs_openFont(rcs_Display* d,char* font) {
#ifdef X
  return XLoadFont(d,font);
#endif
#ifdef WIN32
  rcs_Font ret;
  LOGFONT desc;
  HDC     dc;
  char    fontDescriptor[15][32];
  char*   pChar;
  int     i;
  for (i=0;i<15;i++) strcpy(fontDescriptor[i],"*");
  i=0;
  font++;
  pChar=fontDescriptor[0];
  while (*font != 0) {
    if (*font == '-') {
      *pChar=0;
      i++;
      pChar=fontDescriptor[i];
      } else {
      *pChar++ = *font;
      }
    font++;
    }
  dc=GetDC(rcs_rootWindow(d));
  if (fontDescriptor[6][0] != '*') desc.lfHeight=atoi(fontDescriptor[6]);
  if (fontDescriptor[7][0] != '*')
    desc.lfHeight=-MulDiv(atoi(fontDescriptor[7]), GetDeviceCaps(dc, LOGPIXELSY), 72); 
  ReleaseDC(rcs_rootWindow(d),dc);
  desc.lfWidth=0;
  desc.lfEscapement=0;
  desc.lfOrientation=0;
  desc.lfWeight=FW_DONTCARE;
  if (strcmp(fontDescriptor[2],"black")==0) desc.lfWeight=FW_BLACK;
  if (strcmp(fontDescriptor[2],"bold")==0) desc.lfWeight=FW_BOLD;
  if (strcmp(fontDescriptor[2],"book")==0) desc.lfWeight=FW_NORMAL;
  if (strcmp(fontDescriptor[2],"demibold")==0) desc.lfWeight=FW_DEMIBOLD;
  if (strcmp(fontDescriptor[2],"demi bold")==0) desc.lfWeight=FW_DEMIBOLD;
  if (strcmp(fontDescriptor[2],"light")==0) desc.lfWeight=FW_LIGHT;
  if (strcmp(fontDescriptor[2],"medium")==0) desc.lfWeight=FW_MEDIUM;
  if (strcmp(fontDescriptor[2],"regular")==0) desc.lfWeight=FW_REGULAR;
  desc.lfItalic= (fontDescriptor[3][0]=='i') ? TRUE : FALSE;
  desc.lfUnderline=FALSE;
  desc.lfStrikeOut=FALSE;
  desc.lfCharSet=ANSI_CHARSET;
  desc.lfOutPrecision=OUT_DEFAULT_PRECIS;
  desc.lfClipPrecision=CLIP_DEFAULT_PRECIS;
  desc.lfQuality=DEFAULT_QUALITY;
  desc.lfPitchAndFamily=VARIABLE_PITCH+FF_DONTCARE;
  if (fontDescriptor[1][0] != '0') strcpy(desc.lfFaceName,fontDescriptor[1]);
    else strcpy(desc.lfFaceName,"Ariel");
  ret=CreateFontIndirect(&desc);
  return ret;
#endif
  }

rcs_GC rcs_openGC(rcs_Display* d,rcs_Window win) {
#ifdef X
  unsigned long mask;
  XGCValues     values;
  mask=0;
  mask=GCForeground | GCBackground;
  values.foreground=BlackPixel(d,DefaultScreen(d));
  values.background=WhitePixel(d,DefaultScreen(d));
  return XCreateGC(d,win,mask,&values);
#endif
#ifdef WIN32
  rcs_GC ret;
	ret=(rcs_GC)malloc(sizeof(struct _GC));
  ret->foreground=RGB(0,0,0);
  ret->background=RGB(255,255,255);
  ret->font=(HFONT)GetStockObject(SYSTEM_FONT);
  return ret;
#endif
  }

void rcs_raiseWindow(rcs_Display* d,rcs_Window win) {
#ifdef X
  XRaiseWindow(d,win);
  XFlush(d);
#endif
#ifdef WIN32
  BringWindowToTop(win);
#endif
  }

void rcs_resizeWindow(rcs_Display* d,rcs_Window win,int w,int h) {
#ifdef X
  XResizeWindow(d,win,w,h);
  XFlush(d);
#endif
#ifdef WIN32
  RECT rect;
  GetWindowRect(win,&rect);
  MoveWindow(win,rect.left,rect.top,w,h,TRUE);
#endif
  }

rcs_Window rcs_rootWindow(rcs_Display* d) {
#ifdef X
  return DefaultRootWindow(d);
#endif
#ifdef WIN32
  return GetDesktopWindow();
#endif
  }

#ifdef X
void rcs_setFont(rcs_Display* d,rcs_GC gc,rcs_Font font) {
  XSetFont(d,gc,font);
#endif
#ifdef WIN32
void rcs_setFont(rcs_Display* d,rcs_GC gc,rcs_Font font) {
  gc->font=font;
#endif
  }

void rcs_showWindow(rcs_Display* d,rcs_Window win) {
#ifdef X
  XMapWindow(d,win);
  XFlush(d);
#endif
#ifdef WIN32
  ShowWindow(win,SW_SHOW);
#endif
  }

#ifdef X
void  _rcs_buildColors(rcs_Display* d,XColor* colors,char** data,int *none) {
  XColor clr1,clr2;
#endif
#ifdef WIN32
void  _rcs_buildColors(rcs_Display* d,COLORREF* colors,char** data,int *none) {
#endif
  int        sizeX,sizeY,numColors;
  int        x,i;
  char       index,temp,index2;
  char       buffer[80];
  char       nbuffer[8];
  int        colorIndex;
  int        bytesPer;
  unsigned long        red,green,blue;
  *none=-1;
  sscanf(data[0],"%d %d %d %d",&sizeX,&sizeY,&numColors,&bytesPer);
  for (x=1;x<=numColors;x++) {
    if (bytesPer != 2) {
      sscanf(data[x],"%c %c %s",&index,&temp,buffer);
      colorIndex = index;
      } else {
      sscanf(data[x],"%c%c %c %s",&index,&index2,&temp,buffer);
      colorIndex = (index-32)*96 + (index2-32);
      }
    if (buffer[0] != '#') {
      if (strcmp(buffer,"None")==0) *none=index;
#ifdef X
      XAllocNamedColor(d,DefaultColormap(d,DefaultScreen(d)),buffer,
                       &clr1,&clr2);
      colors[colorIndex]=clr1;
#endif
#ifdef WIN32
      rcs_namedColor(buffer,&red,&green,&blue);
      colors[colorIndex]=RGB(red,green,blue);
#endif
      } else {
      for (i=0;i<4;i++) nbuffer[i]=buffer[i+1];
      nbuffer[4]=0;
      sscanf(nbuffer,"%lx",&red);
      for (i=0;i<4;i++) nbuffer[i]=buffer[i+5];
      nbuffer[4]=0;
      sscanf(nbuffer,"%lx",&green);
      for (i=0;i<4;i++) nbuffer[i]=buffer[i+9];
      nbuffer[4]=0;
      sscanf(nbuffer,"%lx",&blue);
#ifdef WIN32
      if (red>255) red/=256;
      if (blue>255) blue/=256;
      if (green>255) green/=256;
#endif
#ifdef X
      colors[colorIndex].blue=blue;
      colors[colorIndex].red=red;
      colors[colorIndex].green=green;
      colors[colorIndex].flags=DoRed | DoGreen | DoBlue;
      XAllocColor(d,DefaultColormap(d,DefaultScreen(d)),&colors[colorIndex]);
#endif
#ifdef WIN32
      colors[colorIndex]=RGB(red,green,blue);
#endif
      }
    }
  }


rcs_Pixmap rcs_xpmToPixmap(rcs_Display* d,rcs_Window win,char** data) {
  int        sizeX,sizeY,numColors,x;
  rcs_Pixmap ret;
  rcs_GC     gc;
  sscanf(data[0],"%d %d %d %d",&sizeX,&sizeY,&numColors,&x);
  ret=rcs_createPixmap(d,win,sizeX,sizeY);
  gc=rcs_openGC(d,ret);
  rcs_drawPixmap(d,ret,gc,0,0,data);
  rcs_closeGC(d,gc);
  return ret;
  }

void  rcs_drawPixmap(rcs_Display* d,rcs_Window win,rcs_GC gc,int dx,int dy,char** data) {
  int        sizeX,sizeY,numColors;
  int        x,y;
/*  char       index; */
  int        none;
  int        colorIndex;
  int        bytesPer;
#ifdef X
  XWindowAttributes attr;
  unsigned long red,green,blue;
  XColor     colors[10000];
#endif
#ifdef WIN32
  HDC        dc;
  HPEN       pen,oldPen;
  COLORREF   colors[10000];
#endif
  none=-1;
  _rcs_buildColors(d,colors,data,&none);
  sscanf(data[0],"%d %d %d %d",&sizeX,&sizeY,&numColors,&bytesPer);
#ifdef WIN32
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
#endif
  for (y=0;y<sizeY;y++)
    for (x=0;x<sizeX;x++) {
      if (bytesPer != 2) colorIndex=data[y+numColors+1][x];
        else colorIndex = (data[y+numColors+1][x*2]-32) * 96 +
                          (data[y+numColors+1][x*2+1]-32);
      if (colorIndex != none) {
#ifdef X
        XSetForeground(d,gc,colors[colorIndex].pixel);
        XDrawPoint(d,win,gc,x+dx,y+dy);
#endif
#ifdef WIN32
        pen=CreatePen(PS_SOLID,0,colors[colorIndex]);
        oldPen=(HPEN)SelectObject(dc,pen);
        MoveToEx(dc,x+dx,y+dy,NULL);
        LineTo(dc,x+1+dx,y+dy);
        oldPen=(HPEN)SelectObject(dc,oldPen);
        DeleteObject(oldPen);
#endif
        }
      }
#ifdef WIN32
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif      
  }

void  rcs_drawSubPixmap(rcs_Display* d,rcs_Window win,rcs_GC gc,int dx,int dy,char** data,int sx,int sy,int w,int h) {
  int        sizeX,sizeY,numColors;
  int        x,y;
  char       index;
  int        none;
#ifdef X
  XWindowAttributes attr;
  unsigned long red,green,blue;
  XColor     colors[10000];
#endif
#ifdef WIN32
  HDC        dc;
  HPEN       pen;
  COLORREF   colors[10000];
#endif
  none=-1;
  _rcs_buildColors(d,colors,data,&none);
  sscanf(data[0],"%d %d %d %d",&sizeX,&sizeY,&numColors,&x);
#ifdef WIN32
  if (_rcs_isBitmap(win)==TRUE) {
    dc=CreateCompatibleDC(0);
    SelectObject(dc,win);
    } else dc=GetDC(win);
#endif
  for (y=0;y<h;y++)
    for (x=0;x<w;x++) {
      index=data[y+numColors+1+sy][x+sx];
      if (index != none) {
#ifdef X
        XSetForeground(d,gc,colors[index].pixel);
        XDrawPoint(d,win,gc,x+dx,y+dy);
#endif
#ifdef WIN32
        pen=CreatePen(PS_SOLID,0,colors[index]);
        pen=(HPEN)SelectObject(dc,pen);
        MoveToEx(dc,x+dx,y+dy,NULL);
        LineTo(dc,x+1+dx,y+dy);
        pen=(HPEN)SelectObject(dc,pen);
        DeleteObject(pen);
#endif
        }
      }
#ifdef WIN32
  if (_rcs_isBitmap(win)==TRUE) DeleteDC(dc);
    else ReleaseDC(win,dc);
#endif      
  }

rcs_Event rcs_getEvent(rcs_Display* d) {
  rcs_Event ret;
#ifdef X
  XEvent event;
  KeySym key;
  XComposeStatus status;
  char tmp[10];
  XNextEvent(d,&event);
  switch (event.type) {
    case ConfigureNotify:
                      ret.type=EVENT_CONFIGURE;
                      ret.d1=event.xconfigure.x;
                      ret.d2=event.xconfigure.y;
                      ret.d3=event.xconfigure.width;
                      ret.d4=event.xconfigure.height;
                      break;
    case MotionNotify:ret.type=EVENT_MOTION;
                      ret.d2=event.xmotion.x;
                      ret.d3=event.xmotion.y;
                      ret.window=event.xmotion.window;
                      break;
    case ButtonPress:ret.type=EVENT_BUTTON_PRESS;
                     ret.window=event.xbutton.window;
                     ret.d1=event.xbutton.button;
                     ret.d2=event.xbutton.x;
                     ret.d3=event.xbutton.y;
                     break;
    case ButtonRelease:ret.type=EVENT_BUTTON_RELEASE;
                     ret.window=event.xbutton.window;
                     ret.d1=event.xbutton.button;
                     ret.d2=event.xbutton.x;
                     ret.d3=event.xbutton.y;
                     break;
    case Expose:ret.type=EVENT_EXPOSE;
                ret.window=event.xexpose.window;
                ret.d1=event.xexpose.x;
                ret.d2=event.xexpose.y;
                ret.d3=event.xexpose.width;
                ret.d4=event.xexpose.height;
                ret.d5=event.xexpose.count;
                break;
    case KeyRelease:ret.type=EVENT_KEY_RELEASE;
                  ret.window=event.xkey.window;
                  XLookupString((XKeyEvent*)&event,tmp,10,&key,&status);
                  ret.d1=key;
                  switch (ret.d1) {
                    case XK_Return:ret.d1=13; break;
                    case XK_Escape:ret.d1=27; break;
                    }
                  break;
    case KeyPress:ret.type=EVENT_KEY_PRESS;
                  ret.window=event.xkey.window;
                  XLookupString((XKeyEvent*)&event,tmp,10,&key,&status);
                  ret.d1=key;
                  switch (ret.d1) {
                    case XK_Return:ret.d1=13; break;
                    case XK_Escape:ret.d1=27; break;
                    }
                  break;
    }
#endif
#ifdef WIN32
	MSG msg;
  RECT rect;
  ret.type=EVENT_NONE;
  GetMessage(&msg, NULL, 0, 0);
    if (msg.message == WM_MOUSEMOVE) {
      ret.type=EVENT_MOTION;
      ret.window=msg.hwnd;
      ret.d1=1;
      ret.d2=msg.lParam & 0xffff;
      ret.d3=msg.lParam >> 16;
      }
    if (msg.message == WM_LBUTTONDOWN) {
      ret.type=EVENT_BUTTON_PRESS;
      ret.window=msg.hwnd;
      ret.d1=1;
      ret.d2=msg.lParam & 0xffff;
      ret.d3=msg.lParam >> 16;
      }
    else if (msg.message == WM_RBUTTONDOWN) {
      ret.type=EVENT_BUTTON_PRESS;
      ret.window=msg.hwnd;
      ret.d1=2;
      ret.d2=msg.lParam & 0xffff;
      ret.d3=msg.lParam >> 16;
      }
    else if (msg.message == WM_LBUTTONUP) {
      ret.type=EVENT_BUTTON_RELEASE;
      ret.window=msg.hwnd;
      ret.d1=1;
      ret.d2=msg.lParam & 0xffff;
      ret.d3=msg.lParam >> 16;
      }
    else if (msg.message == WM_RBUTTONUP) {
      ret.type=EVENT_BUTTON_RELEASE;
      ret.window=msg.hwnd;
      ret.d1=2;
      ret.d2=msg.lParam & 0xffff;
      ret.d3=msg.lParam >> 16;
      }
    else if (msg.message == WM_PAINT) {
      ret.type=EVENT_EXPOSE;
      ret.window=msg.hwnd;
      GetUpdateRect(ret.window,&rect,FALSE);
      ret.d1=rect.left;
      ret.d2=rect.top;
      ret.d3=rect.right-rect.left;
      ret.d4=rect.bottom-rect.top;
      ret.d5=0;
      }
    if (msg.message == WM_KEYDOWN && (msg.lParam&0x1000000)==0x1000000) {
      ret.type=EVENT_KEY_PRESS;
      ret.window=msg.hwnd;
      ret.d1=msg.wParam+200;
      }
	  TranslateMessage(&msg);
    if (msg.message == WM_CHAR) {
      ret.type=EVENT_KEY_PRESS;
      ret.window=msg.hwnd;
      ret.d1=msg.wParam;
      }
		DispatchMessage(&msg);
      
#endif
  return ret;
  }

rcs_Event rcs_pollEvent(rcs_Display* d) {
  rcs_Event ret;
#ifdef X
  if (XPending(d)>0) return rcs_getEvent(d);
#endif
#ifdef WIN32
	MSG msg;
  if (PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE)!=0) return rcs_getEvent(d);
#endif
  ret.type=EVENT_NONE;
  return ret;
  }

