#pragma once
#include "Matrix.cpp"
#include "Utils.cpp"

namespace term3lab2 {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Сводка для MyForm
/// </summary>
public
ref class MyForm : public System::Windows::Forms::Form {
 public:
  MyForm() { InitializeComponent(); }

 protected:
  ~MyForm() {
    if (components) {
      delete components;
      delete matrix;
    }
  }

 private:
  Matrix* matrix = nullptr;

 private:
  System::Windows::Forms::Label ^ labelRows;

 private:
  System::Windows::Forms::Label ^ labelCols;

 private:
  System::Windows::Forms::Button ^ buttonSetGridSize;

 private:
  System::Windows::Forms::DataGridView ^ gridView;

 private:
  System::Windows::Forms::TextBox ^ inputRows;

 private:
  System::Windows::Forms::TextBox ^ inputCols;

 private:
  System::Windows::Forms::Label ^ labelCounterRowsWithoutZerosDescription;

 private:
  System::Windows::Forms::Label ^ labelCounterRowsWithoutZeros;

 private:
  System::Windows::Forms::Button ^ buttonClearGrid;

 private:
  System::Windows::Forms::Button ^ buttonCloseApp;

 private:
  System::Windows::Forms::Button ^ buttonComputeCounterRowsWithoutZeros;

 private:
  System::Windows::Forms::Button ^ buttonRandomizeGrid;

 private:
  System::Windows::Forms::TextBox ^ inputFilename;

 private:
  System::Windows::Forms::Button ^ buttonFillMatrix;

 private:
 private:
 private:
  System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
  /// <summary>
  /// Требуемый метод для поддержки конструктора — не изменяйте
  /// содержимое этого метода с помощью редактора кода.
  /// </summary>
  void InitializeComponent(void) {
    System::ComponentModel::ComponentResourceManager ^ resources =
        (gcnew System::ComponentModel::ComponentResourceManager(
            MyForm::typeid));
    this->labelRows = (gcnew System::Windows::Forms::Label());
    this->labelCols = (gcnew System::Windows::Forms::Label());
    this->buttonSetGridSize = (gcnew System::Windows::Forms::Button());
    this->gridView = (gcnew System::Windows::Forms::DataGridView());
    this->inputRows = (gcnew System::Windows::Forms::TextBox());
    this->inputCols = (gcnew System::Windows::Forms::TextBox());
    this->labelCounterRowsWithoutZerosDescription =
        (gcnew System::Windows::Forms::Label());
    this->labelCounterRowsWithoutZeros =
        (gcnew System::Windows::Forms::Label());
    this->buttonClearGrid = (gcnew System::Windows::Forms::Button());
    this->buttonCloseApp = (gcnew System::Windows::Forms::Button());
    this->buttonComputeCounterRowsWithoutZeros =
        (gcnew System::Windows::Forms::Button());
    this->buttonRandomizeGrid = (gcnew System::Windows::Forms::Button());
    this->inputFilename = (gcnew System::Windows::Forms::TextBox());
    this->buttonFillMatrix = (gcnew System::Windows::Forms::Button());
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->gridView))
        ->BeginInit();
    this->SuspendLayout();
    //
    // labelRows
    //
    resources->ApplyResources(this->labelRows, L"labelRows");
    this->labelRows->Name = L"labelRows";
    //
    // labelCols
    //
    resources->ApplyResources(this->labelCols, L"labelCols");
    this->labelCols->Name = L"labelCols";
    //
    // buttonSetGridSize
    //
    resources->ApplyResources(this->buttonSetGridSize, L"buttonSetGridSize");
    this->buttonSetGridSize->Cursor = System::Windows::Forms::Cursors::Hand;
    this->buttonSetGridSize->Name = L"buttonSetGridSize";
    this->buttonSetGridSize->UseVisualStyleBackColor = true;
    this->buttonSetGridSize->Click +=
        gcnew System::EventHandler(this, &MyForm::SetGridSize);
    //
    // gridView
    //
    resources->ApplyResources(this->gridView, L"gridView");
    this->gridView->AllowUserToAddRows = false;
    this->gridView->AllowUserToDeleteRows = false;
    this->gridView->AllowUserToResizeColumns = false;
    this->gridView->AllowUserToResizeRows = false;
    this->gridView->BackgroundColor = System::Drawing::Color::White;
    this->gridView->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
    this->gridView->ColumnHeadersBorderStyle =
        System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
    this->gridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::
        DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->gridView->Name = L"gridView";
    this->gridView->RowHeadersVisible = false;
    this->gridView->RowHeadersWidthSizeMode = System::Windows::Forms::
        DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
    this->gridView->RowTemplate->Height = 28;
    this->gridView->CellEndEdit +=
        gcnew System::Windows::Forms::DataGridViewCellEventHandler(
            this, &MyForm::gridView_CellEndEdit);
    //
    // inputRows
    //
    resources->ApplyResources(this->inputRows, L"inputRows");
    this->inputRows->Name = L"inputRows";
    //
    // inputCols
    //
    resources->ApplyResources(this->inputCols, L"inputCols");
    this->inputCols->Name = L"inputCols";
    //
    // labelCounterRowsWithoutZerosDescription
    //
    resources->ApplyResources(this->labelCounterRowsWithoutZerosDescription,
                              L"labelCounterRowsWithoutZerosDescription");
    this->labelCounterRowsWithoutZerosDescription->Name =
        L"labelCounterRowsWithoutZerosDescription";
    //
    // labelCounterRowsWithoutZeros
    //
    resources->ApplyResources(this->labelCounterRowsWithoutZeros,
                              L"labelCounterRowsWithoutZeros");
    this->labelCounterRowsWithoutZeros->Name = L"labelCounterRowsWithoutZeros";
    //
    // buttonClearGrid
    //
    resources->ApplyResources(this->buttonClearGrid, L"buttonClearGrid");
    this->buttonClearGrid->Cursor = System::Windows::Forms::Cursors::Hand;
    this->buttonClearGrid->Name = L"buttonClearGrid";
    this->buttonClearGrid->UseVisualStyleBackColor = true;
    this->buttonClearGrid->Click +=
        gcnew System::EventHandler(this, &MyForm::buttonClearGrid_Click);
    //
    // buttonCloseApp
    //
    resources->ApplyResources(this->buttonCloseApp, L"buttonCloseApp");
    this->buttonCloseApp->BackColor = System::Drawing::Color::White;
    this->buttonCloseApp->Cursor = System::Windows::Forms::Cursors::Hand;
    this->buttonCloseApp->Name = L"buttonCloseApp";
    this->buttonCloseApp->UseVisualStyleBackColor = false;
    this->buttonCloseApp->Click +=
        gcnew System::EventHandler(this, &MyForm::CloseApp);
    this->buttonCloseApp->MouseLeave +=
        gcnew System::EventHandler(this, &MyForm::buttonCloseApp_MouseLeave);
    this->buttonCloseApp->MouseHover +=
        gcnew System::EventHandler(this, &MyForm::buttonCloseApp_MouseHover);
    //
    // buttonComputeCounterRowsWithoutZeros
    //
    resources->ApplyResources(this->buttonComputeCounterRowsWithoutZeros,
                              L"buttonComputeCounterRowsWithoutZeros");
    this->buttonComputeCounterRowsWithoutZeros->Cursor =
        System::Windows::Forms::Cursors::Hand;
    this->buttonComputeCounterRowsWithoutZeros->Name =
        L"buttonComputeCounterRowsWithoutZeros";
    this->buttonComputeCounterRowsWithoutZeros->UseVisualStyleBackColor = true;
    this->buttonComputeCounterRowsWithoutZeros->Click +=
        gcnew System::EventHandler(
            this, &MyForm::buttonComputeCounterRowsWithoutZeros_Click);
    //
    // buttonRandomizeGrid
    //
    resources->ApplyResources(this->buttonRandomizeGrid,
                              L"buttonRandomizeGrid");
    this->buttonRandomizeGrid->Cursor = System::Windows::Forms::Cursors::Hand;
    this->buttonRandomizeGrid->Name = L"buttonRandomizeGrid";
    this->buttonRandomizeGrid->UseVisualStyleBackColor = true;
    this->buttonRandomizeGrid->Click +=
        gcnew System::EventHandler(this, &MyForm::buttonRandomizeGrid_Click);
    //
    // inputFilename
    //
    resources->ApplyResources(this->inputFilename, L"inputFilename");
    this->inputFilename->Name = L"inputFilename";
    //
    // buttonFillMatrix
    //
    resources->ApplyResources(this->buttonFillMatrix, L"buttonFillMatrix");
    this->buttonFillMatrix->Cursor = System::Windows::Forms::Cursors::Hand;
    this->buttonFillMatrix->Name = L"buttonFillMatrix";
    this->buttonFillMatrix->UseVisualStyleBackColor = true;
    this->buttonFillMatrix->Click +=
        gcnew System::EventHandler(this, &MyForm::buttonFillMatrix_Click);
    //
    // MyForm
    //
    resources->ApplyResources(this, L"$this");
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->BackColor = System::Drawing::Color::White;
    this->ControlBox = false;
    this->Controls->Add(this->inputFilename);
    this->Controls->Add(this->buttonRandomizeGrid);
    this->Controls->Add(this->buttonFillMatrix);
    this->Controls->Add(this->buttonComputeCounterRowsWithoutZeros);
    this->Controls->Add(this->buttonCloseApp);
    this->Controls->Add(this->labelCounterRowsWithoutZeros);
    this->Controls->Add(this->labelCounterRowsWithoutZerosDescription);
    this->Controls->Add(this->inputCols);
    this->Controls->Add(this->inputRows);
    this->Controls->Add(this->gridView);
    this->Controls->Add(this->buttonClearGrid);
    this->Controls->Add(this->buttonSetGridSize);
    this->Controls->Add(this->labelCols);
    this->Controls->Add(this->labelRows);
    this->Name = L"MyForm";
    this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->gridView))
        ->EndInit();
    this->ResumeLayout(false);
    this->PerformLayout();
  }
#pragma endregion

 private:
  System::Void CloseApp(System::Object ^ sender, System::EventArgs ^ e) {
    this->Close();
  }

 private:
  System::Void ShowError(System::String ^ message) {
    MessageBox::Show(message, "", MessageBoxButtons::OK, MessageBoxIcon::Error);
  }

 private:
  void ColorizeGridRowsWithoutZeros() {
    this->ResetGridViewCellsColor();

    for (size_t i = 0; i < this->matrix->getRows(); i++) {
      bool rowHaveZeros = false;
      size_t zeros = 0;
      for (size_t j = 0; j < this->matrix->getCols(); j++) {
        if (this->matrix->getCellValue(i, j) == 0) {
          rowHaveZeros = true;
          zeros++;
        }
      }

      if (!rowHaveZeros) {
        this->ColorizeGridViewRow(i, System::Drawing::Color::LightGreen);
      }
    }
  }

 private:
  System::Void ColorizeGridViewRow(size_t row,
                                   System::Drawing::Color color) {
    for (size_t colIndex = 0; colIndex < this->matrix->getCols(); colIndex++) {
      this->gridView->Rows[row]->Cells[colIndex]->Style->BackColor = color;
    }
  }

 private:
  System::Void ResetGridViewCellsColor() {
    for (size_t rowIndex = 0; rowIndex < this->matrix->getRows(); rowIndex++) {
      this->ColorizeGridViewRow(rowIndex, System::Drawing::Color::White);
    }
  }

 private:
  System::Boolean IsMatrixExist() { return this->matrix != nullptr; }

 private:
  System::Void SetGridSize(System::Object ^ sender, System::EventArgs ^ e) {
    if (this->IsMatrixExist() && this->matrix->isNotEmpty()) {
      this->ShowError("Matrix is not empty, clear matrix to set new size");
      return;
    }

    size_t rows;
    size_t cols;

    try {
      rows = this->ParseSize(inputRows->Text);
    } catch (...) {
      this->ShowError("The number of rows is entered incorrectly");
      rows = 1;
      this->inputRows->Text = System::Convert::ToString(rows);
      return;
    }

    try {
      cols = this->ParseSize(inputCols->Text);
    } catch (...) {
      this->ShowError("The number of columns is entered incorrectly");
      cols = 1;
      this->inputCols->Text = System::Convert::ToString(cols);
      return;
    }

    delete this->matrix;
    matrix = new Matrix(rows, cols);
    this->ShowGridView();
    this->EnableButtons();
  }

 private:
  System::Void EnableButtons() {
    this->buttonClearGrid->Enabled = true;
    this->buttonRandomizeGrid->Enabled = true;
    this->buttonComputeCounterRowsWithoutZeros->Enabled = true;
  }

 private:
  size_t ParseSize(System::String ^ rawSize) {
    System::Boolean isValid = true;

    System::Int32 newSize = System::Int32::Parse(rawSize);

    System::Exception ^ e = gcnew System::Exception;

    if (newSize <= 0)
      throw e;

    return newSize;
  }

 private:
  System::Void UpdateLabel(Label ^ label, System::String ^ text) {
    label->Text = text;
  }

 private:
  System::Void ShowGridView() {
    this->gridView->RowCount = this->matrix->getRows();
    this->gridView->ColumnCount = this->matrix->getCols();

    for (size_t i = 0; i < this->matrix->getRows(); i++) {
      for (size_t j = 0; j < this->matrix->getCols(); j++) {
        this->gridView->Rows[i]->Cells[j]->Value = matrix->getCellValue(i, j);
      }
    }
  }

 private:
  System::Void buttonClearGrid_Click(System::Object ^ sender,
                                     System::EventArgs ^ e) {
    this->InvalidateLabelCounterRowsWithoutZeros();
    this->ResetGridViewCellsColor();

    this->matrix->clear();
    this->ShowGridView();
  }

 private:
  System::Void buttonComputeCounterRowsWithoutZeros_Click(System::Object ^
                                                              sender,
                                                          System::EventArgs ^
                                                              e) {
    if (!this->IsMatrixExist()) {
      this->ShowError("Matrix does not exist");
      return;
    }

    this->ColorizeGridRowsWithoutZeros();
    this->UpdateLabel(
        this->labelCounterRowsWithoutZeros,
        System::Convert::ToString(this->matrix->rowsWithoutZeros()));
  }

 private:
  System::Void gridView_CellEndEdit(
      System::Object ^ sender,
      System::Windows::Forms::DataGridViewCellEventArgs ^ e) {
    this->InvalidateLabelCounterRowsWithoutZeros();
    this->ResetGridViewCellsColor();

    DataGridViewCell ^ cell = this->gridView->CurrentCell;

    try {
      System::Double value = System::Convert::ToDouble(cell->Value);
      this->matrix->setCellValue(cell->RowIndex, cell->ColumnIndex, value);
    } catch (...) {
      this->matrix->setCellValue(cell->RowIndex, cell->ColumnIndex, 0);
    }

    this->gridView->Rows[cell->RowIndex]->Cells[cell->ColumnIndex]->Value =
        System::Convert::ToString(
            this->matrix->getCellValue(cell->RowIndex, cell->ColumnIndex));
  }

 private:
  System::Void InvalidateLabelCounterRowsWithoutZeros() {
    this->UpdateLabel(this->labelCounterRowsWithoutZeros, "-");
  }

 private:
  System::Void buttonRandomizeGrid_Click(System::Object ^ sender,
                                         System::EventArgs ^ e) {
    if (!this->IsMatrixExist()) {
      MessageBox::Show("Matrix does not exist");
      return;
    }

    this->InvalidateLabelCounterRowsWithoutZeros();
    this->ResetGridViewCellsColor();

    this->matrix->randomize();
    this->ShowGridView();
  }

 private:
  System::Void buttonCloseApp_MouseHover(System::Object ^ sender,
                                         System::EventArgs ^ e) {
    Button ^ button = safe_cast<Button ^>(sender);
    button->BackColor = Color::MistyRose;
  }

 private:
  System::Void buttonCloseApp_MouseLeave(System::Object ^ sender,
                                         System::EventArgs ^ e) {
    Button ^ button = safe_cast<Button ^>(sender);
    button->BackColor = Color::White;
  }

 private:
  System::Void buttonFillMatrix_Click(System::Object ^ sender,
                                      System::EventArgs ^ e) {
      if (this->IsMatrixExist() && this->matrix->isNotEmpty()) {
        this->ShowError("Matrix is not empty, clear matrix to set new size");
        return;
      }
    try {
      
      delete matrix;
      this->matrix = Matrix::fromFile(
          Utils::ConvertSystemStringToStd(inputFilename->Text));
      this->ShowGridView();
      this->EnableButtons();
    } catch (...) {
      this->ShowError("Error when opening file");
    }
  }
};

}  // namespace term3lab2
