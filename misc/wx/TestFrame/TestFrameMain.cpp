/***************************************************************
 * Name:      TestFrameMain.cpp
 * Purpose:   Code for Application Frame
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

#include "TestFrameMain.h"

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

BEGIN_EVENT_TABLE(TestFrameFrame, wxFrame)
    EVT_CLOSE(TestFrameFrame::OnClose)

    EVT_MENU(idMenuFileNew,  TestFrameFrame::OnFileNew)
    EVT_MENU(idMenuFileOpen, TestFrameFrame::OnFileOpen)
    EVT_MENU(idMenuFileSave, TestFrameFrame::OnFileSave)
    EVT_MENU(idMenuFileClose, TestFrameFrame::OnFileClose)
    EVT_MENU(idMenuFileQuit, TestFrameFrame::OnFileQuit)

    EVT_MENU(idMenuHelpHelp, TestFrameFrame::OnHelpHelp)
    EVT_MENU(idMenuHelpAbout, TestFrameFrame::OnHelpAbout)
END_EVENT_TABLE()

TestFrameFrame::TestFrameFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuFileNew, _("&New\tCtl-N"), _("New file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(idMenuFileOpen, _("&Open\tCtl-O"), _("Open file"));
    fileMenu->Append(idMenuFileSave, _("&Save\tCtl-S"), _("Save file"));
    fileMenu->Append(idMenuFileClose, _("&Close\tCtl-W"), _("Close file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(idMenuFileQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuHelpHelp, _("&Help\tF1"), _("Show help for this application"));
    helpMenu->Append(idMenuHelpAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello app user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR

}

TestFrameFrame::~TestFrameFrame()
{
}

// System callbacks
//
void TestFrameFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

// File Menu callbacks
//
void TestFrameFrame::OnFileNew(wxCommandEvent &event)
{
    Destroy();
}

void TestFrameFrame::OnFileOpen(wxCommandEvent &event)
{
    Destroy();
}

void TestFrameFrame::OnFileSave(wxCommandEvent &event)
{
    Destroy();
}

void TestFrameFrame::OnFileClose(wxCommandEvent &event)
{
    Destroy();
}

void TestFrameFrame::OnFileQuit(wxCommandEvent &event)
{
    Destroy();
}

// Help Menu callbacks
//
void TestFrameFrame::OnHelpHelp(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Help ..."));
}

void TestFrameFrame::OnHelpAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
