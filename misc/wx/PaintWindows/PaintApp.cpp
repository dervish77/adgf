/***************************************************************
 * Name:      PaintApp.cpp
 * Purpose:   Code for Application Class
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

#include "PaintApp.h"
#include "PaintMain.h"

IMPLEMENT_APP(PaintApp);

bool PaintApp::OnInit()
{
    PaintFrame* frame = new PaintFrame(0L, _("wxWidgets Application Template"));

#if defined(__WXMSW__)
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
#endif

    frame->Show();

    return true;
}
