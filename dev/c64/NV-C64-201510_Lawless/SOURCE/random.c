#include <stdio.h>
#include <stdlib.h>
#include <peekpoke.h>

int roll_one_die(int);
int roll_dice();

int main()
{
   unsigned char i;

      // Use the last two bytes
      // of the jiffy clock at
      // $a0 - $a2 to init the
      // randomizer. ( Use $a1
      // and $a2 only )
   srand( PEEKW(0x00a1));

   printf("10 6-sided single die rolls:\n");
   for(i=0;i<10;i++) {
      printf("%d ",roll_one_die(6));
   }   
   printf("\n\n");

   printf("10 6-sided dice rolls:\n");
   for(i=0;i<10;i++) {
      printf("%d ",roll_dice());
   }   
   printf("\n\n");
   
   printf("10 20-sided single die rolls:\n");
   for(i=0;i<10;i++) {
      printf("%d ",roll_one_die(20));
   }   
   printf("\n\n");
   return 0;
}

int roll_one_die(int sides)
{
   return ( rand() % sides ) + 1 ;
}

int roll_dice()
{
   return roll_one_die(6) + roll_one_die(6);
}

