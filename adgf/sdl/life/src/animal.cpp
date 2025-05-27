// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "animal.h"

animal::animal(){
}

animal::~animal(){
}

void animal::setSpecies(int species) {
  mySpecies = species;
}

int animal::getSpecies() {
  return(mySpecies);
}

