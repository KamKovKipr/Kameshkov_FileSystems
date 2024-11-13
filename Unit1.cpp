//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	ComboBox1 -> Visible  = false;
	ComboBox2 -> Visible  = false;
	Button1 -> Visible  = false;
	VirtualStringTree1 -> Visible  = false;
	Edit1 -> Visible  = false;
	ShowCustomMessageDialog();
    VirtualStringTree1->NodeDataSize=sizeof(TreeNode);
}

void __fastcall TForm1::ShowCustomMessageDialog()
{
	// Создание диалога для выбора режима программы (Том/Файл)
	TForm* dialog = CreateMessageDialog("Выберите объект анализа:", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo);
	dialog->Caption = "";


	static_cast<TButton*>(dialog->FindComponent("Yes"))->Caption = "Том";
	static_cast<TButton*>(dialog->FindComponent("No"))->Caption = "Файл";

    int result = dialog->ShowModal();

	if (result == mrYes)
	{
		ComboBox1 -> Visible  = true;
		ComboBox2 -> Visible  = true;
		Button1 -> Visible  = true;
		VirtualStringTree1 -> Visible  = true;
		char driveStrings[256];
		//Поиск подключенных логических томов
		DWORD length = GetLogicalDriveStringsA(sizeof(driveStrings), driveStrings);
		for (char* drive = driveStrings; *drive; drive += strlen(drive) + 1)
		{
			ComboBox1->Items->Add(drive);
		}

	}
	else if (result == mrNo)
	{
		ComboBox2 -> Visible  = true;
		Button1 -> Visible  = true;
		VirtualStringTree1 -> Visible  = true;
		Edit1 -> Visible  = true;
	}
	else // Если диалог закрыт без выбора, закрываем программу
	{
        Application->Terminate();
	}

	delete dialog;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Click(TObject *Sender) //Создание диалога проводника при выборе режима анализа файла
{
    TOpenDialog *OpenDialog = new TOpenDialog(this);
    OpenDialog->Filter = "Image Files (*.img;*.vmdk;*.dd;*.vhd;*.vhdx)|*.img;*.vmdk;*.dd;*.vhd;*.vhdx|All Files (*.*)|*.*"; // Фильтр для файлов
    OpenDialog->Title = "Выберите файл образа";

    if (OpenDialog->Execute())
    {
		String selectedFile = OpenDialog->FileName;
		Edit1->Clear();
		Edit1->Text = selectedFile.c_str();
		open = selectedFile.c_str();
		openU =Edit1->Text;
    }

	delete OpenDialog;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) //Запуск анализа с проверкой выбранных параметров
{
	if (ComboBox2->ItemIndex == -1 && open == NULL)
	{
		ShowMessage("Выберите все параметры");
    }
	else if (ComboBox2->ItemIndex == -1)
	{
		ShowMessage("Не выбрано расширение для поиска");
	}
	else if (open == NULL)
	{
		ShowMessage("Выберите объект исследования");
	}
	else
	{
		ComboBox1 -> Enabled  = false;
		ComboBox2 -> Enabled  = false;
		Button1 -> Enabled  = false;
		Edit1 -> Enabled  = false;
		Thread1* start = new Thread1(false);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender) //Реакция на выбор логического тома в элементе ComboBox при выборе режима анализа файла
{
	UnicodeString path_uni = NULL;
	openU = NULL;
	open = NULL;
	openU = ComboBox1->Items->Strings[ComboBox1->ItemIndex];
	path_uni = u"\\\\?\\" + openU;
	path_uni = path_uni.SetLength(path_uni.Length() - 1);
	open = path_uni.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	if (!Node) return;
	TreeNode* myData = (TreeNode*)Sender->GetNodeData(Node);
	switch (Column)
	{
		case 0: CellText = myData->index; break;
		case 1: CellText = myData->path; break;
		case 2: CellText = myData->exeption; break;
		case 3: CellText = myData->cluster; break;
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
