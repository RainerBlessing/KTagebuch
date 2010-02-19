/*
    pluginloader.cpp - ktagebuch Plugin Loader

    Copyright (c) 2002 by Rainer Blessing

    Portions of this code based on Kopete and  Noatun plugin code:
    Kopete Copyright (c) 2002 by Duncan Mac-Vicar Prett       <duncan@kde.org>
    Noatun Copyright (c) 2000-2002 The Noatun Developers


    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#include <qdir.h>
#include <qfile.h>
#include <kglobal.h>
#include <klocale.h>
#include <knotifyclient.h>
#include <ksimpleconfig.h>
#include <kstddirs.h>
#include <kurl.h>
#include <kparts/componentfactory.h>
#include <kdebug.h>
#include "ktagebuchplugin.h"
#include "pluginloader.h"

class KTagebuchLibraryInfo;

bool operator ==(const KTagebuchLibraryInfo &a, const KTagebuchLibraryInfo &b)
{
	// Feels like cheating, doesn't it?
	return a.specfile == b.specfile;
}

LibraryLoader::LibraryLoader()
{
}

LibraryLoader::~LibraryLoader()
{
	QValueList<KTagebuchLibraryInfo> l;

	l = loaded();
	for(QValueList<KTagebuchLibraryInfo>::Iterator i = l.begin(); i != l.end(); ++i)
	{
		if((*i).type != "protocol" && (*i).type != "ui" && (*i).type != "dock")
		{
			removeNow((*i).specfile);
		}
	}
	/*
	l = loaded();
	for(QValueList<NoatunLibraryInfo>::Iterator i = l.begin(); i != l.end(); ++i)
	{
		if((*i).type == "userinterface")
		{
			removeNow((*i).specfile);
		}
	}
	*/
	l = loaded();
	for(QValueList<KTagebuchLibraryInfo>::Iterator i = l.begin(); i != l.end(); ++i)
	{
		removeNow((*i).specfile);
	}
}

QValueList<KTagebuchLibraryInfo> LibraryLoader::available() const
{
	QValueList<KTagebuchLibraryInfo> items;
	QStringList files=KGlobal::dirs()->findAllResources("appdata", "*.plugin", false, true);	
	for (QStringList::Iterator i=files.begin(); i!=files.end(); ++i){
		items.append(getInfo(*i));	
		}
	return items;
}

QPtrList<ktagebuchPlugin> LibraryLoader::plugins() const
{
	QPtrList<ktagebuchPlugin> list;
	QDictIterator<LibraryLoader::PluginLibrary> i( mLibHash );
	for( ; i.current(); ++i )
		list.append( i.current()->plugin );

	return list;
}

bool LibraryLoader::loadAll(void)
{
	KConfig *config=KGlobal::config();
	config->setGroup("");
	QStringList plugins = config->readListEntry("Plugins");
	return loadAll(plugins);
}

bool LibraryLoader::loadAll(const QStringList &plugins)
{	
	for(QStringList::ConstIterator i=plugins.begin(); i!=plugins.end(); ++i)
	{		
		if ( !loadSO(*i) )
			kdDebug() << "[LibraryLoader] loading " << (*i) << " failed!" << endl;
	}
		
	return true;
}

KTagebuchLibraryInfo LibraryLoader::getInfo(const QString &spec) const
{
	QMap<QString, KTagebuchLibraryInfo>::iterator cached = m_cachedInfo.find(spec);        
	if (cached != m_cachedInfo.end() )
		return *cached;
	KTagebuchLibraryInfo info;
	QString specPath = (spec[0]=='/') ? spec : KGlobal::dirs()->findResource("appdata", spec);
	if (!QFile::exists(specPath))
		return info;
		
	KSimpleConfig file(specPath);
	if (spec.find('/')>=0)
		info.specfile=KURL(spec).fileName();
	else
		info.specfile=spec;
	info.filename=file.readEntry("Filename");
	info.author=file.readEntry("Author");
	info.site=file.readEntry("Site");
	info.email=file.readEntry("Email");
	info.type=file.readEntry("Type");
	info.name=file.readEntry("Name");
	info.comment=file.readEntry("Comment");
	info.require=file.readListEntry("Require");
	info.license=file.readEntry("License");
	m_cachedInfo[spec]=info;
	return info;
}

bool LibraryLoader::isLoaded(const QString &spec) const
{
	PluginLibrary *lib=mLibHash[spec];
	if (!lib) return false;
	return lib->plugin;
}

bool LibraryLoader::loadSO(const QString &spec)
{
	if( !isLoaded(spec) )
	{
		KTagebuchLibraryInfo info = getInfo(spec);
		if (info.specfile != spec)
			return false;

		for (QStringList::ConstIterator it = info.require.begin(); it != info.require.end(); ++it)
			loadSO(*it);

		// get the library loader instance
		KLibLoader *loader = KLibLoader::self();

		PluginLibrary *listitem=mLibHash[spec];

		if (!listitem)
		{
			KLibrary *lib = loader->library( QFile::encodeName(info.filename) );
			if (!lib)
			{
				kdDebug() << "[LibraryLoader] loadSO(), error while loading library: " << loader->lastErrorMessage() << endl;
				return false;
			}
			listitem = new PluginLibrary;
			listitem->library = lib;
			mLibHash.insert(spec, listitem);
		}

		listitem->plugin =
			KParts::ComponentFactory::createInstanceFromFactory<ktagebuchPlugin>
			( listitem->library->factory(), 0L /* FIXME: parent object */ );
		
		// Automatically load the i18n catalogue for the plugin
		//KGlobal::locale()->insertCatalogue( info.filename );

		listitem->plugin->init();

		emit pluginLoaded(listitem->plugin);
		return true;
	}
	else
	{
		kdDebug() << "[LibraryLoader] loadSO(), " << spec << " is already loaded!" << endl;
		return false;
	}
}

void LibraryLoader::add(const QString &spec)
{
	PluginLibrary *lib=mLibHash[spec];
	if (lib)
		if (lib->plugin) return;

	loadSO(spec);
}

void LibraryLoader::setModules(const QStringList &mods)
{
	KConfig *config=KGlobal::config();
	config->setGroup("");
	config->writeEntry("Plugins", mods);
	KGlobal::config()->sync();	
}

bool LibraryLoader::remove(const QString &spec)
{
	removeNow(spec);
	return true;
}

bool LibraryLoader::remove(const PluginLibrary *pl)
{
	for (QDictIterator<PluginLibrary> i(mLibHash); i.current(); ++i)
	{
		if (i.current()==pl)
			return remove(i.currentKey());
	}
	return false;
}

bool LibraryLoader::remove(const ktagebuchPlugin *plugin)
{
	for (QDictIterator<PluginLibrary> i(mLibHash); i.current(); ++i)
	{
		if (i.current()->plugin==plugin)
			return remove(i.currentKey());
	}
	return false;

}


QValueList<KTagebuchLibraryInfo> LibraryLoader::loaded() const
{
	QValueList<KTagebuchLibraryInfo> items;

	for (QDictIterator<PluginLibrary> i(mLibHash); i.current(); ++i)
		if (isLoaded(i.currentKey()))
			items.append(getInfo(i.currentKey()));

	return items;
}

void LibraryLoader::removeNow(const QString &spec)
{
	
	KTagebuchLibraryInfo info = getInfo(spec);
	if (info.specfile == spec)
	{
		QValueList<KTagebuchLibraryInfo> l = loaded();
		for (QValueList<KTagebuchLibraryInfo>::Iterator i = l.begin(); i != l.end(); ++i)
		{
			for (QStringList::ConstIterator it = (*i).require.begin(); it != (*i).require.end(); ++it)
				if (*it == spec)
				removeNow((*i).specfile);
		}
	}

	PluginLibrary *lib=mLibHash[spec];

	if (!lib)
		return;

	// Added by Duncan 20/01/2002
	// We need to call unload function for the plugin
	lib->plugin->unload();

	delete lib->plugin;
	lib->plugin=0;

	mLibHash.remove(spec);
}

ktagebuchPlugin* LibraryLoader::searchByID( const QString &Id )
{
	QValueList<KTagebuchLibraryInfo> l = loaded();

	for (QValueList<KTagebuchLibraryInfo>::Iterator i = l.begin(); i != l.end(); ++i)
	{
		ktagebuchPlugin *tmp_plug = mLibHash[(*i).specfile]->plugin;
		if ( tmp_plug->id() == Id )
		{
			return tmp_plug;
		}
	}
	return NULL;
}

#include <pluginloader.moc>

// vim: set noet ts=4 sts=4 sw=4:

