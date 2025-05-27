//---------------------------------------------------------------------------
//
// Name:        WxTestApp.h
// Author:      bl12960
// Created:     2/8/2009 1:50:10 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __WXTESTFRMApp_h__
#define __WXTESTFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class WxTestFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
