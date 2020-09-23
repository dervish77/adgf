// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _ANIMAL_H
#define _ANIMAL_H


//This class is the base class for all animal objects.

class animal {
  public:
    animal();

    virtual ~animal();

    void setSpecies(int species);

    int getSpecies();


  private:
    int mySpecies;

};
#endif
