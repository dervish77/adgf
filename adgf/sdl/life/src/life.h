// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _LIFE_H
#define _LIFE_H


#include "boundstest.h"
#include "inittest.h"
#include "leaktest.h"

//This class executes the cell life simulation.
class life {
  private:
    boundstest boundsTest;

    inittest initTest;

    leaktest leakTest;


  public:
    life();

    ~life();

    // The runProgram method determines which startup pattern needs to be used and then executes the simulation.
    // 
    bool runProgram(int patternId, int ruleId, int simMode);

};
#endif
