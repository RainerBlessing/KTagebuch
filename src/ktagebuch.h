/*
 * ktagebuch.h
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#ifndef KTAGEBUCH_H
#define KTAGEBUCH_H


#include <kxmlguiwindow.h>

#include "ui_prefs_base.h"
#include "ui_prefs_colors.h"
#include "ui_prefs_font.h"

class KTagebuchView;
class QPrinter;
class KToggleAction;
class KUrl;
class QDir;
class FileSystem;
class KTextEdit;
class KDatePicker;
class KFontCombo;
class KFontSizeAction;
class KFontAction;
class KToolBar;
class KTagebuchConfigDialog;

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

    /** sets font and colors */
    void applyConfig();
    void insert(QString string);
    /** returns the date of the loaded entry */
    QDate today();
    /** selects specified text */
    void select(int para,int index,int length);
    
    //void getCursorPosition(int* para,int* index){ text->getCursorPosition(para,index); };
    /*
    KTagebuchConfigDialog *preferencesBox() {
        return cdlg;
    }
    LibraryLoader *libraryLoader() {
        return mLibraryLoader;
    }
    */
    QString getText();
    
    void setText(QString _text);

    /** inserts text into the entry */
    void insertHTML(QString HTMLtext);

    
    
  private:
    enum saveResult{ SAVE_OK, SAVE_CANCEL,SAVE_NO, SAVE_RETRY, SAVE_ERROR };
    
public slots:
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
    
    void slotFirstEntry();
    void slotYearBack();
    void slotMonthBack();
    void slotDayBack();
    void slotPreviousEntry();    
    void slotToday();
    void slotNextEntry();
    void slotDayForward();
    void slotMonthForward();
    void slotYearForward();
    void slotLastEntry();
    void slotDatepicker();
    
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
    
private slots:
    void fileNew();
    void optionsPreferences();
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
    void slotBold(bool toggled);
    /** No descriptions */
    void slotItalic(bool toggled);
    /** No descriptions */
    void slotUnderline(bool toggled);
    /** No descriptions */
    void slotPrint();
    /** No descriptions */
    void slotSpelling();
    /** No descriptions */
    void slotFind();
    /** No descriptions */
    void slotInsertImage();
    /** No descriptions */
    void slotAlignLeft(bool);
    /** No descriptions */
    void slotAlignCenter(bool);
    /** No descriptions */
    void slotAlignRight(bool);
    /** No descriptions */
    void slotAlignBlock(bool);
    /** sets the text color, called by tkselectcoloraction */
    void slotColor();
    void slotFontChanged(const QFont & f);
    void slotColorChanged(const QColor & f);
    /** No descriptions */
    void slotExportEntry();
private:
    void setupActions();
    KTagebuchConfigDialog *cdlg;
    FileSystem *m_fileSystem;
//    LibraryLoader *mLibraryLoader;
    KToolBar *browseTB;
    KTextEdit *text;
    KDatePicker* dateW;
    KFontCombo* fontCombo;
    KFontSizeAction* actionFormatFontSize;
    QDate currDate;
    QDate todayD;
    KFontAction *actionFormatFontFamily;
    KToggleAction *actionFormatBold;
    KToggleAction *actionFormatItalic;
    KToggleAction *actionFormatUnderline;
//    TKSelectColorAction *actionFormatColor;
    KToggleAction *actionFormatAlignLeft;
    KToggleAction *actionFormatAlignCenter;
    KToggleAction *actionFormatAlignRight;
    KToggleAction *actionFormatAlignBlock;    
//    Plugins *mPluginsModule;

    void getDate_Str(QDate qdate,QString* string);
    void getDate_QD(QDate *qdate,QString* string);
    saveResult entryChanged();
    void loadPlugins();

    Ui::prefs_base ui_prefs_base ;
    Ui::prefs_colors ui_prefs_colors ;
    Ui::prefs_font ui_prefs_font ;
    KTagebuchView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
    
    QString m_appDirPath;
    
};

#endif // _KTAGEBUCH_H_
