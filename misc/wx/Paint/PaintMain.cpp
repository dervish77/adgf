/***************************************************************
 * Name:      PaintMain.cpp
 * Purpose:   Code for Application Frame
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

#include "PaintMain.h"
#include "BasicDrawPane.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(PaintFrame, wxFrame)
    EVT_CLOSE(PaintFrame::OnClose)

    EVT_MENU(idMenuFileNew,   PaintFrame::OnFileNew)
    EVT_MENU(idMenuFileOpen,  PaintFrame::OnFileOpen)
    EVT_MENU(idMenuFileSave,  PaintFrame::OnFileSave)
    EVT_MENU(idMenuFileClose, PaintFrame::OnFileClose)
    EVT_MENU(idMenuFileQuit,  PaintFrame::OnFileQuit)

    EVT_MENU(idMenuEditUndo,  PaintFrame::OnEditUndo)
    EVT_MENU(idMenuEditRedo,  PaintFrame::OnEditRedo)
    EVT_MENU(idMenuEditCut,   PaintFrame::OnEditCut)
    EVT_MENU(idMenuEditCopy,  PaintFrame::OnEditCopy)
    EVT_MENU(idMenuEditPaste, PaintFrame::OnEditPaste)
    EVT_MENU(idMenuEditSelectAll, PaintFrame::OnEditSelectAll)

    EVT_MENU(idMenuDrawLine,   PaintFrame::OnDrawLine)
    EVT_MENU(idMenuDrawBox,    PaintFrame::OnDrawBox)
    EVT_MENU(idMenuDrawCircle, PaintFrame::OnDrawCircle)

    EVT_MENU(idMenuHelpHelp,  PaintFrame::OnHelpHelp)
    EVT_MENU(idMenuHelpAbout, PaintFrame::OnHelpAbout)
END_EVENT_TABLE()

PaintFrame::PaintFrame(wxFrame *frame, const wxString& title)
    : wxFrame(NULL, wxID_ANY, wxT("PaintApp"), wxPoint(10,10), wxSize(800,600))
{
#if wxUSE_MENUS
    // create a menu bar
    menuBar = new wxMenuBar();

    fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuFileNew,   _("&New\tCtrl-N"),      _("New file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(idMenuFileOpen,  _("&Open...\tCtrl-O"),  _("Open file"));
    fileMenu->Append(idMenuFileSave,  _("&Save...\tCtrl-S"),  _("Save file"));
    fileMenu->Append(idMenuFileClose, _("&Close\tCtrl-W"),    _("Close file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(idMenuFileQuit,  _("&Quit\tCtrl-Q"),  _("Quit the application"));
    menuBar->Append(fileMenu, _("&File"));

    editMenu = new wxMenu(_T(""));
    editMenu->Append(idMenuEditUndo,  _("&Undo\tCtrl-Z"),       _("Undo operation"));
    editMenu->Append(idMenuEditRedo,  _("&Redo\tCtrl-Shft-Z"),  _("Redo operation"));
    editMenu->AppendSeparator();
    editMenu->Append(idMenuEditCut,   _("&Cut\tCtrl-X"),   _("Cut selection"));
    editMenu->Append(idMenuEditCopy,  _("&Copy\tCtrl-C"),  _("Copy selection"));
    editMenu->Append(idMenuEditPaste, _("&Paste\tCtrl-V"), _("Paste selection"));
    editMenu->AppendSeparator();
    editMenu->Append(idMenuEditSelectAll, _("&Select All\tCtrl-A"), _("Select all"));
    menuBar->Append(editMenu, _("&Edit"));

    drawMenu = new wxMenu(_T(""));
    drawMenu->Append(idMenuDrawLine,    _("&Line\tCtrl-1"),      _("Draw a line"));
    drawMenu->Append(idMenuDrawBox,     _("&Box\tCtrl-2"),       _("Draw a box"));
    drawMenu->Append(idMenuDrawCircle,  _("&Circle\tCtrl-3"),    _("Draw a circle"));
    menuBar->Append(drawMenu, _("&Draw"));

    helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuHelpHelp,  _("&Help\tF1"),             _("Show help for this application"));
    helpMenu->Append(idMenuHelpAbout, _("&About NotepadApp\tF8"), _("Show info about this application"));
    menuBar->Append(helpMenu, _("&Help"));

    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello PaintApp user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR

    // create canvas area widget
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    drawPane = new BasicDrawPane( (wxFrame*) frame );
    sizer->Add(drawPane, 1, wxEXPAND);

    this->SetSizer(sizer);
    this->SetAutoLayout(true);

}


PaintFrame::~PaintFrame()
{
}

// System callbacks
//
void PaintFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

// File Menu callbacks
//
void PaintFrame::OnFileNew(wxCommandEvent &event)
{
    drawPane->Clear();

    SetStatusText(_("Start painting"),0);
}

void PaintFrame::OnFileOpen(wxCommandEvent &event)
{
    wxFileDialog *openDialog = new wxFileDialog(this, wxT("Open File~"), wxT(""), wxT(""),
	                                                wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxOPEN);

    int response = openDialog->ShowModal();

    if (response == wxID_OK)
    {
        SetStatusText(_("Opened"),0);
    }
}

void PaintFrame::OnFileSave(wxCommandEvent &event)
{
    wxFileDialog *saveDialog = new wxFileDialog(this, wxT("Save File~"), wxT(""), wxT(""),
	                                            wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxSAVE);

    int response = saveDialog->ShowModal();

    if (response == wxID_OK)
    {
        SetStatusText(_("Saved"),0);
    }
}

void PaintFrame::OnFileClose(wxCommandEvent &event)
{
    if (0)
    {
        this->OnFileSave(event);
    }

    drawPane->Clear();

    SetStatusText(_("Closed"),0);
}

void PaintFrame::OnFileQuit(wxCommandEvent &event)
{
    if (0)
    {
        this->OnFileSave(event);
    }

    drawPane->Clear();

    Destroy();
}

// Edit Menu callbacks
//
void PaintFrame::OnEditUndo(wxCommandEvent &event)
{

    SetStatusText(_("Undone"),0);
}

void PaintFrame::OnEditRedo(wxCommandEvent &event)
{

    SetStatusText(_("Redone"),0);
}

void PaintFrame::OnEditCut(wxCommandEvent &event)
{

    SetStatusText(_("Deleted"),0);
}

void PaintFrame::OnEditCopy(wxCommandEvent &event)
{


    SetStatusText(_("Copied"),0);
}

void PaintFrame::OnEditPaste(wxCommandEvent &event)
{


    SetStatusText(_("Pasted"),0);
}

void PaintFrame::OnEditSelectAll(wxCommandEvent &event)
{


    SetStatusText(_("Selected"),0);
}

// Draw Menu callbacks
//
void PaintFrame::OnDrawLine(wxCommandEvent &event)
{
    SetStatusText(_("Line"),0);

    drawPane->SetDrawMode( DrawModeLine );

    drawPane->OnPaintNow();
}

void PaintFrame::OnDrawBox(wxCommandEvent &event)
{
    SetStatusText(_("Box"),0);

    drawPane->SetDrawMode( DrawModeBox );

    drawPane->OnPaintNow();
}

void PaintFrame::OnDrawCircle(wxCommandEvent &event)
{
    SetStatusText(_("Circle"),0);

    drawPane->SetDrawMode( DrawModeCircle );

    drawPane->OnPaintNow();
}

// Help Menu callbacks
//
void PaintFrame::OnHelpHelp(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Help ..."));
}

void PaintFrame::OnHelpAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("About ..."));
}

// END
