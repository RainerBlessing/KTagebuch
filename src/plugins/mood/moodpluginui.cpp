#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './moodpluginui.ui'
**
** Created: Mo Jun 6 22:23:34 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "moodpluginui.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlistbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "./moodpluginui.ui.h"
static const char* const img0_moodpluginui[] = { 
"16 16 90 2",
"Qt c None",
".H c #000000",
"#x c #1d7ddc",
"#w c #1d7edd",
"#s c #1e73c6",
"#v c #1e73c7",
"#t c #2487e9",
"#l c #267ace",
"#q c #2794ff",
"#d c #2c7bc9",
"#p c #2c8ef0",
"#m c #2d92f6",
".5 c #337cc5",
"#h c #3593f0",
"#e c #3696f6",
"#r c #3c9dfb",
".V c #3d84cb",
"#i c #3d9fff",
".6 c #3e97ef",
"#. c #3e98f1",
".Z c #4a9ff5",
"#u c #4ca4f9",
".P c #4f9ce8",
".B c #5188bf",
"#k c #52a6f9",
"#c c #55a8fa",
".4 c #59abfb",
".G c #5ea8f4",
".U c #5eaefd",
"## c #60afff",
"#n c #63adf5",
"#f c #63aff7",
".u c #64a0db",
".7 c #65b0fa",
".A c #66acf2",
".W c #6ab3fb",
".t c #6fb0f1",
".n c #74b0ed",
".m c #77b4f3",
".M c #7cbcfb",
".h c #7db8f5",
".0 c #7fbfff",
".g c #84c2ff",
".O c #90c5f9",
".Q c #95caff",
".F c #a0cefb",
".b c #a4d1ff",
"#j c #a7cbe9",
"#o c #abcde8",
".e c #add6ff",
".I c #b0d8ff",
".z c #b1d7fc",
".p c #b1d7ff",
"#a c #b2d1e9",
".c c #b2d8ff",
".j c #b5d9ff",
".9 c #b8d5ed",
".C c #b8dbff",
".w c #bbddff",
".1 c #c0d9ed",
".Y c #c1daf0",
".s c #c1dffe",
".J c #c2def7",
"#b c #c7dae6",
".3 c #caddea",
".f c #cbe5ff",
"#g c #ccdce5",
".R c #cde0f0",
".l c #cde5ff",
".T c #cfe0ee",
".d c #cfe7ff",
".D c #d0e5f9",
".8 c #d1e0e9",
".L c #d3e4f2",
".2 c #d6e2e8",
".i c #d6ebff",
".X c #d7e4ed",
".o c #d9ecff",
".x c #daebfb",
".N c #dce8f1",
".v c #dcedff",
".S c #dee7ec",
".q c #e3f1fe",
".a c #e5f2ff",
".K c #e6edf0",
".k c #e9f4ff",
".E c #edf2f5",
".y c #f5f8f9",
".r c #fbfcfd",
".# c #ffffff",
"QtQtQtQtQt.#.#.#.#QtQtQtQtQtQtQt",
"QtQtQtQt.#.#.a.b.cQtQtQtQtQtQtQt",
"QtQtQt.#.#.d.e.f.g.hQtQtQtQtQtQt",
"QtQt.#.#.i.j.k.#.l.m.nQtQtQtQtQt",
"Qt.#.#.o.p.q.r.r.r.s.t.uQtQtQtQt",
".#.#.v.w.x.y.y.y.y.y.z.A.BQtQtQt",
".#.a.C.D.E.E.E.E.E.E.E.F.G.HQtQt",
".#.I.J.K.K.K.L.M.N.K.K.K.O.P.HQt",
".#.Q.R.S.S.T.U.V.W.X.S.S.Y.Z.HQt",
".#.0.1.2.3.4.5.H.6.7.8.2.9#..HQt",
".####a#b#c#d.H.H.H#e#f#g#a#h.HQt",
".##i#j#k#l.H.H.H.#.H#m#n#o#p.HQt",
".##q#r#s.H.H.HQt.#.#.H#t#u#v.HQt",
".#Qt#w.H.H.HQtQtQt.#Qt.H#x.H.HQt",
"QtQt.H.H.HQtQtQtQtQtQtQt.H.H.HQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};

static const char* const img1_moodpluginui[] = { 
"16 16 94 2",
".# c None",
".f c #000000",
"#f c #0b1a29",
"#B c #0c345c",
"#m c #133557",
"#y c #15508a",
"#t c #164676",
"#z c #1b72c8",
"#A c #1f84e8",
"#u c #268ff6",
"#s c #277cd2",
"#x c #2995ff",
"#l c #2d7fcf",
"#n c #2d90f4",
"#v c #2d97fe",
"#o c #3399fe",
"#g c #3594f2",
"#e c #3683d0",
"#h c #3a9dff",
"#. c #3f88d1",
"#a c #3f9af4",
".4 c #407dbb",
"## c #52a4f5",
".6 c #59a9f7",
".W c #5ca6f0",
".M c #66abf1",
".G c #68aef5",
".A c #70b2f4",
".v c #70b3f5",
".R c #72b8fe",
"#w c #77b6f1",
".m c #7ab8f8",
".q c #7bb9fa",
".i c #7fbcfa",
".F c #81bffe",
".X c #83c1ff",
"#d c #8dc2f3",
"#k c #8ec1f0",
".9 c #8ec3f7",
".u c #8ec6ff",
"#r c #8fc1ed",
".N c #8fc6ff",
".3 c #90c5f9",
".S c #96c8fb",
".1 c #96c9fb",
".e c #9acbfc",
"#i c #a0c9ed",
"#b c #a0caf0",
".5 c #a1d0ff",
"#p c #a2c9ea",
".b c #a2d0ff",
".B c #a2d1ff",
".7 c #a4cdf4",
".h c #a5d2ff",
".l c #a6d2ff",
".d c #a8d3ff",
".Y c #abd2f7",
".r c #acd6ff",
".j c #add5ff",
".T c #aed5fd",
".g c #b6daff",
".c c #b9dcff",
".I c #badcff",
".a c #bbddff",
".J c #bcdcfe",
".n c #bcddff",
".o c #bdddff",
".x c #c0dffe",
".w c #c1e0ff",
"#q c #ccdbe2",
"#j c #d0dee4",
".V c #d1e5f7",
".0 c #d5e5f2",
"#c c #d6e2e8",
".O c #d9e9f7",
".L c #daebfa",
".8 c #dee7ec",
".Q c #deebf6",
".2 c #e0eaf1",
".z c #e0effd",
".p c #e3f1ff",
".C c #e4f0fa",
".Z c #e6edf0",
".U c #e9f0f5",
".k c #e9f4ff",
".E c #eaf2f9",
".s c #eaf4fd",
".P c #edf2f5",
".K c #f2f7f9",
".t c #f4f9fd",
".D c #f5f8f9",
".y c #f8fbfd",
".H c #fbfbfb",
"Qt c #ffffff",
"QtQtQtQt.#.#.#.#.#.#QtQtQtQt.#.#",
"QtQt.aQtQt.#.#.#.#QtQtQt.bQt.#.#",
"Qt.c.d.e.f.#.#.#QtQtQt.g.h.i.f.#",
"Qt.j.k.l.m.f.#QtQtQt.n.o.p.q.f.#",
"Qt.r.s.t.u.v.fQtQt.w.x.y.z.A.f.#",
"Qt.B.C.D.E.F.G.H.I.J.K.D.L.M.f.#",
"Qt.N.O.P.P.Q.R.S.T.U.P.P.V.W.f.#",
"Qt.X.Y.Z.Z.Z.0.1.2.Z.Z.Z.3.4.f.#",
"Qt.5.6.7.8.8.8.8.8.8.8.9#..f.f.#",
"QtQt###a#b#c#c#c#c#c#d#e#f.f.f.#",
".#QtQt#g#h#i#j#j#j#k#l#m.f.f.#.#",
".#.#QtQt#n#o#p#q#r#s#t.f.f.#.#.#",
".#.#.#QtQt#u#v#w#x#y.f.f.#.#.#.#",
".#.#.#.#Qt.##z#A#B.f.f.#.#.#.#.#",
".#.#.#.#.#.#.#.f.f.f.#.#.#.#.#.#",
".#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#"};


/*
 *  Constructs a MoodPluginUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
MoodPluginUI::MoodPluginUI( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl ),
      image0( (const char **) img0_moodpluginui ),
      image1( (const char **) img1_moodpluginui )
{
    if ( !name )
	setName( "MoodPluginUI" );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 20, 90, 180, 20 ) );

    lbMoodCB = new QLabel( this, "lbMoodCB" );
    lbMoodCB->setGeometry( QRect( 20, 20, 150, 20 ) );

    LineEdit = new QLineEdit( this, "LineEdit" );
    LineEdit->setGeometry( QRect( 20, 50, 290, 22 ) );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout2" );
    privateLayoutWidget->setGeometry( QRect( 330, 50, 82, 130 ) );
    Layout2 = new QVBoxLayout( privateLayoutWidget, 0, 6, "Layout2"); 

    pbAdd = new QPushButton( privateLayoutWidget, "pbAdd" );
    Layout2->addWidget( pbAdd );

    pbDelete = new QPushButton( privateLayoutWidget, "pbDelete" );
    Layout2->addWidget( pbDelete );

    pbUp = new QPushButton( privateLayoutWidget, "pbUp" );
    pbUp->setPixmap( image0 );
    Layout2->addWidget( pbUp );

    pbDown = new QPushButton( privateLayoutWidget, "pbDown" );
    pbDown->setPixmap( image1 );
    Layout2->addWidget( pbDown );

    ListBox3 = new QListBox( this, "ListBox3" );
    ListBox3->setGeometry( QRect( 20, 120, 290, 280 ) );
    ListBox3->setResizePolicy( QListBox::Manual );
    languageChange();
    resize( QSize(441, 330).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( pbDelete, SIGNAL( clicked() ), this, SLOT( pbDelete_clicked() ) );
    connect( pbAdd, SIGNAL( clicked() ), this, SLOT( pbAdd_clicked() ) );
    connect( ListBox3, SIGNAL( selectionChanged() ), this, SLOT( ListBox3_selectionChanged() ) );
    connect( pbDown, SIGNAL( clicked() ), this, SLOT( pbDown_clicked() ) );
    connect( pbUp, SIGNAL( clicked() ), this, SLOT( pbUp_clicked() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
MoodPluginUI::~MoodPluginUI()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MoodPluginUI::languageChange()
{
    setCaption( tr2i18n( "Form1" ) );
    QToolTip::add( this, QString::null );
    TextLabel2->setText( tr2i18n( "Available Moods" ) );
    lbMoodCB->setText( tr2i18n( "Edit Mood:" ) );
    pbAdd->setText( tr2i18n( "Add" ) );
    pbDelete->setText( tr2i18n( "Delete" ) );
    pbUp->setText( QString::null );
    QToolTip::add( pbUp, tr2i18n( "move mood up" ) );
    pbDown->setText( QString::null );
    QToolTip::add( pbDown, tr2i18n( "move down mood" ) );
    ListBox3->clear();
    ListBox3->insertItem( tr2i18n( "No mood" ) );
    ListBox3->insertItem( tr2i18n( "amused" ) );
    ListBox3->insertItem( tr2i18n( "ecstatic" ) );
    ListBox3->insertItem( tr2i18n( "excited" ) );
    ListBox3->insertItem( tr2i18n( "joyful" ) );
    ListBox3->insertItem( tr2i18n( "tired" ) );
    ListBox3->insertItem( tr2i18n( "sad" ) );
    ListBox3->insertItem( tr2i18n( "annoyed" ) );
    ListBox3->insertItem( tr2i18n( "angry" ) );
    ListBox3->insertItem( tr2i18n( "bored" ) );
    ListBox3->insertItem( tr2i18n( "depressed" ) );
    ListBox3->insertItem( tr2i18n( "disappointed" ) );
    ListBox3->insertItem( tr2i18n( "lonely" ) );
}

#include "moodpluginui.moc"
