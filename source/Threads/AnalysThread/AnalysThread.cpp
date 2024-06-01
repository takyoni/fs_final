//---------------------------------------------------------------------------

#include <System.hpp>
#include <System.SysUtils.hpp>
#pragma hdrstop

#include "AnalysThread.h"
#include "MainUnit.h"
#include "FS.h"
#include "NTFS.h"
#include "windows.h"
#include <string>
#include "NTFSIterator.h"
#include "IteratorDecorator.h"
#include "FSIteratorDecorator.h"
#include "FAT16.h"
#include "EFAT.h"
#include "HFS+.h"
#include "MyFSC.h"
#include "FileSystemCreator.h"
#include "sqlite3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Analyse_thread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall AnalysThread::AnalysThread(bool CreateSuspended, LPCWSTR DatabasePath)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;

	Database = OpenDatabase(DatabasePath);
	CreateTable(Database);
	
	int rc = sqlite3_prepare_v2(Database, "INSERT INTO clusters (cluster_num, content) VALUES (?, ?)", -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		throw "Cannot prepate query";
	}
	
	DataReadyEvent = new TEvent(NULL, true, false, "", false);
	DataCopiedEvent = new TEvent(NULL, true, false, "", false);
}
//---------------------------------------------------------------------------
void __fastcall AnalysThread::Execute()
{
	while(!Terminated)
	{
		// ждать когда будут подготовлены данные к след анализу
		if(DataReadyEvent->WaitFor(INFINITE) == wrSignaled)
		{
			// Скопировать данные об объекте в локальный буфе

			DataReadyEvent->ResetEvent();
			
  			Synchronize(Update);
			InsertData();

			DataCopiedEvent->SetEvent();
		}
	}
	sqlite3_close(Database);
	sqlite3_finalize(res);

    delete DataReadyEvent;
	delete DataCopiedEvent;
}
//---------------------------------------------------------------------------
void __fastcall AnalysThread::Send(Cluster* cluster){
	data = cluster;
}
void __fastcall AnalysThread::Update()
{
	TBytes buff;
    buff.set_length(10);
	memcpy(&buff[0],  data->GetContent(), 10);

	PVirtualNode entryNode = Form1->MainStringTree->AddChild(Form1->MainStringTree->RootNode);
	NodeStruct *nodeData = (NodeStruct*)Form1->MainStringTree->GetNodeData(entryNode);
	nodeData->ClusterNum = data->GetNum();
	nodeData->Content = System::Sysutils::StringOf(buff);
}
// Открытие БД SQLite
sqlite3* __fastcall AnalysThread::OpenDatabase(LPCWSTR DatabasePath)
{
    sqlite3* Database;
	int openResult = sqlite3_open16(DatabasePath, &Database);
	if (openResult != SQLITE_OK) {
		throw "Cannot open sqlite db";
    }
    return Database;
}

// Создание таблицы
void __fastcall AnalysThread::CreateTable(sqlite3* Database)
{
    char* errmsg;
	char sql[] = "CREATE TABLE IF NOT EXISTS clusters("
		"cluster_num INT NOT NULL,"
		"content TEXT NOT NULL);";
    // Создаем таблицу
    int execResult = sqlite3_exec(Database, sql, NULL, NULL, &errmsg);
	if (execResult != SQLITE_OK) {
		throw "Canoot create sqlite table";
	}
}
void __fastcall AnalysThread::InsertData()
{
	char str[10];
	memcpy(str, data->GetContent(), 10);

	sqlite3_exec(Database, "BEGIN;", nullptr, nullptr, nullptr);
	sqlite3_bind_int(res, 1, data->GetNum());
	sqlite3_bind_text(res, 2, str, -1, SQLITE_STATIC);

	// выполняем выражение
	int step = sqlite3_step(res);
	// если выражение успешно выполнено
	if (step == SQLITE_ERROR)
	{
		throw "SQLITE_ERROR";
	}
	
	sqlite3_clear_bindings(res);
	sqlite3_reset(res);
	sqlite3_exec(Database, "COMMIT;", nullptr, nullptr, nullptr);
}

