/***********************************************************************

 Header file for 6502 instruction op codes.

   File:  	in6502.h

   Author: 	Brian Lingard

   Date:	02/02/98

   Revisions:
	0.0	02/02/98 Originated

***********************************************************************/

#ifndef _IN6502_H
#define _IN6502_H


#define LDA_ABS		0xAD
#define LDA_ZPG		0xA5
#define LDA_IMM		0xA9
#define LDA_ABX		0xBD
#define LDA_ABY		0xB9
#define LDA_INX		0xA1
#define LDA_INY		0xB1
#define LDA_ZPX		0xB5

#define LDX		0x00
#define LDY		0x00

#define TAX		0xAA
#define TAY		0xA8
#define TXA		0x8A
#define TYA		0x9A
#define TSX		0xBA
#define TXS		0x9A

#define STA		0x00
#define STX		0x00
#define STY		0x00

#define NOP		0xEA
#define INX		0xE8
#define INY		0xC8
#define DEX		0xCA
#define DEY		0x88

#define JMP		0x00
#define JSR		0x00


#endif /* _IN6502_H */
/* end of in6502.h */
