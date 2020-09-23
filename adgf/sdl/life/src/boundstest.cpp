// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "boundstest.h"

boundstest::boundstest(){
}

boundstest::~boundstest(){
}

// The execute method invokes the stackTest and heapTest methods.
// 
bool boundstest::execute() {

  isRunning = true;
  isCompleted = false;

  printf("executing bounds test...\n");

  stackTest();
  heapTest();

  isRunning = false;
  isCompleted = true;

  return(false);

}

// The stackTest method creates two character arrays on the stack.  It then initializes the 
// second array, and then initializes the first array by over-running the end of the array.
// This creates a buffer over-run condition using stack memory.
// 
bool boundstest::stackTest() {
  char c, l;
 
  printf("  testing via the stack\n");

  char letters[8];
  char numbers[8];

  // init numbers to 0 thru 7
  c = 0x30;
  for (int i=0; i<8; i++)
  {
    numbers[i] = c++;
  }
  numbers[7] = 0;

  // overrun letters into numbers
  l = 0x41;

  if ( 0 == getMode() )
  {
    for (int i=0; i<8; i++)
    {
      letters[i] = l++;
    }
    letters[7] = 0;
  }
  else
  {
    for (int i=0; i<12; i++)
    {
      letters[i] = l++;
    }
  }

  printf("    letters are - %s\n", letters);
  printf("    numbers are - %s\n", numbers);

  return(false);
}

// The heapTest method creates two character arrays on the heap.  It then initializes the 
// second array, and then initializes the first array by over-running the end of the array.
// This creates a buffer over-run condition using heap memory.
// 
bool boundstest::heapTest() {
  char c, l;

  printf("  testing via the heap\n");

  char *pLetters = new char[8];
  char *pNumbers = new char[8];

  // init numbers to 0 thru 7
  c = 0x30;
  for (int i=0; i<8; i++)
  {
    pNumbers[i] = c++;
  }
  pNumbers[7] = 0;

  // overrun letters into numbers
  l = 0x41;

  if ( 0 == getMode() )
  {
    for (int i=0; i<8; i++)
    {
      pLetters[i] = l++;
    }
    pLetters[7] = 0;
  }
  else
  {
    for (int i=0; i<12; i++)
    {
      pLetters[i] = l++;
    }
  }

  printf("    letters are - %s\n", pLetters);
  printf("    numbers are - %s\n", pNumbers);

  delete pLetters;
  delete pNumbers;

  return(false);
}

