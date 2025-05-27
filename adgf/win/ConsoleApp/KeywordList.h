// keyword.h
//

#ifndef __KEYWORD_H
#define __KEYWORD_H


// define keyword type enum
enum KWTYPE {
	 TY_NULL=0,
     TY_TBD
};

// define keyword id enum
enum KWID {
     T_NULL=0, 
     T_QUIT,
     T_CHSRC,
     T_PLAY,
     T_TUNE,
     T_SCAN,
     T_SEEK
};

#define NUM_KEYWORD_ID 7

#define KEYWORD_LENGTH 20


// define keyword class
class Keyword
{
public:
                    Keyword   (KWTYPE kwtype, KWID kwid, char *kw);
    
    KWTYPE          type;
    KWID            id;
    char            keyword[KEYWORD_LENGTH];

private:

}; 

#endif // __KEYWORD_H
