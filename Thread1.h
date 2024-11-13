//---------------------------------------------------------------------------

#ifndef Thread1H
#define Thread1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "Fabric.h"
#include "Decorator.h"
#include "Thread2.h"
#include "DataBase.h"
//---------------------------------------------------------------------------
class Thread1 : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Thread1(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
