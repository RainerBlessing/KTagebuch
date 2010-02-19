/*
 * ktagebuch.h
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#ifndef KTAGEBUCH_H
#define KTAGEBUCH_H


#include <kxmlguiwindow.h>

#include "ui_prefs_base.h"

class KTagebuchView;
class QPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for KTagebuch.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class KTagebuch : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    KTagebuch();

    /**
     * Default Destructor
     */
    virtual ~KTagebuch();

private slots:
    void fileNew();
    void optionsPreferences();

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    KTagebuchView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _KTAGEBUCH_H_
