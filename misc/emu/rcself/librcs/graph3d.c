#include <math.h>
#include "librcs.h"

int rcs_addobject(WORLD* world,GOBJECT o) {
  int i;
/*  VECTOR v; */
  VECTOR vertex;
  GOBJECT obj;
/*  double worldx,worldy,worldz; */
  if (world->maxObjects==world->objectCount) return -1;
  obj=o;
  obj.vertexList=(VECTOR*)calloc(obj.maxVertex,sizeof(VECTOR));
  obj.renderList=(VECTOR*)calloc(obj.maxVertex,sizeof(VECTOR));
  obj.polygonList=(POLYGON*)calloc(obj.maxPoly,sizeof(POLYGON));
  for (i=0;i<obj.polyCount;i++)
    obj.polygonList[i]=o.polygonList[i];
  for (i=0;i<obj.vertexCount;i++) {
    vertex=o.vertexList[i];
    vertex.x+=obj.worldx;
    vertex.y+=obj.worldy;
    vertex.z+=obj.worldz;
    obj.vertexList[i]=vertex;
    }
  world->objectList[world->objectCount++]=obj;
  return world->objectCount-1;
  }

int rcs_raddobject(WORLD* world,GOBJECT o) {
  int i;
/*  VECTOR v; */
  VECTOR vertex;
  GOBJECT obj;
/*  double worldx,worldy,worldz; */
  if (world->maxObjects==world->objectCount) return -1;
  obj=o;
  obj.vertexList=(VECTOR*)calloc(obj.maxVertex,sizeof(VECTOR));
  obj.renderList=(VECTOR*)calloc(obj.maxVertex,sizeof(VECTOR));
  obj.polygonList=(POLYGON*)calloc(obj.maxPoly,sizeof(POLYGON));
  for (i=0;i<obj.polyCount;i++)
    obj.polygonList[i]=o.polygonList[i];
  for (i=0;i<obj.vertexCount;i++) {
    vertex=o.renderList[i];
    vertex.x+=obj.worldx;
    vertex.y+=obj.worldy;
    vertex.z+=obj.worldz;
    obj.vertexList[i]=vertex;
    }
  world->objectList[world->objectCount++]=obj;
  return world->objectCount-1;
  }

int rcs_addpoint(POLYGON* poly,int point) {
  if (poly->pointCount==poly->maxPoints) return -1;
  poly->pointList[poly->pointCount++]=point;
  return poly->pointCount-1;
  }

int rcs_addpoly(GOBJECT* obj,POLYGON poly) {
  int i;
  POLYGON p;
  if (obj->maxPoly==obj->polyCount) return -1;
  p=poly;
  p.pointList=(int*)calloc(p.maxPoints,sizeof(int));
  for (i=0; i<p.pointCount; i++)
    p.pointList[i]=poly.pointList[i]; 
  obj->polygonList[obj->polyCount++]=p;
  return obj->polyCount-1;
  }

int rcs_addvertex(GOBJECT* obj,VECTOR vertex) {
  if (obj->maxVertex==obj->vertexCount) return -1;
  obj->vertexList[obj->vertexCount++]=vertex;
  return obj->vertexCount-1;
  }

void rcs_clrobject(GOBJECT* obj) {
  obj->vertexCount=0;
  obj->polyCount=0;
  }

void rcs_droppoly(POLYGON poly) {
  free(poly.pointList);
  }
  
GOBJECT rcs_gobject(int maxVertex,int maxPoly) {
  GOBJECT ret;
  ret.maxVertex=maxVertex;
  ret.maxPoly=maxPoly;
  ret.vertexCount=0;
  ret.polyCount=0;
  ret.worldx=0;
  ret.worldy=0;
  ret.worldz=0;
  ret.vertexList=(VECTOR*)calloc(maxVertex,sizeof(VECTOR));
  ret.renderList=(VECTOR*)calloc(maxVertex,sizeof(VECTOR));
  ret.polygonList=(POLYGON*)calloc(maxPoly,sizeof(POLYGON));
  return ret;
  }

POLYGON rcs_polygon(int maxPoints) {
  POLYGON ret;
  ret.maxPoints=maxPoints;
  ret.pointCount=0;
  ret.pointList=(int*)calloc(maxPoints,sizeof(int));
  return ret;
  }

void rcs_prepobj(GOBJECT* obj,int cx,int cy) {
  int i;
  VECTOR v;
  VECTOR vertex;
  double worldx,worldy,worldz;
  worldx=obj->worldx;
  worldy=obj->worldy;
  worldz=obj->worldz;
  for (i=0;i<obj->vertexCount;i++) {
    vertex=obj->vertexList[i];
    vertex.x+=worldx;
    vertex.y+=worldy;
    vertex.z+=worldz;
    v.x=(200*vertex.x/vertex.z)+cx;
    v.y=cy-(200*vertex.y/vertex.z);
    obj->renderList[i]=v;
    }
  }

void rcs_prepworld(WORLD* world,int cx,int cy) {
  int i,j;
  GOBJECT obj;
  VECTOR vertex;
  for (i=0;i<world->objectCount;i++) {
    obj=world->objectList[i];
    for (j=0;j<obj.vertexCount;j++) {
      vertex=obj.vertexList[j];
      vertex.x=(200*vertex.x/vertex.z)+cx;
      vertex.y=cy-(200*vertex.y/vertex.z);
      obj.renderList[j]=vertex;
      }
    }
  }

void rcs_rprepworld(WORLD* world,int cx,int cy) {
  int i,j;
  GOBJECT obj;
  VECTOR vertex;
  for (i=0;i<world->objectCount;i++) {
    obj=world->objectList[i];
    for (j=0;j<obj.vertexCount;j++) {
      vertex=obj.renderList[j];
      vertex.x=(200*vertex.x/vertex.z)+cx;
      vertex.y=cy-(200*vertex.y/vertex.z);
      obj.renderList[j]=vertex;
      }
    }
  }
  
MATRIX rcs_tranmat(double sx,double sy,double sz,double rx,double ry,double rz,
               double tx,double ty,double tz) {
  MATRIX ret;
  double sinx,siny,sinz;
  double cosx,cosy,cosz;
  double pi;
  int    rotations;
  rotations=0;
  pi=3.14159265/180;
  ret.m[0][3]=0; ret.m[1][3]=0; ret.m[2][3]=0;
  ret.m[3][0]=tx; ret.m[3][1]=ty; ret.m[3][2]=tz; ret.m[3][3]=1;
  if (rx!=0) {
    sinx=sin(rx*pi); cosx=cos(rx*pi);
    rotations+=1;
    }
  if (ry!=0) {
    siny=sin(ry*pi); cosy=cos(ry*pi);
    rotations+=2;
    }
  if (rz!=0) {
    sinz=sin(rz*pi); cosz=cos(rz*pi);
    rotations+=4;
    }
  switch (rotations) {
    case 0:ret.m[0][0]=1; ret.m[0][1]=0; ret.m[0][2]=0;
           ret.m[1][0]=0; ret.m[1][1]=1; ret.m[1][2]=0;
           ret.m[2][0]=0; ret.m[2][1]=0; ret.m[2][2]=1;
           break;
    case 1:ret.m[0][0]=1; ret.m[0][1]=0; ret.m[0][2]=0;
           ret.m[1][0]=0; ret.m[1][1]=cosx; ret.m[1][2]=sinx;
           ret.m[2][0]=0; ret.m[2][1]=-sinx; ret.m[2][2]=cosx;
           break;
    case 2:ret.m[0][0]=cosy; ret.m[0][1]=0; ret.m[0][2]=-siny;
           ret.m[1][0]=0; ret.m[1][1]=1; ret.m[1][2]=0;
           ret.m[2][0]=siny; ret.m[2][1]=0; ret.m[2][2]=cosy;
           break;
    case 3:ret.m[0][0]=cosy; ret.m[0][1]=0; ret.m[0][2]=-siny;
           ret.m[1][0]=sinx*siny; ret.m[1][1]=cosx; ret.m[1][2]=sinx*cosy;
           ret.m[2][0]=cosx*siny; ret.m[2][1]=-sinx; ret.m[2][2]=cosx*cosy;
           break;
    case 4:ret.m[0][0]=cosz; ret.m[0][1]=sinz; ret.m[0][2]=0;
           ret.m[1][0]=-sinz; ret.m[1][1]=cosz; ret.m[1][2]=0;
           ret.m[2][0]=0; ret.m[2][1]=0; ret.m[2][2]=1;
           break;
    case 5:ret.m[0][0]=cosz; ret.m[0][1]=sinz; ret.m[0][2]=0;
           ret.m[1][0]=cosx*-sinz; ret.m[1][1]=cosx*cosz; ret.m[1][2]=sinx;
           ret.m[2][0]=sinx*sinz; ret.m[2][1]=-sinx*cosz; ret.m[2][2]=cosx;
           break;
    case 6:ret.m[0][0]=cosy*cosz; ret.m[0][1]=cosy*sinz; ret.m[0][2]=-siny;
           ret.m[1][0]=-sinz; ret.m[1][1]=cosz; ret.m[1][2]=0;
           ret.m[2][0]=siny*cosz; ret.m[2][1]=siny*sinz; ret.m[2][2]=cosy;
           break;
    case 7:ret.m[0][0]=sx*cosy*cosz;
           ret.m[0][1]=sx*cosy*sinz;
           ret.m[0][2]=-sx*siny;
           ret.m[1][0]=(sy*sinx*siny*cosz)-(sy*cosx*sinz);
           ret.m[1][1]=(sy*sinx*siny*sinz)+(sy*cosx*cosz);
           ret.m[1][2]=sy*sinx*cosy;
           ret.m[2][0]=(sz*cosx*siny*cosz)+(sz*sinx*sinz);
           ret.m[2][1]=(sz*cosx*siny*sinz)-(sz*sinx*cosz);
           ret.m[2][2]=sz*cosx*cosy;
    }

  if (rotations!=7) {
    if (sx!=1) {
      ret.m[0][0]*=sx;
      ret.m[0][1]*=sx;
      ret.m[0][2]*=sx;
      }
    if (sy!=1) {
      ret.m[1][0]*=sy;
      ret.m[1][1]*=sy;
      ret.m[1][2]*=sy;
      }
    if (sz!=1) {
      ret.m[2][0]*=sz;
      ret.m[2][1]*=sz;
      ret.m[2][2]*=sz;
      }
    }
 
  return ret;  
  }

VECTOR rcs_vectrans(VECTOR v,MATRIX m) {
  VECTOR ret;
  ret.x=(v.x*m.m[0][0])+(v.y*m.m[1][0])+(v.z*m.m[2][0])+m.m[3][0];
  ret.y=(v.x*m.m[0][1])+(v.y*m.m[1][1])+(v.z*m.m[2][1])+m.m[3][1];
  ret.z=(v.x*m.m[0][2])+(v.y*m.m[1][2])+(v.z*m.m[2][2])+m.m[3][2];
  return ret;
  }

void rcs_wireobj(rcs_Display* disp,rcs_Window win,rcs_GC gc,GOBJECT* obj) {
  int i,j;
  POLYGON poly;
  VECTOR v1;
  VECTOR v2;
  for (i=0;i<obj->polyCount;i++) {
    poly=obj->polygonList[i];
    for (j=0;j<poly.pointCount;j++) {
      v1=obj->renderList[poly.pointList[j]];
      if (j!=poly.pointCount-1)
        v2=obj->renderList[poly.pointList[j+1]];
      else
        v2=obj->renderList[poly.pointList[0]];
      rcs_drawLine(disp,win,gc,v1.x,v1.y,v2.x,v2.y);
      }
    }
  }

void rcs_wireworld(rcs_Display* disp,rcs_Window win,rcs_GC gc,WORLD* world) {
/*  int i,j; */
  int i;
  GOBJECT obj;
  for (i=0;i<world->objectCount;i++) {
    obj=world->objectList[i];
    rcs_wireobj(disp,win,gc,&obj);
    }
  }

WORLD rcs_world(int maxObjects) {
  WORLD ret;
  ret.maxObjects=maxObjects;
  ret.objectCount=0;
  ret.objectList=(GOBJECT*)calloc(maxObjects,sizeof(GOBJECT));
  return ret;
  }

void rcs_worldtrans(WORLD* world,MATRIX m) {
  int i,j;
  GOBJECT obj;
  VECTOR v,v2;
  for (i=0;i<world->objectCount;i++) {
    obj=world->objectList[i];
    for (j=0;j<obj.vertexCount;j++) {
      v=obj.vertexList[j];
      v.x+=m.m[3][0];
      v.y+=m.m[3][1];
      v.z+=m.m[3][2];
      v2.x=(v.x*m.m[0][0])+(v.y*m.m[1][0])+(v.z*m.m[2][0]);
      v2.y=(v.x*m.m[0][1])+(v.y*m.m[1][1])+(v.z*m.m[2][1]);
      v2.z=(v.x*m.m[0][2])+(v.y*m.m[1][2])+(v.z*m.m[2][2]);
      obj.renderList[j]=v2;
      }
    }
  }

void rcs_objecttrans(GOBJECT* obj,MATRIX m) {
  int j;
  VECTOR v,v2;
    for (j=0;j<obj->vertexCount;j++) {
      v=obj->vertexList[j];
      v2.x=(v.x*m.m[0][0])+(v.y*m.m[1][0])+(v.z*m.m[2][0])+m.m[3][0];
      v2.y=(v.x*m.m[0][1])+(v.y*m.m[1][1])+(v.z*m.m[2][1])+m.m[3][1];
      v2.z=(v.x*m.m[0][2])+(v.y*m.m[1][2])+(v.z*m.m[2][2])+m.m[3][2];
      obj->renderList[j]=v2;
      }
  }  
