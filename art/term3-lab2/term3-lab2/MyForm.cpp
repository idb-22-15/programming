#include "MyForm.h"
#include <locale>
#include <windows.h>


// �������� �� ������
// box, button, grid �����������
// �������� ������, ���� �� ��� ����

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute] void main(array<String ^> ^ args) {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  term3lab2::MyForm form;
  
  Application::Run(% form);
}