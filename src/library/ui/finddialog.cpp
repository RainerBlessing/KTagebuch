/***************************************************************************
			finddialog.cpp  -  description
			-------------------
begin                : Son Apr 23 2002
copyright            : (C) 2002 by Rainer Blessing
email                : 1@theblessing.net
***************************************************************************/

/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/
#include <qregexp.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <QVBoxLayout>
#include <QLabel>
#include <kguiitem.h>
#include <QTreeWidget>
#include <QGroupBox>
#include <QList>

#include "finddialog.h"
//#include "ui/finddialog.moc"
#include <kmessagebox.h>
#include "../../fs/filesystem.h"

FindDialog::FindDialog(KTagebuch* ktagebuchapp,FileSystem* fileSystem):

KDialog(ktagebuchapp){
  this->setCaption(i18n("Find"));
  this->setButtons(KDialog::User1|KDialog::User2);//TODO Default ,KDialog::User1
  this->setButtonGuiItem(KDialog::User1,KGuiItem(i18n("Find")));
  this->setButtonGuiItem(KDialog::User1,KGuiItem(i18n("Close")));
  ktagebuch=ktagebuchapp;
  this->fileSystem=fileSystem;
  QWidget *page = this;
  QVBoxLayout *topLayout = new QVBoxLayout( page);

m_treeWidget=new QTreeWidget(page);
m_treeWidget->setColumnCount(1);

QList<QTreeWidgetItem *> items;

dateList=fileSystem->getDates();

for ( QStringList::Iterator it = dateList->begin(); it != dateList->end(); ++it ) {
	
	QString year=(*it).left(4);
	QString month=(*it).mid(4,2);
	QString day=(*it).right(2);
	
	QList<QTreeWidgetItem *>::iterator i = items.begin();
	bool found=false;
	while( i != items.end()&&found==false){
	  if((*i)->text(0)==year){
	    found=true;
	  }
	}
	if(found==false)
	  items.append(new QTreeWidgetItem(m_treeWidget, QStringList(year)));
/*

	yearLV=(Q3CheckListItem*)m_treeWidget->firstChild();
	found=false;
	Q3CheckListItem* monthLV;
	while ( yearLV && !found){
		if ( (yearLV->text(0)).compare(year)==0 ){
			monthLV=(Q3CheckListItem*)yearLV->firstChild();
			while ( monthLV && !found){
				if ( (monthLV->text(0)).compare(month)==0 ){
					found=true;

				}else{
					monthLV=(Q3CheckListItem*)monthLV->nextSibling();
				}
			}
			if (!found){
				new Q3CheckListItem(yearLV,month,Q3CheckListItem::CheckBox);
			}
			found=true;
		}else{
			yearLV=(Q3CheckListItem*)yearLV->nextSibling();
		}
	}

	monthLV=(Q3CheckListItem*)yearLV->firstChild();
	found=false;
	while ( monthLV && !found){
		if ( (monthLV->text(0)).compare(month)==0 ){
			Q3CheckListItem* dayLV=(Q3CheckListItem*)monthLV->firstChild();
			while ( dayLV && !found){
				if ( (dayLV->text(0)).compare(day)==0 ){
					found=true;

				}else{
					dayLV=(Q3CheckListItem*)dayLV->nextSibling();
				}
			}
			if (!found){
				new Q3CheckListItem(monthLV,day,Q3CheckListItem::CheckBox);
			}
			found=true;
		}else{
			monthLV=(Q3CheckListItem*)monthLV->nextSibling();
		}
	}
*/
}
topLayout->addWidget( m_treeWidget );
QLabel* findLB=new QLabel(i18n("Find:"),page);
topLayout->addWidget(findLB);
findLE=new QLineEdit(page);
topLayout->addWidget(findLE);
QGroupBox *groupBox=new QGroupBox(i18n("Options"),page);
caseCB=new QCheckBox(i18n("Case &Sensitive"),groupBox);
backwCB=new QCheckBox(i18n("Find &Backwards"),groupBox);
connect (backwCB,SIGNAL (toggled(bool)),this,SLOT(slotBackw(bool)));

topLayout->addWidget(groupBox);
setMainWidget(m_treeWidget );
m_treeWidget->setRootIsDecorated(TRUE);

//m_treeWidget->setGeometry(10,10,210,210);
m_treeWidget->setAllColumnsShowFocus(true);
	
//topLayout->addStretch(10);
}

FindDialog::~FindDialog(){
	delete dateList;
}

/** No descriptions */
void FindDialog::slotFind(){
	QStringList entriesSL;
/*
	Q3CheckListItem* yearLV=(Q3CheckListItem*)m_treeWidget->firstChild();
	if (yearLV){
		Q3CheckListItem* monthLV;
		Q3CheckListItem* dayLV;
		while ( yearLV ){
			if ( yearLV->isOn()){
				entriesSL.append(yearLV->text());
			}else{
				monthLV=(Q3CheckListItem*)yearLV->firstChild();
				while ( monthLV){
					if ( monthLV->isOn()){
						entriesSL.append(yearLV->text()+monthLV->text());
					}else{
						dayLV=(Q3CheckListItem*)monthLV->firstChild();
						while ( dayLV){
							if ( dayLV->isOn()){
								entriesSL.append(yearLV->text()+monthLV->text()+dayLV->text());
							}
							dayLV=(Q3CheckListItem*)dayLV->nextSibling();
						}
					}
					monthLV=(Q3CheckListItem*)monthLV->nextSibling();
				}
			}
			yearLV=(Q3CheckListItem*)yearLV->nextSibling();
		}
	}


	for ( QStringList::Iterator it = entriesSL.begin(); it != entriesSL.end(); ++it ) {
		if ((*it).length()<8){
			QString start=*it;
			QString end=*it;
			uint length=8-(*it).length();
			for (uint i=0;i<length;i++){
				//(*it).append("?");
				start.append("0");
				end.append("9");
			}
			(*it)="between "+start+" and "+end;
		}
	}
	QStringList Flist2;
	QStringList* Flist;
	if (entriesSL.count()>0){		
		Flist=fileSystem->getDates(entriesSL.join(" or "));
	}else return;
	
	QStringList::Iterator it;
	if (!backwCB->isChecked()){
		if (currentDateSTR.isEmpty()){
			currentDateSTR=Flist->first();
		}
		*/
/*TODO
		it=Flist->find(currentDateSTR);
		while ( *it) {
			Flist2 << *it++;
		}
*/
/*	}else {
		if (currentDateSTR.isEmpty()){
			currentDateSTR=Flist->last();
		}*/
/*TODO		
		it=Flist->find(currentDateSTR);
		while ( *it) {
			Flist2 << *it--;
		}
*/
	/*}
	
	static int para=0;
	static int index=0;
	QString directory="";
	bool found=false;
	
	while (!Flist2.isEmpty() && !found){
		if (directory.isEmpty()){
			directory=Flist2.first();
			Flist2.erase(Flist2.at(0));
		}
		while (!directory.isEmpty() && !found) {
			Q3TextEdit text(fileSystem->loadEntry(directory.toInt()));
				if (index<text.length()&&text.find(findLE->text(),caseCB->isChecked(),false,true,&para,&index)){
					QString date=directory.right(8);
					int year=atoi(date.left(4));
					int month=atoi(date.mid(4,2));
					int day=atoi(date.right(2));
					ktagebuch->setDate(QDate(year,month,day));
					ktagebuch->select(para,index,(findLE->text()).length());
					found=true;
					index++;
				}else{
					para=index=0;
					directory="";
					if (Flist2.count()>1){
						currentDateSTR=*(Flist2.at(1));
					}else{
						currentDateSTR="";
						int bc=KMessageBox::warningContinueCancel (this,"End of search range reached.\nContinue from the beginning?",
								"Find -");
						if (bc==KMessageBox::Continue){
							slotFind();
						}
						return;

					}
				}
		}
	}
	delete Flist;
	*/
}

/** No descriptions */
void FindDialog::slotUser1(){
	slotFind();
}

/** No descriptions */
void FindDialog::slotUser2(){
	reject();
}

/** No descriptions */
void FindDialog::slotBackw(bool on){
	currentDateSTR="";
}
