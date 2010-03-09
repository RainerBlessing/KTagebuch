/*
 * ktagebuchview.cpp
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#include "ktagebuchview.h"
#include "settings.h"

#include <ktabwidget.h>
#include <ktextedit.h>
#include <klocale.h>
#include <QtGui/QLabel>
#include "ktagebuch.h"

KTagebuchView::KTagebuchView(KTagebuch *ktagebuch):m_ktagebuch(ktagebuch)
{
  setParent(ktagebuch);  
  addTab(new KTextEdit(this),"textEdit");  
  setAutoFillBackground(true);
  settingsChanged();
}

KTagebuchView::~KTagebuchView()
{  
}

KTextEdit* KTagebuchView::getTextEdit()
{
  return (KTextEdit*)currentWidget();
}

void KTagebuchView::switchColors()
{
    // switch the foreground/background colors of the label
    /*
    QColor color = Settings::col_background();
    Settings::setCol_background( Settings::col_foreground() );
    Settings::setCol_foreground( color );
*/
    settingsChanged();
}

void KTagebuchView::settingsChanged()
{
    QPalette pal;
    pal.setColor( QPalette::Window, Settings::bg_color());
    pal.setColor( QPalette::WindowText, Settings::fg_color());
    getTextEdit()->setPalette(pal);
    // i18n : internationalization
    emit signalChangeStatusbar( i18n("Settings changed") );
}

//#include "ktagebuchview.moc"
