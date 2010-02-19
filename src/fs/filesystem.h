/***************************************************************************
                          ktagebuch.h  -  description
                             -------------------
    begin                : Tue Jul 17 01:36:53 CEST 2001
    copyright            : (C) 2001 by Rainer Blessing
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

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

class QDir;
class QString;
class sqlite3;
class QStringList;

class FileSystem{
	public:
		FileSystem();
		~FileSystem();
		void importEntries();
		QString loadEntry(int date);
		QString loadFile(int date,QString fileName);
		bool saveEntry(int date,QString text);
		QString getPreviousEntry(int date);
		QString getNextEntry(int date);
		QString getFirstEntry();
		QString getLastEntry();
		QStringList* getDates();
		QStringList* getDates(QString restriction);
		bool storeFile(int date,QString fileName, const char* buffer, int size);
		void openDB();
		void closeDB();
		void exportEntry(int date,QString fileName);
	private:
		QString name;
		QDir appDir;
		sqlite3 *db;
};
#endif
