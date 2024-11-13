//---------------------------------------------------------------------------

#ifndef Thread2H
#define Thread2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Thread1.h"
//---------------------------------------------------------------------------
class Thread2 : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Thread2(bool CreateSuspended);
	void __fastcall Clear();
	void __fastcall addRow();
	const wchar_t* path1;
	const wchar_t* exeption1;
	TEvent *Ready;
	TEvent *Copied;
	//TEvent *Written;
	ULONGLONG i;
};
//---------------------------------------------------------------------------
#endif
