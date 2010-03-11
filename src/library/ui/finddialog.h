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

#include <kdialog.h>
#include <qlineedit.h>
#include "ktagebuch.h"
class FileSystem;
class QTreeWidget;

extern KTagebuch *ktagebuchapp;

class FindDialog : public KDialog{

Q_OBJECT

public:
	FindDialog(KTagebuch* ktagebuchapp,FileSystem* fileSystem);
	~FindDialog();
private:
  KGuiItem* close;
  QTreeWidget* m_treeWidget;
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
