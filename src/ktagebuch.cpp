/*
 * ktagebuch.cpp
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#include "ktagebuch.h"
#include "ktagebuchview.h"
#include "settings.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QPrinter>
#include <QtGui/QPrintDialog>
#include <Q3PaintDeviceMetrics>
#include <Q3SimpleRichText>
 
#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>

#include <KDE/KLocale>
#include <kstandarddirs.h>
#include <kfiledialog.h>
#include <ktextedit.h>
#include <ktoolbar.h>
#include <kmessagebox.h>
#include <kfontaction.h>
#include <kfontsizeaction.h>
#include <ktoggleaction.h>

#include "fs/filesystem.h"
#include "library/ui/datepickerdlg.h"
#include "library/ui/finddialog.h"

//#include "library/tkcoloractions.h"

KTagebuch::KTagebuch()
    : KXmlGuiWindow(),
      m_view(new KTagebuchView(this)),
      m_printer(0)      
{
    
    m_fileSystem=new FileSystem();
    m_appDirPath = KGlobal::dirs ()->saveLocation("data", "ktagebuch");
    QDir::setCurrent (m_appDirPath);
    
    // accept dnd
    setAcceptDrops(true);

    // tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(m_view);

    text=m_view->getTextEdit();
    
    QDate qdate;
    currDate = qdate;
    todayD = qdate.currentDate ();
    
    browseTB = new KToolBar ((QWidget*)this, "Browsing Toolbar"); 
    browseTB->setToolButtonStyle(Qt::ToolButtonTextOnly);
    
    // then, setup our actions
    setupActions();
    
    slotToday();
    
    // add a status bar
    statusBar()->show();
    statusBar()->insertItem("",0);
    
    // a call to KXmlGuiWindow::setupGUI() populates the GUI
    // with actions, using KXMLGUI.
    // It also applies the saved mainwindow settings, if any, and ask the
    // mainwindow to automatically save settings if changed: window size,
    // toolbar position, icon size, etc.
    
    setupGUI(Default, "ktagebuchui.rc");
}

KTagebuch::~KTagebuch()
{
}

void KTagebuch::setupActions()
{  
    // File Menu
    //KStandardAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStandardAction::save (this, SLOT (save ()), actionCollection ());
    
    KAction* exportAction = new KAction(this);
    exportAction->setText(i18n ("Export Entry"));
    exportAction->setShortcut(KShortcut( Qt::CTRL + Qt::Key_E));
    actionCollection()->addAction("exportEntry",exportAction);
    connect(exportAction,SIGNAL(triggered()), this, SLOT (slotExportEntry()));
			
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());

    // Edit Menu
    KStandardAction::undo (this, SLOT (undo ()), actionCollection ());
    KStandardAction::redo (this, SLOT (redo ()), actionCollection ());
    KStandardAction::cut (this, SLOT (cut ()), actionCollection ());
    KStandardAction::copy (this, SLOT (copy ()), actionCollection ());
    KStandardAction::paste (this, SLOT (paste ()), actionCollection ());
    KStandardAction::selectAll (this, SLOT (selectAll ()), actionCollection ());

    KStandardAction::print (this, SLOT (slotPrint ()), actionCollection ());
    //TODOKStandardAction::find (this, SLOT (slotFind ()), actionCollection ());

    KAction *insertDateAction = new KAction (this);
    insertDateAction->setText(i18n ("Insert Date"));
    insertDateAction->setShortcut(KShortcut( Qt::CTRL + Qt::Key_D));
    actionCollection()->addAction("insertDate",insertDateAction);
    connect(insertDateAction, SIGNAL(triggered()), this, SLOT(slotInsertDate ()));

    KAction *insertTimeAction = new KAction(this);
    insertTimeAction->setText(i18n ("Insert Time"));
    insertTimeAction->setShortcut(KShortcut( Qt::CTRL + Qt::Key_T));
    actionCollection()->addAction("insertTime",insertTimeAction);
    connect(insertTimeAction,SIGNAL(triggered()),this,SLOT(slotInsertTime()));
    
    KAction *insertDateAndTimeAction = new KAction(this);
    insertDateAndTimeAction->setText(i18n ("Insert Date And Time"));
    insertDateAndTimeAction->setShortcut(KShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_D));
    actionCollection()->addAction("insertDateAndTime",insertDateAndTimeAction);
    connect(insertDateAndTimeAction,SIGNAL(triggered()),this,SLOT (slotInsertDateAndTime ()));
/*TODO    
    KAction *insertImageAction = new KAction(this);
    insertImageAction->setText("Insert &Image");
    insertImageAction->setShortcut(KShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_I));
    actionCollection()->addAction("insertImage",insertImageAction);
    connect(insertImageAction,SIGNAL(triggered()),this,SLOT(slotInsertImage()));
    
    KAction *insertHTMLAction = new KAction(this);
    insertHTMLAction->setText(i18n ("Insert HTML"));
    insertHTMLAction->setShortcut(KShortcut( Qt::CTRL + Qt::Key_H));
    actionCollection()->addAction("insertHTML",insertHTMLAction);
    connect(insertHTMLAction,SIGNAL(triggered()),this,SLOT(slotInsertHTML ()));
*/
    KAction *openSetupDlgAction = new KAction(this);			
    openSetupDlgAction->setText(i18n ("KTagebuch &Configuration"));
    /* TODO
    openSetupDlgAction->setIcon(QIcon (KIconLoader::global ()->
                                  loadIcon ("configure", KIcon::Small)));
				  */
    actionCollection()->addAction("openSetupDlg",openSetupDlgAction);
    connect(openSetupDlgAction,SIGNAL(triggered()),this,SLOT(slotOpenSetupDlg()));
    
    
    KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    // custom menu and menu item - the slot is in the class KTagebuchView
    KAction *custom = new KAction(KIcon("colorize"), i18n("Swi&tch Colors"), this);
    actionCollection()->addAction( QLatin1String("switch_action"), custom );
    connect(custom, SIGNAL(triggered(bool)), m_view, SLOT(switchColors()));

    actionFormatFontFamily = new KFontAction( i18n( "Font Family" ), this);
    actionCollection()->addAction("format_fontfamily",actionFormatFontFamily);
    connect( actionFormatFontFamily, SIGNAL( triggered( const QString & ) ),
             this, SLOT( setFont( const QString & ) ) );
    QFont f=Settings::font();
    
    actionFormatFontFamily->setFont (f.family ());

    actionFormatFontSize=new KFontSizeAction(i18n("Font Size"),this);
    connect (actionFormatFontSize, SIGNAL (triggered(int)), this, SLOT (setFontSize(int)));
    actionFormatFontSize->setEnabled( true );
    actionFormatFontSize->setFontSize(f.pointSize());
    actionCollection()->addAction("format_fontsize",actionFormatFontSize);
    
    actionFormatBold=new KToggleAction(i18n("&Bold"),this);
    actionFormatBold->setIcon(KIcon("format-text-bold"));
    actionFormatBold->setShortcut(KShortcut( Qt::CTRL + Qt::Key_B));
    actionCollection()->addAction("format_bold",actionFormatBold);
    connect (actionFormatBold, SIGNAL (toggled(bool)), this, SLOT (slotBold(bool)));
    
    actionFormatItalic =new KToggleAction(i18n("&Italic"),this);
    actionFormatItalic ->setIcon(KIcon("format-text-italic"));
    actionFormatItalic ->setShortcut(KShortcut( Qt::CTRL + Qt::Key_I));
    actionCollection()->addAction("format_italic",actionFormatItalic);
    connect (actionFormatItalic, SIGNAL (toggled(bool)), this, SLOT (slotItalic(bool)));
    				    
    actionFormatUnderline =new KToggleAction(i18n("&Underline"),this);
    actionFormatUnderline ->setIcon(KIcon("format-text-underline"));
    actionFormatUnderline ->setShortcut(KShortcut( Qt::CTRL + Qt::Key_U));
    actionCollection()->addAction("format_underline",actionFormatUnderline);
    connect (actionFormatUnderline, SIGNAL (toggled(bool)), this, SLOT (slotUnderline(bool)));
			    
    actionFormatAlignLeft =new KToggleAction(i18n("Align &Left"),this);
    actionFormatAlignLeft ->setIcon(KIcon("format-justify-left"));
    actionFormatAlignLeft ->setShortcut(KShortcut( Qt::CTRL + Qt::Key_L));
    actionCollection()->addAction("format_alignleft",actionFormatAlignLeft);
    actionFormatAlignLeft->setChecked( TRUE );
    connect (actionFormatAlignLeft, SIGNAL (toggled(bool)), this, SLOT (slotAlignLeft(bool)));
    
    actionFormatAlignCenter =new KToggleAction(i18n("Align &Center"),this);
    actionFormatAlignCenter ->setIcon(KIcon("format-justify-center"));
    actionFormatAlignCenter ->setShortcut(KShortcut( Qt::CTRL + Qt::Key_C));
    actionCollection()->addAction("format_aligncenter",actionFormatAlignCenter);
    connect (actionFormatAlignCenter, SIGNAL (toggled(bool)), this, SLOT (slotAlignCenter(bool)));
    
    actionFormatAlignRight =new KToggleAction(i18n("Align &Right"),this);
    actionFormatAlignRight ->setIcon(KIcon("format-justify-right"));
    actionFormatAlignRight ->setShortcut(KShortcut( Qt::CTRL + Qt::Key_R));
    actionCollection()->addAction("format_alignright",actionFormatAlignRight);
    connect (actionFormatAlignRight, SIGNAL (toggled(bool)), this, SLOT (slotAlignRight(bool)));
        
    actionFormatAlignBlock =new KToggleAction(i18n("Align &Block"),this);
    actionFormatAlignBlock ->setIcon(KIcon("format-justify-fill"));
    actionFormatAlignBlock ->setShortcut(KShortcut( Qt::CTRL + Qt::Key_J));
    actionCollection()->addAction("format_alignblock",actionFormatAlignBlock);
    connect (actionFormatAlignBlock, SIGNAL (toggled(bool)), this, SLOT (slotAlignBlock(bool)));
    

/*TODO
    actionFormatColor=new TKSelectColorAction( i18n( "Text Color..." ), TKSelectColorAction::TextColor,
                      this, SLOT( slotColor() ),actionCollection(), "format_color",true );
    actionFormatColor->setCurrentColor (QColor (m_editorGroup.readEntry ("fgColor", "#000000")));
*/
    
        
    KIconLoader kiconloader ("ktagebuch");
    
    KAction *firstEntryAction = new KAction(this);
    firstEntryAction->setText(i18n ("First Entry"));
    firstEntryAction->setIcon(KIcon("lastentry"));
    actionCollection()->addAction("firstEntry",firstEntryAction);
    connect(firstEntryAction,SIGNAL(triggered()),this,SLOT (slotFirstEntry()));
    
    KAction *yearBackAction = new KAction(this);
    yearBackAction->setText(i18n ("Year Back"));
    yearBackAction->setIcon(KIcon("yearback"));
    actionCollection()->addAction("yearBack",yearBackAction);
    connect(yearBackAction,SIGNAL(triggered()),this,SLOT (slotYearBack()));
    
    KAction *monthBackAction = new KAction(this);
    monthBackAction->setText(i18n ("Month Back"));
    monthBackAction->setIcon(KIcon("monthback"));
    actionCollection()->addAction("monthBack",monthBackAction);
    connect(monthBackAction,SIGNAL(triggered()),this,SLOT (slotMonthBack()));
            
    KAction *previousEntryAction = new KAction(this);
    previousEntryAction->setText(i18n ("Previous Entry"));
    previousEntryAction->setIcon(KIcon("previousentry"));
    actionCollection()->addAction("previousEntry",previousEntryAction);
    connect(previousEntryAction,SIGNAL(triggered()),this,SLOT (slotLastEntry()));
    
    KAction *dayBackAction = new KAction(this);
    dayBackAction->setText(i18n ("Day Back"));
    dayBackAction->setIcon(KIcon("dayback"));
    actionCollection()->addAction("dayBack",dayBackAction);
    connect(dayBackAction,SIGNAL(triggered()),this,SLOT (slotDayBack()));
    
    KAction *todayAction = new KAction(this);
    todayAction->setText(i18n ("Today"));
    todayAction->setIcon(KIcon("today"));
    actionCollection()->addAction("today",todayAction);
    connect(todayAction,SIGNAL(triggered()),this,SLOT (slotToday()));
    
    KAction *dayForwardAction = new KAction(this);
    dayForwardAction->setText(i18n ("Day Forward"));
    dayForwardAction->setIcon(KIcon("dayforward"));
    actionCollection()->addAction("dayForward",dayForwardAction);
    connect(dayForwardAction,SIGNAL(triggered()),this,SLOT (slotDayForward()));
    
    KAction *nextEntryAction = new KAction(this);
    nextEntryAction->setText(i18n ("Next Entry"));
    nextEntryAction->setIcon(KIcon("nextentry"));
    actionCollection()->addAction("nextEntry",nextEntryAction);
    connect(nextEntryAction,SIGNAL(triggered()),this,SLOT (slotNextEntry()));
    
    KAction *monthForwardAction = new KAction(this);
    monthForwardAction->setText(i18n ("Month Forward"));
    monthForwardAction->setIcon(KIcon("monthforward"));
    actionCollection()->addAction("monthForward",monthForwardAction);
    connect(monthForwardAction,SIGNAL(triggered()),this,SLOT (slotMonthForward()));
    
    KAction *yearForwardAction = new KAction(this);
    yearForwardAction->setText(i18n ("Year Forward"));
    yearForwardAction->setIcon(KIcon("yearforward"));
    actionCollection()->addAction("yearForward",yearForwardAction);
    connect(yearForwardAction,SIGNAL(triggered()),this,SLOT (slotYearForward()));
    
    KAction *lastEntryAction = new KAction(this);
    lastEntryAction->setText(i18n ("Last Entry"));
    lastEntryAction->setIcon(KIcon("newestentry"));
    actionCollection()->addAction("lastEntry",lastEntryAction);
    connect(lastEntryAction,SIGNAL(triggered()),this,SLOT (slotLastEntry()));
    
    KAction *datepickerAction = new KAction(this);
    datepickerAction->setText(i18n ("Select a date"));
    datepickerAction->setIcon(KIcon("office-calendar"));
    actionCollection()->addAction("datepicker",datepickerAction);
    connect(datepickerAction,SIGNAL(triggered()),this,SLOT (slotDatepicker()));            
    
    /*TODO if (m_editorGroup.readEntry("MenuBar").isEmpty())
        resize(800,600);
*/
    setAutoSaveSettings ();
/* TODO
    mLibraryLoader=new LibraryLoader();
    loadPlugins();
    mPluginsModule=new Plugins(this);
    mPluginsModule->reopen();*/
}

void KTagebuch::fileNew()
{
    // this slot is called whenever the File->New menu is selected,
    // the New shortcut is pressed (usually CTRL+N) or the New toolbar
    // button is clicked

    // create a new window
    (new KTagebuch)->show();
}

void KTagebuch::optionsPreferences()
{
    // The preference dialog is derived from prefs_base.ui
    //
    // compare the names of the widgets in the .ui file
    // to the names of the variables in the .kcfg file
    //avoid to have 2 dialogs shown
    if ( KConfigDialog::showDialog( "settings" ) )  {
        return;
    }    
    KConfigDialog *dialog = new KConfigDialog(this, "settings", Settings::self());
    QWidget *generalSettingsDlg = new QWidget;
    ui_prefs_base.setupUi(generalSettingsDlg);
    dialog->addPage(generalSettingsDlg, i18n("General"), "package_setting");
    
    /*
    QWidget *colorSettingsDlg = new QWidget;
    ui_prefs_colors.setupUi(colorSettingsDlg);
    dialog->addPage(colorSettingsDlg, i18n("Colors"), "package_setting");
    */
    
    QWidget *fontSettingsDlg = new QWidget;
    ui_prefs_font.setupUi(fontSettingsDlg);
    dialog->addPage(fontSettingsDlg, i18n("Font"), "package_setting");
    
    connect(dialog, SIGNAL(settingsChanged(const QString &)), m_view, SLOT(settingsChanged()));
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    dialog->show();
}


bool KTagebuch::printDialog () {
    return true;
}


bool KTagebuch::print () {
    return true;
}


void
KTagebuch::selectAll () {
    text->selectAll ();
}

void
KTagebuch::deselect () {
 //TODO   text->selectAll(false);
}

void
KTagebuch::undo () {
    text->undo ();
}

void
KTagebuch::redo () {
    text->redo ();
}

void
KTagebuch::cut () {
    text->cut ();
}


void
KTagebuch::copy () {
    text->copy ();
}

void
KTagebuch::paste () {
    text->paste ();
}


void
KTagebuch::toggleToolBar () {
    if (toolBar ()->isVisible ())
        toolBar ()->hide ();
    else
        toolBar ()->show ();
}

void
KTagebuch::toggleStatusBar () {
    if (statusBar ()->isVisible ())
        statusBar ()->hide ();
    else
        statusBar ()->show (); 
}

void
KTagebuch::saveOptions () {
  /* TODO prüfen
    text->selectAll (false);
    */
}

KTagebuch::saveResult KTagebuch::save () {
    QString dirname;
    getDate_Str (currDate, &dirname);
    
    if (m_fileSystem->saveEntry(dirname.toInt(),text->toHtml())) {        	
	text->document()->setModified (FALSE);
        emit saveEntry();
        return SAVE_OK;
    }
    return SAVE_CANCEL;
}

bool
KTagebuch::loadEntry (QDate qdate) {
    if (entryChanged () == SAVE_CANCEL)
        return false;
    QString dirname;
    currDate = qdate;
    getDate_Str (qdate, &dirname);
    QString entry= m_fileSystem->loadEntry(dirname.toInt());
    
    QFont font=Settings::font();
    
    m_view->settingsChanged();
    
    text->setTextColor(Settings::fg_color());
    text->setTextBackgroundColor(Settings::bg_color());
    text->setCurrentFont (font);
    
    if (entry!=0) {            	    
            text->setText (entry);            
            emit loadEntry();
    } else {
        QTime time;
        QString
        todayStr ((QString) todayD.toString () + " - " +
                  (time.currentTime ()).toString ());
        QTextStream t (&todayStr, QIODevice::ReadOnly);

        text->setText ("");
        text->insertHtml(t.readAll());
    }    

    text->document()->setModified(false);
    statusBar ()->changeItem(i18n (" "),0);    
    return true;
}

void
KTagebuch::getDate_Str (QDate qdate, QString * string) {
    int date;
    QString date_str;
    int day = qdate.day ();
    int month = qdate.month ();
    int year = qdate.year ();
    year = year * 10000;
    month = month * 100;
    date = year + month + day;
    string->setNum (date);
}

void
KTagebuch::getDate_QD (QDate * qdate, QString * string) {
    QString year = string->left (4);
    QString month = string->mid (4, 2);
    QString day = string->right (2);
    qdate->setYMD (atoi (year.toAscii()), atoi (month.toAscii()), atoi (day.toAscii()));
}

void
KTagebuch::slotPreviousEntry () {
    QDate qdate;
    QString todayC;
    getDate_Str (currDate, &todayC);
    
    QString lastEntry=m_fileSystem->getPreviousEntry(todayC.toInt());
    
    if (lastEntry!=0) {
	getDate_QD (&qdate, &lastEntry);
        setDate (qdate);
    } else {
       statusBar ()->changeItem(i18n ("This is the oldest entry!"),0);
    }
}

void
KTagebuch::slotNextEntry () {

    QDate qdate;
    QString todayC;
    getDate_Str (currDate, &todayC);

    QString nextEntry=m_fileSystem->getNextEntry(todayC.toInt());

    if (nextEntry!=0) {
	getDate_QD (&qdate, &nextEntry);
        setDate (qdate);
    } else {
        statusBar ()->changeItem(i18n ("This is the newest entry!"),0);
    }

}

KTagebuch::saveResult KTagebuch::entryChanged () {
    int
    query;
    
    if (text->document()->isModified ()) {
        if (!Settings::autosave()) {
            query = KMessageBox::warningYesNoCancel (this,
                    i18n
                    ("The current Document has been modified.\nWould you like to save it?"));
        } else {
            query = KMessageBox::Yes;
        }
        switch (query) {
        case KMessageBox::Yes:	//yes
            if (save () == SAVE_CANCEL)
                return SAVE_CANCEL;
            if (text->document()->isModified ()) {
                query = KMessageBox::warningContinueCancel (this,
                        i18n
                        ("Could not save the document.\nDiscard it and continue?"),
                        i18n ("&Discard"));
                if (query == KMessageBox::Cancel)
                    return SAVE_CANCEL;
            }
            break;
        case KMessageBox::Cancel:	//cancel
            return SAVE_CANCEL;
        case KMessageBox::No:
            return SAVE_NO;
        }
    }
    return SAVE_OK;
}

void
KTagebuch::slotToday () {
    setDate (todayD.currentDate ());
}

void
KTagebuch::slotFirstEntry () {    
    QString firstEntry=m_fileSystem->getFirstEntry();
    if(firstEntry==0)
	return;
    QDate qdate;
    getDate_QD (&qdate, &firstEntry);
    setDate (qdate);
}

void
KTagebuch::slotYearBack () {
    setDate (currDate.addYears (-1));
}

void
KTagebuch::slotMonthBack () {
    setDate (currDate.addMonths (-1));
}

void
KTagebuch::slotDayBack () {
    setDate (currDate.addDays (-1));
}

void
KTagebuch::slotDayForward () {
    setDate (currDate.addDays (1));
}

void
KTagebuch::slotMonthForward () {
    setDate (currDate.addMonths (1));
}

void
KTagebuch::slotYearForward () {
    setDate (currDate.addYears (1));
}

void
KTagebuch::slotLastEntry () {
    QString lastEntry = m_fileSystem->getLastEntry();
    if(lastEntry==0)return;
    QDate qdate;
    getDate_QD (&qdate, &lastEntry);
    setDate (qdate);
}

bool KTagebuch::queryClose () {
    if (entryChanged () == SAVE_CANCEL)
        return false;
    Settings::self()->writeConfig();
    KTagebuch().queryExit();
    return true;
}

/** opens a KDatepicker dialog */
void
KTagebuch::slotDatepicker () {
    DatepickerDlg *dpd = new DatepickerDlg (this);
    dpd->show ();    
}

/** No descriptions */
void
KTagebuch::setDate (QDate date) {

    if (loadEntry (date)) {
        currDate = date;
	m_view->setTabText(0,currDate.toString ());
    }
}

/** No descriptions */
void
KTagebuch::slotInsertDate () {
    text->insertPlainText(todayD.toString ());
}

/** No descriptions */
void
KTagebuch::slotInsertTime () {
    QTime time;
    time.currentTime ();
    text->insertPlainText ((time.currentTime ()).toString ());
}

/** No descriptions */
void
KTagebuch::slotInsertDateAndTime () {
    QTime time;
    
    text->insertPlainText(todayD.toString () + " - " +
                  (time.currentTime ()).toString ());		  
}

/** No descriptions */
void
KTagebuch::slotInsertHTML () {
 //TODO   new insertHtmlDlgImpl ();
}

/** No descriptions */
void
KTagebuch::slotOpenSetupDlg () {
    //TODO cdlg->show ();
}

/** No descriptions */
void
KTagebuch::slotBold (bool toggled) {
  QTextCharFormat format;
  if(toggled)
    format.setFontWeight(QFont::Bold);
  else
    format.setFontWeight(QFont::Normal);
  text->setCurrentCharFormat(format);   
}

/** No descriptions */
void
KTagebuch::slotUnderline (bool toggled) {
  QTextCharFormat format;
  format.setFontUnderline(toggled);
  
  text->setCurrentCharFormat(format);
}

/** No descriptions */
void
KTagebuch::slotItalic (bool toggled) {
  QTextCharFormat format;
  format.setFontItalic(toggled);
  
  text->setCurrentCharFormat(format);
}

/** No descriptions */
void
KTagebuch::slotAlignLeft(bool toggled) {
  text->setAlignment(Qt::AlignLeft);
  actionFormatAlignBlock->setChecked(false);
  actionFormatAlignCenter->setChecked(false);
  actionFormatAlignRight->setChecked(false);
}

/** No descriptions */
void
KTagebuch::slotAlignCenter(bool toggled) {
  text->setAlignment(Qt::AlignCenter);
  actionFormatAlignBlock->setChecked(false);
  actionFormatAlignLeft->setChecked(false);
  actionFormatAlignRight->setChecked(false);
}

/** No descriptions */
void
KTagebuch::slotAlignRight(bool toggled) {
  text->setAlignment(Qt::AlignRight);
  actionFormatAlignBlock->setChecked(false);
  actionFormatAlignCenter->setChecked(false);
  actionFormatAlignLeft->setChecked(false);
}

/** No descriptions */
void
KTagebuch::slotAlignBlock(bool toggled) {
  text->setAlignment(Qt::AlignJustify);
  actionFormatAlignRight->setChecked(false);
  actionFormatAlignCenter->setChecked(false);
  actionFormatAlignLeft->setChecked(false);
}

/** No descriptions */
void
KTagebuch::setFont (const QString &font) {
    int size=actionFormatFontSize->fontSize();
    QFont qFont(font);
    qFont.setPointSize(size);
    text->setCurrentFont (qFont);
    text->setFocus();
}

void KTagebuch::setFontSize(int size) {
    QFont font=text->font();
    font.setPointSize(size);
    text->setFont(font);
    text->setFocus();  
}

/** sets font and colors */
void
KTagebuch::applyConfig () {
    QFont font=Settings::font();
    text->setCurrentFont (Settings::font());
    actionFormatFontFamily->setFont(font.family());
    actionFormatFontSize->setFontSize(font.pointSize());
    //TODO actionFormatColor->setCurrentColor(QColor(config.readEntry ("fgColor", "#000000")));    
    
    text->setTextColor(Settings::fg_color());
    text->setTextBackgroundColor(Settings::bg_color());
   
    if (Settings::wrap()) {
      text->setWordWrapMode (QTextOption::WordWrap);
      text->setLineWrapColumnOrWidth(Settings::wrap_at());
    } else {
      text->setWordWrapMode(QTextOption::NoWrap);
    }  
}

/** No descriptions */
void
KTagebuch::slotPrint () {
  
    QPrinter printer;
    printer.setFullPage (true);
    QPrintDialog printDialog(&printer, this);
    printDialog.setWindowTitle(i18n("Print Dialog Title"));
    if (printDialog.exec()) {
        QPainter p (&printer);
        // Check that there is a valid device to print to.
        if (!p.device ())
            return;
        Q3PaintDeviceMetrics metrics (p.device ());
        int dpix = metrics.logicalDpiX ();
        int dpiy = metrics.logicalDpiY ();
        const int margin = 72;	// pt
        QRect body (margin * dpix / 72, margin * dpiy / 72,
                    metrics.width () - margin * dpix / 72 * 2,
                    metrics.height () - margin * dpiy / 72 * 2);
        QFont font ("times", 10);
	/* TODO
        Q3SimpleRichText richText (text->toHtml(), font, text->context (),
                                  text->styleSheet (),
                                  text->mimeSourceFactory (), body.height ());
        richText.setWidth (&p, body.width ());
        QRect view (body);
        int page = 1;
        do {
            richText.draw (&p, body.left (), body.top (), view, colorGroup ());
            view.moveBy (0, body.height ());
            p.translate (0, -body.height ());
            p.setFont (font);
            p.drawText (view.right () -
                        p.fontMetrics ().width (QString::number (page)),
                        view.bottom () + p.fontMetrics ().ascent () + 5,
                        QString::number (page));
            if (view.top () >= richText.height ())
                break;
            printer.newPage ();
            page++;
        } while (true);
	*/
    }    
}

/** No descriptions */
void
KTagebuch::slotFind () {
    /*
    FindDialog *fd = new FindDialog (this,m_fileSystem);
    fd->show ();  
    */
}

/** No descriptions */
void
KTagebuch::slotSpelling () {}

/** inserts image */
void
KTagebuch::slotInsertImage () {
/*TODO
    KUrl url =
        KFileDialog::getImageOpenUrl (QDir::homeDirPath (), this,
                                      i18n ("Select Image"));
    if (!url.isLocalFile ()) {
        KMessageBox::sorry (this,
                            i18n ("Currently only local images are possible."));
        return;
    }

    QString filename = url.path ();
    QFile in (filename);
    QFileInfo inFileInfo (filename);
    QString dateString;
    getDate_Str (currDate, &dateString);
    in.open (QIODevice::ReadOnly);
    int size = inFileInfo.size ();
    char *buffer = new char[size];
    in.readBlock (buffer, size);
    in.close ();
    if(m_fileSystem->storeFile(dateString.toInt(),filename,buffer,size))
    insertHTML("<img src=\""+filename+"\">");
    else KMessageBox::sorry (this,
                            i18n ("Image could not be inserted."));
    */
}

void
KTagebuch::insert (QString string) {
   text->insertHtml(string);
}

/** returns the date of the loaded entry */
QDate KTagebuch::today () {
    return currDate;
}

/** No descriptions */
void
KTagebuch::select (int para, int index, int length) {
//TODO    text->setSelection (para, index, para, index + length);
}

void KTagebuch::loadPlugins() {
    QStringList plugins;
    /*
    if (config.hasKey("Plugins"))
        plugins=config.readListEntry("Plugins");
    else {
        plugins.append("mood.plugin");
    }
    config.writeEntry("Plugins",plugins);
    mLibraryLoader->loadAll();
    */
}

void KTagebuch::insertHTML(QString HTMLtext) {
    int para,index;
    /*TODO
    QString textCp=text->text();
    text->getCursorPosition(&para,&index);
    int pos=0,j=-1;
    while(j++<para) {
        pos=textCp.find("<p",pos);
        pos++;
    }
    while (QChar(textCp[(pos++)])!=">")
        ;

    j=0;
    int i=0;

    while(j<index) {
        if (QChar(textCp[pos+j])=="<") {
            while(QChar(textCp[(pos++)+j])!=">") {
                i++;
            }
            i=0;
        } else {
            j++;
        }
    }

    textCp.insert(pos+j,HTMLtext);
    text->setText(textCp);
    text->setCursorPosition(para,index+1);
    text->setModified(true);
    */
}

void KTagebuch::slotColor() {
    //color of icon does not change if color is selected from color chooser
    /*TODO
    actionFormatColor->setCurrentColor(actionFormatColor->color() );
    text->setColor(actionFormatColor->color());
    text->setFocus();
    */
}

FileSystem* KTagebuch::getFileSystem(){
	return m_fileSystem;
}

/** called by text (QTextEdit) */
void KTagebuch::slotFontChanged(const QFont & f) {
    actionFormatFontSize->setFontSize(f.pointSize());
    actionFormatFontFamily->setFont (f.family ()); 
}

/** called by text (QTextEdit) */
void KTagebuch::slotColorChanged(const QColor & c) {
//TODO    actionFormatColor->setCurrentColor(c);
}

void KTagebuch::slotExportEntry() {
  /*
	KFileDialog exportDialog(QDir::homeDirPath (),"*.html" ,this,
                                      0,true);
	exportDialog.setCaption(i18n ("Save as"));
	exportDialog.setOperationMode   (   KFileDialog::Saving    );
	exportDialog.setSelection(currDate.toString("yyyyMMdd")+".html");
	exportDialog.exec();
	KUrl url = exportDialog.selectedURL();
    	m_fileSystem->exportEntry(currDate.toString("yyyyMMdd").toInt(),url.path());
	*/
}

    QString KTagebuch::getText() {
        return text->toHtml();
    }
    void KTagebuch::setText(QString _text) {
        text->setText(_text);
    }
#include "ktagebuch.moc"
