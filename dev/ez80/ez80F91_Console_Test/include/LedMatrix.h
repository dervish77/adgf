/*
 *****************************************************************************
 * LedMatrix.h
 *
 *****************************************************************************
 */

/* LED anode and cathode external I/O pointers */
#define LEDMATRIX_ROW      (*(unsigned char*)0x800000)  //Anode
#define LEDMATRIX_COLUMN   (*(unsigned char*)0x800001)  //Cathode

/* emulated GPIO port */
#define EMUL_GPIO       (*(volatile unsigned char*)0x800002)

extern unsigned char *pcolumn;
extern unsigned char *p_user_input;
extern char user_input;

extern unsigned char matrix_char_map[128][7];

/* eZ80 development board led matrix functions */
extern void ledmatrix_init( void );
extern void ledmatrix_clear( void );
extern void ledmatrix_fill( void );
extern void ledmatrix_putc( char c );
extern void ledmatrix_puts( char *str );
extern void ledmatrix_test( void );
extern void ledmatrix_flash( void );
extern void ledmatrix_spin( void );

