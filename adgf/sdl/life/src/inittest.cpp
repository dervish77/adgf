// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "inittest.h"

inittest::inittest(){
}

inittest::~inittest(){
}

// The execute method invokes the staticTest, stackTest and heapTest methods.
// 
bool inittest::execute() {
  isRunning = true;
  isCompleted = false;

  printf("executing init test...\n");

  staticTest();
  stackTest();
  heapTest();

  isRunning = false;
  isCompleted = true;

  return(false);
}

// The staticTest method initializes a data member of one of two objects that 
// are stored as static data members of the staticTest object.  The same data 
// member of the other object is left uninitialized.
// 
bool inittest::staticTest() {
  printf("Static: contained objects\n");
  if ( 0 == getMode() )
  {
     theCat.setId( 101 );
  }
  theDog.setId( 102 );
  printf("  contained cat's id is %d, species is %d\n", theCat.getId(), theCat.getSpecies() );
  printf("  contained dog's id is %d, species is %d\n", theDog.getId(), theDog.getSpecies() );

  return(false);
}

// The stackTest method initializes a data member of one of two objects that 
// were created on the stack.  The same data member of the other object is 
// left uninitialized.
// 
bool inittest::stackTest() {
  printf("Dynamic: stack objects\n");
  cat oldCat;
  dog oldDog;
  if ( 0 == getMode() )
  {
     oldCat.setId( 201 );
  }
  oldDog.setId( 202 );
  printf("  stack     cat's id is %d, species is %d\n", oldCat.getId(), oldCat.getSpecies() );
  printf("  stack     dog's id is %d, species is %d\n", oldDog.getId(), oldDog.getSpecies() );

  return(false);
}

// The heapTest method initializes a data member of one of two objects that 
// were created on the heap.  The same data member of the other object is 
// left uninitialized.
// 
bool inittest::heapTest() {
  printf("Dynamic: heap objects\n");
  cat *newCat = new cat;
  if ( 0 == getMode() )
  {
     newCat->setId( 301 );
  }
  dog *newDog = new dog;
  newDog->setId( 302 );
  printf("  heap      cat's id is %d, species is %d\n", newCat->getId(), newCat->getSpecies() );
  printf("  heap      dog's id is %d, species is %d\n", newDog->getId(), newDog->getSpecies() );
  delete newCat;
  delete newDog;

  return(false);
}

