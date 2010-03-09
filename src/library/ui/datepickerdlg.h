/***************************************************************************
                          datepickerdlg.h  -  description
                             -------------------
    begin                : Son March 31 2002
    copyright            : (C) 2002 by Rainer Blessing
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

#ifndef DATEPICKERDLG_H
#define DATEPICKERDLG_H

#include <kdialog.h>
#include <kdatepicker.h>
#include "ktagebuch.h"

extern KTagebuch *ktagebuchapp;

class DatepickerDlg : public KDialog {

Q_OBJECT
public:
	DatepickerDlg(KTagebuch *ktagebuch);
	~DatepickerDlg();
private:
  KDatePicker *dateW;
  KTagebuch *m_ktagebuch;
private slots: // Private slots
  /** No descriptions */
  void slotOk();
  /** No descriptions */
  void slotApply();
};

#endif
