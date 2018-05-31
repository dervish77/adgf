/***************************************************************
 * Name:      NotepadMain.cpp
 * Purpose:   Code for Application Frame
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

#include "NotepadMain.h"

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

BEGIN_EVENT_TABLE(NotepadFrame, wxFrame)
    EVT_CLOSE(NotepadFrame::OnClose)

    EVT_MENU(idMenuFileNew,   NotepadFrame::OnFileNew)
    EVT_MENU(idMenuFileOpen,  NotepadFrame::OnFileOpen)
    EVT_MENU(idMenuFileSave,  NotepadFrame::OnFileSave)
    EVT_MENU(idMenuFileClose, NotepadFrame::OnFileClose)
    EVT_MENU(idMenuFilePageSetup, NotepadFrame::OnFilePageSetup)
    EVT_MENU(idMenuFilePrint, NotepadFrame::OnFilePrint)
    EVT_MENU(idMenuFileQuit,  NotepadFrame::OnFileQuit)

    EVT_MENU(idMenuEditUndo,  NotepadFrame::OnEditUndo)
    EVT_MENU(idMenuEditRedo,  NotepadFrame::OnEditRedo)
    EVT_MENU(idMenuEditCut,   NotepadFrame::OnEditCut)
    EVT_MENU(idMenuEditCopy,  NotepadFrame::OnEditCopy)
    EVT_MENU(idMenuEditPaste, NotepadFrame::OnEditPaste)
    EVT_MENU(idMenuEditSelectAll, NotepadFrame::OnEditSelectAll)

    EVT_MENU(idMenuHelpHelp,  NotepadFrame::OnHelpHelp)
    EVT_MENU(idMenuHelpAbout, NotepadFrame::OnHelpAbout)
END_EVENT_TABLE()

NotepadFrame::NotepadFrame(wxFrame *frame, const wxString& title)
    : wxFrame(NULL, wxID_ANY, wxT("NotepadApp"), wxPoint(10,10), wxSize(800,600))
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
    fileMenu->Append(idMenuFilePageSetup, _("&Page Setup...\tCtrl-P"), _("Setup page"));
    fileMenu->Append(idMenuFilePrint,     _("&Print...\tCtrl-P"),      _("Print file"));
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

    helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuHelpHelp,  _("&Help\tF1"),             _("Show help for this application"));
    helpMenu->Append(idMenuHelpAbout, _("&About NotepadApp\tF8"), _("Show info about this application"));
    menuBar->Append(helpMenu, _("&Help"));

    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello NotepadApp user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR

    // create text area widget
    textArea = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
                              wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE);

}

NotepadFrame::~NotepadFrame()
{
}

// System callbacks
//
void NotepadFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

// File Menu callbacks
//
void NotepadFrame::OnFileNew(wxCommandEvent &event)
{
    textArea->Clear();

    SetStatusText(_("Start typing"),0);
}

void NotepadFrame::OnFileOpen(wxCommandEvent &event)
{
    wxFileDialog *openDialog = new wxFileDialog(this, wxT("Open File~"), wxT(""), wxT(""),
	                                                wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxOPEN);

    int response = openDialog->ShowModal();

    if (response == wxID_OK)
    {
        textArea->LoadFile(openDialog->GetPath());
        SetStatusText(_("Opened"),0);
    }
}

void NotepadFrame::OnFileSave(wxCommandEvent &event)
{
    wxFileDialog *saveDialog = new wxFileDialog(this, wxT("Save File~"), wxT(""), wxT(""),
	                                            wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxSAVE);

    int response = saveDialog->ShowModal();

    if (response == wxID_OK)
    {
        textArea->SaveFile(saveDialog->GetPath());
        SetStatusText(_("Saved"),0);
    }
}

void NotepadFrame::OnFilePageSetup(wxCommandEvent &event)
{
    wxPageSetupDialog *setupDialog = new wxPageSetupDialog(this);

    int response = setupDialog->ShowModal();

    if (response == wxID_OK)
    {

    }
}

void NotepadFrame::OnFilePrint(wxCommandEvent &event)
{
    wxPrintDialog *printDialog = new wxPrintDialog(this);

    int response = printDialog->ShowModal();

    if (response == wxID_OK)
    {
        wxDC* printDC = printDialog->GetPrintDC();

        printDC->StartPage();

        // send data to printer one line at a time
        for (int ii = 0; ii < textArea->GetNumberOfLines(); ii++)
        {
            wxCoord w;
            wxCoord h;

            wxString textLine = textArea->GetLineText(ii);

            printDC->GetTextExtent(textLine, &w, &h);

        //    printf("printing - %d - %s\n", ii, textLine);

            printDC->DrawText(textLine, 0, h * ii);
        }

        printDC->EndPage();
        printDC->EndDoc();

        SetStatusText(_("Printed"),0);
    }
}

void NotepadFrame::OnFileClose(wxCommandEvent &event)
{
    if (textArea->IsModified())
    {
        this->OnFileSave(event);
    }

    textArea->Clear();

    SetStatusText(_("Closed"),0);
}

void NotepadFrame::OnFileQuit(wxCommandEvent &event)
{
    if (textArea->IsModified())
    {
        this->OnFileSave(event);
    }

    textArea->Clear();

    Destroy();
}

// Edit Menu callbacks
//
void NotepadFrame::OnEditUndo(wxCommandEvent &event)
{
    textArea->Undo();

    SetStatusText(_("Undone"),0);
}

void NotepadFrame::OnEditRedo(wxCommandEvent &event)
{
    textArea->Redo();

    SetStatusText(_("Redone"),0);
}

void NotepadFrame::OnEditCut(wxCommandEvent &event)
{
    textArea->Cut();

    SetStatusText(_("Deleted"),0);
}

void NotepadFrame::OnEditCopy(wxCommandEvent &event)
{
    textArea->Copy();

    SetStatusText(_("Copied"),0);
}

void NotepadFrame::OnEditPaste(wxCommandEvent &event)
{
    textArea->Paste();

    SetStatusText(_("Pasted"),0);
}

void NotepadFrame::OnEditSelectAll(wxCommandEvent &event)
{
    textArea->SetSelection(-1,-1);

    SetStatusText(_("Selected"),0);
}

// Help Menu callbacks
//
void NotepadFrame::OnHelpHelp(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Help ..."));
}

void NotepadFrame::OnHelpAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("About ..."));
}

// END
