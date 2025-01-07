#include "MainForm.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SystemUtils::MainForm form;
	Application::Run(% form);
}