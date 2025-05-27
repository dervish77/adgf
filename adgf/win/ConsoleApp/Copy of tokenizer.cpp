// tokenizer.cpp
//

#include <cstdlib>
#include <iostream>

using namespace std;

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
    int i, ti=0, index=0;
    char c, *string;
    char *args[MAX_TOKENS];
    
    // copy string to be parsed to local storage
    strcpy(Tokenizer::inputString, str);
    Tokenizer::inputLength = strlen(str);
    Tokenizer::tokenIndex = 0;
    
    // if not blank string, set token count to at least one token
    if (Tokenizer::inputLength > 0)
        Tokenizer::tokenCount = 1;
    
    // set pointer to string to be parsed
    string = Tokenizer::inputString;
    
    // loop for each character in string
    for (i=0; i < Tokenizer::inputLength; i++)
    {
        // get next character from string
        c = *string;

//        cout << c << ", ti=" << ti << endl;

        // if this character is delimiter or end of string, 
        // then increment token count, terminate current token, 
        //      reset token char index
        // else copy to current token, increment token char index
        if ( (c == Tokenizer::delimiter) || (c == '\0') )
        {
            Tokenizer::tokenCount++;   
            if (c == '\0')
            {
                Tokenizer::tokenList[index][ti+1] = '\0';
//                cout << "at " << Tokenizer::tokenList[index][ti+1] << endl;
            }
            else
            {
                Tokenizer::tokenList[index][ti] = '\0';
//                cout << "at " << Tokenizer::tokenList[index][ti] << endl;
            }
            index++;
            ti=0;
        }
        else
        {
            Tokenizer::tokenList[index][ti] = c;
            ti++;
        }
        string++;
    }
        
//    cout << "end ti=" << ti << endl;
//    cout << "end index=" << index << endl;
    Tokenizer::tokenList[index][ti] = '\0';
                        
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
    
    cout << "Tokenizer::DumpDebug: delimiter   = " << Tokenizer::delimiter << endl;
    cout << "Tokenizer::DumpDebug: tokenCount  = " << Tokenizer::tokenCount << endl;
    cout << "Tokenizer::DumpDebug: tokenIndex  = " << Tokenizer::tokenIndex << endl;
    cout << "Tokenizer::DumpDebug: inputLength = " << Tokenizer::inputLength << endl;
    cout << "Tokenizer::DumpDebug: inputString = " << Tokenizer::inputString << endl;
    
    for (i=0; i < Tokenizer::tokenCount; i++)
    {
        cout << "Tokenizer::DumpDebug: token " << i << " = " << Tokenizer::tokenList[i] << endl; 
        cout << "Tokenizer::DumpDebug: token len = " << strlen(Tokenizer::tokenList[i]) << endl;
    }
}
#endif

// eof
