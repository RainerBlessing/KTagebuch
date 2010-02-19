////////////////////////////////////////////////////////////////////////////////
// moodplugin.h 							      //
// 									      //
// Copyright (C)  2002  Rainer Blessing <rainer@theblessing.net>	      //
// 									      //
// This library is free software; you can redistribute it and/or	      //
// modify it under the terms of the GNU Lesser General Public		      //
// License as published by the Free Software Foundation; either		      //
// version 2.1 of the License, or (at your option) any later version.	      //
//   									      //
// This library is distributed in the hope that it will be useful,	      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of	      //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU	      //
// Lesser General Public License for more details.			      //
//  									      //
// You should have received a copy of the GNU Lesser General Public	      //
// License along with this library; if not, write to the Free Software	      //
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA		      //
// 02111-1307  USA							      //
////////////////////////////////////////////////////////////////////////////////
#ifndef MOODPLUGIN_H
#define MOODPLUGIN_H

#include <qobject.h>
#include <qmap.h>

#include "ktagebuchplugin.h"

class MoodPreferences;
class FileSystem;
class QStringList;
class KToolBar;
class KComboBox;

class MoodPlugin : public ktagebuchPlugin
{
	Q_OBJECT
public:
	MoodPlugin( QObject *parent, const char *name, const QStringList &args );
	~MoodPlugin();

	void init();
	bool unload();
	void save();
public slots:
	void loadEntry();
	void saveEntry();
	
public slots:

private:
  MoodPreferences *mPrefs;
  FileSystem *fileSystem;
  KToolBar *toolbar;
  KComboBox *combobox;
};

#endif


