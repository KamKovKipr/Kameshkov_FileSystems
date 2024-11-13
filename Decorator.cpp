//---------------------------------------------------------------------------

#pragma hdrstop

#include "Decorator.h"
#include <iostream>
#include <string>

Decorator::Decorator(Iterator It) //Конструктор декоратора (итератор)
{
    MyIt = It;

	UnicodeString findingExtention = Form1->ComboBox2->Items->Strings[Form1->ComboBox2->ItemIndex];
	if (findingExtention == "exe") //Поиск нужной сигнатуры расширения
    {
		sign = EXE;
        size = sizeof(EXE);
	}
	else if (findingExtention == "pdf")
    {
        sign = PDF;
        size = sizeof(PDF);
	}
    else if (findingExtention == "rar")
    {
        sign = RAR;
        size = sizeof(RAR);
    }
	else if (findingExtention == "vmdk")
	{
		sign = VMDK;
		size = sizeof(VMDK);
	}
	else if (findingExtention == "msoffice")
	{
		sign = MSOFICCE;
		size = sizeof(MSOFICCE);
	}
	else
    {
    	sign = NULL;
        size = NULL;
    }
}

void Decorator::First() //Установка текузего кластера в нулевое значение и переход к следующему
{
    MyIt.First();
    Next();
}

bool Decorator::IsDone() //Проверка обхода ФС
{
    return MyIt.IsDone();
}


void Decorator::Next() //Поиск кластера
{
		MyIt.getCurrentCl();
    	bool check = false;
    	while (!check && !IsDone())
        {
           	MyIt.Next();
            MyIt.getCurrentCl();
           	if (memcmp(MyIt.pResultBuffer, sign, size)==0)
            {
            	check = true;
           	}
            else
            {
            	check = false;
            }
		}
}



//---------------------------------------------------------------------------
#pragma package(smart_init)
