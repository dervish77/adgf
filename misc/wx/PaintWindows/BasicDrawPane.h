/***************************************************************
 * Name:      BasicDrawPane.h
 * Purpose:   Defines BasicDrawPane Class
 * Author:    Brian Lingard ()
 * Created:   2012-05-29
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifndef BASICDRAWPANE_H_INCLUDED
#define BASICDRAWPANE_H_INCLUDED

#include "wx/wx.h"
#include "wx/sizer.h"

enum DrawMode {
    DrawModeLine = 1,
    DrawModeBox,
    DrawModeCircle
};

class BasicDrawPane : public wxPanel
{

public:
    BasicDrawPane(wxFrame* parent);

    void OnPaintEvent(wxPaintEvent & evt);
    void OnPaintNow();

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    void SetDrawMode(DrawMode mode);
    DrawMode GetDrawMode();

    void Clear();

private:

    void render(wxDC& dc);

    void erase(wxDC& dc);

    DrawMode currentDrawingMode;

    DECLARE_EVENT_TABLE()
};

#endif // BASICDRAWPANE_H_INCLUDED
