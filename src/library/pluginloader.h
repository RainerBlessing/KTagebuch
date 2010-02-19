/*
    pluginloader.h - ktagebuch Plugin Loader

    Copyright (c) 2002 by Rainer Blessing

    Portions of this code based on Kopete and Noatun plugin code:
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

#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H

#include <qdict.h>
#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qvaluelist.h>

#include <klibloader.h>

struct KTagebuchLibraryInfo
{
	QString specfile;
	QString filename;
	QString author;
	QString license;
	QString type;
	QString site;
	QString email;
	QString name;
	QString comment;
	QStringList require;
};

bool operator ==(const KTagebuchLibraryInfo &, const KTagebuchLibraryInfo &);

class ktagebuchPlugin;

/**
 * @author Duncan Mac-Vicar P. <duncan@kde.org>
 */
class LibraryLoader : public QObject
{
	Q_OBJECT

private:
	friend class ktagebuchPlugin;
	struct PluginLibrary
	{
		ktagebuchPlugin *plugin;
		KLibrary *library;
	};

public:
	LibraryLoader();
	~LibraryLoader();

	QValueList<KTagebuchLibraryInfo> available() const;
	QValueList<KTagebuchLibraryInfo> loaded() const;

	/**
	 * Search by Id
	 */
	ktagebuchPlugin *searchByID( const QString &Id );

	/**
	 * loads all the enabled plugins
	 */
	bool loadAll(void);
	bool loadAll(const QStringList &);

	bool isLoaded(const QString &spec) const;
	void add(const QString &spec);
	void setModules(const QStringList &mods);
	/**
	 * unload the plugin specified by spec
	 */
	bool remove(const QString &spec);
	/**
	 * unload the plugin that is plugin
	 */
	bool remove(const LibraryLoader::PluginLibrary *plugin);
	bool remove(const ktagebuchPlugin *plugin);

	/**
	 * This is needed for the Plugin-List-View
	 * to see what plugins are required to show
	 * (when required by another noatun-plugin)
	**/
	KTagebuchLibraryInfo getInfo(const QString &spec) const;
	QPtrList<ktagebuchPlugin> plugins() const;
	

private:
	bool loadSO(const QString &spec);
	void removeNow(const QString &spec);

	QDict<LibraryLoader::PluginLibrary> mLibHash;
	
	/**
	 * A cache for plugin info, to avoid reparsing (and hence mutable)
	 */
	mutable QMap<QString, KTagebuchLibraryInfo> m_cachedInfo;

signals: // Signals
	void pluginLoaded(ktagebuchPlugin *);
};

#endif

// vim: set noet ts=4 sts=4 sw=4:

