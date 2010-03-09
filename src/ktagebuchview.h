/*
 * ktagebuchview.h
 *
 * Copyright (C) 2007 %{AUTHOR} <%{EMAIL}>
 */
#ifndef KTAGEBUCHVIEW_H
#define KTAGEBUCHVIEW_H

#include <QtGui/QWidget>
#include <ktabwidget.h>
//#include "ui_ktagebuchview_base.h"

class QPainter;
class KUrl;
class KTextEdit;
class KTagebuch;

/**
 * This is the main view class for KTagebuch.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */

class KTagebuchView : public KTabWidget//, public Ui::ktagebuchview_base
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    KTagebuchView(KTagebuch *parent);

    /**
     * Destructor
     */
    virtual ~KTagebuchView();

    KTextEdit* getTextEdit();
private:
  KTagebuch *m_ktagebuch;
signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

public slots:
    void switchColors();
    void settingsChanged();
};

#endif // KTagebuchVIEW_H
