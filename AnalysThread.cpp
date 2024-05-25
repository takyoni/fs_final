//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "AnalysThread.h"
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

__fastcall AnalysThread::AnalysThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	 FreeOnTerminate = true;

	 DataReadyEvent = new TEvent(NULL, true, false, "", false);
	 DataCopiedEvent = new TEvent(NULL, true, false, "", false);
	 CompleteEvent = new TEvent(NULL, true, false, "", false);
	 Database = OpenDatabase();
     CreateTable(Database);
}
//---------------------------------------------------------------------------
void __fastcall AnalysThread::Execute()
{
    CompleteEvent->SetEvent();
	//---- Place thread code here ----
	while(!Terminated)
	{
		// ждать когда будут подготовлены данные к след анализу
		if(DataReadyEvent->WaitFor(INFINITE) == wrSignaled)  //IFINITE
		{

			// Скопировать данные об объекте в локальный буфер
			//Sleep(1);

			DataReadyEvent->ResetEvent();
			Synchronize(Update);
            InsertData();
			DataCopiedEvent->SetEvent();

			CompleteEvent-> ResetEvent();

			//Synchronize(Update);
//			PVirtualNode entryNode = Form1->MainStringTree->AddChild(Form1->MainStringTree->RootNode);
//			NodeStruct *nodeData = (NodeStruct*)Form1->MainStringTree->GetNodeData(entryNode);
//			nodeData->Id = data.GetNum();
//			nodeData->Name = L"asdasd";
			//nodeData->Info = L"dsadasd";
			//memset(nodeData->Buffer, 0, sizeof(nodeData->Buffer));

			CompleteEvent-> SetEvent();

		}

	}
    delete DataReadyEvent;
	delete DataCopiedEvent;
	delete CompleteEvent;
}
//---------------------------------------------------------------------------
void __fastcall AnalysThread::Send(Cluster cluster){
	data=cluster;
}
void __fastcall AnalysThread::Update()
{
	PVirtualNode entryNode = Form1->MainStringTree->AddChild(Form1->MainStringTree->RootNode);
	NodeStruct *nodeData = (NodeStruct*)Form1->MainStringTree->GetNodeData(entryNode);
	nodeData->Id = data.GetNum();
	nodeData->Name = L"asdasd";
}
// Открытие БД SQLite
sqlite3* __fastcall AnalysThread::OpenDatabase()
{
    sqlite3* Database;
    int openResult = sqlite3_open16(L"../History", &Database);
    if (openResult != SQLITE_OK) {
        wcout << L"Ошибка открытия БД" << endl;
    }
    return Database;
}

// Создание таблицы
void __fastcall AnalysThread::CreateTable(sqlite3* Database)
{
    char* errmsg;
    char sql[] = "CREATE TABLE IF NOT EXISTS test("
        "name TEXT NOT NULL,"
        "value TEXT NOT NULL);";
    // Создаем таблицу
    int execResult = sqlite3_exec(Database, sql, NULL, NULL, &errmsg);
    if (execResult != SQLITE_OK) {
        cout << errmsg << endl;
        wcout << L"Ошибка выполнения запроса" << endl;
    }
}
void __fastcall AnalysThread::InsertData()
{
	sqlite3_stmt* res;  // компилируемое выражение
	int rc = sqlite3_prepare_v2(Database, "INSERT INTO test (name, value) VALUES (?, ?)", -1, &res, 0);

	sqlite3_exec(Database, "BEGIN;", nullptr, nullptr, nullptr);
	sqlite3_bind_text(res, 1, "asd", -1, SQLITE_STATIC);
	sqlite3_bind_text(res, 2, "dsa", -1, SQLITE_STATIC);
	// выполняем выражение
	int step = sqlite3_step(res);
	// если выражение успешно выполнено
	if (step == SQLITE_ERROR)
	{
		printf("Error\n");
	}
	sqlite3_clear_bindings(res);
	sqlite3_reset(res);
	sqlite3_exec(Database, "COMMIT;", nullptr, nullptr, nullptr);
}

