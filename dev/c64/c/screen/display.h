/* display.h */

#ifndef _FIB_H
#define _FIB_H

#define ROWS 25
#define COLS 40

#define SCREEN_TOP_LEFT_LOC 0x400		// 1000 bytes, bits 0:7, uses ascii char code
#define COLOR_TOP_LEFT_LOC  0xD800		// 1000 bytes, only bits 0:3

#define COLOR_BLACK		0
#define COLOR_WHITE		1
#define COLOR_RED		2
#define COLOR_CYAN		3
#define COLOR_PURPLE	4
#define COLOR_GREEN		5
#define COLOR_BLUE		6
#define COLOR_YELLOW	7
#define COLOR_ORANGE	8
#define COLOR_BROWN		9
#define COLOR_LTRED		10
#define COLOR_DKGREY	11
#define COLOR_GREY2		12
#define COLOR_LTGRN		13
#define COLOR_LTBLUE	14
#define COLOR_LTGREY	15


int do_screen_fill( int count, int value, int color );
int do_set_loc( int row, int col, int value, int color );

#endif