/*
 * Kivio - Visual Modelling and Flowcharting
 * Copyright (C) 2000 theKompany.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#ifndef TKACTION_H
#define TKACTION_H

#include <kaction.h>
#include <qstringlist.h>

namespace TK {
  enum IconMode { IconOnly, IconAndText, TextOnly };
};

class TKToolBarButton;
class TKComboBox;

class TKAction : public KAction
{ Q_OBJECT
public:
  TKAction(QObject* parent, const char* name);
  ~TKAction();

  virtual int plug(QWidget* widget, int index = -1);

  TK::IconMode iconMode();

protected:
  virtual void initToolBarButton(TKToolBarButton*);

  QWidget* createLayout(QWidget* parent, QWidget* children);
  void updateLayout();
  virtual void updateLayout(QWidget*);

public slots:
  virtual void setIconMode(TK::IconMode);
  void setText(const QString&);
  void setIcon(const QString&);

private:
  TK::IconMode m_imode;
  class TKActionPrivate;
  TKActionPrivate *d;
};
/******************************************************************************/
class TKBaseSelectAction : public TKAction
{ Q_OBJECT
friend class TKSelectAction;
public:
  TKBaseSelectAction(QObject* parent, const char* name);
  ~TKBaseSelectAction();

  virtual int plug(QWidget* widget, int index = -1);

  int currentItem();
  bool isEditable();

  void activate(int);

protected:
  virtual void initComboBox(TKComboBox*);

public slots:
  virtual void setCurrentItem(int index);
  virtual void setEditable(bool);

protected slots:
  virtual void slotActivated(int);

signals:
  void activated(int);

private:
  int m_current;
  bool m_editable;
  class TKBaseSelectActionPrivate;
  TKBaseSelectActionPrivate *d;
};
/******************************************************************************/
class TKSelectAction : public TKBaseSelectAction
{ Q_OBJECT
public:
  TKSelectAction(QObject* parent, const char* name);
  ~TKSelectAction();

  QStringList items() const;

public slots:
  virtual void setItems(const QStringList& );
  virtual void setEditText(const QString&);
  virtual void clear();

protected:
  virtual void initComboBox(TKComboBox*);

protected slots:
  void slotActivated(const QString&);

signals:
  void activated(const QString&);

private:
  QStringList m_list;
  class TKSelectActionPrivate;
  TKSelectActionPrivate *d;
};
/******************************************************************************/
#endif
