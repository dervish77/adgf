// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _CAT_H
#define _CAT_H


#include "animal.h"

//This class is a "cat", to be used in a list of animals.

class cat : public animal {
  public:
    cat();

    ~cat();

    void setId(int id);

    int getId();


  private:
    int myId;

};
#endif
