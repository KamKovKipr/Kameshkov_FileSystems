//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Thread1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Thread1::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall Thread1::Thread1(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------
void __fastcall Thread1::Execute()
{
	Fabric OpFile(Form1->open); //Вызов фабрики
	BaseFileSystem* MyFS = OpFile.getFS(OpFile.FS_Definder()); //Определение ФС
	Iterator iter(MyFS); //Вызов итератора
	Decorator Dec(iter); //Вызов декоратора
	Thread2* DBWrite = new Thread2(false); //Вызов второго потока
	for (Dec.First(); !Dec.IsDone(); Dec.Next())//Цикл поиска кластеров с заданным расширением
	{
		Form1->cluster =  Dec.MyIt.CurCl;
		DBWrite->Ready->SetEvent(); //Поднятие флага о готовности данных
		while (DBWrite->Copied->WaitFor(INFINITE) != wrSignaled){} //Ожидания записи в БД и VT
		DBWrite->Copied->ResetEvent(); //Сброс флага о записи найденных данных
	}
	//Декор для интерфейса
		ShowMessage("Готово");
		Form1->ComboBox1->ItemIndex = -1;
		Form1->ComboBox2->ItemIndex = -1;
		Form1->ComboBox1 -> Enabled  = true;
		Form1->ComboBox2 -> Enabled  = true;
	    Form1->Button1 -> Enabled  = true;
		Form1->Edit1 -> Enabled  = true;
		Form1->Edit1 -> Clear();
		Form1->Edit1 -> Text = "Выберите файл для анализа";
		Form1->ComboBox1-> Text = "Выберите букву тома";
		Form1->ComboBox2 -> Text = "Выберите искомое расширение";

}
//---------------------------------------------------------------------------
