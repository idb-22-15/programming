#pragma once
#include <cstdlib>
#include <ctime>

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
  MyForm() {
    InitializeComponent();
    //
    // TODO: добавьте код конструктора
    //
  }

 protected:
  /// <summary>
  /// Освободить все используемые ресурсы.
  /// </summary>
  ~MyForm() {
    if (components) {
      delete components;
      delete grid;
    }
  }

 private:
  System::UInt32 rows = 0;
  System::UInt32 cols = 0;
  System::UInt32 counterRowsWithoutZeros = 0;
  System::Double** grid = nullptr;

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
 private:
  System::Windows::Forms::Button ^ buttonCloseApp;

 private:
  System::Windows::Forms::Button ^ buttonComputeCounterRowsWithoutZeros;

 private:
 private:
  System::Windows::Forms::Button ^ buttonRandomizeGrid;

 private:
 private:
 private:
  /// <summary>
  /// Обязательная переменная конструктора.
  /// </summary>
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
    (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
         this->gridView))
        ->BeginInit();
    this->SuspendLayout();
    //
    // labelRows
    //
    this->labelRows->AutoSize = true;
    this->labelRows->Location = System::Drawing::Point(36, 37);
    this->labelRows->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
    this->labelRows->Name = L"labelRows";
    this->labelRows->Size = System::Drawing::Size(283, 40);
    this->labelRows->TabIndex = 0;
    this->labelRows->Text = L"Number of rows";
    //
    // labelCols
    //
    this->labelCols->AutoSize = true;
    this->labelCols->Location = System::Drawing::Point(36, 119);
    this->labelCols->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
    this->labelCols->Name = L"labelCols";
    this->labelCols->Size = System::Drawing::Size(340, 40);
    this->labelCols->TabIndex = 1;
    this->labelCols->Text = L"Number of columns";
    //
    // buttonSetGridSize
    //
    this->buttonSetGridSize->AutoSize = true;
    this->buttonSetGridSize->Location = System::Drawing::Point(662, 37);
    this->buttonSetGridSize->Margin = System::Windows::Forms::Padding(6);
    this->buttonSetGridSize->Name = L"buttonSetGridSize";
    this->buttonSetGridSize->Size = System::Drawing::Size(333, 82);
    this->buttonSetGridSize->TabIndex = 2;
    this->buttonSetGridSize->Text = L"Set matrix size";
    this->buttonSetGridSize->UseVisualStyleBackColor = true;
    this->buttonSetGridSize->Click +=
        gcnew System::EventHandler(this, &MyForm::SetGridSize);
    //
    // gridView
    //
    this->gridView->AllowUserToAddRows = false;
    this->gridView->AllowUserToDeleteRows = false;
    this->gridView->AllowUserToResizeColumns = false;
    this->gridView->AllowUserToResizeRows = false;
    this->gridView->BackgroundColor = System::Drawing::Color::White;
    this->gridView->ColumnHeadersBorderStyle =
        System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
    this->gridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::
        DataGridViewColumnHeadersHeightSizeMode::AutoSize;
    this->gridView->Location = System::Drawing::Point(43, 453);
    this->gridView->Margin = System::Windows::Forms::Padding(6);
    this->gridView->Name = L"gridView";
    this->gridView->RowHeadersVisible = false;
    this->gridView->RowHeadersWidthSizeMode = System::Windows::Forms::
        DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
    this->gridView->RowTemplate->Height = 28;
    this->gridView->Size = System::Drawing::Size(507, 329);
    this->gridView->TabIndex = 3;
    this->gridView->CellValueChanged +=
        gcnew System::Windows::Forms::DataGridViewCellEventHandler(
            this, &MyForm::gridView_CellValueChanged);
    //
    // inputRows
    //
    this->inputRows->Location = System::Drawing::Point(464, 37);
    this->inputRows->Margin = System::Windows::Forms::Padding(6);
    this->inputRows->Name = L"inputRows";
    this->inputRows->Size = System::Drawing::Size(86, 47);
    this->inputRows->TabIndex = 4;
    this->inputRows->Text = L"1";
    //
    // inputCols
    //
    this->inputCols->Location = System::Drawing::Point(464, 112);
    this->inputCols->Margin = System::Windows::Forms::Padding(6);
    this->inputCols->Name = L"inputCols";
    this->inputCols->Size = System::Drawing::Size(86, 47);
    this->inputCols->TabIndex = 5;
    this->inputCols->Text = L"1";
    //
    // labelCounterRowsWithoutZerosDescription
    //
    this->labelCounterRowsWithoutZerosDescription->AutoSize = true;
    this->labelCounterRowsWithoutZerosDescription->Location =
        System::Drawing::Point(36, 223);
    this->labelCounterRowsWithoutZerosDescription->Margin =
        System::Windows::Forms::Padding(6, 0, 6, 0);
    this->labelCounterRowsWithoutZerosDescription->Name =
        L"labelCounterRowsWithoutZerosDescription";
    this->labelCounterRowsWithoutZerosDescription->Size =
        System::Drawing::Size(549, 40);
    this->labelCounterRowsWithoutZerosDescription->TabIndex = 6;
    this->labelCounterRowsWithoutZerosDescription->Text =
        L"Number of rows without zeros";
    //
    // labelCounterRowsWithoutZeros
    //
    this->labelCounterRowsWithoutZeros->AutoSize = true;
    this->labelCounterRowsWithoutZeros->Location =
        System::Drawing::Point(627, 223);
    this->labelCounterRowsWithoutZeros->Margin =
        System::Windows::Forms::Padding(6, 0, 6, 0);
    this->labelCounterRowsWithoutZeros->Name = L"labelCounterRowsWithoutZeros";
    this->labelCounterRowsWithoutZeros->Size = System::Drawing::Size(36, 40);
    this->labelCounterRowsWithoutZeros->TabIndex = 7;
    this->labelCounterRowsWithoutZeros->Text = L"-";
    //
    // buttonClearGrid
    //
    this->buttonClearGrid->Enabled = false;
    this->buttonClearGrid->Location = System::Drawing::Point(43, 338);
    this->buttonClearGrid->Margin = System::Windows::Forms::Padding(6);
    this->buttonClearGrid->Name = L"buttonClearGrid";
    this->buttonClearGrid->Size = System::Drawing::Size(283, 82);
    this->buttonClearGrid->TabIndex = 2;
    this->buttonClearGrid->Text = L"Clear matrix";
    this->buttonClearGrid->UseVisualStyleBackColor = true;
    this->buttonClearGrid->Click +=
        gcnew System::EventHandler(this, &MyForm::buttonClearGrid_Click);
    //
    // buttonCloseApp
    //
    this->buttonCloseApp->Location = System::Drawing::Point(1270, 37);
    this->buttonCloseApp->Name = L"buttonCloseApp";
    this->buttonCloseApp->Size = System::Drawing::Size(61, 53);
    this->buttonCloseApp->TabIndex = 8;
    this->buttonCloseApp->Text = L"x";
    this->buttonCloseApp->UseVisualStyleBackColor = true;
    this->buttonCloseApp->Click +=
        gcnew System::EventHandler(this, &MyForm::CloseApp);
    //
    // buttonComputeCounterRowsWithoutZeros
    //
    this->buttonComputeCounterRowsWithoutZeros->Enabled = false;
    this->buttonComputeCounterRowsWithoutZeros->Location =
        System::Drawing::Point(812, 202);
    this->buttonComputeCounterRowsWithoutZeros->Margin =
        System::Windows::Forms::Padding(6);
    this->buttonComputeCounterRowsWithoutZeros->Name =
        L"buttonComputeCounterRowsWithoutZeros";
    this->buttonComputeCounterRowsWithoutZeros->Size =
        System::Drawing::Size(183, 82);
    this->buttonComputeCounterRowsWithoutZeros->TabIndex = 9;
    this->buttonComputeCounterRowsWithoutZeros->Text = L"Compute";
    this->buttonComputeCounterRowsWithoutZeros->UseVisualStyleBackColor = true;
    this->buttonComputeCounterRowsWithoutZeros->Click +=
        gcnew System::EventHandler(
            this, &MyForm::buttonComputeCounterRowsWithoutZeros_Click);
    //
    // buttonRandomizeGrid
    //
    this->buttonRandomizeGrid->Enabled = false;
    this->buttonRandomizeGrid->Location = System::Drawing::Point(351, 338);
    this->buttonRandomizeGrid->Margin = System::Windows::Forms::Padding(6);
    this->buttonRandomizeGrid->Name = L"buttonRandomizeGrid";
    this->buttonRandomizeGrid->Size = System::Drawing::Size(365, 82);
    this->buttonRandomizeGrid->TabIndex = 9;
    this->buttonRandomizeGrid->Text = L"Randomize matrix";
    this->buttonRandomizeGrid->UseVisualStyleBackColor = true;
    this->buttonRandomizeGrid->Click +=
        gcnew System::EventHandler(this, &MyForm::buttonRandomizeGrid_Click);
    //
    // MyForm
    //
    this->AutoScaleDimensions = System::Drawing::SizeF(19, 40);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->AutoSize = true;
    this->BackColor = System::Drawing::Color::White;
    this->ClientSize = System::Drawing::Size(1386, 1073);
    this->Controls->Add(this->buttonRandomizeGrid);
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
    this->Font = (gcnew System::Drawing::Font(
        L"JetBrains Mono", 16, System::Drawing::FontStyle::Regular,
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
    this->Icon = (cli::safe_cast<System::Drawing::Icon ^>(
        resources->GetObject(L"$this.Icon")));
    this->Margin = System::Windows::Forms::Padding(6);
    this->Name = L"MyForm";
    this->StartPosition =
        System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Computation of rows without zeros";
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
  void ComputeCounterRowsWithoutZeros() {
    this->counterRowsWithoutZeros = 0;

    for (int i = 0; i < this->rows; i++) {
      bool rowHaveZeros = false;
      int zeros = 0;
      for (int j = 0; j < this->cols; j++) {
        if (grid[i][j] == 0) {
          rowHaveZeros = true;
          zeros++;
        }
      }

      if (zeros == 0)
        counterRowsWithoutZeros++;
    }
  }

 private:
  System::Boolean IsGridExist() { return grid != nullptr; }

  System::Boolean IsGridNotEmpty() {
    if (!this->IsGridExist())
      return false;

    System::Boolean notEmpty = false;

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        if (grid[i][j] != 0) {
          notEmpty = true;
          break;
        }
      }
    }

    return notEmpty;
  }

 private:
  System::Void SetGridSize(System::Object ^ sender, System::EventArgs ^ e) {
    if (this->IsGridNotEmpty()) {
      MessageBox::Show("Matrix is not empty, clear matrix to set new size");
      return;
    }

    try {
      this->rows = this->ParseSize(inputRows->Text);
    } catch (...) {
      MessageBox::Show("The number of rows is entered incorrectly");
      this->rows = 1;
      this->inputRows->Text = System::Convert::ToString(this->rows);
      return;
    }

    try {
      this->cols = this->ParseSize(inputCols->Text);
    } catch (...) {
      MessageBox::Show("The number of columns is entered incorrectly");
      this->cols = 1;
      this->inputCols->Text = System::Convert::ToString(this->cols);
      return;
    }

    delete grid;

    this->CreateGrid();
    this->ClearGrid();
    this->ShowGridView();

    this->buttonClearGrid->Enabled = true;
    this->buttonRandomizeGrid->Enabled = true;
    this->buttonComputeCounterRowsWithoutZeros->Enabled = true;
  }

 private:
  System::Void CreateGrid() {
    grid = new System::Double*[rows];

    for (int i = 0; i < this->rows; i++) {
      grid[i] = new System::Double[this->cols];
    }
  }

 private:
  System::UInt32 ParseSize(System::String ^ rawSize) {
    System::Boolean isValid = true;
    System::UInt32 maxSize = 50;

    System::Int32 newSize = System::Int32::Parse(rawSize);

    System::Exception ^ e = gcnew System::Exception;

    if (newSize <= 0)
      throw e;

    if (newSize > maxSize)
      throw e;

    return newSize;
  }

 private:
  System::Void UpdateLabel(Label ^ label, System::String ^ text) {
    label->Text = text;
  }

 private:
  System::Void ClearGrid() {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        grid[i][j] = System::Double(0);
      }
    }
  }

 private:
  System::Void RandomizeGrid() {
    std::srand(std::time(0));

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        if (rand() % 2 == 0)
          grid[i][j] = rand() % 100;
        else
          grid[i][j] = -1 * rand() % 100;
      }
    }
  }

 private:
  System::Void ShowGridView() {
    this->gridView->RowCount = this->rows;
    this->gridView->ColumnCount = this->cols;

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        this->gridView->Rows[i]->Cells[j]->Value = grid[i][j];
      }
    }
  }

 private:
  System::Void buttonClearGrid_Click(System::Object ^ sender,
                                     System::EventArgs ^ e) {
    this->ClearGrid();
    this->ShowGridView();
  }

 private:
  System::Void buttonComputeCounterRowsWithoutZeros_Click(System::Object ^
                                                              sender,
                                                          System::EventArgs ^
                                                              e) {
    if (!this->IsGridExist()) {
      MessageBox::Show("Matrix does not exist");
      return;
    }

    this->ComputeCounterRowsWithoutZeros();
    this->UpdateLabel(this->labelCounterRowsWithoutZeros,
                      System::Convert::ToString(this->counterRowsWithoutZeros));
  }

 private:
  System::Void gridView_CellValueChanged(
      System::Object ^ sender,
      System::Windows::Forms::DataGridViewCellEventArgs ^ e) {
    this->UpdateLabel(this->labelCounterRowsWithoutZeros, "-");

    DataGridViewCell ^ cell = this->gridView->CurrentCell;
    try {
      System::Double value = System::Convert::ToDouble(cell->Value);
      grid[cell->RowIndex][cell->ColumnIndex] = value;

    } catch (...) {
      grid[cell->RowIndex][cell->ColumnIndex] = System::Double(0);
    }

    this->gridView->Rows[cell->RowIndex]->Cells[cell->ColumnIndex]->Value =
        System::Convert::ToString(
            this->grid[cell->RowIndex][cell->ColumnIndex]);
  }

 private:
  System::Void buttonRandomizeGrid_Click(System::Object ^ sender,
                                         System::EventArgs ^ e) {
    if (!this->IsGridExist()) {
      MessageBox::Show("Matrix does not exist");
      return;
    }

    this->RandomizeGrid();
    this->ShowGridView();
  }
};

}  // namespace term3lab2
