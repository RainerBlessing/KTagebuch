/***************************************************************************
                          datepickerdlg.cpp  -  description
                             -------------------
    begin                : Son Mär 31 2002
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

#include "ui/datepickerdlg.h"
//#include "ui/datepickerdlg.moc"

DatepickerDlg::DatepickerDlg():

KDialogBase((QWidget*)ktagebuchapp,"title",true){  
  dateW= new KDatePicker(this);
  setMainWidget (dateW);
}
DatepickerDlg::~DatepickerDlg(){
}
/** No descriptions */
void DatepickerDlg::slotOk(){
  slotApply();
  close();
}

/** No descriptions */
void DatepickerDlg::slotApply(){
  ktagebuchapp->setDate(  dateW->date());
}
