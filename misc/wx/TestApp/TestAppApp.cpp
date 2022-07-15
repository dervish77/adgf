/***************************************************************
 * Name:      TestAppApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Brian Lingard ()
 * Created:   2012-05-23
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestAppApp.h"
#include "TestAppMain.h"

IMPLEMENT_APP(TestAppApp);

bool TestAppApp::OnInit()
{
    TestAppFrame* frame = new TestAppFrame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
