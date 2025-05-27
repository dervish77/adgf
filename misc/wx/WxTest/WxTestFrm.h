//---------------------------------------------------------------------------
//
// Name:        WxTestFrm.h
// Author:      bl12960
// Created:     2/8/2009 1:50:10 PM
// Description: WxTestFrm class declaration
//
//---------------------------------------------------------------------------

#ifndef __WXTESTFRM_h__
#define __WXTESTFRM_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/statusbr.h>
////Header Include End

////Dialog Style Start
#undef WxTestFrm_STYLE
#define WxTestFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class WxTestFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		WxTestFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("WxTest"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = WxTestFrm_STYLE);
		virtual ~WxTestFrm();
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenuBar *WxMenuBar1;
		wxStatusBar *WxStatusBar1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_EDIT_1005 = 1005,
			
			ID_WXSTATUSBAR1 = 1003,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
