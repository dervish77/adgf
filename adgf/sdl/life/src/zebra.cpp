// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "zebra.h"

zebra::zebra(){
  setSpecies(3001);
}

zebra::~zebra(){
}

void zebra::setId(int id) {
  myId = id;
}

int zebra::getId() {
  return(myId);
}

// The doLeak method allocates some memory to a character array.  The pointer is stored 
// on the stack.  But the memory is not freed, thus creating an indirect memory leak when 
// the object is destroyed.
// 
bool zebra::doLeak() {
  char *leakyString;
  leakyString = new char[100];
  for (int i=0; i< 100; i++)
  {
      leakyString[i] = i;
  }
}

