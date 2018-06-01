/*****************************************************************************
 *
 *	ButtonSim module interface.
 *
 *  Description: Simulation of physical buttons using LibSDL for drawing.
 *
 *	File:	buttonsim.h
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#ifndef __buttonssim_h
#define __buttonssim_h


//////////////////////////////////////////////////////////////////////////////
// defines
//////////////////////////////////////////////////////////////////////////////


#define BUTTON_COUNT_1		1
#define BUTTON_COUNT_2		2
#define BUTTON_COUNT_3		3
#define BUTTON_COUNT_4		4
#define BUTTON_COUNT_5		5
#define BUTTON_COUNT_6		6
#define BUTTON_COUNT_7		7

#define BUTTON_COUNT_MIN	BUTTON_COUNT_2
#define BUTTON_COUNT_MAX	BUTTON_COUNT_6

#define BUTTON_COUNT_DEFAULT	BUTTON_COUNT_4


#define BUTTON_IMAGE_PRESSED	"../images/btn_pressed.bmp"
#define BUTTON_IMAGE_RELEASED	"../images/btn_released.bmp"


#define BUTTON_W_SIZE		100
#define BUTTON_H_SIZE		100

#define BUTTON_SPACING		10


//////////////////////////////////////////////////////////////////////////////
// structures
//////////////////////////////////////////////////////////////////////////////

typedef struct _button_s
{
    int buttonId;
    int buttonWidth;
    int buttonHeight;
    int pressedState;
    char buttonLabel[16];
    char imagePressed[64];
    char imageReleased[64];
} ButtonStruct;


//////////////////////////////////////////////////////////////////////////////
// prototypes
//////////////////////////////////////////////////////////////////////////////


int  ButtonSim_Init( int numButtons );

void ButtonSim_Execute( void );


#endif /* __buttonssim_h */

