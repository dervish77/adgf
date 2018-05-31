#include "librcs.h"
#include "math.h"

double rcs_cosD(double a) {
  return cos(rcs_radians(a));
  }

double rcs_degrees(double a) {
  return a*PIUNDER180;
  }

double rcs_frac(double x) {
  return x-((int)x);
  }

double rcs_max(double a,double b) {
  return (a>b) ? a : b;
  }

double rcs_max3(double a,double b,double c) {
  return rcs_max(rcs_max(a,b),c);
  }

double rcs_max4(double a,double b,double c,double d) {
  return rcs_max(rcs_max(a,b),rcs_max(c,d));
  }

double rcs_min(double a,double b) {
  return (a<b) ? a : b;
  }

double rcs_min3(double a,double b,double c) {
  return rcs_min(rcs_min(a,b),c);
  }

double rcs_min4(double a,double b,double c,double d) {
  return rcs_min(rcs_min(a,b),rcs_min(c,d));
  }

double rcs_power(double base,int exp) {
  double bp;
  int    i;
  if (exp==0) return 1;
  bp=1.0;
  for (i=0;i<exp;i++) bp *= exp;
  return bp;
  }

int rcs_powerInt(int base,int exp) {
  if (exp==0) return 1;
  return base*rcs_powerInt(base,exp-1);
  }

double rcs_radians(double a) {
  return a*PIOVER180;
  }

int rcs_round(double x) {
  return (int)(x+0.5);
  }

double rcs_sign(double x) {
  if (x<0) return -1.0;
  if (x>0) return 1.0;
  return 0;
  }

int rcs_signInt(int x) {
  if (x<0) return -1;
  if (x>0) return 1;
  return 0;
  }

double rcs_sinD(double a) {
  return sin(rcs_radians(a));
  }

double rcs_sqr(double x) {
  return x*x;
  }

int rcs_sqrInt(int x) {
  return x*x;
  }

int rcs_sqrtInt(int x) {
  int oddInt,oldArg,firstSqrt;
  oddInt=1;
  oldArg=x;
  while (x>=0) {
    x-=oddInt;
    oddInt+=2;
    }
  firstSqrt=oddInt / 2;
  if (rcs_sqr(firstSqrt)-firstSqrt+1 > oldArg) return firstSqrt-1;
  return firstSqrt;
  }

int rcs_trunc(double x) {
  return (int)x;
  }

double rcs_cos(double angle) {
  double sum;
  double last;
  double k;
  double sgn;
  double pwr;
  double fct;
  double fctCount;
  sum = 1;
  last = 0;
  k = 1;
  sgn = 1;
  pwr = 1;
  fct = 1;
  fctCount = 1;
  angle *= angle;
  while (last != sum) {
    last = sum;
    sgn *= -1;
    pwr *= angle;
    fct *= fctCount++;
    fct *= fctCount++;
    sum += ( (sgn * pwr) / fct);
    k++;
    }
  return sum;
  }

double rcs_sin(double angle) {
  double sum;
  double last;
  double k;
  double sgn;
  double pwr;
  double fct;
  double fctCount;
  sum = angle;
  last = 0;
  k = 1;
  sgn = 1;
  pwr = angle;
  fct = 1;
  fctCount = 2;
  angle *= angle;
  while (last != sum) {
    last = sum;
    sgn *= -1;
    pwr *= angle;
    fct *= fctCount++;
    fct *= fctCount++;
    sum += ( (sgn * pwr) / fct);
    k++;
    }
  return sum;
  }

double rcs_exp(double n) {
  double sum;
  double last;
  double fct;
  double fctCount;
  double pwr;
  last = 0;
  pwr = n;
  fct = 1;
  fctCount = 2;
  sum = 1 + n;
  while (last != sum) {
    last = sum;
    pwr *= n;
    fct *= fctCount++;
    sum += (pwr / fct);
    }
  return sum;
  }

double rcs_log(double n) {
  double sum;
  double last;
  double k;
  double pwr;
  int    cnt;
  n = (n-1)/(n+1);
  sum = 0;
  pwr = n;
  k = 1;
  last = 1;
  cnt = 20;
  n *= n;
  while (last != sum) {
    last = sum;
    sum += pwr / k;
    pwr *= n;
    k+=2;
    cnt--;
    }
  return sum * 2;
  }

double rcs_pow(double x,double y) {
  return rcs_exp(rcs_log(x)*y);
  } 
 
double rcs_log10(double n) {
  return (rcs_log(n) / 2.30258509299404568402);
  } 

double rcs_exp10(double n) {
  return (rcs_exp(n * 2.30258509299404568402));
  }

double rcs_root(double n,double rt) {
  return rcs_pow(n,(1/rt));
  }

double rcs_sqrt(double n) {
  return rcs_pow(n,0.5);
  }

double rcs_tan(double n) {
  return (rcs_sin(n)/rcs_cos(n));
  } 

double rcs_atan(double n) {
  double sum;
  double k;
  double last;
  double sgn;
  double pwr;
  int    cnt;
  k = 3;
  pwr = n;
  sum = n;
  last = 99999;
  cnt = 1000;
  n *=n;
  if (n <= 1) {
    sgn = 1;
    while (last != sum && cnt-- > 0) {
      last = sum;
      pwr *= n;
      sgn *= -1;
      sum += (sgn * pwr/k);
      k += 2;
      }
    } else {
    sum = (3.14159265358979323846 / 2) - (1 / sum);
    sgn = -1;
    while (last != sum && cnt-- > 0) {
      last = sum;
      pwr *= n;
      sgn *= -1;
      sum += (sgn / (k*pwr));
      k += 2;
      }
    }
  return sum;
  }

double rcs_acos(double n) {
  n *= n;
  return rcs_atan(rcs_sqrt((1-n)/n));
  }

double rcs_asin(double n) {
  n *= n;
  return rcs_atan(rcs_sqrt(n/(1-n)));
  }

double rcs_sinh(double n) {
  return (rcs_exp(n) - rcs_exp(-n))/2;
  }

double rcs_cosh(double n) {
  return (rcs_exp(n) + rcs_exp(-n))/2;
  }

double rcs_tanh(double n) {
  return rcs_sinh(n) / rcs_cosh(n);
  }

double rcs_asinh(double n) {
  return rcs_log(rcs_sqrt(n * n + 1) + n);
  }

double rcs_acosh(double n) {
  return rcs_log(rcs_sqrt(n * n - 1) + n);
  }

double rcs_atanh(double n) {
  return rcs_log((1 + n) / (1 - n)) / 2;
  }

double rcs_cot(double n) {
  return rcs_cos(n) / rcs_sin(n);
  }

double rcs_cosec(double n) {
  return 1/rcs_sin(n);
  }

double rcs_sec(double n) {
  return 1/rcs_cos(n);
  }

double rcs_acot(double n) {
  return rcs_atan(1/n);
  }

double rcs_acosec(double n) {
  return rcs_atan(rcs_sqrt(1 / (n * n - 1)));
  }

double rcs_asec(double n) {
  return rcs_atan(rcs_sqrt(n * n - 1));
  }

double rcs_cosech(double n) {
  return 1/rcs_sinh(n);
  }

double rcs_sech(double n) {
  return 1/rcs_cosh(n);
  }

double rcs_coth(double n) {
  return 1/rcs_tanh(n);
  }

double rcs_acosech(double n) {
  return rcs_log(((rcs_sqrt(n * n + 1) + 1) / n));
  }

double rcs_asech(double n) {
  return rcs_log(((rcs_sqrt(1 - n * n) + 1) / n));
  }

double rcs_acoth(double n) {
  return rcs_log((n + 1) / (n - 1)) / 2;
  }

