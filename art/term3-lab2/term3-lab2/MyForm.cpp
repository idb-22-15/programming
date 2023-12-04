#include "MyForm.h"
#include <locale>
#include <windows.h>


// пересчёт по кнопке
// box, button, grid обязательно
// проверка данных, если не ввёл тоже

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute] void main(array<String ^> ^ args) {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  term3lab2::MyForm form;
  
  Application::Run(% form);
}