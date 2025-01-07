#pragma once

#include "../Disk/Disk.h"
#include "Disk/DiskBenchmarkForm.h"
#include <thread>

namespace SystemUtils {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ runDiskBenchmarkButton;
	protected:

	protected:

	private:
		// Required designer variable.
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->runDiskBenchmarkButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// runDiskBenchmarkButton
			// 
			this->runDiskBenchmarkButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->runDiskBenchmarkButton->Location = System::Drawing::Point(13, 12);
			this->runDiskBenchmarkButton->Name = L"runDiskBenchmarkButton";
			this->runDiskBenchmarkButton->Size = System::Drawing::Size(401, 47);
			this->runDiskBenchmarkButton->TabIndex = 0;
			this->runDiskBenchmarkButton->Text = L"Run Disk Benchmark";
			this->runDiskBenchmarkButton->UseVisualStyleBackColor = true;
			this->runDiskBenchmarkButton->Click += gcnew System::EventHandler(this, &MainForm::runDiskBenchmarkButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(426, 402);
			this->Controls->Add(this->runDiskBenchmarkButton);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"MainForm";
			this->Text = L"System Utils";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void runDiskBenchmarkButton_Click(System::Object^ sender, System::EventArgs^ e) {
		DiskBenchmarkForm^ diskBenchmarkForm = gcnew DiskBenchmarkForm();
		diskBenchmarkForm->Show();
	}
	};
}
