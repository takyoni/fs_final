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
	__int64 clusters;
	UnicodeString DetectedFS;
    LPCWSTR logicDisk;
	class AnalysThread *AnalysThreadObject;
    unsigned int clusterCount;
protected:
	void __fastcall Execute();
	void __fastcall UpdateLabel();
	void __fastcall UpdateLabel2();
    void __fastcall UpdateFS();
	FSEnum __fastcall DetectFS(LPCWSTR device);
	FileTypeEnum __fastcall GetFileType();
public:
	__fastcall ReadThread(bool CreateSuspended);

};
//---------------------------------------------------------------------------
#endif
