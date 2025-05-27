// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _LEAKTEST_H
#define _LEAKTEST_H


#include "test.h"
#include "cat.h"
#include "dog.h"
#include "zebra.h"

//This test forces a memory leak condition to test dynamic 
//memory analysis tools.

class leaktest : public test {
  public:
    leaktest();

    virtual ~leaktest();

    // The execute method invokes the heapTest method.
    // 
    virtual bool execute();

    // The heapTest method creates two arrays of objects on the heap.  As each 
    // object is created, some data within the object is initialized.  Then 
    // nearly all the objects in each array are deleted, one object in one array, 
    // and two objects in the other array are left intact, hence creating a direct 
    // memory leak.
    //
    // Also another object is created that contains a method called doLeak.  This 
    // method is called before deleting the object which results in an indirect 
    // memory leak when the object itself is deleted.
    // 
    bool heapTest();


  private:
    cat theCat;

    dog theDog;

    zebra theZebra;

    int numCats;

    int numDogs;

};
#endif
