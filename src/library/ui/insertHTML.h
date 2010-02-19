/***************************************************************************
                          insertHTML.h  -  description
                             -------------------
    begin                : Son Apr 23 2002
    copyright            : (C) 2002 by Rainer Blessing
    email                : rainer@theblessing.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef INSERTHTML_H
#define INSERTHTML_H
#include <qobject.h> 
#include <kdialogbase.h>
#include <klistview.h>
#include <qabstractlayout.h>
#include <qlineedit.h>
#include "ui/inserthtmldialog.h"

class QTextEdit;


class insertHtmlDlgImpl:public InsertHTMLDialog{
	
public:
	insertHtmlDlgImpl();	
private:	
	InsertHTMLDialog *dialogUi;
};

#endif
