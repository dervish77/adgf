// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _ZEBRA_H
#define _ZEBRA_H


#include "animal.h"

//This class is a "zebra", to be used in a list of animals.

class zebra : public animal {
  public:
    zebra();

    ~zebra();

    void setId(int id);

    int getId();

    // The doLeak method allocates some memory to a character array.  The pointer is stored 
    // on the stack.  But the memory is not freed, thus creating an indirect memory leak when 
    // the object is destroyed.
    // 
    bool doLeak();


  private:
    int myId;

};
#endif
