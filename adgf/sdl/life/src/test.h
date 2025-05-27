// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _TEST_H
#define _TEST_H


//This class is the base class for all test objects.

class test {
  public:
    test();

    virtual ~test();

    virtual bool execute() = 0;

    void setMode(int mode);

    int getMode();


  protected:
    bool isRunning;

    bool isCompleted;

    int theMode;

};
#endif
