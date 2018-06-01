/*****************************************************************************
 *
 *	ButtonSim module implementation.
 *
 *  Description: Simulation of physical buttons using LibSDL for drawing.
 *
 *	File:	buttonsim.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw-sdl.h"
#include "draw-text.h"

#include "buttonsim.h"


#define WIDTH   WIDTH_1024
#define HEIGHT  HEIGHT_768
#define BPP     DEPTH_BPP_16


/*
 *  STATICS
 */

int numberOfButtons = 0;

int simWidth = WIDTH_1024;
int simHeight = HEIGHT_768;
int simBpp = DEPTH_BPP_16;

ButtonStruct buttonArray[BUTTON_COUNT_MAX];



/*
 *  FUNCTIONS
 */


int ButtonSim_Init( int numButtons )
{
    int retVal = 1;

    printf("ButtonSim_Init - configuring for %d buttons...\n", numButtons);

    if (numButtons < BUTTON_COUNT_MIN)
    {
        printf("ButtonSim_Init - too few buttons requested!\n");
	retVal = 0;
    }
    else if (numButtons > BUTTON_COUNT_MAX)
    {		    
        printf("ButtonSim_Init - too many buttons requested!\n");
	retVal = 0;
    }
    else
    {
	numberOfButtons = numButtons;

        for (int i = 0; i < numberOfButtons; i++)
        {
            buttonArray[i].buttonId = i + 1;
	    buttonArray[i].buttonWidth = BUTTON_W_SIZE;
	    buttonArray[i].buttonHeight = BUTTON_H_SIZE;
	    buttonArray[i].pressedState = 0;
            sprintf(buttonArray[i].buttonLabel, "Button %d", i + 1);
	    strcpy(buttonArray[i].imagePressed, BUTTON_IMAGE_PRESSED);
	    strcpy(buttonArray[i].imageReleased, BUTTON_IMAGE_RELEASED);
        }

	// width = sp + (btn_width + sp) + (btn_width + sp) + ...
        simWidth = BUTTON_SPACING + (BUTTON_W_SIZE + BUTTON_SPACING) * numberOfButtons;

	// height = sp + btn_height + sp
        simHeight = BUTTON_H_SIZE + 2 * BUTTON_SPACING;
        
	// use default BPP
	simBpp = BPP;
    }

    return retVal;
}


void ButtonSim_Execute( void )
{
    int w,  h;                      // screen width and height   
    int sw, sh;                     // sprite width and height   
    spriteContext buttonSprite;

    // initialize the drawing package
    drawInit(simWidth, simHeight, simBpp);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw button outlines
    int x_offset = BUTTON_SPACING;
    int y_offset = BUTTON_SPACING;
    for (int i = 0; i < numberOfButtons; i++)
    {
        drawRect( CLR_WHITE, x_offset, y_offset, buttonArray[i].buttonWidth, buttonArray[i].buttonHeight );
	x_offset += (buttonArray[i].buttonWidth + BUTTON_SPACING);
    }

    // draw initial buttons
    drawLoadSprite(&buttonSprite, (char *) BUTTON_IMAGE_RELEASED);
    drawGetSpriteExtent(&buttonSprite, &sw, &sh);

    int sx = BUTTON_SPACING + (BUTTON_W_SIZE / 2) - (sw / 2);
    int sy = BUTTON_SPACING + (BUTTON_H_SIZE / 2) - (sh / 2);
    for (int i = 0; i < numberOfButtons; i++)
    {
        drawSprite(&buttonSprite, sx, sy); 
	sx += (buttonArray[i].buttonWidth + BUTTON_SPACING);
    }  

    // handle button event loop


    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
    
    drawWait(2000);
}


/* end of buttonsim.cpp */
