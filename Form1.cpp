#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  oop_laba8::MainForm form;
  Application::Run(% form);
}
