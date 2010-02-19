/****************************************************************************
** Form interface generated from reading ui file './inserthtmldialog.ui'
**
** Created: Mo Jun 6 22:21:56 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef INSERTHTMLDIALOG_H
#define INSERTHTMLDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTextEdit;
class QPushButton;

class InsertHTMLDialog : public QDialog
{
    Q_OBJECT

public:
    InsertHTMLDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~InsertHTMLDialog();

    QTextEdit* htmlcode;
    QPushButton* buttonOk;
    QPushButton* buttonApply;
    QPushButton* buttonCancel;

public slots:
    virtual void slotOk();
    virtual void slotClose();
    virtual void slotApply();

protected:
    QGridLayout* InsertHTMLDialogLayout;
    QVBoxLayout* layout5;
    QHBoxLayout* layout4;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // INSERTHTMLDIALOG_H
