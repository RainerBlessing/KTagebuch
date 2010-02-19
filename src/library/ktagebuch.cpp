/***************************************************************************
                          ktagebuch.cpp  -  description
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

#include "ktagebuch.h"
#include "ktagebuch.moc"
#include "ui/datepickerdlg.h"
#include "ui/ktagebuchconfigdialog.h"
#include "ui/finddialog.h"
#include "ui/insertHTML.h"
#include "../fs/filesystem.h"

#include <stdio.h>
#include <qregexp.h>
#include <kimageio.h>
#include <qglobal.h>
#include <tkcoloractions.h>
#include <pluginloader.h>
#include <ui/pluginmodule.h>

KTagebuch *ktagebuchapp;

KTagebuch::~KTagebuch () {
    delete fileSystem;
    delete mLibraryLoader;
}


KTagebuch::KTagebuch () {
    fileSystem=new FileSystem();
    config = kapp->config ();
    ktagebuchapp=this;
    cdlg = new KTagebuchConfigDialog ();
    cdlg->hide();
    appDir = KGlobal::dirs ()->saveLocation ("data", "ktagebuch");
    QDir::setCurrent (appDir.path ());
    KIconLoader kiconloader ("ktagebuch");
    QPixmap first = KGlobal::iconLoader ()->loadIcon ("lastentry", KIcon::Toolbar);
    QIconSet firstI (first);
    QPixmap previous = KGlobal::iconLoader ()->loadIcon ("previousentry", KIcon::Toolbar);
    QIconSet previousI (previous);
    QPixmap yearback = KGlobal::iconLoader ()->loadIcon ("yearback", KIcon::Toolbar);
    QIconSet yearbackI (yearback);
    QPixmap monthback = KGlobal::iconLoader ()->loadIcon ("monthback", KIcon::Toolbar);
    QIconSet monthbackI (monthback);
    QPixmap dayback = KGlobal::iconLoader ()->loadIcon ("dayback", KIcon::Toolbar);
    QIconSet daybackI (dayback);
    QPixmap dayforward = kiconloader.loadIcon ("dayforward", KIcon::Toolbar);
    QIconSet forwardI (dayforward);
    QPixmap today = kiconloader.loadIcon ("today", KIcon::Toolbar);
    QIconSet todayI (today);
    QPixmap nextentry = kiconloader.loadIcon ("nextentry", KIcon::Toolbar);
    QIconSet nextentryI (nextentry);
    QPixmap newestentry = kiconloader.loadIcon ("newestentry", KIcon::Toolbar);
    QIconSet newestentryI (newestentry);
    QPixmap monthforward = kiconloader.loadIcon ("monthforward", KIcon::Toolbar);
    QIconSet monthfowardI (monthforward);
    QPixmap yearforward = kiconloader.loadIcon ("yearforward", KIcon::Toolbar);
    QIconSet yearforwardI (yearforward);
    QPixmap datepicker = kiconloader.loadIcon ("date", KIcon::Toolbar);
    QIconSet datepickerI (datepicker);
    KStdAction::save (this, SLOT (save ()), actionCollection ());
    (void) new KAction (i18n ("Export Entry"),KShortcut( CTRL + Key_E), this, SLOT (slotExportEntry()),
                        actionCollection (), "exportEntry");
    KStdAction::quit (this, SLOT (queryClose ()), actionCollection ());

    // setup edit menu
    KStdAction::undo (this, SLOT (undo ()), actionCollection ());
    KStdAction::redo (this, SLOT (redo ()), actionCollection ());
    KStdAction::cut (this, SLOT (cut ()), actionCollection ());
    KStdAction::copy (this, SLOT (copy ()), actionCollection ());
    KStdAction::paste (this, SLOT (paste ()), actionCollection ());
    KStdAction::selectAll (this, SLOT (selectAll ()), actionCollection ());

    KStdAction::print (this, SLOT (slotPrint ()), actionCollection ());
    KStdAction::find (this, SLOT (slotFind ()), actionCollection ());

    //    KStdAction::spelling( this, SLOT (slotSpelling()),actionCollection());

    (void) new KAction (i18n ("Insert Date"),KShortcut( CTRL + Key_D), this, SLOT (slotInsertDate ()),
                        actionCollection (), "insertDate");
    (void) new KAction (i18n ("Insert Time"),KShortcut( CTRL + Key_T), this, SLOT (slotInsertTime ()),
                        actionCollection (), "insertTime");
    (void) new KAction (i18n ("Insert Date And Time"), KShortcut( CTRL + SHIFT + Key_D), this,
                        SLOT (slotInsertDateAndTime ()), actionCollection (),
                        "insertDateAndTime");
    (void) new KAction (i18n ("Insert &Image"), KShortcut( CTRL + SHIFT + Key_I), this,
                        SLOT (slotInsertImage ()), actionCollection (),
                        "insertImage");


    (void) new KAction (i18n ("Insert HTML"), KShortcut( CTRL + Key_H), this, SLOT (slotInsertHTML ()),
                        actionCollection (), "insertHTML");

    (void) new KAction (i18n ("KTagebuch &Configuration"),
                        QIconSet (KGlobal::iconLoader ()->
                                  loadIcon ("configure", KIcon::Small)),
                        KShortcut (), this, SLOT (slotOpenSetupDlg ()),
                        actionCollection (), "openSetupDlg");

    // setup Settings menu
    KStdAction::showToolbar (this, SLOT (toggleToolBar ()),
                             actionCollection ());
    KStdAction::showStatusbar (this, SLOT (toggleStatusBar ()),
                               actionCollection ());


    statusBar ()->message (i18n ("Ready!"));

    text = new KTextEdit ((QWidget*)this);
    text->setTextFormat (Qt::RichText);
    text->mimeSourceFactory ()->setFilePath (appDir.path ());
    connect (text,SIGNAL(currentFontChanged ( const QFont & )),this,SLOT(slotFontChanged(const QFont &)));
    connect (text,SIGNAL(currentColorChanged ( const QColor & )),this,SLOT(slotColorChanged(const QColor &)));
    if (config->readBoolEntry ("wrap")) {
        text->setWordWrap (QTextEdit::FixedColumnWidth);
    }
    setCentralWidget (text);

    actionFormatFontFamily = new KFontAction( i18n( "Font Family" ), 0,
                             actionCollection(), "format_fontfamily" );
    connect( actionFormatFontFamily, SIGNAL( activated( const QString & ) ),
             this, SLOT( setFont( const QString & ) ) );
    QFont f;
    if (config->readEntry ("font")) {
        f.fromString (config->readEntry ("font"));
    } else {
        f = QApplication::font ();
    }
    actionFormatFontFamily->setFont (f.family ());

    actionFormatFontSize=new KFontSizeAction(i18n("Font Size"),0,actionCollection(),"format_fontsize");
    connect (actionFormatFontSize, SIGNAL (fontSizeChanged(int)), this, SLOT (setFontSize(int)));
    actionFormatFontSize->setEnabled( true );
    actionFormatFontSize->setFontSize(f.pointSize());

    actionFormatBold=new KToggleAction(i18n("&Bold"),"text_bold",CTRL + Key_B,this,SLOT(slotBold()),
                                       actionCollection(),"format_bold");
    actionFormatBold->setEnabled(true);

    actionFormatItalic = new KToggleAction( i18n( "&Italic" ), "text_italic", CTRL + Key_I,
                                            this, SLOT( slotItalic() ),
                                            actionCollection(), "format_italic" );
    actionFormatUnderline = new KToggleAction( i18n( "&Underline" ), "text_under", CTRL + Key_U,
                            this, SLOT( slotUnderline() ),
                            actionCollection(), "format_underline" );
    actionFormatAlignLeft = new KToggleAction( i18n( "Align &Left" ), "text_left", CTRL + Key_L,
                            this, SLOT( slotLeft() ),
                            actionCollection(), "format_alignleft" );
    actionFormatAlignLeft->setExclusiveGroup( "align" );
    actionFormatAlignLeft->setChecked( TRUE );
    actionFormatAlignCenter = new KToggleAction( i18n( "Align &Center" ), "text_center", CTRL
                              + ALT + Key_C,
                              this, SLOT( slotCenter() ),
                              actionCollection(), "format_aligncenter" );
    actionFormatAlignCenter->setExclusiveGroup( "align" );
    actionFormatAlignRight = new KToggleAction( i18n( "Align &Right" ), "text_right", CTRL +
                             ALT + Key_R,
                             this, SLOT( slotRight() ),
                             actionCollection(), "format_alignright" );
    actionFormatAlignRight->setExclusiveGroup( "align" );
    actionFormatAlignBlock = new KToggleAction( i18n( "Align &Block" ), "text_block", CTRL +
                             Key_J,
                             this, SLOT( slotBlock() ),
                             actionCollection(), "format_alignblock" );
    actionFormatAlignBlock->setExclusiveGroup( "align" );

    actionFormatColor=new TKSelectColorAction( i18n( "Text Color..." ), TKSelectColorAction::TextColor,
                      this, SLOT( slotColor() ),actionCollection(), "format_color",true );
    actionFormatColor->setCurrentColor (QColor (config->readEntry ("fgColor", "#000000")));

    createGUI (locate ("data", "ktagebuch/ktagebuchui.rc"));

    KToolBar *browseTB = new KToolBar ((QWidget*)this, "Browsing Toolbar");

    QDate qdate;
    currDate = qdate;
    todayD = qdate.currentDate ();
    dateL = new QLabel (todayD.toString (), browseTB);
    browseTB->insertButton (first, 0, SIGNAL (clicked (int)), this,
                            SLOT (slotFirstEntry ()), true, "first entry");
    browseTB->insertButton (yearback, 1, SIGNAL (clicked (int)), this,
                            SLOT (slotYearBack ()), true, "last year");
    browseTB->insertButton (monthback, 2, SIGNAL (clicked (int)), this,
                            SLOT (slotMonthBack ()), true, "last month");
    browseTB->insertButton (previous, 3, SIGNAL (clicked (int)), this,
                            SLOT (slotLastEntry ()), true, "previous entry");
    browseTB->insertButton (dayback, 4, SIGNAL (clicked (int)), this,
                            SLOT (slotDayBack ()), true, "yesterday's entry");
    browseTB->insertButton (today, 5, SIGNAL (clicked (int)), this,
                            SLOT (slotToday ()), true, "today's entry");
    browseTB->insertButton (dayforward, 6, SIGNAL (clicked (int)), this,
                            SLOT (slotDayForward ()), true, "tomorrow's entry");
    browseTB->insertButton (nextentry, 7, SIGNAL (clicked (int)), this,
                            SLOT (slotNextEntry ()), true, "next entry");
    browseTB->insertButton (monthforward, 8, SIGNAL (clicked (int)), this,
                            SLOT (slotMonthForward ()), true, "next month");
    browseTB->insertButton (yearforward, 9, SIGNAL (clicked (int)), this,
                            SLOT (slotYearForward ()), true, "next year");
    browseTB->insertButton (newestentry, 10, SIGNAL (clicked (int)), this,
                            SLOT (slotNewestEntry ()), true, "newest entry");
    browseTB->insertButton (datepicker, 11, SIGNAL (clicked (int)), this,
                            SLOT (datepicker ()), true, "Select a date");
    browseTB->insertWidget (12, dateL->width (), dateL);
    slotToday ();
    browseTB->setBarPos (KToolBar::Bottom);
    browseTB->setFullSize ();

    if (config->readEntry("MenuBar").isEmpty())
        resize(640,400);

    setAutoSaveSettings ();

    mLibraryLoader=new LibraryLoader();
    loadPlugins();
    mPluginsModule=new Plugins(this);
    mPluginsModule->reopen();
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
    text->selectAll (false);
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
    text->selectAll (false);
}

KTagebuch::saveResult KTagebuch::save () {
    QString dirname;
    getDate_Str (currDate, &dirname);
    
    if (fileSystem->saveEntry(dirname.toInt(),text->text ())) {
        
        // files in the directory which are not needed get deleted
	
	/*
        int index = 0;
        QRegExp imgRE ("<img src=(.+) >");
        imgRE.setMinimal (TRUE);
        QStrList slImg;
        while ((index = sText.find (imgRE, index)) != -1) {
            slImg.append (imgRE.cap (1));
            index++;
        }
        QString dirname;
        getDate_Str (currDate, &dirname);
        QDir dirEntry (appDir.path () + "/" + dirname);
        dirEntry.setFilter (QDir::Files);
        const QFileInfoList *Flist = dirEntry.entryInfoList ();
        QFileInfoListIterator itFI (*Flist);
        QStrListIterator itIMG (slImg);
        QFileInfo *fi;
        QString img;
        QFileInfoList deleteFlist;
        int found;
        while ((fi = itFI.current ())) {
            found = 0;
            itIMG.toFirst ();
            while (img = itIMG.current ()) {
                if (img.find (fi->fileName ().data ()) != -1) {
                    found = 1;
                }
                ++itIMG;
            }
            if (found == 0 && QString::compare (fi->fileName ().data (), "entry") != 0) {
                dirEntry.remove (fi->fileName ().data ());
            }
            ++itFI;
        }
	*/
	text->setModified (FALSE);
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
    QString entry= fileSystem->loadEntry(dirname.toInt());
	
    config->setGroup ("Editor");
    QFont font;
    if (config->readEntry ("font")) {
        font.fromString (config->readEntry ("font"));
    } else {
        font = QApplication::font ();
    }
    if (entry!=0) {
            text->setColor (QColor (config->readEntry ("fgColor", "#000000")));
            text->
            setPaper (QBrush
                      (QColor (config->readEntry ("bgColor", "#ffffff"))));
            text->setText (entry);            
            emit loadEntry();
    } else {
        QTime time;
        QString
        todayStr ((QString) todayD.toString () + " - " +
                  (time.currentTime ()).toString ());
        QTextStream t (&todayStr, IO_ReadOnly);

        text->setText ("");
        text->setCurrentFont (font);
        text->setColor (QColor (config->readEntry ("fgColor", "#000000")));
        text->setPaper (QBrush (QColor (config->readEntry ("bgColor", "#ffffff"))));
        text->setTextFormat (Qt::RichText);
        text->insert (t.read ());
    }

    text->setModified (false);
    statusBar ()->message (i18n (" "));
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
    qdate->setYMD (atoi (year), atoi (month), atoi (day));
}

void
KTagebuch::slotLastEntry () {
    QDate qdate;
    QString todayC;
    getDate_Str (currDate, &todayC);
    
    QString lastEntry=fileSystem->getPreviousEntry(todayC.toInt());
    
    if (lastEntry!=0) {
	getDate_QD (&qdate, &lastEntry);
        setDate (qdate);
    } else {
        statusBar ()->message (i18n ("This is the oldest entry!"));
    }
}

void
KTagebuch::slotNextEntry () {

    QDate qdate;
    QString todayC;
    getDate_Str (currDate, &todayC);

    QString nextEntry=fileSystem->getNextEntry(todayC.toInt());

    if (nextEntry!=0) {
	getDate_QD (&qdate, &nextEntry);
        setDate (qdate);
    } else {
        statusBar ()->message (i18n ("This is the newest entry!"));
    }

}

KTagebuch::saveResult KTagebuch::entryChanged () {
    int
    query;

    if (text->isModified ()) {
        if (!config->readBoolEntry ("autosave")) {
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
            if (text->isModified ()) {
                query = KMessageBox::warningContinueCancel (this,
                        i18n
                        ("Could not save the document.\nDiscard it and continue?"),
                        QString::null,
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
    QString firstEntry=fileSystem->getFirstEntry();
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
KTagebuch::slotNewestEntry () {
    QString lastEntry = fileSystem->getLastEntry();
    if(lastEntry==0)return;
    QDate qdate;
    getDate_QD (&qdate, &lastEntry);
    setDate (qdate);
}

bool KTagebuch::queryClose () {
    if (entryChanged () == SAVE_CANCEL)
        return false;
    kapp->quit ();
    return true;
}

/** opens a KDatepicker dialog */
void
KTagebuch::datepicker () {
    DatepickerDlg *dpd = new DatepickerDlg ();
    dpd->show ();
}

/** No descriptions */
void
KTagebuch::setDate (QDate date) {

    if (loadEntry (date)) {
        currDate = date;
        dateL->setText (currDate.toString ());
    }
}

/** No descriptions */
void
KTagebuch::slotInsertDate () {
    text->insert (todayD.toString ());
}

/** No descriptions */
void
KTagebuch::slotInsertTime () {
    QTime time;
    time.currentTime ();
    text->insert ((time.currentTime ()).toString ());
}

/** No descriptions */
void
KTagebuch::slotInsertDateAndTime () {
    QTime time;
    text->insert (todayD.toString () + " - " +
                  (time.currentTime ()).toString ());
}

/** No descriptions */
void
KTagebuch::slotInsertHTML () {
    new insertHtmlDlgImpl ();
}

/** No descriptions */
void
KTagebuch::slotOpenSetupDlg () {

    cdlg->show ();
}

/** No descriptions */
KConfig *
KTagebuch::getConfig () {
    return config;
}

/** No descriptions */
void
KTagebuch::slotBold () {
    text->setBold (actionFormatBold->isChecked());
}

/** No descriptions */
void
KTagebuch::slotUnderline () {
    text->setUnderline (actionFormatUnderline->isChecked ());
}

/** No descriptions */
void
KTagebuch::slotItalic () {
    text->setItalic (actionFormatItalic->isChecked ());
}

/** No descriptions */
void
KTagebuch::setFont (const QString &font) {
    int fontSize=actionFormatFontSize->fontSize();
    text->setCurrentFont (QFont(font).family());
    text->setPointSize(fontSize);
    text->setFocus();
}

/** sets font and colors */
void
KTagebuch::applyConfig () {
    config->setGroup ("Editor");
    QFont font;
    font.fromString (config->readEntry ("font"));
    text->setCurrentFont (font);

    actionFormatFontFamily->setFont(font.family());
    actionFormatFontSize->setFontSize(font.pointSize());
    actionFormatColor->setCurrentColor(QColor(config->readEntry ("fgColor", "#000000")));
    text->setColor (QColor (config->readEntry ("fgColor", "#000000")));
    text->setPaper (QBrush (QColor (config->readEntry ("bgColor", "#ffffff"))));
    if (config->readBoolEntry ("wrap")) {
        text->setWordWrap (QTextEdit::FixedColumnWidth);
        text->setWrapColumnOrWidth (config->readNumEntry ("wrapAt"));
    } else {
        text->setWordWrap (QTextEdit::WidgetWidth);
    }
}

/** No descriptions */
void
KTagebuch::slotPrint () {
    KPrinter printer;
    printer.setFullPage (true);
    if (printer.setup (this)) {
        QPainter p (&printer);
        // Check that there is a valid device to print to.
        if (!p.device ())
            return;
        QPaintDeviceMetrics metrics (p.device ());
        int dpix = metrics.logicalDpiX ();
        int dpiy = metrics.logicalDpiY ();
        const int margin = 72;	// pt
        QRect body (margin * dpix / 72, margin * dpiy / 72,
                    metrics.width () - margin * dpix / 72 * 2,
                    metrics.height () - margin * dpiy / 72 * 2);
        QFont font ("times", 10);
        QSimpleRichText richText (text->text (), font, text->context (),
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
    }
}

/** No descriptions */
void
KTagebuch::slotFind () {
    FindDialog *fd = new FindDialog (fileSystem);
    fd->show ();
}

/** No descriptions */
void
KTagebuch::slotSpelling () {}

/** inserts image */
void
KTagebuch::slotInsertImage () {

    KURL url =
        KFileDialog::getImageOpenURL (QDir::homeDirPath (), this,
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
    in.open (IO_ReadOnly);
    int size = inFileInfo.size ();
    char *buffer = new char[size];
    in.readBlock (buffer, size);
    in.close ();
    if(fileSystem->storeFile(dateString.toInt(),filename,buffer,size))
    insertHTML("<img src=\""+filename+"\">");
    else KMessageBox::sorry (this,
                            i18n ("Image could not be inserted."));
}

/** text will be leftaligned */
void
KTagebuch::slotLeft () {
    if ( actionFormatAlignLeft->isChecked() ) {
        text->setAlignment (Qt::AlignLeft);
    } else
        actionFormatAlignLeft->setChecked( true );

}

/** text will be rightaligned */
void
KTagebuch::slotRight () {
    if ( actionFormatAlignRight->isChecked() ) {
        text->setAlignment (Qt::AlignRight);
    } else
        actionFormatAlignRight->setChecked( true );
}

/** text will be centered */
void
KTagebuch::slotCenter () {
    if ( actionFormatAlignCenter->isChecked() ) {
        text->setAlignment (Qt::AlignCenter);
    } else
        actionFormatAlignCenter->setChecked( true );
}

void KTagebuch::slotBlock() {
    if ( actionFormatAlignBlock->isChecked() ) {
        text->setAlignment (Qt::AlignJustify);
    } else
        actionFormatAlignBlock->setChecked( true );
}

void
KTagebuch::insert (QString string) {
    text->insert (string);
}

/** returns the date of the loaded entry */
QDate KTagebuch::today () {
    return currDate;
}

/** No descriptions */
void
KTagebuch::select (int para, int index, int length) {
    text->setSelection (para, index, para, index + length);
}

void KTagebuch::loadPlugins() {
    QStringList plugins;
    if (config->hasKey("Plugins"))
        plugins=config->readListEntry("Plugins");
    else {
        plugins.append("mood.plugin");
    }
    config->writeEntry("Plugins",plugins);
    mLibraryLoader->loadAll();
}

void KTagebuch::insertHTML(QString HTMLtext) {
    int para,index;
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
}

void KTagebuch::setFontSize(int size) {
    text->setPointSize(size);
    text->setFocus();
}

void KTagebuch::slotColor() {
    //color of icon does not change if color is selected from color chooser
    actionFormatColor->setCurrentColor(actionFormatColor->color() );
    text->setColor(actionFormatColor->color());
    text->setFocus();
}

FileSystem* KTagebuch::getFileSystem(){
	return fileSystem;
}

/** called by text (QTextEdit) */
void KTagebuch::slotFontChanged(const QFont & f) {
    actionFormatFontSize->setFontSize(f.pointSize());
    actionFormatFontFamily->setFont (f.family ());
}

/** called by text (QTextEdit) */
void KTagebuch::slotColorChanged(const QColor & c) {
    actionFormatColor->setCurrentColor(c);
}

void KTagebuch::slotExportEntry() {
	KFileDialog exportDialog(QDir::homeDirPath (),"*.html" ,this,
                                      0,true);
	exportDialog.setCaption(i18n ("Save as"));
	exportDialog.setOperationMode   (   KFileDialog::Saving    );
	exportDialog.setSelection(currDate.toString("yyyyMMdd")+".html");
	exportDialog.exec();
	KURL url = exportDialog.selectedURL();
    	fileSystem->exportEntry(currDate.toString("yyyyMMdd").toInt(),url.path());
}
