/*
    pluginmodule.h  -  ktagebuch Plugin Module

    Copyright (c) 2002 Rainer Blessing
    
    This class is based on the Kopete class of the same name:
    Copyright (c) 2000-2001 Charles Samuels        <charles@kde.org>
    Copyright (c) 2000-2001 Neil Stevens           <nei@qualityassistant.com>
    Copyright (c) 2001-2002 Duncan Mac-Vicar Prett <duncan@kde.org>


    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#ifndef PLUGINMODULE_H
#define PLUGINMODULE_H

#include <klistview.h>
#include <qframe.h>
#include <qstringlist.h>
#include <qlistview.h>

#include "pluginloader.h"
#include "ui/configmodule.h"

class KTabCtl;
struct KTagebuchLibraryInfo;

class PluginListItem : public QCheckListItem
{
public:
	PluginListItem(const bool _exclusive, bool _checked, const KTagebuchLibraryInfo &_info, QListView *_parent);
	const KTagebuchLibraryInfo &info() const { return mInfo; }

	// This will toggle the state without "emitting" the stateChange
	void setChecked(bool);

protected:
	virtual void stateChange(bool);
	virtual void paintCell(QPainter *, const QColorGroup &, int, int, int);

private:
	KTagebuchLibraryInfo mInfo;
	bool silentStateChange;
	bool exclusive;
};

class PluginListView : public KListView
{
	Q_OBJECT

friend class PluginListItem;

public:
	PluginListView( QWidget *parent = 0, const char *name = 0 );

	virtual void clear();

signals:
	void stateChange(PluginListItem *, bool);

private:
	void stateChanged( PluginListItem *, bool );

	unsigned m_count;
};
extern KTagebuch *ktagebuchapp;


class Plugins : public ConfigModule
{
	Q_OBJECT

public:
	Plugins(QObject *_parent = 0);
	virtual void save();
	virtual void reopen();

private slots:
	void stateChange(PluginListItem *, bool);

private:
	void addPlugin(const KTagebuchLibraryInfo &);
	void removePlugin(const KTagebuchLibraryInfo &);

	QStringList mAdded, mDeleted;
	PluginListView *otherList;
};

#endif

// vim: set noet ts=4 sts=4 sw=4:

