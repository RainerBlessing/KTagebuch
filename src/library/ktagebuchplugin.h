/*
    ktagebuchplugin.h - ktagebuch Plugin API

    Copyright (c) 2002      by Rainer Blessing

    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#ifndef ktagebuchPLUGIN_H
#define ktagebuchPLUGIN_H

#include <qobject.h>

class KActionCollection;

/**
 * @author Duncan Mac-Vicar P. <duncan@kde.org>
 *
 * ktagebuchPlugin is the base class for all ktagebuch plugins, and can implement
 * virtually anything you like. Currently not the full ktagebuch API allows it
 * to have plugins hooked into it, but that will hopefully change soon.
 */
class ktagebuchPlugin : public QObject
{
	Q_OBJECT

public:
	ktagebuchPlugin( QObject *parent = 0L, const char *name = 0L );
	virtual ~ktagebuchPlugin();

	virtual void init();
	virtual bool unload();
	virtual const char *id() const;
public slots:
	virtual void loadEntry();
	virtual void saveEntry();

public slots:
};

#endif

// vim: set noet ts=4 sts=4 sw=4:

