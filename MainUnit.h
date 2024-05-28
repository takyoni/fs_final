//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include "ReadThread.h"
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button3;
	TLabel *SearchTimeResultLabel;
	TLabel *CountResultLabel;
	TVirtualStringTree *MainStringTree;
	TRadioButton *JpegButton;
	TRadioButton *PdfButton;
	TRadioButton *ExeButton;
	TRadioButton *ElfButton;
	TButton *StopButton;
	TPanel *Panel1;
	TLabel *FileFormatLabel;
	TLabel *SearchTimeLabel;
	TLabel *CountLabel;
	TLabel *DetectLabel;
	TLabel *DetectResultLabel;
	TEdit *Edit1;
	TLabel *DiskNameLabel;
	TLabel *SqlLabel;
	TEdit *Edit2;
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall MainStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
private:	// User declarations
	ReadThread *thrd;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct
{
	ULONGLONG ClusterNum;
	UnicodeString Content;
} NodeStruct;
#endif
