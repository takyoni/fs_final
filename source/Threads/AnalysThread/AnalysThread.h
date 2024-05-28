//---------------------------------------------------------------------------

#ifndef AnalysThreadH
#define AnalysThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "MainUnit.h"
#include "FS.h"
#include "NTFS.h"
#include "windows.h"
#include "NTFSIterator.h"
#include "IteratorDecorator.h"
#include "FSIteratorDecorator.h"
#include "FAT16.h"
#include "EFAT.h"
#include "HFS+.h"
#include "MyFSC.h"
#include "FileSystemCreator.h"
#include <sqlite3.h>
//---------------------------------------------------------------------------
class AnalysThread : public TThread
{
private:
protected:
	void __fastcall Execute();
	Cluster data;
	sqlite3* Database;
	sqlite3_stmt* res;
	LPCWSTR DatabasePath;
public:
	__fastcall AnalysThread(bool CreateSuspended, LPCWSTR DatabasePath);
	sqlite3* __fastcall OpenDatabase(LPCWSTR DatabasePath);
	void __fastcall Send(Cluster data);
	void __fastcall CreateTable(sqlite3* Database);
	void __fastcall Update();
	void __fastcall InsertData();
	// события, необходимые для реализации анализа
	TEvent *DataReadyEvent;
	TEvent *DataCopiedEvent;
};
//---------------------------------------------------------------------------
#endif
