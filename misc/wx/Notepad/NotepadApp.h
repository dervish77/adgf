/***************************************************************
 * Name:      NotepadApp.h
 * Purpose:   Defines Application Class
 * Author:    Brian Lingard ()
 * Created:   2012-05-25
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifndef NOTEPADAPP_H
#define NOTEPADAPP_H

#include <wx/app.h>

class NotepadApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // NOTEPADAPP_H
