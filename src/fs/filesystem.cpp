#include <stdio.h>
#include <sqlite3.h>
#include <kglobal.h>
#include <kstandarddirs.h> 
#include <kmessagebox.h>
#include <klocale.h>

#include <qfile.h>
#include <qdir.h>
#include <qstringlist.h>
#include <qcstring.h>
#include <qregexp.h>

#include "filesystem.h"
#include <iostream>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

FileSystem::FileSystem():name("default"){
  importEntries();
  openDB();
}

FileSystem::~FileSystem(){
	QDir tmpDir = KGlobal::dirs()->saveLocation ("tmp", "ktagebuch");
	QStringList tmpFiles= tmpDir.entryList();
		for ( QStringList::Iterator it = tmpFiles.begin(); it != tmpFiles.end(); ++it ) {
        		QFile file(tmpDir.absPath()+"/"+*it);
			file.remove();
		}
	
	if(tmpDir.cdUp())
        	tmpDir.rmdir("ktagebuch");
	sqlite3_close(db);  	
}

/**
 * import the directories into the database
 */
void FileSystem::importEntries(){
	appDir = KGlobal::dirs()->saveLocation ("data", "ktagebuch");
	appDir.setFilter(QDir::Dirs);
	QStringList all= appDir.entryList();

       /*
	* start the import if the application directory contains
 	* at least one directory with a length of 8 charaters (date)
 	*/
	bool import=false;
	for ( QStringList::Iterator it = all.begin(); it != all.end(); ++it ) {
		if(((QString)*it).length()==8) {
			import=true;
			break;
		}
	}
	if (import==false) return;

	int res=KMessageBox::warningContinueCancel   (0,i18n("All journal entries will be migrated to a database file.\n The files and subdirectories in ")+appDir.absPath()+i18n(" will be deleted after the import.\n Make a backup of this directory in case the import fails.\n Press 'Continue' to start the import."));
	if(res!=KMessageBox::Continue){
		exit(1);
	}                	
	
	sqlite3_stmt *plineInfo = 0;

  	char *zErrMsg = 0;
  	int rc;
	/**
	 * - open or create databasefile
	 * - open table or create table
	 * - exit if file or table could not be created
	 */
	rc = sqlite3_open(appDir.absPath()+"/ktagebuch.db", &db);
  	if( rc!=SQLITE_OK ){
    		sqlite3_close(db);
		KMessageBox::error   (   0, i18n("Can't open database: ")+ sqlite3_errmsg(db));
   		exit (1); 
  	}
	rc = sqlite3_exec(db, "SELECT * FROM ktagebuch_entries", 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
    		rc=sqlite3_exec(db, "create table ktagebuch_entries( Date int(8) , Journal varchar(50), Filename varchar(50) , File blob ,PRIMARY KEY(Date, Journal, Filename))", callback, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			sqlite3_close(db);
			KMessageBox::error   (   0, i18n("Can't create database: ")+ zErrMsg);
   			exit (1); 
		}
  	}

	for ( QStringList::Iterator it = all.begin(); it != all.end(); ++it ) {
		if((*it).length()!=8)continue;
		QDir dateDir(appDir.absPath()+"/"+*it);
		dateDir.setFilter(QDir::Files);
		QStringList subDir= dateDir.entryList();
		for ( QStringList::Iterator it2 = subDir.begin(); it2 != subDir.end(); ++it2 ) {
        		QFile file(dateDir.absPath()+"/"+*it2);
			if ( file.open( IO_ReadOnly ) ) {
				QByteArray fileArray=file.readAll();
				QString sql(sqlite3_mprintf("INSERT INTO ktagebuch_entries(Date,Journal,Filename,File) VALUES(%d,'%q','%q',?);", atoi(*it),"default",((QString)*it2).ascii()));
				rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
				if (rc == SQLITE_OK && plineInfo != NULL) {	
					sqlite3_bind_blob(plineInfo, 1, fileArray, fileArray.size(),free);
					if((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){
						KMessageBox::error   (   0, i18n("Can't insert row.\n"));
						exit(1);
					}					
				}
				file.close();			
			}else {
				KMessageBox::error   (   0, i18n("Could not open file: ")+ dateDir.absPath()+"/"+*it2);
				exit(1);
			}
		}
    	}
	sqlite3_close(db);

	bool removed=true;
	for ( QStringList::Iterator it = all.begin(); it != all.end(); ++it ) {
		QDir dateDir(appDir.absPath()+"/"+*it);
		dateDir.setFilter(QDir::Files);
		QStringList subDir= dateDir.entryList();
		for ( QStringList::Iterator it2 = subDir.begin(); it2 != subDir.end(); ++it2 ) {
        		QFile file(dateDir.absPath()+"/"+*it2);
			if (!((QString)*it).startsWith("."))
			  if(file.remove()==false) removed=false;
		}
		QDir dir(appDir.absPath());
		if (!((QString)*it).startsWith("."))
			if(dir.rmdir(*it)==false) removed=false;
	}
	if(removed==false){
		KMessageBox::error   (   0, i18n("Some files could not be deleted.\n Please open the directory ")+ appDir.absPath()+i18n(" and delete the subdirectories manually."));
	}
}

void FileSystem::openDB(){
	int rc = sqlite3_open(appDir.absPath()+"/ktagebuch.db", &db);
	if( rc!=SQLITE_OK ){
    		sqlite3_close(db);
		KMessageBox::error   (   0, i18n("Can't open database: ")+ sqlite3_errmsg(db));
   		exit (1); 
  	}
	
	char *zErrMsg = 0;
  	rc = sqlite3_exec(db, "SELECT * FROM ktagebuch_entries", 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
    		rc=sqlite3_exec(db, "create table ktagebuch_entries( Date int(8) , Journal varchar(50), Filename varchar(50) , File blob ,PRIMARY KEY(Date, Journal, Filename))", callback, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			sqlite3_close(db);
			KMessageBox::error   (   0, i18n("Can't create database: ")+ zErrMsg);
   			exit (1); 
		}
  	}
}


QString FileSystem::loadEntry(int date){
	sqlite3_stmt *plineInfo = 0;
	int rc;

	QString sql(sqlite3_mprintf("Select Filename,File from ktagebuch_entries where Date=%d and Filename not like 'entry';",date));

	/*
	 * copy files to tmpdir
	 */

	QDir tmpDir = KGlobal::dirs()->saveLocation ("tmp", "ktagebuch");	
	rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	
	QStringList slImg;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){	
		QString filename=(const char*)(sqlite3_column_text(plineInfo,0));		
		char* contentArray;
		contentArray=(char*)sqlite3_column_blob(plineInfo,1);
		QFile out (tmpDir.absPath() + "/" + filename);
		if(out.open (IO_WriteOnly)){
			out.writeBlock (contentArray, sqlite3_column_bytes(plineInfo,1));
			out.close();
		}
		slImg.append(filename);
	}		


	sql=sqlite3_mprintf("Select Filename,File from ktagebuch_entries where Date=%d and Filename='entry';", date);
	rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			entry=(const char*)(sqlite3_column_text(plineInfo,1));
	}
	

	/*
	 * replace path in image urls
	 */ 
	for ( QStringList::Iterator it = slImg.begin(); it != slImg.end(); ++it ) {
		QRegExp linkQRegExp("src=.+/"+(*it));
		linkQRegExp.setMinimal(true);
		int pos=0;
		int pos2=pos;
		while ((pos=linkQRegExp.search(entry,pos))>-1){
			if (pos>-1 && (pos2=entry.find(*it,pos))>-1){
				entry=entry.replace(pos,pos2-pos-1,"src="+tmpDir.absPath());
			}
			pos++;
		}		
	}
	return entry;
}

bool FileSystem::saveEntry(int date,QString text){
	sqlite3_stmt *plineInfo = 0;
	int rc;
	QString sql(sqlite3_mprintf("INSERT INTO ktagebuch_entries(Date,Journal,Filename,File) VALUES(%d,'%q','%q',?);", date,"default","entry"));
				rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
				if (rc == SQLITE_OK && plineInfo != NULL) {	
					sqlite3_bind_blob(plineInfo, 1, text, text.length(),free);
					if((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){
						QString sql(sqlite3_mprintf("Update ktagebuch_entries set File=? where Date=%d and Journal='%q' and Filename='%q'", date,name.ascii(),"entry"));
						rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);				
						if (rc == SQLITE_OK && plineInfo != NULL) {	
							sqlite3_bind_blob(plineInfo, 1, text, text.length(),free);
							if((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){
								KMessageBox::error   (   0, i18n("Can't insert row.\n"));
								return false;
							}
						}						
					}					
				}
	return true;
}

QString FileSystem::getPreviousEntry(int date){	
	sqlite3_stmt *plineInfo = 0;
	QString sql(sqlite3_mprintf("select max(Date) from ktagebuch_entries where Date<%d;", date));
	int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			entry=(const char*)(sqlite3_column_text(plineInfo,0));
	}
	return entry;
}

QString FileSystem::getFirstEntry(){	
	sqlite3_stmt *plineInfo = 0;
	QString sql(sqlite3_mprintf("select min(Date) from ktagebuch_entries where Date>0;"));	
	int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			entry=(const char*)(sqlite3_column_text(plineInfo,0));						
	}
	return entry;
}

QString FileSystem::getNextEntry(int date){
	sqlite3_stmt *plineInfo = 0;
	QString sql(sqlite3_mprintf("select min(Date) from ktagebuch_entries where Date>%d;", date));
	int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){											
			entry=(const char*)(sqlite3_column_text(plineInfo,0));
	}
	return entry;
}

QString FileSystem::getLastEntry(){	
	sqlite3_stmt *plineInfo = 0;
	QString sql(sqlite3_mprintf("select max(Date) from ktagebuch_entries;"));
	int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			entry=(const char*)(sqlite3_column_text(plineInfo,0));
	}
	return entry;
}

QStringList* FileSystem::getDates(){	
	sqlite3_stmt *plineInfo = 0;
	QString sql("select Date from ktagebuch_entries Order by Date;");
	int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	QStringList* dateStringList=new QStringList();
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			dateStringList->append((const char*)(sqlite3_column_text(plineInfo,0)));
	}
	return dateStringList;
}

QStringList* FileSystem::getDates(QString restriction){	
	sqlite3_stmt *plineInfo = 0;
	QString sql("select Date from ktagebuch_entries where Date "+restriction+" and Filename='entry' Order by Date;");
	int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	QStringList* dateStringList=new QStringList();
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			dateStringList->append((const char*)(sqlite3_column_text(plineInfo,0)));
	}
	return dateStringList;
}

bool FileSystem::storeFile(int date,QString fileName, const char* buffer, int size){
	sqlite3_stmt *plineInfo = 0;
	QString sql(sqlite3_mprintf("INSERT INTO ktagebuch_entries(Date,Journal,Filename,File) VALUES(%d,'%q','%q',?);", date,"default",fileName.ascii()));
				int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
				if (rc == SQLITE_OK && plineInfo != NULL) {	
					sqlite3_bind_blob(plineInfo, 1, buffer, size,free);
					if((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){
						QString sql(sqlite3_mprintf("Update ktagebuch_entries set File=? where Date=%d and Journal='%q' and Filename='%q'", date,"default",fileName.ascii()));
						rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);				
						if (rc == SQLITE_OK && plineInfo != NULL) {	
							sqlite3_bind_blob(plineInfo, 1, buffer, size,free);
							if((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){
								KMessageBox::error   (   0, i18n("Can't insert row.\n"));
								return false;
							}
						}						
					}					

				}
	return true;
}

QString FileSystem::loadFile(int date,QString fileName){
	sqlite3_stmt *plineInfo = 0;
	int rc;
	
	QString sql=sqlite3_mprintf("Select Filename,File from ktagebuch_entries where Date=%d and Filename='%q';", date,fileName.ascii());
	rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			entry=(const char*)(sqlite3_column_text(plineInfo,1));
	}	
	return entry;
}

void FileSystem::exportEntry(int date,QString fileName){
	sqlite3_stmt *plineInfo = 0;
	QString sql,dateStr;
	dateStr.setNum(date);
	sql=sqlite3_mprintf("Select File from ktagebuch_entries where Date=%d and Filename='entry';", date);
	int rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	QString entry=0;
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			entry=(const char*)(sqlite3_column_text(plineInfo,0));
	}
	
	QStringList linkList;
	QRegExp linkQRegExp("src=(\\S+)\\b");
        int pos=0;
	
	while ((pos=linkQRegExp.search(entry,pos))>-1){
			QString link=linkQRegExp.cap(1);
			int i=link.findRev(QRegExp("/"));
			linkList.append(link.right(link.length()-(i+1)));	
			entry=entry.replace(pos+4,i+1,"");
		pos++;
	}		
	
	QFile entry_out (fileName);
	if(entry_out.open (IO_WriteOnly)){
		entry_out.writeBlock (entry, entry.length());
		entry_out.close();
	}

	sql="select Filename,File from ktagebuch_entries where Date="+dateStr+" and Filename not like 'entry';";
				
	rc = sqlite3_prepare(db, sql.ascii(), -1, &plineInfo, 0);
	
	while ((rc=sqlite3_step(plineInfo))!=SQLITE_DONE){					
			QString entry_filename=(const char*)(sqlite3_column_text(plineInfo,0));
			for ( QStringList::Iterator it = linkList.begin(); it != linkList.end(); ++it ) {
				if(entry_filename==(*it)){					
					char* contentArray;
					contentArray=(char*)sqlite3_column_blob(plineInfo,1);
					QFile out (fileName.left(fileName.findRev(QRegExp("/"))+1)+entry_filename);
					if(out.open (IO_WriteOnly)){
						out.writeBlock (contentArray, sqlite3_column_bytes(plineInfo,1));
						out.close();
					}
					break;
				}
			}						
	}
	
}
