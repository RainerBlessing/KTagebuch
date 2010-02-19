#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './inserthtmldialog.ui'
**
** Created: Mo Jun 6 22:22:23 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "inserthtmldialog.h"

#include <qvariant.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "./inserthtmldialog.ui.h"

/*
 *  Constructs a InsertHTMLDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
InsertHTMLDialog::InsertHTMLDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "InsertHTMLDialog" );
    setSizeGripEnabled( TRUE );
    InsertHTMLDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "InsertHTMLDialogLayout"); 

    layout5 = new QVBoxLayout( 0, 0, 6, "layout5"); 

    htmlcode = new QTextEdit( this, "htmlcode" );
    layout5->addWidget( htmlcode );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 
    Horizontal_Spacing2 = new QSpacerItem( 150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    layout4->addWidget( buttonOk );

    buttonApply = new QPushButton( this, "buttonApply" );
    buttonApply->setAutoDefault( TRUE );
    buttonApply->setDefault( TRUE );
    layout4->addWidget( buttonApply );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    layout4->addWidget( buttonCancel );
    layout5->addLayout( layout4 );

    InsertHTMLDialogLayout->addLayout( layout5, 0, 0 );
    languageChange();
    resize( QSize(487, 289).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( slotOk() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( slotClose() ) );
    connect( buttonApply, SIGNAL( clicked() ), this, SLOT( slotApply() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
InsertHTMLDialog::~InsertHTMLDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void InsertHTMLDialog::languageChange()
{
    setCaption( tr2i18n( "Insert HTML Code" ) );
    buttonOk->setText( tr2i18n( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonApply->setText( tr2i18n( "&Apply" ) );
    buttonApply->setAccel( QKeySequence( tr2i18n( "Alt+A" ) ) );
    buttonCancel->setText( tr2i18n( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}

#include "inserthtmldialog.moc"
