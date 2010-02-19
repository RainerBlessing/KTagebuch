/***************************************************************************
                          ktagebuch.h  -  description
                             -------------------
    begin                : Tue Jul 17 01:36:53 CEST 2001
    copyright            : (C) 2001 by Rainer Blessing
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

#ifndef KTAGEBUCH_H
#define KTAGEBUCH_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapplication.h>
#include <kmainwindow.h>
#include <kstatusbar.h>
#include <qlabel.h>
#include <kstdaccel.h>
#include <kiconloader.h>
#include <kmenubar.h>
#include <kaction.h>
#include <kstdaction.h>
#include <klocale.h>
#include <keditcl.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <qfile.h>
#include <qtextstream.h>
#include <ktoolbar.h>
#include <kpushbutton.h>
#include <qpixmap.h>
#include <qiconset.h>
#include <kdatewidget.h>
#include <kdatepicker.h>
#include <qdatetime.h>
#include <qstring.h>
#include <qdir.h>
#include <kmessagebox.h>
#include <dcopclient.h>
#include <qmessagebox.h>
#include <kdialog.h>
#include <kprinter.h>
#include <qspinbox.h>
#include <qpainter.h>
#include <kstandarddirs.h>
#include <qimage.h>
#include <kconfig.h>
#include <kfontcombo.h>
#include <qpushbutton.h>
#include <qsimplerichtext.h>
#include <qpaintdevicemetrics.h>
#include <kfiledialog.h>
#include <ktextedit.h>

class TKSelectColorAction;
class KFontSizeAction;
class LibraryLoader;
class Plugins;
class KTagebuchConfigDialog;
class FileSystem;

/** KTagebuch is the base class of the project */
class KTagebuch : public KMainWindow {
    Q_OBJECT
public:
    /** construtor */
    KTagebuch();
    /** destructor */
    ~KTagebuch();
    /** No descriptions */
    KConfig* getConfig();
    /** sets font and colors */
    void applyConfig();
    void insert(QString string);
    /** returns the date of the loaded entry */
    QDate today();
    /** selects specified text */
    void select(int para,int index,int length);

    //void getCursorPosition(int* para,int* index){ text->getCursorPosition(para,index); };
    KTagebuchConfigDialog *preferencesBox() {
        return cdlg;
    }
    LibraryLoader *libraryLoader() {
        return mLibraryLoader;
    }
    QString getText() {
        return text->text();
    }
    void setText(QString _text) {
        text->setText(_text);
    };

    /** inserts text into the entry */
    void insertHTML(QString HTMLtext);

private:
    KTagebuchConfigDialog *cdlg;
    FileSystem* fileSystem;
    LibraryLoader *mLibraryLoader;
    KTextEdit *text;
    KDatePicker* dateW;
    KFontCombo* fontCombo;
    KFontSizeAction* actionFormatFontSize;
    QLabel* dateL;
    QDate currDate;
    QDate todayD;
    QDir appDir;
    KConfig *config;
    KFontAction *actionFormatFontFamily;
    KToggleAction *actionFormatBold;
    KToggleAction *actionFormatItalic;
    KToggleAction *actionFormatUnderline;
    TKSelectColorAction *actionFormatColor;
    KToggleAction *actionFormatAlignLeft;
    KToggleAction *actionFormatAlignCenter;
    KToggleAction *actionFormatAlignRight;
    KToggleAction *actionFormatAlignBlock;
    enum saveResult{ SAVE_OK, SAVE_CANCEL,SAVE_NO, SAVE_RETRY, SAVE_ERROR };
    Plugins *mPluginsModule;

    void getDate_Str(QDate qdate,QString* string);
    void getDate_QD(QDate *qdate,QString* string);
    saveResult entryChanged();
    void loadPlugins();

public slots:
    /** opens a KDatepicker dialog */
    void datepicker();
    bool print();
    bool printDialog();
    void selectAll();
    void deselect();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void toggleToolBar();
    void toggleStatusBar();
    void saveOptions();

    saveResult save();
    bool loadEntry(QDate);
    void slotLastEntry();
    void slotNextEntry();
    void slotToday();
    void slotFirstEntry();
    void slotYearBack();
    void slotMonthBack();
    void slotDayBack();
    void slotDayForward();
    void slotMonthForward();
    void slotYearForward();
    void slotNewestEntry();
    bool queryClose();
    void setFontSize(int size);
    /** No descriptions */
    void setDate(QDate date);
    /** No descriptions */
    void setFont(const QString &font);

    FileSystem* getFileSystem();

signals:
    void loadEntry();
    void saveEntry();

private slots: // Private slots
    /** No descriptions */
    void slotInsertDate();
    /** No descriptions */
    void slotInsertDateAndTime();
    /** No descriptions */
    void slotInsertTime();
    /** No descriptions */
    void slotInsertHTML();
    /** No descriptions */
    void slotOpenSetupDlg();
    /** No descriptions */
    void slotBold();
    /** No descriptions */
    void slotItalic();
    /** No descriptions */
    void slotUnderline();
    /** No descriptions */
    void slotPrint();
    /** No descriptions */
    void slotSpelling();
    /** No descriptions */
    void slotFind();
    /** No descriptions */
    void slotInsertImage();
    /** No descriptions */
    void slotLeft();
    /** No descriptions */
    void slotCenter();
    /** No descriptions */
    void slotRight();
    /** No descriptions */
    void slotBlock();
    /** sets the text color, called by tkselectcoloraction */
    void slotColor();
    void slotFontChanged(const QFont & f);
    void slotColorChanged(const QColor & f);
    /** No descriptions */
    void slotExportEntry();
};

#endif
