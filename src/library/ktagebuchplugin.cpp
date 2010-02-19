/*
    ktagebuchplugin.cpp - ktagebuch Plugin API

    Copyright (c) 2001-2002 by Rainer Blessing

    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#include "ktagebuchplugin.h"
#include "pluginloader.h"

ktagebuchPlugin::ktagebuchPlugin( QObject *parent, const char *name )
: QObject( parent, name )
{
}

ktagebuchPlugin::~ktagebuchPlugin()
{
}

void ktagebuchPlugin::init()
{
}

bool ktagebuchPlugin::unload()
{
	return true; //ktagebuchapp->libraryLoader()->remove( this );
}

const char *ktagebuchPlugin::id() const
{
	return this->className();
}

void ktagebuchPlugin::loadEntry()
{
}

void ktagebuchPlugin::saveEntry()
{
}

#include "ktagebuchplugin.moc"

// vim: set noet ts=4 sts=4 sw=4:

