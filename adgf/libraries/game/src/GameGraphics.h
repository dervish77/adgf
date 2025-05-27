// ======================================================================
// File: ${artifact}
//
// ======================================================================

#ifndef _GAMEGRAPHICS_H
#define _GAMEGRAPHICS_H


class GameSurface {
  public:
    GameSurface();

    ~GameSurface();

    GameExtent GetExtent();

    GamePoint GetTopLeft();

    void SetAlpha(int alpha);

    int GetAlpha();

     SetColorKey(const GameColor & key);

    GameColor GetColorKey();

    void EnableColorKey(bool enable);


  private:
    SDL_Surface* surface;

    GameExtent extent;

    GamePoint topleft;

    int alpha;

    GameColor colorKey;

};
class GameColor {
  public:
    char red;

    char green;

    char blue;

    char alpha;

};
class GameExtent {
  public:
    int width;

    int height;

};
class GamePoint {
  public:
    int x;

    int y;

};
class GameRect {
  public:
    GameExtent extent;

    GamePoint topleft;

};
#endif
