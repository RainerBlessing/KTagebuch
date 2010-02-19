/*
    moodprefs.cpp

    mood plugin

    Copyright (c) 2002 by Rainer Blessing

    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/


#include "moodprefs.moc"
#include "moodpluginui.h"
#include "moodplugin.h"
#include "ktagebuch.h"

#include <qlayout.h>
#include <kconfig.h>

MoodPreferences::MoodPreferences(const QString &pixmap,QObject *parent) 
 : ConfigModule(i18n("Mood"),i18n("Mood Plugin"),pixmap,parent)
{
	( new QVBoxLayout( this ) )->setAutoAdd( true );
	preferencesDialog = new MoodPluginUI(this);
}

MoodPreferences::~MoodPreferences()
{
}


void MoodPreferences::save()
{
	KConfig *config = ktagebuchapp->getConfig();
	config->setGroup("Mood Plugin");
	config->writeEntry("moods", preferencesDialog->getMoods() );
	config->sync();
	emit saved();	
}

