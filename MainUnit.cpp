//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
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
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StopButtonClick(TObject *Sender)
{
	thrd->Terminate();
    delete thrd;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Form1->MainStringTree->Clear();
	Form1->SearchTimeResultLabel->Caption = L"0";
	Form1->CountResultLabel->Caption = L"0";
	Form1->DetectResultLabel->Caption = L"Underfind";

	thrd = new ReadThread(false);
	thrd->Resume();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainStringTreeGetText(
	TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	if (!Node) return;
	NodeStruct *nodeData = (NodeStruct*)Sender->GetNodeData(Node);
	switch(Column){
		case 0: CellText = nodeData->ClusterNum; break;
        case 1: CellText = nodeData->Content; break;
	}
}


