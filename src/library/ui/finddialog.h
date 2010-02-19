/***************************************************************************
                          finddialog.h  -  description
                             -------------------
    begin                : Son Apr 23 2002
    copyright            : (C) 2002 by Rainer Blessing
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

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <kdialogbase.h>
#include <klistview.h>
#include <qabstractlayout.h>
#include <qlineedit.h>
#include "ktagebuch.h"
class FileSystem;
extern KTagebuch *ktagebuchapp;

class FindDialog : public KDialogBase  {

Q_OBJECT

public:
	FindDialog(FileSystem* fileSytem);
	~FindDialog();
private:
  KGuiItem* close;
  QListView* ListView;
  KTagebuch* ktagebuch;
  QLineEdit* findLE;
  QCheckBox* caseCB;
  QCheckBox* backwCB;
  QString currentDateSTR;
  QStringList* dateList;
  FileSystem* fileSystem;
private slots: // Private slots
  /** Search Function */
  void slotFind();
  /** Find Button */
  void slotUser1();
  /** Close Button */
  void slotUser2();				
  /** No descriptions */
  void slotBackw(bool on);
};

#endif
