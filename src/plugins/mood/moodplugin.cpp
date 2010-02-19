#include <kgenericfactory.h>
#include <kstandarddirs.h>
#include <qregexp.h>
#include <qcolor.h>
#include <qlabel.h>
#include <ktoolbar.h>
#include <kcombobox.h>
#include <kconfig.h>

#include "ktagebuch.h"
#include "filesystem.h"
#include "moodplugin.h"
#include "moodpluginui.h"
#include "moodprefs.h"

K_EXPORT_COMPONENT_FACTORY( ktagebuch_mood, KGenericFactory<MoodPlugin> );

MoodPlugin::MoodPlugin( QObject *parent, const char *name,
			      const QStringList &/*args*/ )
	: ktagebuchPlugin( parent, name )
{
	
	connect( ktagebuchapp, SIGNAL(saveEntry()),
		 SLOT(saveEntry()) );
	connect( ktagebuchapp, SIGNAL(loadEntry()),
		 SLOT(loadEntry()) );
	
        this->fileSystem=ktagebuchapp->getFileSystem();		
	mPrefs=new MoodPreferences("looknfeel",this);	
}

MoodPlugin::~MoodPlugin()
{
}

void
MoodPlugin::init()
{
	toolbar=new KToolBar((QMainWindow*)ktagebuchapp,QMainWindow::Top);
	new QLabel(i18n("Mood :"),toolbar);
	combobox=new KComboBox(toolbar);
	
	KConfig *config = ktagebuchapp->getConfig();
	config->setGroup("Mood Plugin");
	if (!config->hasKey("moods"))
		mPrefs->save();
	QStringList strList=QStringList(config->readListEntry("moods"));
	for (QStringList::Iterator it=strList.begin();it!=strList.end();++it){
	    combobox->insertItem(i18n(*it));
	}
	combobox->show();	
	loadEntry();
}

bool
MoodPlugin::unload()
{		
	delete combobox;
	delete toolbar;	
	return true;
}

void MoodPlugin::save()
{
}

void MoodPlugin::loadEntry()
{
	
	QString mood;
	        mood=fileSystem->loadFile(ktagebuchapp->today().toString("yyyyMMdd").toInt(),QString("mood"));
		int i=0;
		int count=combobox->count();
		while (mood.compare(combobox->text(i))!=0 && i<count-1){ i++;}
		if (mood.compare(combobox->text(i))==0){
			combobox->setCurrentItem(i);
		}else{
			combobox->insertItem(mood,0);
		}
}
void MoodPlugin::saveEntry()
{
        fileSystem->storeFile(ktagebuchapp->today().toString("yyyyMMdd").toInt(),"mood",combobox->currentText(),combobox->currentText().length());
}
