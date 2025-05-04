#include <stdio.h>
#include <stdlib.h>

struct room {
   struct room *north;
   struct room *south;
   struct room *east;
   struct room *west;
   char *description;
} *r1,*r2,*r3, *r4,*the_exit;

void init_rooms();
void look(struct room *);

int main()
{
   struct room *current;
   char inp[3];
   
   init_rooms();
   current=r1;
   for(;;) {
      look(current);
      if(current==the_exit) {
         printf("Thank you for playing!");
         return 0;
      }      
      printf("Go where? (n,s,e,w) ");
      fgets(inp,2,stdin);
      printf("\n");
      if( (*inp=='n')||(*inp=='N')) {
         if(current->north==NULL) {
            printf("There is no doorway to the North.\n");
         }
         else {
            current=current->north;
         }
         continue;
      }

      if( (*inp=='s')||(*inp=='S')) {
         if(current->south==NULL) {
            printf("There is no doorway to the South.\n");
         }
         else {
            current=current->south;
         }
         continue;
      }

      if( (*inp=='e')||(*inp=='E')) {
         if(current->east==NULL) {
            printf("There is no doorway to the East.\n");
         }
         else {
            current=current->east;
         }
         continue;
      }

      if( (*inp=='w')||(*inp=='W')) {
         if(current->west==NULL) {
            printf("There is no doorway to the West.\n");
         }
         else {
            current=current->west;
         }
         continue;
      }      
      printf("I don't understand %c\n",*inp);
   }
}

void init_rooms()
{
   
   the_exit=(struct room *) malloc(sizeof(struct room));
   the_exit->description=
      "the outside of the building";
   
   r1=(struct room *) malloc(sizeof(struct room));
   r1->description=
      "the main lobby";
   
   r2=(struct room *) malloc(sizeof(struct room));
   r2->description=
      "the dining room";
   
   r3=(struct room *) malloc(sizeof(struct room));
   r3->description=
      "the kitchen";
   
   r4=(struct room *) malloc(sizeof(struct room));
   r4->description=
      "the gift shop";
   
   r1->south=the_exit;
   r1->north=NULL;
   r1->west=r2;
   r1->east=r4;
   
   r2->south=NULL;
   r2->north=r3;
   r2->west=NULL;
   r2->east=r1;
   
   r3->south=r2;
   r3->north=NULL;
   r3->west=NULL;
   r3->east=NULL;

   r4->south=NULL;
   r4->north=NULL;
   r4->west=r1;
   r4->east=NULL;

   the_exit->south=NULL;
   the_exit->north=r1;
   the_exit->west=NULL;
   the_exit->east=NULL;
}

void look(struct room *r)
{
   printf("You are at %s.\n\n",r->description);
   printf("Doorways appear in these directions:\n");
   if(r->north!=NULL) {
      printf("   North\n");
   }
   if(r->south!=NULL) {
      printf("   South\n");
   }
   if(r->east!=NULL) {
      printf("   East\n");
   }
   if(r->west!=NULL) {
      printf("   West\n");
   }
}
