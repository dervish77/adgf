#include "librcs.h"

double rcs_compabs(COMPLEX a) {
  return rcs_sqrt(a.r * a.r + a.i * a.i);
  }

COMPLEX rcs_compadd(COMPLEX a,COMPLEX b) {
  COMPLEX ret;
  ret.r=a.r+b.r;
  ret.i=a.i+b.i;
  return ret;
  }

COMPLEX rcs_compconj(COMPLEX a) {
  COMPLEX ret;
  ret.r = a.r;
  ret.i = -a.i;
  return ret;
  }

COMPLEX rcs_compcos(COMPLEX a) {
  COMPLEX ret;
  ret.r = rcs_cos(a.r) * rcs_cosh(a.i);
  ret.i = -rcs_sin(a.r) * rcs_sinh(a.i);
  return ret;
  }

COMPLEX rcs_compcosec(COMPLEX a) {
  return rcs_compdiv(rcs_complex(1,0),rcs_compsin(a));
  }

COMPLEX rcs_compcotan(COMPLEX a) {
  return rcs_compdiv(rcs_compcos(a),rcs_compsin(a));
  }

COMPLEX rcs_compdiv(COMPLEX a,COMPLEX b) {
  COMPLEX ret;
  ret.r = (a.r * b.r + a.i * b.i) / (b.r * b.r + b.i * b.i);
  ret.i = (a.i * b.r - a.r * b.i) / (b.r * b.r + b.i * b.i);
  return ret;
  }

COMPLEX rcs_compexp(COMPLEX a) {
  COMPLEX ret;
  double  mag;
  mag = rcs_exp(a.r);
  ret.r = mag * rcs_cos(a.i);
  ret.i = mag * rcs_sin(a.i);
  return ret;
  }

COMPLEX rcs_complex(double r,double i) {
  COMPLEX ret;
  ret.r=r;
  ret.i=i;
  return ret;
  }

COMPLEX rcs_complog(COMPLEX a) {
  COMPLEX ret;
  ret.r = rcs_log(rcs_sqrt(a.r * a.r + a.i * a.i));
  ret.i = rcs_atan(a.i / a.r);
  return ret;
  }

COMPLEX rcs_compmul(COMPLEX a,COMPLEX b) {
  COMPLEX ret;
  ret.r=(a.r*b.r)-(a.i*b.i);
  ret.i=(a.r*b.i)+(a.i*b.r);
  return ret;
  }

COMPLEX rcs_compneg(COMPLEX a) {
  COMPLEX ret;
  ret.r = -a.r;
  ret.i = -a.i;
  return ret;
  }

COMPLEX rcs_comppow(COMPLEX a,COMPLEX b) {
  return rcs_compexp(rcs_compmul(b,rcs_complog(a)) );
  }

COMPLEX rcs_compsec(COMPLEX a) {
  return rcs_compdiv(rcs_complex(1,0),rcs_compcos(a));
  }

COMPLEX rcs_compsin(COMPLEX a) {
  COMPLEX ret;
  ret.r = rcs_sin(a.r) * rcs_cosh(a.i);
  ret.i = rcs_cos(a.r) * rcs_sinh(a.i);
  return ret;
  }

COMPLEX rcs_compsqr(COMPLEX a) {
  COMPLEX ret;
  ret.r = a.r * a.r - a.i * a.i;
  ret.i = 2 * a.r * a.i;
  return ret;
  }

COMPLEX rcs_compsqrt(COMPLEX a) {
  COMPLEX ret;
  ret.i = rcs_sqrt((rcs_compabs(a) - a.r) / 2);
  ret.r = a.i / (2 * ret.i);
  return ret;
  }

COMPLEX rcs_compsub(COMPLEX a,COMPLEX b) {
  COMPLEX ret;
  ret.r=a.r-b.r;
  ret.i=a.i-b.i;
  return ret;
  }

COMPLEX rcs_comptan(COMPLEX a) {
  return rcs_compdiv(rcs_compsin(a),rcs_compcos(a));
  }

