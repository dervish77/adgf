//---------------------------------------------------------------------------
//
// Name:        WxTestApp.cpp
// Author:      bl12960
// Created:     2/8/2009 1:50:10 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "WxTestApp.h"
#include "WxTestFrm.h"

IMPLEMENT_APP(WxTestFrmApp)

bool WxTestFrmApp::OnInit()
{
    WxTestFrm* frame = new WxTestFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int WxTestFrmApp::OnExit()
{
	return 0;
}
