//---------------------------------------------------------------------------

#ifndef ReadThreadH
#define ReadThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "AnalysThread.h"
#include "FileSystemCreator.h"
//---------------------------------------------------------------------------
class ReadThread : public TThread
{
private:
	DWORD processTime;
	__int64 ProgressId;
    __int64 clusters;
	bool AnalyseSeparate;
	class AnalysThread *AnalysThreadObject;
protected:
	void __fastcall Execute();
	void __fastcall UpdateLabel();
	void __fastcall UpdateLabel2();
	void __fastcall UpdateProgress();
    FSEnum __fastcall DetectFS(LPCWSTR device);
public:
	__fastcall ReadThread(bool analyseInSeparateThread, bool CreateSuspended);

};
//---------------------------------------------------------------------------
#endif
