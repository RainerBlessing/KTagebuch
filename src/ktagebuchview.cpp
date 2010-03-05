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

KTagebuchView::KTagebuchView(QWidget *parent)
{
  setParent(parent);
  addTab(new KTextEdit(this),"textEdit");  
  //  ui_ktagebuchview_base.setupUi(this);
    settingsChanged();
    setAutoFillBackground(true);
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
    QColor color = Settings::col_background();
    Settings::setCol_background( Settings::col_foreground() );
    Settings::setCol_foreground( color );

    settingsChanged();
}

void KTagebuchView::settingsChanged()
{
    QPalette pal;
    pal.setColor( QPalette::Window, Settings::col_background());
    pal.setColor( QPalette::WindowText, Settings::col_foreground());
    
    // i18n : internationalization
    emit signalChangeStatusbar( i18n("Settings changed") );
}

//#include "ktagebuchview.moc"
