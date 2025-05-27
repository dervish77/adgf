/*****************************************************************************
 *
 *	Test program parsing and diagramming sentences.
 *
 *	File:	lang.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	11/02/95
 *
 *	Revs:
 *	  0.0 	11/02/95  originated
 *
 *****************************************************************************/

#ifndef _LANG_H
#define _LANG_H


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||

typedef int 		BOOLEAN_T;
typedef unsigned char 	UBYTE_T;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


#define DEFAULT_DICTIONARY	"def_dict"

/*  define word type strings
 */
#define WT_DETERMINER_STR	'D'
#define WT_NOUN_STR		'N'
#define WT_VERB_STR		'V'
#define WT_PRONOUN_STR		'U'

#define WT_PREPOSITION_STR	'P'
#define WT_ADJECTIVE_STR	'A'
#define WT_ADVERB_STR		'R'


/*  define enumerated type for word types
 */
typedef enum {
	UNKN_WT,
	DETERMINER_WT,
	NOUN_WT,
	VERB_WT,
	PRONOUN_WT,
	PREPOSITION_WT,
	ADJECTIVE_WT,
	ADVERB_WT
} WORD_TYPE_T;


/*  define word array type
 */
#define MAX_WORD_LENGTH		20
typedef char WORD_A_T[MAX_WORD_LENGTH];


/*  define dictionary entry record
 */
typedef struct dictionary_rec_t {
   WORD_TYPE_T	type;			/* type of this word */
   char		str;			/* type string */
   int		length;			/* length of this word in bytes */
   WORD_A_T	word;			/* ascii string of word */
} DICTIONARY_REC_T;

#define MAX_WORDS_IN_DICT	100


/*  define file name type
 */
#define FILE_NAME_LEN	30
typedef char FILENAME_T[FILE_NAME_LEN];


/*  define dictionary structure
 */
typedef struct dictionary_s_t {
   FILENAME_T		file_name;
   FILE			*fp;
   int			num_words;	/* number of words in dictionary */
   DICTIONARY_REC_T	list[MAX_WORDS_IN_DICT]; /* list of entry records */
} DICTIONARY_S_T;


/*  define phrase type
 */
typedef enum {
	UNKN_PT,
	NP_PT,		/* noun phrase */
	VP_PT,		/* verb phrase */
	PP_PT		/* prepositional phrase */
} PHRASE_T;
   


/*  define sentence string type
 */
#define SENTENCE_LEN	80
typedef char SENTENCE_A_T[SENTENCE_LEN];

#define MAX_WORDS_IN_SENT	20


/*  define sentence structure
 */
typedef struct sentence_s_t {
   int			num_words;
   SENTENCE_A_T		sentence;
   DICTIONARY_REC_T	list[MAX_WORDS_IN_SENT];
   SENTENCE_A_T		np;		/* noun phrase */
   SENTENCE_A_T		vp;		/* verb phrase */
   SENTENCE_A_T		pp;		/* preposition phrase */
} SENTENCE_S_T;


/*  define main database structure 
 */
typedef struct database_s_t {
   DICTIONARY_S_T	dict;		/* dictionary data */
   SENTENCE_S_T		current_sent;	/* current sentence */
} DATABASE_S_T;




/*  declare prototypes for all functions
 */
extern BOOLEAN_T OpenDictionary( char *filename, DICTIONARY_S_T *dictionary );
extern BOOLEAN_T ReadDictionary( DICTIONARY_S_T *dictionary );
extern BOOLEAN_T DisplayDictionary( DICTIONARY_S_T *dictionary );
extern BOOLEAN_T SearchDictionary( char *word, DICTIONARY_S_T *dictionary, int *index);

extern BOOLEAN_T GetSentence( SENTENCE_S_T *sentence );
extern BOOLEAN_T ParseSentence( DICTIONARY_S_T *dictionary, SENTENCE_S_T *sentence );
extern BOOLEAN_T DisplaySentence( SENTENCE_S_T *sentence );
extern BOOLEAN_T DiagramSentence( SENTENCE_S_T *sentence );

extern int ParseString(char *string, char *args[]);

#endif 	/* _LANG_H */
