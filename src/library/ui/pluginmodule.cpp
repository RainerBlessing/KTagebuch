/*
    pluginmodule.cpp  -  Kopete Plugin Module

    Copyright (c) 2002 Rainer Blessing
    
    This class is based on the Kopete class of the same name:
    Copyright (c) 2000-2001 Charles Samuels        <charles@kde.org>
    Copyright (c) 2000-2001 Neil Stevens           <neil@qualityassistant.com>
    Copyright (c) 2001-2002 Duncan Mac-Vicar Prett <duncan@kde.org>

    *************************************************************************
    *                                                                       *
    * This program is free software; you can redistribute it and/or modify  *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    *                                                                       *
    *************************************************************************
*/

#include <kdialog.h>
#include <kiconloader.h>
#include <kglobal.h>
#include <klocale.h>
#include <ktabctl.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlayout.h>
#include "ui/ktagebuchlistview.h"
#include <qwhatsthis.h>
#include "ktagebuch.h"
#include "ui/pluginmodule.h"

PluginListItem::PluginListItem(const bool _exclusive, bool _checked, const KTagebuchLibraryInfo &_info, QListView *_parent)
	: QCheckListItem(_parent, _info.name, CheckBox)
	, mInfo(_info)
	, silentStateChange(false)
	, exclusive(_exclusive)
{
	setChecked(_checked);
	if( _checked )
		static_cast<PluginListView *>( listView() )->m_count++;
}


void PluginListItem::setChecked(bool b)
{
	silentStateChange = true;
	setOn(b);
	silentStateChange = false;
}

void PluginListItem::stateChange(bool b)
{
	if(!silentStateChange)
		static_cast<PluginListView *>(listView())->stateChanged(this, b);
}

void PluginListItem::paintCell(QPainter *p, const QColorGroup &cg, int a, int b, int c)
{
	QCheckListItem::paintCell(p, cg, a, b, c);	
}

PluginListView::PluginListView( QWidget *parent, const char *name )
: KListView( parent, name )
{
	m_count = 0;

	addColumn( i18n( "Name" ) );
	addColumn( i18n( "Description" ) );
	addColumn( i18n( "Author" ) );
	addColumn( i18n( "License" ) );
}

void PluginListView::clear()
{
	m_count = 0;
	KListView::clear();
}

void PluginListView::stateChanged( PluginListItem *item, bool b )
{
	if( b )
	{
		m_count++;
		emit stateChange( item, b );
	}
	else
	{
		if( !m_count )
		{
			item->setChecked( true );
		}
		else
		{
			m_count--;
			emit stateChange( item, b );
		}
	}
}

Plugins::Plugins( QObject *_parent )
: ConfigModule( i18n( "Plugins" ), i18n( "Choose Your Plugins" ),
	"input_devices_settings", _parent )
{
	//( new QVBoxLayout( this ) )->setAutoAdd( true );
	//KTabCtl *tabControl = new KTabCtl( this );
	
	//QFrame *otherTab = new QFrame( tabControl );
	/*( new QVBoxLayout( protocolTab, KDialog::marginHint(),
		KDialog::spacingHint() ) )->setAutoAdd( true );
	( void ) new QLabel( i18n( "<b>Choose protocol plugins to use:</b>" ),
		protocolTab );
	*/
	//protocolList = new PluginListView( protocolTab );
	
	/*connect( protocolList, SIGNAL( stateChange( PluginListItem *, bool ) ),
		this, SLOT( stateChange( PluginListItem *, bool ) ) );
	*/

	
	( new QVBoxLayout(this, KDialog::marginHint(),
		KDialog::spacingHint() ) )->setAutoAdd( true );
	//( void ) new QLabel( i18n( "<b>Choose plugins to use</b>" ), otherTab );

	otherList = new PluginListView( this );
	connect(otherList, SIGNAL(stateChange(PluginListItem *, bool)), this, SLOT(stateChange(PluginListItem *, bool)));
	//tabControl->addTab(otherTab, i18n("Other Plugins"));
	
	name="plugin";	
}

void Plugins::reopen()
{	
	otherList->clear();

	QValueList<KTagebuchLibraryInfo> available = ktagebuchapp->libraryLoader()->available();
	QValueList<KTagebuchLibraryInfo> loaded = ktagebuchapp->libraryLoader()->loaded();

	for(QValueList<KTagebuchLibraryInfo>::Iterator i = available.begin(); i != available.end(); ++i)
	{
		PluginListView *parent;
		bool exclusive = false;

			parent = otherList;
		
		if(parent)
		{
			PluginListItem *item = new PluginListItem(exclusive, loaded.contains(*i), *i, parent);
			item->setText(0, (*i).name);
			item->setText(1, (*i).comment);
			item->setText(2, (*i).author);
			item->setText(3, (*i).license);
		}
	}
}

void Plugins::stateChange(PluginListItem *item, bool b)
{
	if(b)
		addPlugin(item->info());
	else
		removePlugin(item->info());	
}

void Plugins::addPlugin(const KTagebuchLibraryInfo &info)
{
	// Load any that this one depends upon
	for(QStringList::ConstIterator i = info.require.begin(); i != info.require.end(); ++i)
	{
		KTagebuchLibraryInfo requiredInfo = ktagebuchapp->libraryLoader()->getInfo(*i);
	}

	if(mDeleted.contains(info.specfile))
		mDeleted.remove(info.specfile);
	else if(!mAdded.contains(info.specfile))
		mAdded.append(info.specfile);
}

void Plugins::removePlugin(const KTagebuchLibraryInfo &info)
{
	LibraryLoader &loader = *(ktagebuchapp->libraryLoader());

	// Here are the ones loaded
	QValueList<KTagebuchLibraryInfo> loaded = ktagebuchapp->libraryLoader()->loaded();
	
	// Add the ones marked for loading
	for(QStringList::ConstIterator i = mAdded.begin(); i != mAdded.end(); ++i)
		loaded.append(loader.getInfo(*i));

	// Subtract the ones marked for removal
	for(QStringList::ConstIterator i = mDeleted.begin(); i != mDeleted.end(); ++i)
		loaded.remove(loader.getInfo(*i));
	
	if (mAdded.contains(info.specfile))
		mAdded.remove(info.specfile);
	else if(!mDeleted.contains(info.specfile))
		mDeleted.append(info.specfile);


}

void Plugins::save()
{
	LibraryLoader &loader = *(ktagebuchapp->libraryLoader());
		
	// Load the plugins the user added
	for(QStringList::Iterator i = mAdded.begin(); i != mAdded.end(); ++i)
		loader.add(*i);

	// Remove the plugins the user removed
	for (QStringList::Iterator i = mDeleted.begin(); i != mDeleted.end(); ++i)
		loader.remove(*i);

	// Round up the ones that weren't loaded right now, for saving in the configuration
	QStringList specList(mAdded);

	QValueList<KTagebuchLibraryInfo> loaded = loader.loaded();
	for(QValueList<KTagebuchLibraryInfo>::Iterator i = loaded.begin(); i != loaded.end(); ++i)
		if(!specList.contains((*i).specfile) && loader.isLoaded((*i).specfile))
				specList += (*i).specfile;

	// Now we actually save
	loader.setModules(specList);

	mDeleted.clear();
	mAdded.clear();
}

//#include "pluginmodule.moc"

// vim: set noet ts=4 sts=4 sw=4:

