#include <stdio.h>
#include <stdlib.h>

int main() {
   unsigned int count;
   char *p;
   count=0xf000;
   for(;;) {
      p=(char *)malloc(count);
      if(p!=NULL)
         break;
      count-=16;
   }
   printf("We were able to allocate %u bytes of memory.\n",count);
   printf("Start: %p End: %p\n", p,p+count);
}
