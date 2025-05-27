// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _INITTEST_H
#define _INITTEST_H


#include "test.h"
#include "cat.h"
#include "dog.h"

//This test forces an uninitialized variable condition to test dynamic 
//memory analysis tools.
class inittest : public test {
  public:
    inittest();

    ~inittest();

    // The execute method invokes the staticTest, stackTest and heapTest methods.
    // 
    virtual bool execute();

    // The staticTest method initializes a data member of one of two objects that 
    // are stored as static data members of the staticTest object.  The same data 
    // member of the other object is left uninitialized.
    // 
    bool staticTest();

    // The stackTest method initializes a data member of one of two objects that 
    // were created on the stack.  The same data member of the other object is 
    // left uninitialized.
    // 
    bool stackTest();

    // The heapTest method initializes a data member of one of two objects that 
    // were created on the heap.  The same data member of the other object is 
    // left uninitialized.
    // 
    bool heapTest();


  private:
    cat theCat;

    dog theDog;

};
#endif
