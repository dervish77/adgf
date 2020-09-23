/*****************************************************************************
 *
 *	Test program parsing and diagramming sentences.
 *
 *	File:	lang.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	11/02/95
 *
 *	Revs:
 *	  0.1	03/10/98  added support for prep phrase
 *	  0.0 	11/02/95  originated
 *
 *	Usage:	lang [sentence string]
 *
 *****************************************************************************/


#include <stdio.h>

#ifndef _LANG_H
#include "lang.h"
#endif


/*
#define DEBUG
*/


/*  OpenDictionary	- opens specified dictionary file
 *
 *  Parameters:
 *	filename	- file name of specified dictionary
 *	dictionary	- pointer to dictionary structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
OpenDictionary( char *filename, DICTIONARY_S_T *dictionary )
{
   strcpy( dictionary->file_name, filename );

   dictionary->fp = fopen( dictionary->file_name, "r" );
   if ( dictionary->fp EQ (FILE *) NULL)
   {
      return(TRUE);
   }

   return(FALSE);
}


/*  ReadDictionary	- reads specified dictionary file
 *
 *  Parameters:
 *	dictionary	- pointer to dictionary structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 *
 *  Notes:	file format
 *
 *	count
 *	type_1 word_string_1
 *	type_2 word_string_2
 *	...
 *	type_n word_string_n
 *
 *  example:	
 *
 *	3
 *	N boy
 *	V is
 *	N green
 *
 */
BOOLEAN_T 
ReadDictionary( DICTIONARY_S_T *dictionary )
{
   int i, count;
   char type;
   WORD_A_T word;


   fscanf( dictionary->fp, "%d\n", &count );

   dictionary->num_words = count;

   for (i = 0; i < dictionary->num_words; i++)
   {
      fscanf( dictionary->fp, "%c %s\n", &type, word);

      dictionary->list[i].str = type;

      if ( type EQ WT_DETERMINER_STR )
         dictionary->list[i].type = DETERMINER_WT;
      else if ( type EQ WT_NOUN_STR )
         dictionary->list[i].type = NOUN_WT;
      else if ( type EQ WT_VERB_STR )
         dictionary->list[i].type = VERB_WT;
      else if ( type EQ WT_PRONOUN_STR )
         dictionary->list[i].type = PRONOUN_WT;
      else if ( type EQ WT_PREPOSITION_STR )
         dictionary->list[i].type = PREPOSITION_WT;
      else if ( type EQ WT_ADJECTIVE_STR )
         dictionary->list[i].type = ADJECTIVE_WT;
      else if ( type EQ WT_ADVERB_STR )
         dictionary->list[i].type = ADVERB_WT;
      else 
         dictionary->list[i].type = UNKN_WT;

      dictionary->list[i].length = strlen( word );

      strncpy(dictionary->list[i].word, word, MAX_WORD_LENGTH);
   }

   return(FALSE);
}


/*  DisplayDictionary	- displays specified dictionary file on screen
 *
 *  Parameters:
 *	dictionary	- pointer to dictionary structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
DisplayDictionary( DICTIONARY_S_T *dictionary )
{
   int i;

   printf("Dictionary is:\n");

   for (i = 0; i < dictionary->num_words; i++)
   {
      printf("   %c -- %02d -- %s\n", dictionary->list[i].str, 
					dictionary->list[i].length,
					dictionary->list[i].word );
   }

   return(FALSE);
}


/*  SearchDictionary	- searches dictionary for specified word
 *
 *  Parameters:
 *	word		- pointer to word string to search for
 *	dictionary	- pointer to dictionary structure
 *
 *  Returns:
 *	success flag	- TRUE, if match was found
 *	index		- pointer to index of matching entry
 *
 */
BOOLEAN_T 
SearchDictionary( char *word, DICTIONARY_S_T *dictionary, int *index)
{
   int i;

   for (i = 0; i < dictionary->num_words; i++)
   {
      if ( strlen(word) EQ dictionary->list[i].length )
      {
         if ( strcmp(word, dictionary->list[i].word) EQ 0)
         {
            *index = i;
            return(TRUE);
         }
      }
   }

   return(FALSE);
}


/*  GetSentence	- asks user for sentence input
 *
 *  Parameters:
 *	sentence	- pointer to sentence structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
GetSentence( SENTENCE_S_T *sentence )
{
   SENTENCE_A_T	sent;


   printf( "\nPlease enter a sentence (no caps), followed by <cr>:\n\n" );

   fgets( sent, SENTENCE_LEN, stdin );

   strncpy( sentence->sentence, sent, SENTENCE_LEN );

   return(FALSE);
}


/*  ParseSentence	- parses specified sentence into separate words
 *
 *  Parameters:
 *	dictionary	- pointer to dictionary structure
 *	sentence	- pointer to sentence structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
ParseSentence( DICTIONARY_S_T *dictionary, SENTENCE_S_T *sentence )
{
   int i, word_count, index;
   char *buffer, *word_array[MAX_WORDS_IN_SENT];


   printf( "\nParsing sentence ->   %s\n", sentence->sentence );

   buffer = &sentence->sentence[0];
   sentence->sentence[SENTENCE_LEN - 1] = '\0';

   word_count = ParseString( buffer, word_array );

   sentence->num_words = word_count;

   for (i = 0; i < sentence->num_words; i++)
   {
      sentence->list[i].length = strlen( word_array[i] );

      strcpy(sentence->list[i].word, word_array[i]);

      if (SearchDictionary( &sentence->list[i].word[0], dictionary, &index ))
      {
         sentence->list[i].type = dictionary->list[index].type;
         sentence->list[i].str = dictionary->list[index].str;
      }
      else
      {
         sentence->list[i].type = UNKN_WT;
         sentence->list[i].str = ' ';

         printf("\nwarning:  %s not found in dictionary\n", word_array[i]);
      }
   }

   return(FALSE);
}


/*  DisplaySentence	- output sentence to screen
 *
 *  Parameters:
 *	sentence	- pointer to sentence structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
DisplaySentence( SENTENCE_S_T *sentence )
{
   int i;


   printf("\nSentence contains %d words:\n", sentence->num_words);

   for (i = 0; i < sentence->num_words; i++)
   {
      printf("   %c -- %02d -- %s\n", sentence->list[i].str, 
					sentence->list[i].length,
					sentence->list[i].word );
   }

   return(FALSE);
}


/*  DiagramSentence	- diagrams sentence and displays on screen
 *
 *  Parameters:
 *	sentence	- pointer to sentence structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
DiagramSentence( SENTENCE_S_T *sentence )
{
   int i;
   BOOLEAN_T found_verb;
   BOOLEAN_T found_prep;

   printf("\nSentence Diagram:\n");

   sentence->np[0] = '\0';
   sentence->vp[0] = '\0';
   sentence->pp[0] = '\0';

   found_verb = FALSE;
   found_prep = FALSE;

   for (i = 0; i < sentence->num_words; i++)
   {
      if ( sentence->list[i].type EQ VERB_WT
		|| sentence->list[i].type EQ ADVERB_WT )
      {
         found_verb = TRUE;
      }

      if ( sentence->list[i].type EQ PREPOSITION_WT )
      {
         found_prep = TRUE;
      }

      if (found_verb AND found_prep)	/* work on prep phrase */
      {
         strcat( sentence->pp, sentence->list[i].word );
         strcat( sentence->pp, " " );

         strcat( sentence->vp, sentence->list[i].word );
         strcat( sentence->vp, " " );
      }
      else if (found_verb) 		/* work on verb phrase */
      {
         strcat( sentence->vp, sentence->list[i].word );
         strcat( sentence->vp, " " );
      }
      else				/* word on noun phrase */
      {
         strcat( sentence->np, sentence->list[i].word );
         strcat( sentence->np, " " );
      }
   }

   printf("   noun phrase -> %s\n", sentence->np );
   printf("   verb phrase -> %s\n", sentence->vp );
   printf("   prep phrase -> %s\n", sentence->pp );

   return(FALSE);
}


/*  main	- main program
 *
 *  Parameters:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  Returns:
 *	none
 */
void 
main(int argc, char **argv)
{
   DATABASE_S_T	data;		/* main database */


   /*  open dictionary then read it in
    */
   if ( OpenDictionary( DEFAULT_DICTIONARY, &data.dict ) )
   {
      fprintf(stderr, "Error:  opening %s as dictionary\n", DEFAULT_DICTIONARY);
      exit(1);
   }
   else
   {
      ReadDictionary( &data.dict );
   }


   /*  get sentence input
    */
   if (argc EQ 1)
   {
#ifdef DEBUG
      DisplayDictionary( &data.dict );
#endif

      if ( GetSentence( &data.current_sent ) )
      {
         fprintf(stderr, "Error:  getting sentence\n" );
         exit(1);
      }
   }
   else
   {
      fprintf(stderr, "Error:  command line input not supported yet\n" );
      exit(1);
   }


   /*  parse the sentence
    */
   ParseSentence( &data.dict, &data.current_sent );

#ifdef DEBUG
   DisplaySentence( &data.current_sent );
#endif


   /*  display the sentence diagram
    */
   DiagramSentence( &data.current_sent );

   exit(0);
}



/*  ParseString	- general purpose string parser
 *
 *  Parameters:
 *	string	- pointer to string to be parsed
 *	args	- pointer to parsed array of strings
 *
 *  Returns:
 *	count	- count of substrings in array
 */
int 
ParseString(char *string, char *args[])
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */


/* end of lang.c */
