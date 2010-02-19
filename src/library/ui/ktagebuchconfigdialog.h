/***************************************************************************
                          ktagebuchconfigdialog.h  -  description
                             -------------------
    begin                : Son Mär 31 2002
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

#ifndef __ktagebuch_configdialog_h__
#define __ktagebuch_configdialog_h__

#include "ktagebuch.h"

#include <kdialogbase.h>
#include <kfontdialog.h>
#include <kcolorbutton.h>
#include <qcheckbox.h>
#include <qspinbox.h>

class ConfigModule;
extern KTagebuch *ktagebuchapp;
class KTagebuchConfigDialog : public KDialogBase
{
  Q_OBJECT


  public:
    KTagebuchConfigDialog ();
    ~KTagebuchConfigDialog ();
   
    int exec ();
    void add(ConfigModule *page);    
    void remove(ConfigModule *page);
    
  private:    
    KConfig *config;
    KTagebuch *mainWindow;
    KFontChooser *fontchooser;
    KColorButton *fgColor;
    KColorButton *bgColor;
    QCheckBox *wrapCB;
    QLabel *wrapL;
    QSpinBox *wrapSB;
    QCheckBox *autosaveCB;
    QList<ConfigModule> mModules;

private: // Private methods
  /** No descriptions */
  void storeConfiguration();
  
private slots: // Private slots
  /** No descriptions */
  void slotOk();
  void slotApply();
  void slotCancel();
  
public slots: // Public slots
  /** No descriptions */
  void slotWrap(bool on);
};

#endif
