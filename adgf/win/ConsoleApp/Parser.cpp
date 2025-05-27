// parser.cpp
//

#include <cstdlib>
#include <iostream>

#include "parser.h"
#include "keyword.h"


//------------------------------------------------------------------------------   
// Parser constructor.
//------------------------------------------------------------------------------  

Parser::Parser(void)
{     
    Parser::tokenId = T_NULL;    
}


//------------------------------------------------------------------------------   
// Public Method -- Parser::Identify()
//
// input:
//       *token       - new delimiter character
// output:
//       tokenId      - ID of token
//------------------------------------------------------------------------------  

KWID Parser::Identify(char *token)
{
    int i;

    Keyword keywords[] = {
            Keyword( T_NULL,  "null" ),
            Keyword( T_QUIT,  "quit" ),
            Keyword( T_CHSRC, "chsrc" ),
            Keyword( T_PLAY,  "play" ),
            Keyword( T_TUNE,  "tune" ),
            Keyword( T_SCAN,  "scan" ),
            Keyword( T_SEEK,  "seek" ),
    };
    
    // init token id to not found
    Parser::tokenId = T_NULL;
//    printf("Parser::Identify: token = %s\n", token);
    
    // loop through the keywords table 
    for (i=0; i < NUM_KEYWORDS; i++)
    {
//        printf("Parser::Identify: keyword %d - %s\n", i, keywords[i].keyword);
        
        // if match found, then save the keyword id
        if ( strcmp( token, keywords[i].keyword ) == 0 )
        {
//            printf("Parser::Identify: found it - %d\n", keywords[i].id);
            Parser::tokenId = keywords[i].id;     
        } 
    }
    
    return(Parser::tokenId);
}

//------------------------------------------------------------------------------   
// Public Method -- Parser::DumpDebug()
//------------------------------------------------------------------------------  
#ifdef ENABLE_DEBUG
void Parser::DumpDebug(void)
{
    int i;
    
    printf("Parser::DumpDebug: tokenId   = %s\n", Parser::tokenId);

}
#endif

// eof
