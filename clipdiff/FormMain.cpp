// clipdiff.cpp : main project file.

#include "stdafx.h"
#include "FormMain.h"
#include "difflist.h"
#include "ListViewForScroll.h"
#include "LVInfo.h"

namespace clipdiff {


	using namespace Ambiesoft;

	FormMain::FormMain(void)
	{
		InitializeComponent();

		int intval;
		bool boolval;

		HashIni^ ini =  Profile::ReadAll(Ambiesoft::AmbLib::GetIniPath());
		try 
		{
			String^ fontstring;
			Profile::GetString(APP_OPTION, L"Font", L"", fontstring, ini);

			if(!String::IsNullOrEmpty(fontstring))
			{
				System::ComponentModel::TypeConverter^ converter =
					System::ComponentModel::TypeDescriptor::GetConverter( System::Drawing::Font::typeid );

				FontLV = dynamic_cast<System::Drawing::Font^>(converter->ConvertFromString(fontstring));
			}
		}
		catch(Exception^ ex) 
		{
			MessageBox::Show(ex->Message,
				Application::ProductName);
		}


		Profile::GetBool(APP_OPTION, L"ShowToolbar", true, boolval, ini);
		toolMain->Visible=boolval;

		Profile::GetBool(APP_OPTION, L"ShowStatusbar", true, boolval, ini);
		stMain->Visible=boolval;

		Profile::GetBool(APP_OPTION, L"ShowListheader", true, boolval, ini);
		IsHeaderVisible=boolval;



		Profile::GetInt(APP_OPTION, L"EngineLevel", 1, intval, ini);
		EngineLevel = (DifferenceEngine::DiffEngineLevel)intval;


		addColumn();
		addColumn();


		bool posReadFailed=false;
		int x,y,width,height;
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"X", -10000, x, ini);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Y", -10000, y, ini);

		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Width", -10000, width, ini);
		posReadFailed |= !Profile::GetInt(APP_OPTION, L"Height", -10000, height, ini);
		if(!posReadFailed)
		{
			if(AmbLib::IsPointInMonitor(x,y))
			{
				this->StartPosition = FormStartPosition::Manual;
				this->Location = System::Drawing::Point(x,y);
				this->Size = System::Drawing::Size(width, Height);
			}
		}


	}

	System::Void FormMain::tsmAbout_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::Text::StringBuilder msg;

		msg.Append(Application::ProductName + L" version:");
		msg.Append(System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString());


		MessageBox::Show(msg.ToString(),
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}

	void FormMain::addColumn()
	{
		int index = !tlpMain ? 1 : tlpMain->ColumnCount+1;

		ListViewForScroll^ lv = gcnew ListViewForScroll();

		ColumnHeader^ chLine = (gcnew System::Windows::Forms::ColumnHeader());
		chLine->Text = L"Line";
		chLine->Name = L"chLine";

		ColumnHeader^ chText = (gcnew System::Windows::Forms::ColumnHeader());
		chText->Text = L"Text";
		chText->Name = L"chText";
		chText->Width = 213;

		lv->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  > {chLine, chText});
		lv->Dock = System::Windows::Forms::DockStyle::Fill;
		lv->FullRowSelect = true;
		lv->HeaderStyle = IsHeaderVisible ? ColumnHeaderStyle::Nonclickable : ColumnHeaderStyle::None;
		lv->HideSelection = false;
		lv->Location = System::Drawing::Point(0, 0);
		lv->Name = L"lv" + index;
		lv->Size = System::Drawing::Size(138, 255);
		lv->TabIndex = index;
		lv->UseCompatibleStateImageBehavior = false;
		lv->View = System::Windows::Forms::View::Details;
		lv->Tag = gcnew LVInfo();
		if(FontLV)
		{
			lv->Font=FontLV;
		}
		// flowLayoutPanel1->Controls->Add(lv);
		if(!tlpMain)
		{
			tlpMain = gcnew System::Windows::Forms::TableLayoutPanel();
			this->tlpMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tlpMain->Location = System::Drawing::Point(0, 24);
			this->tlpMain->Name = L"tlpMain";
			this->tlpMain->RowCount = 1;
			this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tlpMain->Size = System::Drawing::Size(622, 387);
			this->tlpMain->TabIndex = 3;
			this->tlpMain->SizeChanged += gcnew System::EventHandler(this, &FormMain::tlpMain_SizeChanged);

			this->panelClient->Controls->Add(this->tlpMain);
		}

		for each(Control^ control in tlpMain->Controls)
		{
			ListViewForScroll^ other = (ListViewForScroll^)control;
			lv->others_.Add(other);

			other->others_.Add(lv);
		}
		tlpMain->ColumnCount++;
		tlpMain->Controls->Add(lv, tlpMain->ColumnCount-1, 0);
		tlpMain->ColumnStyles->Clear();
		for(int i=0 ; i < tlpMain->ColumnCount; ++i)
		{
			tlpMain->ColumnStyles->Add((gcnew ColumnStyle(SizeType::Percent, 100.0F/tlpMain->ColumnCount)));
		}
	}

	void FormMain::removeColumn()
	{
		if(tlpMain->ColumnCount <= 2)
			return;

		tlpMain->ColumnCount--;
		// tlpMain->Controls->R Add(lv, tlpMain->ColumnCount-1, 0);
		tlpMain->ColumnStyles->Clear();
		for(int i=0 ; i < tlpMain->ColumnCount; ++i)
			tlpMain->ColumnStyles->Add((gcnew ColumnStyle(SizeType::Percent, 100.0F/tlpMain->ColumnCount)));
	}

	void FormMain::updateTitle(int addCount, int replaceCount, int deleteCount, int nochangeCount)
	{
		System::Text::StringBuilder title;
		System::Text::StringBuilder msg;
		if(addCount==0 && replaceCount==0 && deleteCount==0)
		{
			title.Append(L"Identical");
			msg.Append(L"Identical");
		}
		else
		{
			title.Append(addCount);
			title.Append(L" : ");

			msg.Append(L"Add"+L": "+addCount.ToString());
			msg.Append(L" ");
			

			
			title.Append(replaceCount);
			title.Append(L" : ");
			
			msg.Append(L"Replace"+L": "+replaceCount.ToString());
			msg.Append(L" ");



			title.Append(deleteCount);
			title.Append(L" : ");

			msg.Append(L"Delete"+L": "+deleteCount.ToString());
			msg.Append(L" ");



			title.Append(nochangeCount);
			msg.Append(L"Nochange"+L": "+nochangeCount.ToString());
		}

		slChange->Text = msg.ToString();

		
		title.Append(L" | ");
		title.Append(Application::ProductName);
		Text = title.ToString();

	}

	void FormMain::updateTitle()
	{
		updateTitle(0,0,0,0);
	}

	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		de_ = gcnew DifferenceEngine::DiffEngine();
		ClipboardViewerNext_ = SetClipboardViewer((HWND)this->Handle.ToPointer());

		this->Text = Application::ProductName;
	}



	System::Void FormMain::tlpMain_SizeChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//lv1->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
		//lv2->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);

		//int width = Math::Max(chText1->Width, chText2->Width);

		//lv1->AutoResizeColumns(ColumnHeaderAutoResizeStyle::None);
		//lv2->AutoResizeColumns(ColumnHeaderAutoResizeStyle::None);

		//chText1->Width = width;
		//chText2->Width = width;


		//lv2->Columns["Text"]->Width = width;
		//int hPad = lv1->Padding.Left + lv1->Padding.Right;
		//int i = lv1->Columns->IndexOfKey("Text");
		// lv1->Columns[i];
	}





	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		String^ inipath = AmbLib::GetIniPath();
		HashIni^ ini =  Profile::ReadAll(inipath);
		Profile::WriteInt(APP_OPTION, L"X", this->Location.X, ini);
		Profile::WriteInt(APP_OPTION, L"Y", this->Location.Y, ini);

		Profile::WriteInt(APP_OPTION, L"Width", this->Size.Width , ini);
		Profile::WriteInt(APP_OPTION, L"Height", this->Size.Height, ini);

		String^ fontstring=L"";
		if(FontLV) {
			System::ComponentModel::TypeConverter^ converter =
				System::ComponentModel::TypeDescriptor::GetConverter( System::Drawing::Font::typeid );

			fontstring = converter->ConvertToInvariantString(FontLV);


			// System::Drawing::Font^ font1 = dynamic_cast<System::Drawing::Font^>(converter->ConvertFromString( "Arial, 12pt" ));
		}
		Profile::WriteString(APP_OPTION, L"Font", fontstring, ini);


		Profile::WriteBool(APP_OPTION, L"ShowToolbar", toolMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, L"ShowStatusbar", stMain->Visible, ini);
		Profile::WriteBool(APP_OPTION, L"ShowListheader", IsHeaderVisible, ini);

		Profile::WriteInt(APP_OPTION, L"EngineLevel", (int)EngineLevel, ini);

		for(;;)
		{
			try
			{
				Profile::WriteAll(ini, inipath,true);
				break;

			}
			catch(Exception^ ex)
			{
				if(System::Windows::Forms::DialogResult::Retry != MessageBox::Show(I18N("Failed to save settings." + "\r\n" + ex->Message),
					Application::ProductName,
					MessageBoxButtons::RetryCancel,
					MessageBoxIcon::Exclamation))
				{
					break;
				}
			}
		}


	}

	void FormMain::onKeep()
	{
		IsKeep = !IsKeep;

		tsmKeep->Checked = IsKeep;
		tsbKeep->Checked = IsKeep;
	}
	void FormMain::onIgnoreSame()
	{
		IsIgnoreSame = !IsIgnoreSame;

		tsmIgnoreSame->Checked=IsIgnoreSame;
		tsbIgnoreSame->Checked=IsIgnoreSame;
	}
	System::Void FormMain::onTopMost(System::Object^  sender, System::EventArgs^  e)
	{
		bool newvalue = !tsmTopMost->Checked;
		tsmTopMost->Checked = newvalue;
		tsbTopMost->Checked = newvalue;

		this->TopMost = newvalue;
	}

	System::Void FormMain::windowToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
	{
		tsmTopMost->Checked = this->TopMost;
	}


	System::Void FormMain::FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		ChangeClipboardChain((HWND)this->Handle.ToPointer(), ClipboardViewerNext_);
		ClipboardViewerNext_ = NULL;
	}
	System::Void FormMain::exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	System::Void FormMain::addColumnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		addColumn();
	}
	System::Void FormMain::removeColumnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		removeColumn();
	}


	System::Void FormMain::tsmIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e) {
		onIgnoreSame();
	}
	System::Void FormMain::tsbIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e) {
		onIgnoreSame();
	}

	System::Void FormMain::tsmKeep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onKeep();
	}
	System::Void FormMain::tsbKeep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		onKeep();
	}

	System::Void FormMain::tsmFont_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		FontDialog dlg;
		dlg.Font=FontLV;
		if(System::Windows::Forms::DialogResult::OK != dlg.ShowDialog())
			return;


		for(int i=0 ; i < tlpMain->Controls->Count; ++i)
		{
			ListViewForScroll^ lv = (ListViewForScroll^)tlpMain->Controls[i];
			lv->Font = dlg.Font;
		}
		FontLV = dlg.Font;
	}

	System::Void FormMain::toolMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
	{
		tsmShowToolbar->Checked = toolMain->Visible;
	}
	System::Void FormMain::tsmShowToolbar_Click(System::Object^  sender, System::EventArgs^  e)
	{
		toolMain->Visible = !toolMain->Visible;
	}

	System::Void FormMain::stMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
	{
		tsmShowStatusbar->Checked = stMain->Visible;
	}
	System::Void FormMain::tsmShowStatusbar_Click(System::Object^  sender, System::EventArgs^  e)
	{
		stMain->Visible = !stMain->Visible;
	}

	System::Void FormMain::viewToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
	{
		bool visible = !(((ListViewForScroll^)(tlpMain->Controls[0]))->HeaderStyle==ColumnHeaderStyle::None);
		tsmShowListheader->Checked = visible;
	}
	System::Void FormMain::tsmShowListheader_Click(System::Object^  sender, System::EventArgs^  e)
	{
		IsHeaderVisible = !IsHeaderVisible;
		for each(Control^ control in tlpMain->Controls)
		{
			ListViewForScroll^ list = (ListViewForScroll^)control;
			list->HeaderStyle = IsHeaderVisible ? ColumnHeaderStyle::Nonclickable : ColumnHeaderStyle::None;
		}
	}



	System::Void FormMain::engineLevelToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e) 
	{
		tsmELFast->Checked = false;
		tsmELMedium->Checked = false;
		tsmELSlow->Checked = false;

		switch(EngineLevel)
		{
		case DifferenceEngine::DiffEngineLevel::FastImperfect:
			tsmELFast->Checked = true;
			break;
		case DifferenceEngine::DiffEngineLevel::Medium:
			tsmELMedium->Checked = true;
			break;
		case DifferenceEngine::DiffEngineLevel::SlowPerfect:
			tsmELSlow->Checked = true;
			break;
		default:
			System::Diagnostics::Debug::Assert(false);
			break;
		}
	}

	System::Void FormMain::tsmELFast_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		EngineLevel = DifferenceEngine::DiffEngineLevel::FastImperfect;
	}
	System::Void FormMain::tsmELMedium_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		EngineLevel = DifferenceEngine::DiffEngineLevel::Medium;
	}
	System::Void FormMain::tsmELSlow_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		EngineLevel = DifferenceEngine::DiffEngineLevel::SlowPerfect;
	}


	using namespace System::Collections::Generic;
	using namespace System::IO;
	List<StreamWriter^>^ FormMain::GetsaveAsFiles(int filecount, String^ filenamepre)
	{
		List<StreamWriter^>^ ret = gcnew List<StreamWriter^>();
		try
		{
			for(int i=0 ; i < filecount; ++i)
			{
				String^ filename = filenamepre + (i+1).ToString() + L".txt";
				if(System::IO::File::Exists(filename))
				{
					return nullptr;
				}
	
				StreamWriter^ sw = gcnew StreamWriter(filename, false, System::Text::Encoding::UTF8);
				ret->Add(sw);
			}
			return ret;
		}
		catch(System::Exception^)
		{}

		return nullptr;
		
	}
	System::Void FormMain::tsmSaveAs_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		String^ path = Environment::GetFolderPath(Environment::SpecialFolder::Desktop);

		String^ filenamepre = path + L"\\" + Application::ProductName + Environment::TickCount.ToString() + L"-";
		List<StreamWriter^>^ files = GetsaveAsFiles(tlpMain->Controls->Count, filenamepre);
		if(!files) 
		{
			MessageBox::Show(L"Could not create file on" + L" " + path,
				Application::ProductName);
			return;
		}

		try
		{
			for(int i=0 ; i < tlpMain->Controls->Count; ++i)
			{
				StreamWriter^ sw=files[i];

				ListViewForScroll^ list = (ListViewForScroll^)tlpMain->Controls[i];
				String^ text=list->GetDiff()->GetText();
				sw->Write(text);
				sw->Close();
			}
		}
		catch(System::Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName);
		}
	}

}

