#include <math.h>
#include "librcs.h"

void   rcs_unvec(VECTOR v,double* x,double* y,double* z) {
  *x=v.x;
  *y=v.y;
  *z=v.z;
  }

void   rcs_univec(IVECTOR v,int* x,int* y,int* z) {
  *x=v.x;
  *y=v.y;
  *z=v.z;
  }

VECTOR rcs_vector(double x,double y,double z) {
  VECTOR ret;
  ret.x=x;
  ret.y=y;
  ret.z=z;
  return ret;
  }

IVECTOR rcs_ivector(int x,int y,int z) {
  IVECTOR ret;
  ret.x=x;
  ret.y=y;
  ret.z=z;
  return ret;
  }

void rcs_vecadd(VECTOR a,VECTOR b,VECTOR* c) {
  c->x=a.x+b.x;
  c->y=a.y+b.y;
  c->z=a.z+b.z;
  }

void rcs_vecadd3(VECTOR a,VECTOR b,VECTOR c,VECTOR* d) {
  d->x=a.x+b.x+c.x;
  d->y=a.y+b.y+c.y;
  d->z=a.z+b.z+c.z;
  }

void rcs_veccrs(VECTOR a,VECTOR b,VECTOR* c) {
  c->x=(a.y*b.z)-(a.z*b.y);
  c->y=-(a.x*b.z)-(a.z*b.x);
  c->z=(a.x*b.y)-(a.y*b.x);
  }

double rcs_vecdot(VECTOR a,VECTOR b) {
  return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
  }

double rcs_veclen(VECTOR a) {
  return sqrt((a.x*a.x)+(a.y*a.y)+(a.z*a.z));
  }

void rcs_veclin(VECTOR a,double sa,VECTOR b,double sb,VECTOR* dv) {
  dv->x=(a.x*sa)+(b.x*sb);
  dv->y=(a.y*sa)+(b.y*sb);
  dv->z=(a.z*sa)+(b.z*sb);
  }
    
void rcs_vecmax(VECTOR a,VECTOR b,VECTOR* c) {
  c->x=(a.x>b.x)?a.x:b.x;
  c->y=(a.y>b.y)?a.y:b.y;
  c->z=(a.z>b.z)?a.z:b.z;
  }

void rcs_vecmin(VECTOR a,VECTOR b,VECTOR* c) {
  c->x=(a.x<b.x)?a.x:b.x;
  c->y=(a.y<b.y)?a.y:b.y;
  c->z=(a.z<b.z)?a.z:b.z;
  }

VECTOR rcs_vecmulmat(VECTOR v,MATRIX m) {
  VECTOR ret;
  ret.x=(v.x*m.m[0][0])+(v.x*m.m[0][1])+(v.x*m.m[0][2])+m.m[0][3];
  ret.y=(v.y*m.m[1][0])+(v.y*m.m[1][1])+(v.y*m.m[1][2])+m.m[1][3];
  ret.z=(v.z*m.m[2][0])+(v.z*m.m[2][1])+(v.z*m.m[2][2])+m.m[2][3];
  return ret;
  }
  
void rcs_vecneg(VECTOR a,VECTOR* b) {
  b->x=-a.x;
  b->y=-a.y;
  b->z=-a.z;
  }

void rcs_vecnrm(VECTOR a,VECTOR* b) {
  double scale;
  scale=1.0/rcs_veclen(a);
  b->x=a.x*scale;
  b->y=a.y*scale;
  b->z=a.z*scale;
  }

void rcs_vecsadd(VECTOR a,double sa,VECTOR b,VECTOR* dv) {
  dv->x=(sa*a.x)+b.x;
  dv->y=(sa*a.y)+b.y;
  dv->z=(sa*a.z)+b.z;
  }

void rcs_vecscale(VECTOR a,double scale,VECTOR* b) {
  b->x=a.x*scale;
  b->y=a.y*scale;
  b->z=a.z*scale;
  }

IVECTOR rcs_ivecscale(IVECTOR a,int scale) {
  IVECTOR ret;
  ret.x=a.x*scale;
  ret.y=a.y*scale;
  ret.z=a.z*scale;
  return ret;
  }

void rcs_vecsmul(VECTOR a,double sa,VECTOR b,VECTOR* c) {
  c->x=(sa*a.x)*b.x;
  c->y=(sa*a.y)*b.y;
  c->z=(sa*a.z)*b.z;
  }

IVECTOR rcs_ivecsub(IVECTOR a,IVECTOR b) {
  IVECTOR ret;
  ret.x=a.x-b.x;
  ret.y=a.y-b.y;
  ret.z=a.z-b.z;
  return ret;
  }

void rcs_vecsub(VECTOR a,VECTOR b,VECTOR* c) {
  c->x=a.x-b.x;
  c->y=a.y-b.y;
  c->z=a.z-b.z;
  }

void rcs_veczero(VECTOR* a) {
  a->x=0;
  a->y=0;
  a->z=0;
  }

IVECTOR rcs_iveczero() {
  IVECTOR ret;
  ret.x=0;
  ret.y=0;
  ret.z=0;
  return ret;
  }

void rcs_veccpy(VECTOR a,VECTOR* b) {
  b->x=a.x;
  b->y=a.y;
  b->z=a.z;
  }

double rcs_vecelem(VECTOR v,int e) {
  if (e==0) return v.x;
  if (e==1) return v.y;
  return v.z;
  }

