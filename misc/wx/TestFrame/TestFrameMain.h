/***************************************************************
 * Name:      TestFrameMain.h
 * Purpose:   Defines Application Frame
 * Author:    Brian Lingard ()
 * Created:   2012-05-21
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifndef TESTFRAMEMAIN_H
#define TESTFRAMEMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "TestFrameApp.h"

class TestFrameFrame: public wxFrame
{
    public:
        TestFrameFrame(wxFrame *frame, const wxString& title);
        ~TestFrameFrame();

    private:
        enum
        {
            idMenuFileNew = 1001,
            idMenuFileOpen,
            idMenuFileSave,
            idMenuFileClose,
            idMenuFileQuit,
            idMenuHelpHelp = 2001,
            idMenuHelpAbout
        };

        void OnClose(wxCloseEvent& event);

        void OnFileNew(wxCommandEvent& event);
        void OnFileOpen(wxCommandEvent& event);
        void OnFileSave(wxCommandEvent& event);
        void OnFileClose(wxCommandEvent& event);
        void OnFileQuit(wxCommandEvent& event);

        void OnHelpHelp(wxCommandEvent& event);
        void OnHelpAbout(wxCommandEvent& event);

        DECLARE_EVENT_TABLE()
};


#endif // TESTFRAMEMAIN_H
