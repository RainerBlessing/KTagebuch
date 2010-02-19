/*
 * ktagebuchview.h
 *
 * Copyright (C) 2007 %{AUTHOR} <%{EMAIL}>
 */
#ifndef KTAGEBUCHVIEW_H
#define KTAGEBUCHVIEW_H

#include <QtGui/QWidget>

#include "ui_ktagebuchview_base.h"

class QPainter;
class KUrl;

/**
 * This is the main view class for KTagebuch.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */

class KTagebuchView : public QWidget, public Ui::ktagebuchview_base
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    KTagebuchView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~KTagebuchView();

private:
    Ui::ktagebuchview_base ui_ktagebuchview_base;

signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

private slots:
    void switchColors();
    void settingsChanged();
};

#endif // KTagebuchVIEW_H
