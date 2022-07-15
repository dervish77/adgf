// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "cat.h"

cat::cat(){
  setSpecies(1001);
}

cat::~cat(){
}

void cat::setId(int id) {
  myId = id; 
}

int cat::getId() {
  return(myId);
}

