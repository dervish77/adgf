/***************************************************************
 * Name:      PaintMain.h
 * Purpose:   Defines Application Frame
 * Author:    Brian Lingard ()
 * Created:   2012-05-29
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifndef PAINTMAIN_H
#define PAINTMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PaintApp.h"
#include "BasicDrawPane.h"

class PaintFrame: public wxFrame
{
    public:
        PaintFrame(wxFrame *frame, const wxString& title);
        ~PaintFrame();

    private:

        wxMenuBar *menuBar; // the menu bar

	    wxMenu *fileMenu; // the file menu (keep this simple
	    wxMenu *editMenu; // the file menu (keep this simple
	    wxMenu *drawMenu; // the file menu (keep this simple
	    wxMenu *helpMenu; // the file menu (keep this simple

        BasicDrawPane *drawPane;

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

            idMenuDrawLine = 3001,
            idMenuDrawBox,
            idMenuDrawCircle,

            idMenuHelpHelp = 5001,
            idMenuHelpAbout
        };

        void OnClose(wxCloseEvent& event);

        void OnFileNew(wxCommandEvent& event);
        void OnFileOpen(wxCommandEvent& event);
        void OnFileSave(wxCommandEvent& event);
        void OnFileClose(wxCommandEvent& event);
        void OnFileQuit(wxCommandEvent& event);

        void OnEditUndo(wxCommandEvent& event);
        void OnEditRedo(wxCommandEvent& event);
        void OnEditCut(wxCommandEvent& event);
        void OnEditCopy(wxCommandEvent& event);
        void OnEditPaste(wxCommandEvent& event);
        void OnEditSelectAll(wxCommandEvent& event);

        void OnDrawLine(wxCommandEvent& event);
        void OnDrawBox(wxCommandEvent& event);
        void OnDrawCircle(wxCommandEvent& event);

        void OnHelpHelp(wxCommandEvent& event);
        void OnHelpAbout(wxCommandEvent& event);

        DECLARE_EVENT_TABLE()
};


#endif // PAINTMAIN_H
