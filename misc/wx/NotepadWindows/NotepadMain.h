/***************************************************************
 * Name:      NotepadMain.h
 * Purpose:   Defines Application Frame
 * Author:    Brian Lingard ()
 * Created:   2012-05-25
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifndef NOTEPADMAIN_H
#define NOTEPADMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/printdlg.h>
#endif

#include "NotepadApp.h"

class NotepadFrame: public wxFrame
{
    public:
        NotepadFrame(wxFrame *frame, const wxString& title);
        ~NotepadFrame();

    private:

        wxMenuBar *menuBar; // the menu bar

	    wxMenu *fileMenu; // the file menu (keep this simple
	    wxMenu *editMenu; // the file menu (keep this simple
	    wxMenu *helpMenu; // the file menu (keep this simple

        wxTextCtrl *textArea; // the main text area

        enum
        {
            idMenuFileNew = 1001,
            idMenuFileOpen,
            idMenuFileSave,
            idMenuFileClose,
            idMenuFilePageSetup,
            idMenuFilePrint,
            idMenuFileQuit,

            idMenuEditUndo = 2001,
            idMenuEditRedo,
            idMenuEditCut,
            idMenuEditCopy,
            idMenuEditPaste,
            idMenuEditSelectAll,

            idMenuHelpHelp = 5001,
            idMenuHelpAbout
        };

        void OnClose(wxCloseEvent& event);

        void OnFileNew(wxCommandEvent& event);
        void OnFileOpen(wxCommandEvent& event);
        void OnFileSave(wxCommandEvent& event);
        void OnFileClose(wxCommandEvent& event);
        void OnFilePageSetup(wxCommandEvent& event);
        void OnFilePrint(wxCommandEvent& event);
        void OnFileQuit(wxCommandEvent& event);

        void OnEditUndo(wxCommandEvent& event);
        void OnEditRedo(wxCommandEvent& event);
        void OnEditCut(wxCommandEvent& event);
        void OnEditCopy(wxCommandEvent& event);
        void OnEditPaste(wxCommandEvent& event);
        void OnEditSelectAll(wxCommandEvent& event);

        void OnHelpHelp(wxCommandEvent& event);
        void OnHelpAbout(wxCommandEvent& event);

        DECLARE_EVENT_TABLE()
};


#endif // NOTEPADMAIN_H
