// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _BOUNDSTEST_H
#define _BOUNDSTEST_H


#include "test.h"

//This test forces an out of bounds condition to test dynamic memory 
//analysis tools.
class boundstest : public test {
  public:
    boundstest();

    ~boundstest();

    // The execute method invokes the stackTest and heapTest methods.
    // 
    virtual bool execute();

    // The stackTest method creates two character arrays on the stack.  It then initializes the 
    // second array, and then initializes the first array by over-running the end of the array.
    // This creates a buffer over-run condition using stack memory.
    // 
    bool stackTest();

    // The heapTest method creates two character arrays on the heap.  It then initializes the 
    // second array, and then initializes the first array by over-running the end of the array.
    // This creates a buffer over-run condition using heap memory.
    // 
    bool heapTest();

};
#endif
