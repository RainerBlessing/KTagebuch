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

#include "ktagebuchconfigdialog.h"
//#include "ui/ktagebuchconfigdialog.moc"

#include "ktagebuch.h"

#include <qabstractlayout.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qhbox.h>
#include <qinputdialog.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qradiobutton.h>
#include <qspinbox.h>
#include <qvbox.h>
#include <qwhatsthis.h>
#include <kinstance.h>
#include <kdialogbase.h>
#include <kglobalaccel.h>
#include <kglobal.h>
#include <kglobalsettings.h>
#include <kiconloader.h>
#include <kio/netaccess.h>
#include <kkeydialog.h>
#include <klistbox.h>
#include <klocale.h>
#include <ksimpleconfig.h>
#include <kstdaction.h>
#include <kstandarddirs.h>
#include <kwin.h>
#include <qfont.h>

#include <configmodule.h>

KTagebuchConfigDialog::KTagebuchConfigDialog ()
 : KDialogBase (KDialogBase::IconList, i18n("Configure KTagebuch"), KDialogBase::Ok|KDialogBase::Apply|KDialogBase::Cancel, KDialogBase::Ok)
{  
  KTagebuch* kt= ktagebuchapp;
  config = kt->getConfig();
  mainWindow = kt;

  setMinimumSize(600,400);
  setMaximumSize(600,400);
  
  KWin kwin;
  kwin.setIcons(winId(), kapp->icon(), kapp->miniIcon());

  QStringList path;

  setShowIconsInTreeList(true);

  path.clear();
  path << i18n("KTagebuch");
  setFolderIcon (path, SmallIcon("KTagebuch", KIcon::SizeSmall));

  path.clear();


  path.clear();
  path << i18n("Editor");
  setFolderIcon (path, SmallIcon("edit", KIcon::SizeSmall));

  // General
  QFrame* frGeneral = addPage(i18n("General Options"),i18n("General Options"), BarIcon("edit", KIcon::SizeMedium));

  QVBoxLayout *lo = new QVBoxLayout( frGeneral );
  lo->setSpacing(KDialog::spacingHint());
  lo->setAutoAdd( true );
  config->setGroup("Editor");

  wrapCB=new QCheckBox( i18n("Enable Word Wrap"), frGeneral);
  wrapCB->setChecked(config->readBoolEntry("wrap"));
  connect (wrapCB,SIGNAL (toggled(bool)),this,SLOT(slotWrap(bool)));
  QHBox *hbwrap = new QHBox( frGeneral );
  wrapL=new QLabel("Wrap Words At:",hbwrap);
  wrapSB=new QSpinBox(0,999,1,hbwrap);
  if(int wrapAt=config->readNumEntry("wrapAt")){
    wrapSB->setValue(wrapAt);
  }else{
    wrapSB->setValue(80);
  }
  wrapL->setDisabled(!wrapCB->isChecked());
  wrapSB->setDisabled(!wrapCB->isChecked());
  autosaveCB=new QCheckBox( i18n("Autosave Entries"), frGeneral);
  autosaveCB->setChecked(config->readBoolEntry("autosave"));

  QHBox *hbbg = new QHBox( frGeneral );
  QWidget *qLayoutSeemsBroken = new QWidget( frGeneral, "a working spacer" );
  lo->setStretchFactor( qLayoutSeemsBroken, 100 );


  // colors
  QFrame* frColors = addPage(i18n("Colors"),i18n("Colors"), BarIcon("colors", KIcon::SizeMedium));
  lo = new QVBoxLayout( frColors );
  lo->setSpacing(KDialog::spacingHint());
  lo->setAutoAdd( true );
  config->setGroup("Editor");
  QHBox *hbfg = new QHBox( frColors );
  new QLabel( i18n("Text Color"), hbfg);
  fgColor=new KColorButton(QColor(config->readEntry("fgColor","#000000")),hbfg);
  hbbg = new QHBox( frColors );
  new QLabel(i18n("Background Color"), hbbg);
  bgColor=new KColorButton(QColor(config->readEntry("bgColor","#ffffff")),hbbg);
  qLayoutSeemsBroken = new QWidget( frColors, "a working spacer" );
  lo->setStretchFactor( qLayoutSeemsBroken, 100 );

  //font
  QFrame* frFonts = addPage(i18n("Fonts"),i18n("Fonts"), BarIcon("fonts", KIcon::SizeMedium));
  lo = new QVBoxLayout( frFonts );
  lo->setSpacing(KDialog::spacingHint());
  lo->setAutoAdd( true );
  QStringList list;
  KFontChooser::getFontList(list, 0 );
  fontchooser=new KFontChooser(frFonts, "FontList", false, list);
  QFont f;
  if(config->readEntry("font")){
  	f.fromString(config->readEntry("font"));
  }else{
  	f=QApplication::font();
  }
  fontchooser->setFont(f);

}

KTagebuchConfigDialog::~KTagebuchConfigDialog()
{
}


int KTagebuchConfigDialog::exec()
{
  int n = KDialogBase::exec();
  if (n)
    slotApply();
  return n;
}

void KTagebuchConfigDialog::slotApply()
{  
  ConfigModule *i;
 
  for (i=mModules.first();i;i=mModules.next())	
	     i->save();
  storeConfiguration();
}

/** No descriptions */
void KTagebuchConfigDialog::slotOk(){
  slotApply();
  accept();
}

void KTagebuchConfigDialog::slotCancel(){
	
	reject();
}

/** No descriptions */
void KTagebuchConfigDialog::storeConfiguration(){
  config->setGroup("Editor");
  config->writeEntry("font",(fontchooser->font()).toString());
  config->writeEntry("fgColor",(fgColor->color()).name());
  config->writeEntry("bgColor",(bgColor->color()).name());
  config->writeEntry("wrap",wrapCB->isChecked());
  config->writeEntry("wrapAt",wrapSB->value());
  config->writeEntry("autosave",autosaveCB->isChecked());
  config->sync();
  mainWindow->applyConfig();

}

/** Enables word wrapping */
void KTagebuchConfigDialog::slotWrap(bool on){
  wrapL->setEnabled(on);
  wrapSB->setEnabled(on);
}

void KTagebuchConfigDialog::add(ConfigModule *page){
  mModules.append(page);  
}

void KTagebuchConfigDialog::remove(ConfigModule *page){
  mModules.remove(page);
}
