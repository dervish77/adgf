// ======================================================================
// File: ${artifact}
//
// ======================================================================


#include <stdio.h>
#include <stdlib.h>
#include "mymain.h"

mymain::mymain(){
 
  m_PatternId = 0;  // No pattern specified
  m_RuleId = 1;     // Conway's rules
  m_SimMode = 1;    // Interactive sim
  
}

mymain::~mymain(){
}

bool mymain::printBanner(char * progname, char * version) {
  printf("=============================================\n");
  printf(" %s -- version %s\n", progname, version);
  printf("=============================================\n");
}

void mymain::printUsage(char * progname) {
  printf("Usage:  %s [-h|-v]|[-f <file>|-p #|-r #|-s #]\n", progname);
  printf("\n");  
}

void mymain::printHelp(char * progname) {
  printUsage(progname);
  printf("  Options:\n");
  printf("     -h          - get options help\n");
  printf("     -v          - display version\n");
  printf("\n");
  printf("     -f <file>   - run custom pattern from file\n");
  printf("     -p #        - run pre-defined pattern\n");
  printf("     -r #        - rule id, not implemented\n");
  printf("     -s #        - sim mode, not implemented\n");
  printf("\n");
}

bool mymain::parseArgs(int argc, char * argv[]) {
   int i;

   char filename[20];
   sprintf(filename, " ");

   switch (argc)
   {
      case 1:
         printUsage(argv[0]);
         exit(1);
         break;

      default:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'h':
                     printHelp(argv[0]);
                     if (argc == 2)
                        exit(0);
                     else
                        break;

		          case 'f':
                     sprintf(filename, "%s", argv[i+1]);
                     i++;
                     printf("file name is %s\n", filename);
                     break;

                  case 'p':
                     m_PatternId = atoi( argv[i+1] );
                     i++;
                     break;

                  case 'r':
                     m_RuleId = atoi( argv[i+1] );
                     i++;
                     break;

                  case 's':
                     m_SimMode = atoi( argv[i+1] );
                     i++;
                     break;

                  case 'v':
                     printBanner(argv[0], VERSION);
                     exit(0);
                     break;

                  default:
                     printUsage(argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
                printUsage(argv[0]);
                exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

}

void mymain::doProgram() {

  printf("\n");
  printf("pattern id = %d\n", m_PatternId);
  printf("rule id    = %d\n", m_RuleId);
  printf("sim mode   = %d\n", m_SimMode);
  printf("\n");

  if ( m_Life.runProgram( m_PatternId, m_RuleId, m_SimMode ) )
  {   
     fprintf(stderr, "ERROR: runProgram returned failed status!\n");
  }  

}

