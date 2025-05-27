// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _GAMECORE_H
#define _GAMECORE_H


#include "GameGraphics.h"

class GameColor;

class GameCore {
  public:
    GameCore();

    ~GameCore();

    char* GetVersion();

    void SetCaption(char * caption);

    int Open(int width, int height, int bpp);

    int Close();

    GameSurface*   [libgame] GetDisplaySurface();

     ClearDisplay(const GameColor & color);

    void BlitToDisplay(const GameSurface & source);

    void SwapDisplay();


  private:
    GameSurface displaySurface;

};
#endif
