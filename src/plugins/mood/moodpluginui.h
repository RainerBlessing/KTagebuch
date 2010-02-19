/****************************************************************************
** Form interface generated from reading ui file './moodpluginui.ui'
**
** Created: Mo Jun 6 22:23:23 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MOODPLUGINUI_H
#define MOODPLUGINUI_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QListBox;
class QListBoxItem;

class MoodPluginUI : public QWidget
{
    Q_OBJECT

public:
    MoodPluginUI( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~MoodPluginUI();

    QLabel* TextLabel2;
    QLabel* lbMoodCB;
    QLineEdit* LineEdit;
    QPushButton* pbAdd;
    QPushButton* pbDelete;
    QPushButton* pbUp;
    QPushButton* pbDown;
    QListBox* ListBox3;

public slots:
    virtual void pbDelete_clicked();
    virtual void pbAdd_clicked();
    virtual void ListBox3_clicked( QListBoxItem * );
    virtual void ListBox3_selectionChanged();
    virtual void pbDown_clicked();
    virtual void pbUp_clicked();
    virtual QStringList getMoods();

protected:
    QVBoxLayout* Layout2;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;

};

#endif // MOODPLUGINUI_H
