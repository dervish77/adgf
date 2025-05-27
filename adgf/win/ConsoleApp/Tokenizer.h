// tokenizer.h
//

#ifndef __TOKENIZER_H
#define __TOKENIZER_H


//#define ENABLE_DEBUG


// define some helpful constants and types
#define MAX_TOKENS   20

#define TOKEN_LEN	40
typedef char TOKEN_STRING_T[TOKEN_LEN]; 

#define LONG_BUFF_LEN	120
typedef char LONG_BUFFER_T[LONG_BUFF_LEN]; 


// define tokenizer class
class Tokenizer
{
public:
                    Tokenizer                   (void);

    void            SetDelimiter                (char c);

    int             ParseString                 (char *str);
    
    int             GetTokenCount               (void);
    int             GetNextToken                (char *token);

    void            SetTokenIndex               (int index);
    
#ifdef ENABLE_DEBUG
    void            DumpDebug                   (void);
#endif

private:
    char            delimiter;
    int             tokenCount;
    int             tokenIndex;
    
    LONG_BUFFER_T   inputString;
    int             inputLength;
    
    TOKEN_STRING_T  tokenList[MAX_TOKENS];
}; 

#endif // __TOKENIZER_H
