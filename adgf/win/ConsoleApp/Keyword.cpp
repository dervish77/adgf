// keyword.cpp
//

#include <cstdlib>
#include <iostream>

using namespace std;

#include "keyword.h"


//------------------------------------------------------------------------------   
// Keyword constructor.
//------------------------------------------------------------------------------  

Keyword::Keyword(KWID kwid, char *kw)
{     
    Keyword::id = kwid; 
    strcpy(Keyword::keyword, kw);   
}


// eof
