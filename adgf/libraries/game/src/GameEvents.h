// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _GAMEEVENTS_H
#define _GAMEEVENTS_H


#include "GameGraphics.h"

class GameEvent {
  public:
    GameEvent();

    ~GameEvent();

    int GetEventType();


  private:
    int eventType;

    GameKey key;

    GameMouse mouse;

};
class GameKey {
  public:
    int code;

    int state;

};
class GameMouse {
  private:
    GameButtonState leftButtonState;

    GameButtonState middleButtonState;

    GameButtonState rightButtonState;

    GamePoint position;

};
class GameTimer {
};
enum GameButtonState {
  BUTTON_DOWN,
  BUTTON_UP

};
#endif
