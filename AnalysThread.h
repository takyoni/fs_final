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
//---------------------------------------------------------------------------
class AnalysThread : public TThread
{
private:
protected:
	void __fastcall Execute();
	Cluster data;
public:
	__fastcall AnalysThread(bool CreateSuspended);
	void __fastcall Send(Cluster data);
	void __fastcall Update();
	// события, необходимые для реализации анализа
	TEvent *DataReadyEvent;
	TEvent *DataCopiedEvent;
	TEvent *CompleteEvent;
};
//---------------------------------------------------------------------------
#endif
