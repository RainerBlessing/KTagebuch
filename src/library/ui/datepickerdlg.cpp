/***************************************************************************
                          datepickerdlg.cpp  -  description
                             -------------------
    begin                : Son Maerz 31 2002
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

#include "library/ui/datepickerdlg.h"

DatepickerDlg::DatepickerDlg(KTagebuch *ktagebuch):

KDialog((QWidget*)ktagebuch),m_ktagebuch(ktagebuch) {  
  setButtons( KDialog::Ok | KDialog::Cancel | KDialog::Apply );
  dateW= new KDatePicker(this);  

  setMainWidget (dateW);
  connect( this, SIGNAL( applyClicked() ), this, SLOT( slotApply() ) );
  connect( this, SIGNAL( okClicked() ), this, SLOT( slotOk() ) );
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
  m_ktagebuch->setDate(  dateW->date());
}
