#include "ktagebuch.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KDE/KLocale>
#include "fs/filesystem.h"

static const char description[] =
    I18N_NOOP("A KDE 4 Application");

static const char version[] = "0.80";

int main(int argc, char **argv)
{
    KAboutData about("ktagebuch", 0, ki18n("KTagebuch"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2002 - 20010 Rainer Blessing"), KLocalizedString(), 0, "rainer.blessing@googlemail.com");
    about.addAuthor( ki18n("%{AUTHOR}"), KLocalizedString(), "rainer.blessing@googlemail.com" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    KTagebuch *widget = new KTagebuch;
    
    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(KTagebuch);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            //ktagebuch *widget = new ktagebuch;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                //ktagebuch *widget = new ktagebuch;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
