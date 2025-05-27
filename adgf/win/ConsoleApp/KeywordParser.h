// parser.h
//

#ifndef __PARSER_H
#define __PARSER_H

#include "keyword.h"


//#define ENABLE_DEBUG


// define parser class
class Parser
{
public:
                    Parser                      (void);

    KWID            Identify                    (char *token);
    
#ifdef ENABLE_DEBUG
    void            DumpDebug                   (void);
#endif

private:
	KWTYPE			tokenType;
    KWID            tokenId;

}; 

#endif // __PARSER_H
