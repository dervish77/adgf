// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "dog.h"

dog::dog(){
  setSpecies(2001);
}

dog::~dog(){
}

void dog::setId(int id) {
  myId = id;
}

int dog::getId() {
  return(myId);
}

