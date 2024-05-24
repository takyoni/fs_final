//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "ReadThread.h"
#include "AnalysThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

	MainStringTree->NodeDataSize = sizeof(NodeStruct);
//	PVirtualNode entryNode = MainStringTree->AddChild(MainStringTree->RootNode);
//	NodeStruct *nodeData = (NodeStruct*)MainStringTree->GetNodeData(entryNode);
//	nodeData->Id = 1;
//	nodeData->Name = L"asdasd";
//	nodeData->Info = L"dsadasd";
//    memset(nodeData->Buffer, 0, sizeof(nodeData->Buffer));
	//MainStringTree->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	DWORD startTime = GetTickCount();
	//Sleep(5000);

	__int64 NumberOfObjects = 100;
	for (__int64 i = 0; i <= NumberOfObjects; i++)
	{
		//reading
		Sleep(30);

		// обработка
		Sleep(70);

		ProgressBar1->Position = i;
	}

	DWORD endTime = GetTickCount();
	DWORD processTime = endTime - startTime ;

	UnicodeString timestr = UnicodeString(processTime);
	Label1->Caption = timestr;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	//ReadThread(false, false);
	ReadThread *thrd = new ReadThread(false, false);
	thrd->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	//ReadThread(true, false);
	ReadThread *thrd = new ReadThread(true, false);
	thrd->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainStringTreeGetText(
	TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	if (!Node) return;
	NodeStruct *nodeData = (NodeStruct*)Sender->GetNodeData(Node);
	switch(Column){
		case 0: CellText = nodeData->Id; break;
        case 1: CellText = nodeData->Name; break;
	}
}
