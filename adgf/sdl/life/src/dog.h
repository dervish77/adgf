// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _DOG_H
#define _DOG_H


#include "animal.h"

//This class is a "dog", to be used in a list of animals.

class dog : public animal {
  public:
    dog();

    ~dog();

    void setId(int id);

    int getId();


  private:
    int myId;

};
#endif
