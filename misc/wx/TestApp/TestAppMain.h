/***************************************************************
 * Name:      TestAppMain.h
 * Purpose:   Defines Application Frame
 * Author:    Brian Lingard ()
 * Created:   2012-05-23
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifndef TESTAPPMAIN_H
#define TESTAPPMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "TestAppApp.h"

class TestAppFrame: public wxFrame
{
    public:
        TestAppFrame(wxFrame *frame, const wxString& title);
        ~TestAppFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // TESTAPPMAIN_H
