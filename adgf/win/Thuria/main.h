/*****************************************************************************
 *
 *	Main header file for Dungeons of Thuria.
 *
 *	File:	main.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	12/04/96
 *
 *	Revs:
 *	  0.0 	12/04/96  originated
 *
 *****************************************************************************/

#include <stdio.h>

#ifndef MAIN_H
#define MAIN_H


#ifndef ROOM_H
#include "room.h"
#endif


#ifndef OBJECT_H
#include "object.h"
#endif


#ifndef SPECIAL_H
#include "special.h"
#endif


#ifndef MAGIC_H
#include "magic.h"
#endif


#ifndef RANK_H
#include "rank.h"
#endif


#ifndef VERB_H
#include "verb.h"
#endif


#define DUNGEON_DEBUG


/*  define version
 */
#define VERSION		"1.1"
#define VERSIONDATE	"11/06/1998"


/*  define some constants
 */
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define SHORT_BUFF_LEN	40
#define LONG_BUFF_LEN	120

#define MAX_INV_OBJS	10

#define MAX_CHEST_OBJS	25

#define MAX_CMD_ARGS	12

#define MIN_SCORE	0
#define MAX_SCORE	700

#define MAX_HEALTH	100
#define DAMAGE_FALL	25
#define DAMAGE_BEAVER	10
#define DAMAGE_SKEL	20
#define DAMAGE_STATUE	100

#define MAX_OIL		300
#define CAN_OIL		150
#define LOW_OIL		10

#define PROMPT		"> "

#define ATRG		5

#define RANK_0_MAX	140
#define RANK_1_MAX	280
#define RANK_2_MAX	420
#define RANK_3_MAX	560
#define RANK_4_MAX	(MAX_SCORE - 70)
#define RANK_5_MAX	MAX_SCORE


/*  define some useful types
 */
typedef unsigned char BOOLEAN_T;

typedef char SHORT_BUFFER_T[SHORT_BUFF_LEN];
typedef char LONG_BUFFER_T[LONG_BUFF_LEN];

typedef short int 	INDEX_T;



/*  define map structure
 */
typedef struct map_s_t {
   INDEX_T        roomnum;  /* room number index */
   LONG_BUFFER_T	roomname; /* room name string */
   BOOLEAN_T      beenhere;	/* i've been here flag */
   BOOLEAN_T      inside;   /* inside flag */
   INDEX_T        n;		/* index for north */
   INDEX_T        s;		/* index for south */
   INDEX_T        e;		/* index for east */
   INDEX_T        w;		/* index for west */
   INDEX_T        d;		/* index for down */
   INDEX_T        u;		/* index for up */
   INDEX_T        special;	/* special effect index */
   INDEX_T        object;		/* object index */
} MAP_S_T;


/*  define object structure
 */
typedef struct object_s_t {
   INDEX_T        objnum;   /* object id number */
   INDEX_T        score;    /* score value */
   SHORT_BUFFER_T	key;      /* search key word */
   SHORT_BUFFER_T	prep;     /* prep phrase */
   SHORT_BUFFER_T	name;     /* object name string */
   LONG_BUFFER_T  examine;  /* examine phrase */
} OBJECT_S_T;


/*  define special structure
 */
typedef struct special_s_t {
   INDEX_T        spnum;		/* special id number */
   INDEX_T        score;		/* score value */
   LONG_BUFFER_T	phrase;		/* special phrase string */
} SPECIAL_S_T;


/*  define magic structure
 */
typedef struct magic_s_t {
   INDEX_T        mgnum;    /* magic id number */
   INDEX_T        score;    /* score value */
   INDEX_T        fromroom; /* from room index */
   INDEX_T        toroom;   /* to room index */
   SHORT_BUFFER_T	word;     /* magic word string */
   LONG_BUFFER_T  phrase;   /* magic phrase string */
} MAGIC_S_T;


/*  define rank structure
 */
typedef struct rank_s_t {
   INDEX_T        rnum;     /* rank id number */
   SHORT_BUFFER_T	title;    /* rank title string */
   LONG_BUFFER_T  phrase;   /* rank phrase string */
} RANK_S_T;


/*  define verb structure
 */
typedef struct verb_s_t {
   INDEX_T        vnum;		/* verb id number */
   SHORT_BUFFER_T	word;		/* verb word string */
   INDEX_T        type;		/* verb type */
} VERB_S_T;


/*  define room structure
 */
typedef struct room_s_t {
   INDEX_T        roomnum;	/* room number index */
   INDEX_T        linenum;	/* line number of text */
   LONG_BUFFER_T	roomline;	/* text string */
} ROOM_S_T;


/*  define intro structure
 */
typedef struct intro_s_t {
   INDEX_T        linenum;    /* line number of text */
   LONG_BUFFER_T  introline;	/* text string */
} INTRO_S_T;


/*  define inventory structure
 */
typedef struct inv_s_t {
   INDEX_T    count;              /* count of objects */
   INDEX_T    list[MAX_INV_OBJS];	/* list of object indexes */
} INV_S_T;


/*  define treasure chest structure
 */
typedef struct chest_s_t {
   INDEX_T		count;                /* count of objects */
   INDEX_T		list[MAX_CHEST_OBJS];	/* list of object indexes */
} CHEST_S_T;


/*  define command word structure
 */
typedef struct cmd_s_t {
   int            type;		/* type of command word */
   int            length;	/* length of string */
   SHORT_BUFFER_T	cmd;		/* cmd word string */
} CMD_S_T;


/*  define main game structure
 */
typedef struct game_s_t {
   BOOLEAN_T 	 	  play_game;		/* play game flag */
   BOOLEAN_T	 	  suppress_instructions;	/* flag */
   BOOLEAN_T	 	  adult_enabled;		/* adult flag */
   int            adult_count;		/* adult count */
   BOOLEAN_T		  debug_enabled;		/* debug flag */
   BOOLEAN_T		  verbose;		/* verbose flag */
   BOOLEAN_T		  have_lamp;		/* i have the lamp flag */
   BOOLEAN_T		  lamp_is_on;		/* the lamp is on flag */
   INDEX_T        current_room;		/* current room index */
   int            score;			/* current score */
   int            health;			/* current health */
   int            moves;			/* number of moves */
   int            oil;			/* amount of oil */
   BOOLEAN_T      load_game;		/* load the game flag */
   BOOLEAN_T 		  save_game;		/* save the game flag */
   BOOLEAN_T 		  game_loaded;		/* game is loaded flag */
   BOOLEAN_T		  game_saved;		/* game is saved flag */
   SHORT_BUFFER_T	load_file_name;		/* load file name */
   SHORT_BUFFER_T	save_file_name;		/* save file name */
   FILE			      *load_file_fp;		/* load file pointer */
   FILE			      *save_file_fp;		/* save file pointer */
   INV_S_T		    inventory;		/* inventory list */
   CHEST_S_T		  chest;			/* treasure chest list */
   LONG_BUFFER_T	cmdstring;		/* whole command string */
   int			      argcount;		/* word count of cmd string */
   CMD_S_T		    list[MAX_CMD_ARGS];	/* list of cmd words */
} GAME_S_T;


/*
 *  GLOBAL EXTERNS
 */
extern ROOM_S_T room[];
extern MAP_S_T map[];
extern OBJECT_S_T object[];
extern SPECIAL_S_T special[];
extern MAGIC_S_T magic[];
extern RANK_S_T rank[];
extern VERB_S_T verb[];

#endif

/* end of main.h */
