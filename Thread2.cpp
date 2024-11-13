//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Thread2.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Thread2::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall Thread2::Thread2(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	Ready = new TEvent(NULL, true, false, "", false);
	Copied = new TEvent(NULL, true, false, "", false);
}
//---------------------------------------------------------------------------
void __fastcall Thread2::Execute()
{
	Synchronize(Clear);
	DataBase DB;
	Copied->ResetEvent();
	exeption1 = Form1->ComboBox2->Items->Strings[Form1->ComboBox2->ItemIndex].c_str();
	i = 0;

	while(!Terminated)  // Пока поток не завершен
	{
		if(Ready->WaitFor(INFINITE) == wrSignaled)
		{
			Ready->ResetEvent(); //Сброс флага готовности данных
			i++; //Номер строки в VT
			path1 = Form1->openU.c_str(); //Путь к объекту исследования
			DB.writing(path1, Form1->cluster, Form1->ComboBox2->Items->Strings[Form1->ComboBox2->ItemIndex].c_str()); //Запись в БД
			Synchronize(addRow); //Запись в VT
			Copied->SetEvent(); //Установка флага о копировании

    	}
	}
}

void __fastcall Thread2::addRow()
{
	PVirtualNode myNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode); //Добавление дочернего узла к корневому
	TreeNode* myData = (TreeNode*)Form1->VirtualStringTree1->GetNodeData(myNode);
	// Запись в VT согласно структуре, объявленной в Unit1.h
	myData->index = i;
	myData->path = path1;
	myData->exeption = Form1->ComboBox2->Items->Strings[Form1->ComboBox2->ItemIndex].c_str();
	myData->cluster = Form1->cluster;
}

void __fastcall Thread2::Clear() //Очистка VT
{
	Form1->VirtualStringTree1->Clear();
}
//---------------------------------------------------------------------------
