/*
 * ktagebuchview.cpp
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#include "ktagebuchview.h"
#include "settings.h"

#include <klocale.h>
#include <QtGui/QLabel>

KTagebuchView::KTagebuchView(QWidget *)
{
    ui_ktagebuchview_base.setupUi(this);
    settingsChanged();
    setAutoFillBackground(true);
}

KTagebuchView::~KTagebuchView()
{

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
    ui_ktagebuchview_base.kcfg_sillyLabel->setPalette( pal );

    // i18n : internationalization
    ui_ktagebuchview_base.kcfg_sillyLabel->setText( i18n("This project is %1 days old",Settings::val_time()) );
    emit signalChangeStatusbar( i18n("Settings changed") );
}

#include "ktagebuchview.moc"
