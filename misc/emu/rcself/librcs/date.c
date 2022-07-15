#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "librcs.h"

long rcs_daysInYear(long year) {
  if (year%400 == 0) return 366;
  if (year%100 == 0) return 365;
  if (year%4   == 0) return 366;
  return 365;
  }

long rcs_daysInMonth(long year,long month) {
  if (month==1 || month==3 || month==5 || month==7 || month==8 ||
      month==10 || month==12) return 31;
  if (month==4 || month==6 || month==9 || month==11) return 30;
  return (rcs_daysInYear(year)==366)?29:28;
  }

rcs_dt rcs_daysToDate(long t,rcs_dt baseDate) {
  while (t>rcs_daysInYear(baseDate.year))
    t-=rcs_daysInYear(baseDate.year++);
  while (t>rcs_daysInMonth(baseDate.year,baseDate.month))
    t-=rcs_daysInMonth(baseDate.year,baseDate.month++);
  baseDate.day += t;
  while (baseDate.day > rcs_daysInMonth(baseDate.year, baseDate.month)) {
    baseDate.day -= rcs_daysInMonth(baseDate.year, baseDate.month);
    baseDate.month++;
    }
  return baseDate;
  }

long rcs_dateToDays(rcs_dt dt,rcs_dt base) {
  long ret;
  ret=(long)(dt.day-base.day);
  while (dt.month>base.month) ret+=(long)(rcs_daysInMonth(dt.year,--dt.month));
  while (dt.year>base.year) ret+=(long)(rcs_daysInYear(--dt.year));
  return ret;
  }

void rcs_daysToString(long t,char* buffer,rcs_dt base) {
  rcs_dt dt;
  dt=rcs_daysToDate(t,base);
  if (dt.year==0) strcpy(buffer,"  /  /    ");
    else sprintf(buffer,"%02ld/%02ld/%04ld",dt.month,dt.day,dt.year);
  }

long rcs_stringToDays(char* date,rcs_dt base) {
  rcs_dt dt;
  dt.month=atol(date);
  dt.day=atol(&date[3]);
  dt.year=atol(&date[6]);
  return rcs_dateToDays(dt,base);
  }

double rcs_sidereal(double mo,double da,double yr,
                    double hr,double mi,double sc,
                    double lng,double* hrRet,double* miRet,double* scRet) {
  double d;
  double st;
  d = 367*yr-floor(7*(yr+floor((mo+9)/12))/4)+floor(275*mo/9)+da-730531.5 +
      ((hr + mi/60 + sc/3600)/24);
  st = 280.46061837 + 360.98564736629 * d + lng;
  st /= 360;
  st = (st - floor(st)) * 360;
  d = st/15;
  *hrRet = floor(d);
  d -= floor(d);
  d *= 60;
  *miRet = floor(d);
  d -= floor(d);
  *scRet = d*60;
  return st;
  }

long rcsgl_julianDay(int m,int d,int y) {
  if (m < 3) {
    m += 12;
    y--;
    }
  return 2-(y/100)+((y/100)/4) + d + (365.25*(y+4716)) + (30.6001*(m+1)) - 1524.5;
  }

