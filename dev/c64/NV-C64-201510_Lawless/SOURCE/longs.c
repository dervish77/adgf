#include <stdio.h>

int main() {
   char i;
   unsigned long x=1L;
   for(i=0;i<32;i++) {
      printf("         %10lu ",x);
      x=x*2;
   }
}
