/*
    moodprefs.h

    Copyright (c) 2002 by Rainer Blessing   <rainer@theblessing.net>
    

    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#ifndef MOODPREFERENCES_H
#define MOODPREFERENCES_H

#include <qmap.h>
#include <qcombobox.h>

#include <qwidget.h>
#include <klineedit.h>
#include "configmodule.h"


class QString;
class MoodPluginUI;

class MoodPreferences : public ConfigModule
{
  Q_OBJECT
public:
	MoodPreferences(const QString &pixmap,QObject *parent=0);
	~MoodPreferences();
	virtual void save();	
	
signals:
	void saved();

private:
	MoodPluginUI *preferencesDialog;	
};

#endif
