/***************************************************************
 * Name:      BasicDrawPane.cpp
 * Purpose:   Code for BasicDrawPane Class
 * Author:    Brian Lingard ()
 * Created:   2012-05-29
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "BasicDrawPane.h"

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BasicDrawPane::OnPaintEvent)

END_EVENT_TABLE()


// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 */

BasicDrawPane::BasicDrawPane(wxFrame* parent) : wxPanel(parent)
{
    currentDrawingMode = DrawModeLine;
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BasicDrawPane::OnPaintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);

    PrepareDC(dc);

    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::OnPaintNow()
{
    wxClientDC dc(this);

    PrepareDC(dc);

    render(dc);
}


void BasicDrawPane::SetDrawMode(DrawMode mode)
{
    currentDrawingMode = mode;
}

DrawMode BasicDrawPane::GetDrawMode()
{
    return currentDrawingMode;
}

void BasicDrawPane::Clear()
{
    wxPaintDC dc(this);

    erase(dc);
}


/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC&  dc)
{
    erase(dc);

    dc.SetBackgroundMode( wxTRANSPARENT );
    dc.SetBackground( wxColor(255,255,255) );

    // draw some text
    dc.DrawText(wxT("Testing"), 40, 80);

    switch( currentDrawingMode )
    {
        case DrawModeLine:
            // draw a line
            dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
            dc.DrawLine( 300, 100, 700, 500 ); // draw line across the rectangle
            break;

        case DrawModeBox:
            // draw a rectangle
            dc.SetBrush(*wxBLUE_BRUSH); // blue filling
            dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
            dc.DrawRectangle( 300, 100, 400, 400 );
            break;

        case DrawModeCircle:
            // draw a circle
            dc.SetBrush(*wxGREEN_BRUSH); // green filling
            dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
            dc.DrawCircle( wxPoint(150,200), 50 /* radius */ );
            dc.DrawCircle( wxPoint(150,400), 50 /* radius */ );
            break;

        default:
            break;
    }

    // Look at the wxDC docs to learn how to draw other stuff
}

/*
 * Erase the drawing canvas
 *
 */
void BasicDrawPane::erase(wxDC&  dc)
{
    wxColour backgroundColour = GetBackgroundColour();
    if (!backgroundColour.Ok())
    {
        backgroundColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
    }

    dc.SetBrush(wxBrush(backgroundColour));
    dc.SetPen(wxPen(backgroundColour, 1));

    wxRect windowRect(wxPoint(0, 0), GetClientSize());

    // We need to shift the client rectangle to take into account
    // scrolling, converting device to logical coordinates
//    CalcUnscrolledPosition(windowRect.x, windowRect.y, & windowRect.x, & windowRect.y);

//    dc.DrawRectangle(windowRect);
}

