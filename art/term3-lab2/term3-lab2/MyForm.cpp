#include "MyForm.h"
#include <windows.h>

// Дана матрица размера M x N.
// Вывести количество строк, в которых нет нулевых элементов.

// считать из файла можно только полностью заполненную матрицу
// в которой числа разделены пробелом
// размер матрицы произвольный
// файл не может быть пустым

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute] void main(array<String ^> ^ args) {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  term3lab2::MyForm form;

  Application::Run(% form);
}
