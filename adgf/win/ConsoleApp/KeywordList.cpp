// keyword.cpp
//

#include <cstdlib>
#include <iostream>

#include "keyword.h"


//------------------------------------------------------------------------------   
// Keyword constructor.
//------------------------------------------------------------------------------  

Keyword::Keyword(KWTYPE kwtype, KWID kwid, char *kw)
{     
	Keyword::type = kwtype;
    Keyword::id = kwid; 
    strcpy(Keyword::keyword, kw);   
}


// eof
