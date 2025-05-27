//---------------------------------------------------------------------------
//
// Name:        WxTestFrm.cpp
// Author:      bl12960
// Created:     2/8/2009 1:50:10 PM
// Description: WxTestFrm class implementation
//
//---------------------------------------------------------------------------

#include "WxTestFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// WxTestFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(WxTestFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(WxTestFrm::OnClose)
END_EVENT_TABLE()
////Event Table End

WxTestFrm::WxTestFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

WxTestFrm::~WxTestFrm()
{
}

void WxTestFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxStatusBar1 = new wxStatusBar(this, ID_WXSTATUSBAR1);

	WxMenuBar1 = new wxMenuBar();
	wxMenu *wxID_FILE1_Mnu_Obj = new wxMenu(0);
	wxID_FILE1_Mnu_Obj->Append(wxID_NEW, wxT("New..."), wxT(""), wxITEM_NORMAL);
	wxID_FILE1_Mnu_Obj->AppendSeparator();
	wxID_FILE1_Mnu_Obj->Append(wxID_OPEN, wxT("Open..."), wxT(""), wxITEM_NORMAL);
	wxID_FILE1_Mnu_Obj->AppendSeparator();
	wxID_FILE1_Mnu_Obj->Append(wxID_SAVE, wxT("Save"), wxT(""), wxITEM_NORMAL);
	wxID_FILE1_Mnu_Obj->Append(wxID_SAVEAS, wxT("Save As..."), wxT(""), wxITEM_NORMAL);
	wxID_FILE1_Mnu_Obj->AppendSeparator();
	wxID_FILE1_Mnu_Obj->Append(wxID_CLOSE, wxT("Close"), wxT(""), wxITEM_NORMAL);
	wxID_FILE1_Mnu_Obj->AppendSeparator();
	wxID_FILE1_Mnu_Obj->Append(wxID_EXIT, wxT("Exit"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(wxID_FILE1_Mnu_Obj, wxT("File"));
	
	wxMenu *ID_MNU_EDIT_1005_Mnu_Obj = new wxMenu(0);
	ID_MNU_EDIT_1005_Mnu_Obj->Append(wxID_UNDO, wxT("Undo"), wxT(""), wxITEM_NORMAL);
	ID_MNU_EDIT_1005_Mnu_Obj->Append(wxID_CUT, wxT("Cut"), wxT(""), wxITEM_NORMAL);
	ID_MNU_EDIT_1005_Mnu_Obj->Append(wxID_COPY, wxT("Copy"), wxT(""), wxITEM_NORMAL);
	ID_MNU_EDIT_1005_Mnu_Obj->Append(wxID_PASTE, wxT("Paste"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_EDIT_1005_Mnu_Obj, wxT("Edit"));
	
	wxMenu *wxID_HELP_Mnu_Obj = new wxMenu(0);
	wxID_HELP_Mnu_Obj->Append(wxID_HELP, wxT("Help..."), wxT(""), wxITEM_NORMAL);
	wxID_HELP_Mnu_Obj->Append(wxID_ABOUT, wxT("About"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(wxID_HELP_Mnu_Obj, wxT("Help"));
	SetMenuBar(WxMenuBar1);

	SetStatusBar(WxStatusBar1);
	SetTitle(wxT("WxTest"));
	SetIcon(wxNullIcon);
	SetSize(8,8,680,387);
	Center();
	
	////GUI Items Creation End
}

void WxTestFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}
