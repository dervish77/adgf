// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "life.h"

life::life(){
}

life::~life(){
}

// The runProgram method determines which startup pattern needs to be used and then executes the simulation.
// 
bool life::runProgram(int patternId, int ruleId, int simMode) {
  bool error = true;

  switch(patternId)
  {
	  case 1:
		  printf("runTest: executing test 1\n");
		  boundsTest.setMode( simMode );
		  error = boundsTest.execute();
		  break;
	  case 2:
		  printf("runTest: executing test 2\n");
		  initTest.setMode( simMode );
		  error = initTest.execute();
		  break;
	  case 3:
		  printf("runTest: executing test 3\n");
		  leakTest.setMode( simMode );
		  error = leakTest.execute();
		  break;
	  default:
		  fprintf(stderr, "ERROR: unknown testId attempted\n");
		  break;
  }

  printf("runTest: test completed.\n");

  return(error);
}

