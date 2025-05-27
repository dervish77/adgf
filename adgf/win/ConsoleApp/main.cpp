// main.cpp
//

#include <cstdlib>
#include <iostream>

#include "main.h"
#include "tokenizer.h"
#include "parser.h"
#include "keyword.h"


int main(int argc, char *argv[])
{
    int i;
    BOOLEAN_T	    quit = FALSE; 
    LONG_BUFFER_T	cmd, cmdstring;
    TOKEN_STRING_T  token;
    
    Tokenizer       tkn;
    
    Parser          parse;
    KWID            tokenId;

    printf("Hello from ConsoleApp!\n");
    printf("\n");
    
//    tkn.SetDelimiter(';');
    
#ifdef ENABLE_DEBUG        
    tkn.DumpDebug();
#endif

    while ( !quit )
    {
        // get string from user
        printf("\n%s", PROMPT);
        fgets( cmd, LONG_BUFF_LEN, stdin );
        strncpy( cmdstring, cmd, LONG_BUFF_LEN );
        
        // remove newline ('\r') character
        cmdstring[strlen(cmdstring)-1] = '\0';
        
//        printf("Main: you typed  --> %s\n", cmdstring);
//        printf("Main: char count --> %d\n", strlen(cmdstring) );
        
        // pass string to tokenizer
        tkn.ParseString(cmdstring);

#ifdef ENABLE_DEBUG        
        tkn.DumpDebug();
#endif

        // check if any tokens were found
        if (tkn.GetTokenCount() > 0)
        {
            // get each token from tokenizer and display
            printf("Main: token count = %d\n", tkn.GetTokenCount() );
            for (i=0; i < tkn.GetTokenCount(); i++)
            {
                tkn.GetNextToken( token );
                printf("Main: token %d - %s\n", i, token);
            }
            
            // reset tokenizer to first token and retrieve it
            // then parse it to see what the user typed
            tkn.SetTokenIndex(0);
            tkn.GetNextToken( token );
            tokenId = parse.Identify( token );
            switch (tokenId)
            {
                case T_QUIT:
                    printf("Quitting...\n");
                    quit = TRUE;
                    break;
                case T_CHSRC:
                    printf("Changing source...\n");
                    break;
                case T_PLAY:
                    printf("Playing...\n");
                    break;
                case T_TUNE:
                    printf("Tuning...\n");
                    break;
                case T_SCAN:
                    printf("Scanning...\n");   
                    break;
                case T_SEEK:
                    printf("Seeking...\n");             
                    break;
                default:
                    printf("Unknown command\n");
                    break;
            }
        }
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
