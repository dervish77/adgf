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
	Parser::tokenType = TY_NULL;
    Parser::tokenId   = T_NULL;    
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
            Keyword( TY_NULL, T_NULL,  "null"  ),
            Keyword( TY_NULL, T_QUIT,  "quit"  ),
            Keyword( TY_NULL, T_CHSRC, "chsrc" ),
            Keyword( TY_NULL, T_PLAY,  "play"  ),
            Keyword( TY_NULL, T_TUNE,  "tune"  ),
            Keyword( TY_NULL, T_SCAN,  "scan"  ),
            Keyword( TY_NULL, T_SEEK,  "seek"  ),
    };
    
    // init token id to not found
	Parser::tokenType = TY_NULL;
    Parser::tokenId   = T_NULL;
//    printf("Parser::Identify: token = %s\n", token);
    
    // loop through the keywords table 
    for (i=0; i < NUM_KEYWORD_ID; i++)
    {
//        printf("Parser::Identify: keyword %d - %s\n", i, keywords[i].keyword);
        
        // if match found, then save the keyword id
        if ( strcmp( token, keywords[i].keyword ) == 0 )
        {
//            printf("Parser::Identify: found it - %d\n", keywords[i].id);
			Parser::tokenType = keywords[i].type;
            Parser::tokenId   = keywords[i].id;     
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
    printf("Parser::DumpDebug: tokenType = %s\n", Parser::tokenType);
    printf("Parser::DumpDebug: tokenId   = %s\n", Parser::tokenId);
}
#endif

// eof
