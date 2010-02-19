/*
    configmodule.cpp - ktagebuch Plugin Config Module

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

#include "configmodule.h"
#include "ktagebuch.h"
#include "ktagebuchconfigdialog.h"

#include <qlabel.h>
#include <qlayout.h>

#include <kglobal.h>
#include <kiconloader.h>
#include <klocale.h>

ConfigModule::ConfigModule(const QString &name, const QString &description, QObject *owner)
	: QWidget(ktagebuchapp->preferencesBox()->addPage(name, description))
{	
	if (owner)
		connect(owner, SIGNAL(destroyed()), SLOT(ownerDeleted()));
	ktagebuchapp->preferencesBox()->add(this);
	QFrame *page=static_cast<QFrame*>(parent());
	(new QHBoxLayout(page))->addWidget(this);
}

ConfigModule::ConfigModule(const QString &name, const QString &description, const QString &pixmap, QObject *owner)
	: QWidget(ktagebuchapp->preferencesBox()->addPage(name, description, KGlobal::iconLoader()->loadIcon(pixmap,KIcon::NoGroup, KIcon::SizeMedium)  ))	
{	
	if (owner)
		connect(owner, SIGNAL(destroyed()), SLOT(ownerDeleted()));
	ktagebuchapp->preferencesBox()->add(this);
	
	
	QFrame *page=static_cast<QFrame*>(parent());
	(new QHBoxLayout(page))->addWidget(this);	
	
}


ConfigModule::~ConfigModule()
{
	ktagebuchapp->preferencesBox()->remove(this);
}

void ConfigModule::ownerDeleted()
{
	QObject *p=parent();
	delete this;
	delete p;
}

void ConfigModule::activate()
{
	QFrame *page=static_cast<QFrame*>(parent());
	ktagebuchapp->preferencesBox()->showPage(ktagebuchapp->preferencesBox()->pageIndex(page));
	ktagebuchapp->preferencesBox()->show();
	ktagebuchapp->preferencesBox()->raise();
}

QString ConfigModule::getName(){
	QString _name(name);
	return _name;
}

//#include "configmodule.moc"
