/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include <qstringlist.h>
#include "moodpluginui.h"
#include <qlistbox.h>
#include <qlineedit.h>

void MoodPluginUI::pbDelete_clicked()
{
    ListBox3->removeItem(ListBox3->currentItem());
}

void MoodPluginUI::pbAdd_clicked()
{
    if (LineEdit->text()){
	ListBox3->insertItem(LineEdit->text());
    }
}

void MoodPluginUI::ListBox3_clicked( QListBoxItem * )
{

}

void MoodPluginUI::ListBox3_selectionChanged()
{
    LineEdit->setText(ListBox3->currentText());
}

void MoodPluginUI::pbDown_clicked()
{
    int index=0;
    QString mood;
    index=ListBox3->currentItem();
    if (index>-1&&index<ListBox3->count()-1){
	mood=ListBox3->currentText();
	ListBox3->removeItem(index);
	ListBox3->insertItem(mood,++index);
	ListBox3->setSelected(index,true);
	ListBox3->centerCurrentItem();
    }
}

void MoodPluginUI::pbUp_clicked()
{
    int index=0;
    QString mood;
    index=ListBox3->currentItem();
    if (index>0){
	mood=ListBox3->currentText();
	ListBox3->removeItem(index);
	ListBox3->insertItem(mood,--index);
	ListBox3->setSelected(index,true);
	ListBox3->centerCurrentItem();
    }
    
}



QStringList MoodPluginUI::getMoods()
{
    QStringList moods;
    for (int i=0;i<ListBox3->count();i++){
	moods << ListBox3->text(i);
    }
    return moods;
}
