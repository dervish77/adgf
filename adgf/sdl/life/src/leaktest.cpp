// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "leaktest.h"

leaktest::leaktest(){
  numCats = 4;
  numDogs = 8;
}

leaktest::~leaktest(){
}

// The execute method invokes the heapTest method.
// 
bool leaktest::execute() {
  isRunning = true;
  isCompleted = false;

  printf("executing leak test...\n");

  heapTest();

  isRunning = false;
  isCompleted = true;

  return(false);
}

// The heapTest method creates two arrays of objects on the heap.  As each 
// object is created, some data within the object is initialized.  Then 
// nearly all the objects in each array are deleted, one object in one array, 
// and two objects in the other array are left intact, hence creating a direct 
// memory leak.
//
// Also another object is created that contains a method called doLeak.  This 
// method is called before deleting the object which results in an indirect 
// memory leak when the object itself is deleted.
// 
bool leaktest::heapTest() {
  cat *myCatArray[numCats];
  dog *myDogArray[numDogs];
  zebra *myZebra;

  printf("  creating %d cats...\n", numCats);
  for (int i=0; i < numCats; i++)
  {
     myCatArray[i] = new cat;
     myCatArray[i]->setId(i+1);
  }

  printf("  creating %d dogs...\n",numDogs);
  for (int i=0; i < numDogs; i++)
  {
     myDogArray[i] = new dog;
     myDogArray[i]->setId(i+1);
  }

  printf("  creating 1 zebra...\n");
  myZebra = new zebra;

  if ( 0 == getMode() )
  {
    printf(" errors are disabled...\n");
    printf("  releasing %d cats...\n", numCats);
    for (int i=0; i < (numCats); i++)
    {
       delete myCatArray[i];
    }

    printf("  releasing %d dogs...\n", numDogs);
    for (int i=0; i < (numDogs); i++)
    {
       delete myDogArray[i];
    }

    printf("  releasing 1 zebra...\n");
    delete myZebra;
  }
  else
  {
    printf("  releasing %d cats...\n", (numCats-1));
    for (int i=0; i < (numCats-1); i++)
    {
       delete myCatArray[i];
    }

    printf("  releasing %d dogs...\n", (numDogs-1));
    for (int i=0; i < (numDogs-2); i++)
    {
       delete myDogArray[i];
    }

    printf("  releasing 1 leaky zebra...\n");
    myZebra->doLeak();
    delete myZebra;
  }

  return(false);
}

