/***************************************************************
 * Name:      NotepadApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Brian Lingard ()
 * Created:   2012-05-25
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "NotepadApp.h"
#include "NotepadMain.h"

IMPLEMENT_APP(NotepadApp);

bool NotepadApp::OnInit()
{
    NotepadFrame* frame = new NotepadFrame(0L, _("NotepadApp"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
