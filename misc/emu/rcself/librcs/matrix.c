#include "librcs.h"

MATRIX rcs_matident() {
  MATRIX ret;
  int    i;
  ret=rcs_matzero();
  for (i=0;i<4;i++)
    ret.m[i][i]=1;
  return ret;
  }

MATRIX rcs_matmul(MATRIX a,MATRIX b) {
  MATRIX ret;
  int    i,j,k;
  double acc;
  for (i=0;i<4;i++)
    for (j=0;j<4;j++) {
      acc=0;
      for (k=0;k<4;k++)
        acc += a.m[i][k]*b.m[k][j];
       ret.m[i][j]=acc;
      }
   return ret;
  }
  
MATRIX rcs_matscale(double sx,double sy,double sz) {
  MATRIX ret;
  ret=rcs_matzero();
  ret.m[0][0]=sx;
  ret.m[1][1]=sy;
  ret.m[2][2]=sz;
  ret.m[3][3]=1;
  return ret;
  }
 
MATRIX rcs_mattran(double tx,double ty,double tz) {
  MATRIX ret;
  ret=rcs_matident();
  ret.m[0][3]=tx;
  ret.m[1][3]=ty;
  ret.m[2][3]=tz;
  return ret;
  }

MATRIX rcs_matzero() {
  int x,y;
  MATRIX ret;
  for (x=0;x<4;x++)
    for (y=0;y<4;y++)
      ret.m[x][y]=0;
  return ret;
  }

MATRIX rcs_matrot(int axis,double angle) {
  int    m1,m2;
  double c,s;
  MATRIX ret;
  ret=rcs_matzero();
  ret.m[axis-1][axis-1]=1.0;
  ret.m[3][3]=1.0;
  m1=(axis % 3)+1;
  m2=(m1 % 3);
  m1--;
  c=rcs_cosD(angle);
  s=rcs_sinD(angle);
  ret.m[m1][m1]=c;
  ret.m[m1][m2]=s;
  ret.m[m2][m2]=c;
  ret.m[m2][m1]=-s;
  return ret;
  }

MATRIX rcs_transMatrix(double tx,double ty,double tz,
                       double sx,double sy,double sz,
                       double rx,double ry,double rz) {
  MATRIX m1,m2,m3,m4,m5,m6,m7,m8,ret;
  m1=rcs_matscale(sx,sy,sz);
  m2=rcs_matrot(1,rx);
  m3=rcs_matrot(2,ry);
  m4=rcs_matrot(3,rz);
  m5=rcs_mattran(tx,ty,tz);
  m6=rcs_matmul(m2,m1);
  m7=rcs_matmul(m3,m6);
  m8=rcs_matmul(m4,m7);
  ret=rcs_matmul(m5,m8);
  return ret;
  }

MATRIX rcs_transInvMatrix(double tx,double ty,double tz,
                       double sx,double sy,double sz,
                       double rx,double ry,double rz) {
  MATRIX m1,m2,m3,m4,m5,m6,m7,m8,ret;
  m1=rcs_matscale(sx,sy,sz);
  m2=rcs_matrot(1,rx);
  m3=rcs_matrot(2,ry);
  m4=rcs_matrot(3,rz);
  m5=rcs_mattran(tx,ty,tz);
  m6=rcs_matmul(m4,m5);
  m7=rcs_matmul(m3,m6);
  m8=rcs_matmul(m2,m7);
  ret=rcs_matmul(m1,m8);
  return ret;
  }

VECTOR rcs_transform(VECTOR a,MATRIX m) {
  VECTOR ret;
  ret.x=m.m[0][0]*a.x + m.m[0][1]*a.y + m.m[0][2]*a.z + m.m[0][3];
  ret.y=m.m[1][0]*a.x + m.m[1][1]*a.y + m.m[1][2]*a.z + m.m[1][3];
  ret.z=m.m[2][0]*a.x + m.m[2][1]*a.y + m.m[2][2]*a.z + m.m[2][3];
  return ret;
  }

