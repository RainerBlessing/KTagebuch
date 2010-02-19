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
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <kguiitem.h>
#include "ui/finddialog.h"
//#include "ui/finddialog.moc"
#include <kmessagebox.h>
#include "filesystem.h"

FindDialog::FindDialog(FileSystem* fileSystem):

KDialogBase(KDialogBase::Plain,i18n("Find"),KDialogBase::User1|KDialogBase::User2,User1, ktagebuchapp ,"find",true,false,KGuiItem(i18n("Find")),KGuiItem(i18n("Close")) ){
ktagebuch=ktagebuchapp;
this->fileSystem=fileSystem;
QWidget *page = this->plainPage();
QVBoxLayout *topLayout = new QVBoxLayout( page, 0, spacingHint() );
ListView=new QListView(page);
ListView->addColumn( i18n("Entries") );
ListView->setTreeStepSize(20);
dateList=fileSystem->getDates();

for ( QStringList::Iterator it = dateList->begin(); it != dateList->end(); ++it ) {
	
	QString year=(*it).left(4);
	QString month=(*it).mid(4,2);
	QString day=(*it).right(2);
	
	bool found=false;
	QCheckListItem* yearLV=(QCheckListItem*)ListView->firstChild();
	if (yearLV){
		while ( yearLV && !found){
			if ( (yearLV->text(0)).compare(year)==0 ){
				found=true;
			}else{
				yearLV=(QCheckListItem*)yearLV->nextSibling();
			}
		}
	}      
	if (!found){	 
		new QCheckListItem(ListView,year,QCheckListItem::CheckBox);
	}

	yearLV=(QCheckListItem*)ListView->firstChild();
	found=false;
	QCheckListItem* monthLV;
	while ( yearLV && !found){
		if ( (yearLV->text(0)).compare(year)==0 ){
			monthLV=(QCheckListItem*)yearLV->firstChild();
			while ( monthLV && !found){
				if ( (monthLV->text(0)).compare(month)==0 ){
					found=true;

				}else{
					monthLV=(QCheckListItem*)monthLV->nextSibling();
				}
			}
			if (!found){
				new QCheckListItem(yearLV,month,QCheckListItem::CheckBox);
			}
			found=true;
		}else{
			yearLV=(QCheckListItem*)yearLV->nextSibling();
		}
	}

	monthLV=(QCheckListItem*)yearLV->firstChild();
	found=false;
	while ( monthLV && !found){
		if ( (monthLV->text(0)).compare(month)==0 ){
			QCheckListItem* dayLV=(QCheckListItem*)monthLV->firstChild();
			while ( dayLV && !found){
				if ( (dayLV->text(0)).compare(day)==0 ){
					found=true;

				}else{
					dayLV=(QCheckListItem*)dayLV->nextSibling();
				}
			}
			if (!found){
				new QCheckListItem(monthLV,day,QCheckListItem::CheckBox);
			}
			found=true;
		}else{
			monthLV=(QCheckListItem*)monthLV->nextSibling();
		}
	}

}
topLayout->addWidget( ListView );
QLabel* findLB=new QLabel(i18n("Find:"),page);
topLayout->addWidget(findLB);
findLE=new QLineEdit(page);
topLayout->addWidget(findLE);
QButtonGroup* optionsBG=new QButtonGroup (2,QGroupBox::Horizontal,i18n("Options"),page);
caseCB=new QCheckBox(i18n("Case &Sensitive"),optionsBG);
backwCB=new QCheckBox(i18n("Find &Backwards"),optionsBG);
connect (backwCB,SIGNAL (toggled(bool)),this,SLOT(slotBackw(bool)));

topLayout->addWidget(optionsBG);
setMainWidget(page);
ListView->setRootIsDecorated(TRUE);

//ListView->setGeometry(10,10,210,210);
ListView->setAllColumnsShowFocus(true);
	
//topLayout->addStretch(10);
}

FindDialog::~FindDialog(){
	delete dateList;
}

/** No descriptions */
void FindDialog::slotFind(){
	QStringList entriesSL;

	QCheckListItem* yearLV=(QCheckListItem*)ListView->firstChild();
	if (yearLV){
		QCheckListItem* monthLV;
		QCheckListItem* dayLV;
		while ( yearLV ){
			if ( yearLV->isOn()){
				entriesSL.append(yearLV->text());
			}else{
				monthLV=(QCheckListItem*)yearLV->firstChild();
				while ( monthLV){
					if ( monthLV->isOn()){
						entriesSL.append(yearLV->text()+monthLV->text());
					}else{
						dayLV=(QCheckListItem*)monthLV->firstChild();
						while ( dayLV){
							if ( dayLV->isOn()){
								entriesSL.append(yearLV->text()+monthLV->text()+dayLV->text());
							}
							dayLV=(QCheckListItem*)dayLV->nextSibling();
						}
					}
					monthLV=(QCheckListItem*)monthLV->nextSibling();
				}
			}
			yearLV=(QCheckListItem*)yearLV->nextSibling();
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

		it=Flist->find(currentDateSTR);
		while ( *it) {
			Flist2 << *it++;
		}

	}else {
		if (currentDateSTR.isEmpty()){
			currentDateSTR=Flist->last();
		}
		it=Flist->find(currentDateSTR);
		while ( *it) {
			Flist2 << *it--;
		}

	}
	
	static int para=0; /* find */
	static int index=0; /* find */
	QString directory="";
	bool found=false;
	
	while (!Flist2.isEmpty() && !found){
		if (directory.isEmpty()){
			directory=Flist2.first();
			Flist2.erase(Flist2.at(0));
		}
		while (!directory.isEmpty() && !found) {
			QTextEdit text(fileSystem->loadEntry(directory.toInt()));
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
