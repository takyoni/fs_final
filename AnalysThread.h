//---------------------------------------------------------------------------

#ifndef AnalysThreadH
#define AnalysThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Unit1.h"
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
public:
	__fastcall AnalysThread(bool CreateSuspended);
	void __fastcall Send(Cluster data);
	sqlite3* __fastcall OpenDatabase();
	void __fastcall CreateTable(sqlite3* Database);
	void __fastcall Update();
    void __fastcall InsertData();
	// события, необходимые для реализации анализа
	TEvent *DataReadyEvent;
	TEvent *DataCopiedEvent;
	TEvent *CompleteEvent;
};
//---------------------------------------------------------------------------
#endif
