// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "test.h"

test::test(){
  isRunning = false;
  isCompleted = false;
}

test::~test(){
}

void test::setMode(int mode) {
  theMode = mode;
}

int test::getMode() {
  return(theMode);
}

