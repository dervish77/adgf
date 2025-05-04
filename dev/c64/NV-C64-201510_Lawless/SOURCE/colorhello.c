#include <stdio.h>
#include <peekpoke.h>


int main()
{
      // set border to black (53280 )
   POKE(0xd020,0);

      // set background to black (53281)
   POKE(0xd021,0);

      // set text color to white
   POKE(646,15);

   printf("Hello, world!\n");
}
