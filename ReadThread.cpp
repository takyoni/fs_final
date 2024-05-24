//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "AnalysThread.h"
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include "Unit1.h"
#include "FS.h"
#include "NTFS.h"
#include "windows.h"
#include "IteratorDecorator.h"
#include "FSIteratorDecorator.h"
#include "FAT16.h"
#include "EFAT.h"
#include "HFS+.h"
#include "MyFSC.h"
#include "FileSystemCreator.h"
#include "ReadThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall read_thread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ReadThread::ReadThread(bool analyseInSeparateThread, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	 FreeOnTerminate = true;
	 AnalyseSeparate = analyseInSeparateThread;
	 AnalysThreadObject = new AnalysThread(false);

}
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
	//---- Place thread code here ----

	DWORD startTime = GetTickCount();
    FileSystemCreator* fsCreator = new MyFSC;
    FSEnum fsType = DetectFS(L"\\\\.\\C:");
    FS* fs = fsCreator->CreateFileSystem(fsType, L"\\\\.\\C:");
    if (!fs->Init(L"\\\\.\\C:")) {
        cout << "Init: " << GetLastError();
        return ;
    };
	unsigned int clusterCount = fs->ClusterCount();
	unsigned int clusterSize = fs->ClusterSize();
    Iterator<Cluster>* it = new FSIteratorDecorator(
        new NTFSIterator(fs),
        FileTypeEnum::Jpeg
	);

	for (it->First();!it->IsDone();it->Next()) {
		Cluster currentObject = it->GetCurrent();
		clusters += 1;
		if (AnalyseSeparate) {
			  // анализ в доп потоке

			  // передаем данные на обработку
			  //Sleep(1);
			  AnalysThreadObject->Send(currentObject);
			  AnalysThreadObject->DataReadyEvent->SetEvent();

			  while(AnalysThreadObject->DataCopiedEvent->WaitFor(3000) != wrSignaled)
			  { }

			  AnalysThreadObject->DataCopiedEvent->ResetEvent();
		}
		else
		{

		// обработка
			Sleep(70);
		}
		ProgressId += (100/clusterCount);
		Synchronize(UpdateProgress);
		Synchronize(UpdateLabel2);
	}

	DWORD endTime = GetTickCount();
	processTime = endTime - startTime ;

	UnicodeString timestr = UnicodeString(processTime);
	Synchronize(UpdateLabel);

	AnalysThreadObject->Terminate();

}
//---------------------------------------------------------------------------
void __fastcall ReadThread::UpdateLabel()
{
	UnicodeString timestr = UnicodeString(processTime);
	Form1->Label1->Caption = timestr;

}
void __fastcall ReadThread::UpdateLabel2()
{
	UnicodeString timestr = UnicodeString(clusters);
	Form1->Label2->Caption = timestr;

}
void __fastcall ReadThread::UpdateProgress()
{
	UnicodeString timestr = UnicodeString();
	Form1->ProgressBar1->Position = ProgressId;

}
__fastcall FSEnum ReadThread::DetectFS(LPCWSTR device) {
    HANDLE fileHandler = CreateFileW(
        device,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (fileHandler == INVALID_HANDLE_VALUE)
    {
        throw std::invalid_argument("Error INVALID_HANDLE_VALUE!");
    }
    DWORD bytesRead;
    BYTE buffer[2048];
    // Читаем первые 2048 байт
    if (!ReadFile(fileHandler, buffer, sizeof(buffer), &bytesRead, nullptr)) {
        throw "Error reading volume\n";
    }

    // Проверяем сигнатуру NTFS
    BYTE ntfsSignature[] = { 0x4E, 0x54, 0x46, 0x53 };
    if (memcmp(buffer + 3, ntfsSignature, sizeof(ntfsSignature)) == 0) {
        return FSEnum::NTFS;
    }
    // Проверяем сигнатуру FAT16
    BYTE fat16Signature[] = { 0x1C, 0xEB, 0x52, 0x90 };
    if (memcmp(buffer + 11, fat16Signature, sizeof(fat16Signature)) == 0) {
        return FSEnum::FAT16;
    }
    // Проверяем сигнатуру ExFAT
    BYTE exfatSignature[] = { 0x45, 0x78, 0x46, 0x41, 0x54 };
    if (memcmp(buffer + 3, exfatSignature, sizeof(exfatSignature)) == 0) {
        return FSEnum::ExFAT;
    }
    // Проверяем сигнатуру HFS+
    BYTE hfsPlusSignature[] = { 0x48, 0x2B, 0x0E, 0x0E };
    if (memcmp(buffer + 1024, hfsPlusSignature, sizeof(hfsPlusSignature)) == 0) {
        return FSEnum::HFSp;
    }
    throw "Cannot detect fs!";
}
