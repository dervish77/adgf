#include <time.h>
#include <stdlib.h>
#include "librcs.h"

int rcs_random(int size) {
  float r;
  r=rand();
  r/=RAND_MAX;
  r-=(int)r;
  r*=size;
  return (int)r;
  }

void rcs_randomize() {
  time_t t;
  t=time(&t);
  t&=0xfffff;
  srand(t);
  }

