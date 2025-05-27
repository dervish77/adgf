#ifndef TYPES_H
#define TYPES_H

#ifndef _ASMLANGUAGE
/************************************************************************/
/* GLOBAL DATA TYPES                                                    */
/************************************************************************/

typedef char           int8_t;   /* standard scalar types */
typedef unsigned char  uint8_t;  /* standard scalar types */
typedef short int      int16_t;  /* standard scalar types */
typedef unsigned short uint16_t; /* standard scalar types */
typedef long int       int32_t;  /* standard scalar types */
typedef unsigned long  uint32_t; /* standard scalar types */
typedef long long      int64_t;       /* unique to 64bit processors */
typedef unsigned long long uint64_t;  /* unique to 64bit processors */
typedef uint32_t       bool_t;   /* standard scalar types */

typedef bool_t   (*PFB)();	 /* pointer to BOOL function */
typedef void     (*PFV)();	 /* pointer to void function */
typedef int      (*PFI)();	 /* pointer to function returning an int */

typedef uint32_t (*PFU_INT32)();
typedef uint16_t (*PFU_INT16)();
typedef uint8_t  (*PFU_INT8)();
typedef uint32_t (*pfu_int32)();
typedef uint16_t (*pfu_int16)();
typedef uint8_t  (*pfu_int8)();
typedef void     (*pfv)();
typedef int32_t  (*pfi)();

typedef struct _DBL_LWORD {
  uint32_t hi;   /* [63:32] */
  uint32_t lo;   /* [31:0] */
}DBL_LWORD;

#endif /* _ASMLANGUAGE */

#ifndef TRUE
#define TRUE           1             /* explicit boolean true         */
#define FALSE          0             /* explicit boolean false        */
#endif

#ifndef NULL
#define NULL           0             /* -- to be replaced with FINGER */
#endif

#define LONG_MAX       0xffffffff
#define PASSED         0
#define FAILED         1

#endif /* TYPES_H */






