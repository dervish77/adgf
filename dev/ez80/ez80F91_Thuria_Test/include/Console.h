/*                                                   Copyright (c) ZiLOG, 2003
 *****************************************************************************
 *  Console.h
 *
 *  Console I/O functions used by printf, scanf, etc....
 *****************************************************************************
 */

extern void console_init(int baurdrate);
extern void putch(unsigned char ch);
extern unsigned char getch(void);
extern unsigned char getche(void);
extern int kbhit(void);

extern char char_ready;
