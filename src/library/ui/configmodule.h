/*
    configmodule.h - ktagebuch Plugin Config Module

    Copyright (c) 2002 Rainer Blessing

    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#ifndef CONFIGMODULE_H
#define CONFIGMODULE_H

#include <qwidget.h>


class KTagebuch;

extern KTagebuch *ktagebuchapp;

class ConfigModule : public QWidget
{   
   Q_OBJECT
public:
	ConfigModule(const QString &name, const QString &description, QObject *parent=0);
	ConfigModule(const QString &name, const QString &description, const QString &icon, QObject *parent=0);
	virtual ~ConfigModule();
	QString getName();
public slots:
	virtual void save() {}
	virtual void reopen() {}
	void activate();

private slots:
	void ownerDeleted();
protected:
	QString name;
};

#endif

