/***************************************************************
 * Name:      PaintApp.h
 * Purpose:   Defines Application Class
 * Author:    Brian Lingard ()
 * Created:   2012-05-29
 * Copyright: Brian Lingard ()
 * License:
 **************************************************************/

#ifndef PAINTAPP_H
#define PAINTAPP_H

#include <wx/app.h>

class PaintApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // PAINTAPP_H
