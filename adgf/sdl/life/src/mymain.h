// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _MYMAIN_H
#define _MYMAIN_H


#include "version.h"
#include "life.h"

//This class is the engine which drives the appropriate program actions based on 
//command line options.

class mymain {
  private:
    life m_Life;


  public:
    mymain();

    ~mymain();

    bool printBanner(char * progname, char * version);

    void printUsage(char * progname);

    void printHelp(char * progname);

    bool parseArgs(int argc, char * argv[]);

    void doProgram();


  private:
    int m_PatternId;

    int m_RuleId;

    int m_SimMode;

};
#endif
