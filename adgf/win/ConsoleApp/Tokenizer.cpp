// tokenizer.cpp
//

#include <cstdlib>
#include <iostream>

#include "tokenizer.h"


//------------------------------------------------------------------------------   
// Tokenizer constructor.
//------------------------------------------------------------------------------  

Tokenizer::Tokenizer(void)
{     
    Tokenizer::delimiter = ' ';    
    Tokenizer::tokenCount = 0;
    Tokenizer::tokenIndex = 0;
    Tokenizer::inputString[0] = '\0';
    Tokenizer::inputLength = 0;
}


//------------------------------------------------------------------------------   
// Public Method -- Tokenizer::SetDelimiter()
//
// input:
//       c       - new delimiter character
// output:
//       n/a
//------------------------------------------------------------------------------  

void Tokenizer::SetDelimiter(char c)
{
    Tokenizer::delimiter = c;                           
}

//------------------------------------------------------------------------------   
// Public Method -- Tokenizer::GetTokenCount()
//
// input:
//       n/a     
// output:
//       count      - token count from ParseString operation
//------------------------------------------------------------------------------  

int Tokenizer::GetTokenCount(void)
{
    return(Tokenizer::tokenCount);                        
}

//------------------------------------------------------------------------------   
// Public Method -- Tokenizer::ParseString()
//
// input:
//       str       - pointer to string to parse
//       length    - length of string to parse
// output:
//       count     - token count from parsed string
//------------------------------------------------------------------------------  

int Tokenizer::ParseString(char *str)
{
    int eos = 1;
    int i, ti=0, index=0;
    char c, *string;
    char *args[MAX_TOKENS];
    
    // copy string to be parsed to local storage
    strcpy(Tokenizer::inputString, str);
    Tokenizer::inputLength = strlen(str);
    Tokenizer::tokenIndex = 0;
    Tokenizer::tokenCount = 0;
    
    // set pointer to string to be parsed
    string = Tokenizer::inputString;
    
    // detect if string was typed
    if (Tokenizer::inputLength > 0)
    {
        eos = 0;
    }
    
    // loop for each character in string
    while (!eos)
    {
        // get next character from string
        c = *string;

        // if at end of string
        // then increment token count, terminate current token, 
        //      reset token char index, set eos to true
        if ( c == '\0' )
        {
            Tokenizer::tokenCount++;      
            Tokenizer::tokenList[index][ti] = '\0';
            index++;
            ti=0;
            eos = 1;
        }
        // else if at delimiter character
        // then increment token count, terminate current token,
        //      reset token char index
        else if ( c == Tokenizer::delimiter )
        {
            Tokenizer::tokenCount++;      
            Tokenizer::tokenList[index][ti] = '\0';
            index++;
            ti=0;
            
            // skip repeated delimiter characters
            string++;
            while (*string == Tokenizer::delimiter)
            {
                string++;
                if (*string == '\0') 
                {
                    eos = 1;
                }
            }
            string--;
        }
        // else copy character to current token
        else
        {
            Tokenizer::tokenList[index][ti] = c;
            ti++;        
        }
        
        string++;
    }

//    printf("end ti=%d\n", ti);
//    printf("end index=%d\n", index);
                        
    return(Tokenizer::tokenCount);                        
}

//------------------------------------------------------------------------------   
// Public Method -- Tokenizer::GetNextToken()
//
// input:
//       *token    - pointer to token buffer
// output:
//       length    - length of token
//------------------------------------------------------------------------------  

int Tokenizer::GetNextToken(char *token)
{
    int length;
    
    // copy token to output, calc string length, 
    // and increment token index
    strcpy(token, Tokenizer::tokenList[Tokenizer::tokenIndex]);
    length = strlen(Tokenizer::tokenList[Tokenizer::tokenIndex]);
    Tokenizer::tokenIndex++;
    
    return( length );                        
}

//------------------------------------------------------------------------------   
// Public Method -- Tokenizer::SetTokenIndex()
//
// input:
//       index    - new token index
// output:
//       n/a
//------------------------------------------------------------------------------  

void Tokenizer::SetTokenIndex(int index)
{
    Tokenizer::tokenIndex = index;                     
}

//------------------------------------------------------------------------------   
// Public Method -- Tokenizer::DumpDebug()
//------------------------------------------------------------------------------  
#ifdef ENABLE_DEBUG
void Tokenizer::DumpDebug(void)
{
    int i;
    
    printf("Tokenizer::DumpDebug: delimiter   = %c\n", Tokenizer::delimiter);
    printf("Tokenizer::DumpDebug: tokenCount  = %d\n", Tokenizer::tokenCount);
    printf("Tokenizer::DumpDebug: tokenIndex  = %d\n", Tokenizer::tokenIndex);
    printf("Tokenizer::DumpDebug: inputLength = %d\n", Tokenizer::inputLength);
    printf("Tokenizer::DumpDebug: inputString = %s\n", Tokenizer::inputString);
    
    for (i=0; i < Tokenizer::tokenCount; i++)
    {
        printf("Tokenizer::DumpDebug: token %d = %s\n", i, Tokenizer::tokenList[i]); 
        printf("Tokenizer::DumpDebug: token len = %d\n", strlen(Tokenizer::tokenList[i]) );
    }
}
#endif

// eof
