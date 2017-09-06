#pragma once

#include "ListViewForScroll.h"
namespace clipdiff {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//ref class DiffList;


	/// <summary>
	/// Summary for FormMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
		literal String^ APP_OPTION = L"Option";

	private:
		HANDLE childProcess_;
		System::Windows::Forms::ToolStripMenuItem^  tsmDocdiffChar;
		System::Windows::Forms::ToolStripMenuItem^  tsmGotoWebpage;
		System::Windows::Forms::ContextMenuStrip^  ctxMenuList;
		System::Windows::Forms::ToolStripMenuItem^  tsmCompareThisLineWithDocdiffChar;
		System::Windows::Forms::ToolStripMenuItem^  tsmCompareThisLineWithDocdiffword;


		static System::Resources::ResourceManager^ theResource_ =
			gcnew System::Resources::ResourceManager(FormMain::typeid->Namespace + ".StringResource", System::Reflection::Assembly::GetExecutingAssembly());

	internal:
		static String^ getI18NString(String^ sIn)
		{
			String^ ret = theResource_->GetString(sIn);
			return String::IsNullOrEmpty(ret) ? sIn : ret;
		}

	private:
		HWND childHwnd_;
		HWND GetChildMainFormWindow();
		bool RunDocDiff();
		bool RunDocDiff(String^ text1, String^ text2, DocDiffEngineKind dk, bool standalone);
		void compareSelectedLineWithDocdiff(DocDiffEngineKind dk);
		System::Void lv_doubleClick(System::Object^  sender, System::EventArgs^  e);
		Panel^ GetPanel(int i);
		ToolStripItem^ GetSS(int i);
		ListViewForScroll^ GetList(int i);
		void UpdateView();
		void UpdateView2();
		void renderAllDiff();
		String^ GetDocdiffEngineLevelAsString(DocDiffEngineKind dk);
	public:
		FormMain(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuMain;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmEdit;






















	private: System::Windows::Forms::ToolStripMenuItem^  tsmAddColumn;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmRemoveColumn;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;

	private: System::Windows::Forms::StatusStrip^  stMain;
	private: System::Windows::Forms::ToolStripStatusLabel^  stlMain;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmWindow;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmTopMost;



	private: System::Windows::Forms::TableLayoutPanel^ tlpMain;
	private: System::Windows::Forms::Panel^  panelClient;
	private: System::Windows::Forms::ToolStripSeparator^  tsmSepCopyTop;



	private: System::Windows::Forms::ToolStrip^  toolMain;
	private: System::Windows::Forms::ToolStripButton^  tsbKeep;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmKeep;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmIgnoreSame;
	private: System::Windows::Forms::ToolStripButton^  tsbIgnoreSame;
	private: System::Windows::Forms::ToolStripButton^  tsbTopMost;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmAbout;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmFont;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmView;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowToolbar;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowStatusbar;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmShowListheader;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmEngineLevel;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELFast;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELMedium;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmELSlow;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmSaveAs;
	private: System::Windows::Forms::ToolStripStatusLabel^  slChange;
	private: System::Windows::Forms::ToolStripStatusLabel^  stlResult;

	private: System::Windows::Forms::ToolStripMenuItem^  tsmMonitorClipboard;
	private: System::Windows::Forms::ToolStripButton^  tsbMonitorClipboard;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmPaste;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripButton^  tsbPaste;
	private: System::Windows::Forms::SplitContainer^  spRoot;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^  tsmDocdiffWord;










	protected:
		virtual void WndProc(System::Windows::Forms::Message% m) override = Control::WndProc;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void);

#pragma endregion

		HWND ClipboardViewerNext_;
		DifferenceEngine::DiffEngine^ de_;
		//DiffList^ df1_;
		//DiffList^ df2_;
		String^ lastText_;
		void onKeepLeft();
		bool isKeep_;
		property bool IsKeepLeft
		{
			bool get();
			void set(bool value);
		}

		void onIgnoreSame();
		bool isIgnoreSame_;
		property bool IsIgnoreSame
		{
			bool get();
			void set(bool value);
		}


		property System::Drawing::Font^ FontLV;
		property bool IsHeaderVisible;



		EngineKind engine_;
		EngineKind updatedEngine_;
		property EngineKind Engine
		{
			EngineKind get();
			void set(EngineKind value);
		}

		DifferenceEngine::DiffEngineLevel engineLevel_;
		DifferenceEngine::DiffEngineLevel updatedEngineLevel_;
		property DifferenceEngine::DiffEngineLevel EngineLevel
		{
			DifferenceEngine::DiffEngineLevel get();
			void set(DifferenceEngine::DiffEngineLevel value);
		}

		DocDiffEngineKind docdiffEngineLevel_;
		DocDiffEngineKind updatedDocdiffEngineLevel_;
		property DocDiffEngineKind DocDiffEngineLevel
		{
			DocDiffEngineKind get();
			void set(DocDiffEngineKind value);
		}


		void onMonitor();
		bool isMonitor_;
		property bool IsMonitor
		{
			bool get();
			void set(bool value);
		}

		initonly Ambiesoft::HashIni^ InitialIni_;

		void onIdle(Object^ sender, EventArgs^ e);

		bool isIdling_;
		property bool IsIdling
		{
			bool get();
			void set(bool value);
		}
	protected:

		void renderDiff(ListView^ lvOld, ListView^ lvNew);
		void addColumn();
		void removeColumn();
		void updateTitle(int addCount, int replaceCount, int deleteCount, int nochangeCount);
		void updateTitle();
		void pasteClipboard();
		void pasteClipboard(bool showError);

		System::Collections::Generic::List<System::IO::StreamWriter^>^ GetsaveAsFiles(int filecount, String^ filenamepre, System::Collections::Generic::List<String^>^ filenames);

		System::Void copy_Clicked(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
		System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmAddColumn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmRemoveColumn_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tlpMain_SizeChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void onTopMost(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmWindow_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void tsmIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbIgnoreSame_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmAbout_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmKeep_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbKeep_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmFont_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmShowToolbar_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmShowStatusbar_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmShowListheader_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void toolMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void stMain_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmView_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmELFast_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmELMedium_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmELSlow_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmEngineLevel_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmSaveAs_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmEdit_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmMonitorClipboard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbMonitorClipboard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmPaste_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsbPaste_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmDocdiffWord_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void spRoot_Panel2_Resize(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmDocdiffChar_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmGotoWebpage_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmCompareThisLineWithDocdiffword_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tsmCompareThisLineWithDocdiffChar_Click(System::Object^  sender, System::EventArgs^  e);

	}; // class FormMain

} // namespace clipdiff

