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
