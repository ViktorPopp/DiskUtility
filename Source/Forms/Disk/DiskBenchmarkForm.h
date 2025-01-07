#pragma once

#include "../../Disk/Disk.h"
#include <thread>
#include <msclr/marshal_cppstd.h>

namespace SystemUtils {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class DiskBenchmarkForm : public System::Windows::Forms::Form
	{
	public:
		DiskBenchmarkForm(void)
		{
			InitializeComponent();
		}

	protected:
		~DiskBenchmarkForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ sizeLabel;
	private: System::Windows::Forms::NumericUpDown^ sizeInput;
	private: System::Windows::Forms::Label^ driveLetterLabel;
	private: System::Windows::Forms::ComboBox^ driveLetterInput;
	private: System::Windows::Forms::CheckBox^ useCachingCheckBox;
	private: System::Windows::Forms::NumericUpDown^ iterationCountInput;
	private: System::Windows::Forms::Label^ iterationCountLabel;
	private: System::Windows::Forms::Button^ runDiskBenchmarkButton;

	protected:

	protected:




	private:
		/// Required designer variable.
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->sizeLabel = (gcnew System::Windows::Forms::Label());
			this->sizeInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->driveLetterLabel = (gcnew System::Windows::Forms::Label());
			this->driveLetterInput = (gcnew System::Windows::Forms::ComboBox());
			this->useCachingCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->iterationCountInput = (gcnew System::Windows::Forms::NumericUpDown());
			this->iterationCountLabel = (gcnew System::Windows::Forms::Label());
			this->runDiskBenchmarkButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sizeInput))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->iterationCountInput))->BeginInit();
			this->SuspendLayout();
			// 
			// sizeLabel
			// 
			this->sizeLabel->AutoSize = true;
			this->sizeLabel->Location = System::Drawing::Point(12, 49);
			this->sizeLabel->Name = L"sizeLabel";
			this->sizeLabel->Size = System::Drawing::Size(115, 13);
			this->sizeLabel->TabIndex = 0;
			this->sizeLabel->Text = L"Size to read/write (MB)";
			// 
			// sizeInput
			// 
			this->sizeInput->Location = System::Drawing::Point(12, 65);
			this->sizeInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32768, 0, 0, 0 });
			this->sizeInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->sizeInput->Name = L"sizeInput";
			this->sizeInput->Size = System::Drawing::Size(120, 20);
			this->sizeInput->TabIndex = 1;
			this->sizeInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// driveLetterLabel
			// 
			this->driveLetterLabel->AutoSize = true;
			this->driveLetterLabel->Location = System::Drawing::Point(12, 9);
			this->driveLetterLabel->Name = L"driveLetterLabel";
			this->driveLetterLabel->Size = System::Drawing::Size(84, 13);
			this->driveLetterLabel->TabIndex = 2;
			this->driveLetterLabel->Text = L"Drive/Disk letter";
			// 
			// driveLetterInput
			// 
			this->driveLetterInput->FormattingEnabled = true;
			this->driveLetterInput->Items->AddRange(gcnew cli::array< System::Object^  >(26) {
				L"A", L"B", L"C", L"D", L"E", L"F", L"G",
					L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", L"T", L"U", L"V", L"W", L"X", L"Y", L"Z"
			});
			this->driveLetterInput->Location = System::Drawing::Point(12, 25);
			this->driveLetterInput->Name = L"driveLetterInput";
			this->driveLetterInput->Size = System::Drawing::Size(121, 21);
			this->driveLetterInput->TabIndex = 3;
			// 
			// useCachingCheckBox
			// 
			this->useCachingCheckBox->AutoSize = true;
			this->useCachingCheckBox->Location = System::Drawing::Point(12, 91);
			this->useCachingCheckBox->Name = L"useCachingCheckBox";
			this->useCachingCheckBox->Size = System::Drawing::Size(92, 17);
			this->useCachingCheckBox->TabIndex = 5;
			this->useCachingCheckBox->Text = L"Use caching\?";
			this->useCachingCheckBox->UseVisualStyleBackColor = true;
			// 
			// iterationCountInput
			// 
			this->iterationCountInput->Location = System::Drawing::Point(12, 127);
			this->iterationCountInput->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32768, 0, 0, 0 });
			this->iterationCountInput->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->iterationCountInput->Name = L"iterationCountInput";
			this->iterationCountInput->Size = System::Drawing::Size(120, 20);
			this->iterationCountInput->TabIndex = 7;
			this->iterationCountInput->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// iterationCountLabel
			// 
			this->iterationCountLabel->AutoSize = true;
			this->iterationCountLabel->Location = System::Drawing::Point(12, 111);
			this->iterationCountLabel->Name = L"iterationCountLabel";
			this->iterationCountLabel->Size = System::Drawing::Size(75, 13);
			this->iterationCountLabel->TabIndex = 6;
			this->iterationCountLabel->Text = L"Iteration count";
			// 
			// runDiskBenchmarkButton
			// 
			this->runDiskBenchmarkButton->Location = System::Drawing::Point(13, 154);
			this->runDiskBenchmarkButton->Name = L"runDiskBenchmarkButton";
			this->runDiskBenchmarkButton->Size = System::Drawing::Size(120, 23);
			this->runDiskBenchmarkButton->TabIndex = 8;
			this->runDiskBenchmarkButton->Text = L"Run disk benchmark";
			this->runDiskBenchmarkButton->UseVisualStyleBackColor = true;
			this->runDiskBenchmarkButton->Click += gcnew System::EventHandler(this, &DiskBenchmarkForm::runDiskBenchmarkButton_Click);
			// 
			// DiskBenchmarkForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->runDiskBenchmarkButton);
			this->Controls->Add(this->iterationCountInput);
			this->Controls->Add(this->iterationCountLabel);
			this->Controls->Add(this->useCachingCheckBox);
			this->Controls->Add(this->driveLetterInput);
			this->Controls->Add(this->driveLetterLabel);
			this->Controls->Add(this->sizeInput);
			this->Controls->Add(this->sizeLabel);
			this->Name = L"DiskBenchmarkForm";
			this->Text = L"DiskBenchmarkForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sizeInput))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->iterationCountInput))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void runDiskBenchmarkButton_Click(System::Object^ sender, System::EventArgs^ e) {
		//TODO: Implement more checks. Also don't ouput to terminal window.
		if (driveLetterInput->SelectedItem->ToString() == L"C")
		{
			MessageBox::Show("System Utils will need admin privileges to run disk benchmark on system drive: \"C\"", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		std::string driveLetter = msclr::interop::marshal_as<std::string>(driveLetterInput->SelectedItem->ToString());
		int size = static_cast<int>(sizeInput->Value);
		bool useCaching = useCachingCheckBox->Checked;
		int iterationCount = static_cast<int>(iterationCountInput->Value);

		std::thread diskBenchmarkThread(Disk::Benchmark::performDiskTests, driveLetter, size, useCaching, iterationCount);
		diskBenchmarkThread.detach();
	}
};
}
