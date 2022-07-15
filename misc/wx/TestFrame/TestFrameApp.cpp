/***************************************************************
 * Name:      TestFrameApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Brian Lingard ()
 * Created:   2012-05-21
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestFrameApp.h"
#include "TestFrameMain.h"

IMPLEMENT_APP(TestFrameApp);

bool TestFrameApp::OnInit()
{
    TestFrameFrame* frame = new TestFrameFrame(0L, _("Brian's Application"));

    frame->Show();

    return true;
}
