#include <stdio.h>
#include <stdlib.h>
#include <peekpoke.h>

void play_the_game();
int play_again();

int main()
{
   srand(  PEEKW(0x00a1));

   for(;;) {
      play_the_game();
      if( ! play_again()) {
         break;
      }
   }
   return 0;
}

void play_the_game()
{
   int number;
   int tries;
   char answerBuff[5];
   int answer;

   number=(rand()%100)+1;
   tries=1;
   printf("I am thinking of a number between 1 and 100.\n");
   printf("Please try to guess the number.\n");
   for(;;tries++) {
      fgets(answerBuff,4,stdin);
      answer=atoi(answerBuff);
      if(answer==number) {
         printf(" Correct!\n");
         printf("It took you %d %s\n",tries,
            tries==1 ? "try" : "tries" );
         break;
      }   
      else
      if(answer>number) {
         printf(" Too high. Guess again.\n");
      }
      else {
         printf(" Too low. Guess again.\n");
      }
   }
}

int play_again()
{
   char buff[5];
   printf("\n\nPlay again? (y/n):");
   fgets(buff,4,stdin);
   printf("\n");
   return ((*buff=='y')||(*buff=='Y'));
}
