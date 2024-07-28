#pragma once
#include "MeasurementDevice.h"
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "PrintForm.h"

namespace oop_laba8 {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace std;

  public ref class MainForm : public System::Windows::Forms::Form {
  public:
    MainForm(void) {
      InitializeComponent();
      devices = new vector<MeasurementDevice*>();
    }

  protected:
    ~MainForm() {
      if (components) {
        delete components;
      }
      for (auto device : *devices) {
        delete device;
      }
      delete devices;
    }

  private: System::Windows::Forms::Button^ createButton;
  private: System::Windows::Forms::Button^ deleteButton;
  private: System::Windows::Forms::Button^ printButton;
  private: System::Windows::Forms::ListBox^ listBoxDevices;
  private: System::Windows::Forms::TextBox^ deviceNameTextBox;
  private: System::Windows::Forms::TextBox^ unitTextBox;
  private: System::Windows::Forms::TextBox^ minValueTextBox;
  private: System::Windows::Forms::TextBox^ maxValueTextBox;
  private: System::Windows::Forms::TextBox^ materialTextBox;
  private: vector<MeasurementDevice*>* devices;

  private:
    System::ComponentModel::Container^ components;

    void InitializeComponent(void) {
      this->createButton = (gcnew System::Windows::Forms::Button());
      this->deleteButton = (gcnew System::Windows::Forms::Button());
      this->listBoxDevices = (gcnew System::Windows::Forms::ListBox());
      this->deviceNameTextBox = (gcnew System::Windows::Forms::TextBox());
      this->unitTextBox = (gcnew System::Windows::Forms::TextBox());
      this->minValueTextBox = (gcnew System::Windows::Forms::TextBox());
      this->maxValueTextBox = (gcnew System::Windows::Forms::TextBox());
      this->materialTextBox = (gcnew System::Windows::Forms::TextBox());
      this->printButton = (gcnew System::Windows::Forms::Button());
      this->SuspendLayout();
      // 
      // createButton
      // 
      this->createButton->Location = System::Drawing::Point(14, 13);
      this->createButton->Name = L"createButton";
      this->createButton->Size = System::Drawing::Size(75, 23);
      this->createButton->TabIndex = 0;
      this->createButton->Text = L"Create";
      this->createButton->UseVisualStyleBackColor = true;
      this->createButton->Click += gcnew System::EventHandler(this, &MainForm::createButton_Click);
      // 
      // deleteButton
      // 
      this->deleteButton->Location = System::Drawing::Point(14, 43);
      this->deleteButton->Name = L"deleteButton";
      this->deleteButton->Size = System::Drawing::Size(75, 23);
      this->deleteButton->TabIndex = 1;
      this->deleteButton->Text = L"Delete";
      this->deleteButton->UseVisualStyleBackColor = true;
      this->deleteButton->Click += gcnew System::EventHandler(this, &MainForm::deleteButton_Click);
      // 
      // listBoxDevices
      // 
      this->listBoxDevices->FormattingEnabled = true;
      this->listBoxDevices->Location = System::Drawing::Point(135, 178);
      this->listBoxDevices->Name = L"listBoxDevices";
      this->listBoxDevices->Size = System::Drawing::Size(120, 95);
      this->listBoxDevices->TabIndex = 4;
      this->listBoxDevices->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listBoxDevices_SelectedIndexChanged);
      // 
      // deviceNameTextBox
      // 
      this->deviceNameTextBox->Location = System::Drawing::Point(135, 13);
      this->deviceNameTextBox->Name = L"deviceNameTextBox";
      this->deviceNameTextBox->Size = System::Drawing::Size(120, 20);
      this->deviceNameTextBox->TabIndex = 5;
      this->deviceNameTextBox->Text = L"Device Name";
      // 
      // unitTextBox
      // 
      this->unitTextBox->Location = System::Drawing::Point(135, 43);
      this->unitTextBox->Name = L"unitTextBox";
      this->unitTextBox->Size = System::Drawing::Size(120, 20);
      this->unitTextBox->TabIndex = 6;
      this->unitTextBox->Text = L"Unit";
      // 
      // minValueTextBox
      // 
      this->minValueTextBox->Location = System::Drawing::Point(135, 73);
      this->minValueTextBox->Name = L"minValueTextBox";
      this->minValueTextBox->Size = System::Drawing::Size(120, 20);
      this->minValueTextBox->TabIndex = 7;
      this->minValueTextBox->Text = L"Min Value";
      // 
      // maxValueTextBox
      // 
      this->maxValueTextBox->Location = System::Drawing::Point(135, 103);
      this->maxValueTextBox->Name = L"maxValueTextBox";
      this->maxValueTextBox->Size = System::Drawing::Size(120, 20);
      this->maxValueTextBox->TabIndex = 8;
      this->maxValueTextBox->Text = L"Max Value";
      // 
      // materialTextBox
      // 
      this->materialTextBox->Location = System::Drawing::Point(135, 133);
      this->materialTextBox->Name = L"materialTextBox";
      this->materialTextBox->Size = System::Drawing::Size(120, 20);
      this->materialTextBox->TabIndex = 9;
      this->materialTextBox->Text = L"Material";
      // 
      // printButton
      // 
      this->printButton->Location = System::Drawing::Point(14, 133);
      this->printButton->Name = L"printButton";
      this->printButton->Size = System::Drawing::Size(75, 23);
      this->printButton->TabIndex = 10;
      this->printButton->Text = L"Print";
      this->printButton->UseVisualStyleBackColor = true;
      this->printButton->Click += gcnew System::EventHandler(this, &MainForm::printButton_Click);
      // 
      // MainForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(5, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(312, 318);
      this->Controls->Add(this->printButton);
      this->Controls->Add(this->materialTextBox);
      this->Controls->Add(this->maxValueTextBox);
      this->Controls->Add(this->minValueTextBox);
      this->Controls->Add(this->unitTextBox);
      this->Controls->Add(this->deviceNameTextBox);
      this->Controls->Add(this->listBoxDevices);
      this->Controls->Add(this->deleteButton);
      this->Controls->Add(this->createButton);
      this->Name = L"MainForm";
      this->Text = L"Measurement Devices";
      this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
      this->ResumeLayout(false);
      this->PerformLayout();
    }

  private:
    System::Void createButton_Click(System::Object^ sender, System::EventArgs^ e) {
      try {
        string name = msclr::interop::marshal_as<std::string>(deviceNameTextBox->Text);
        string unit = msclr::interop::marshal_as<std::string>(unitTextBox->Text);
        int minValue = Convert::ToInt32(minValueTextBox->Text);
        int maxValue = Convert::ToInt32(maxValueTextBox->Text);
        string material = msclr::interop::marshal_as<std::string>(materialTextBox->Text);
        
        if (minValue > maxValue) {
          MessageBox::Show("Min Value should not be greater than Max Value.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
          return;
        }

        MeasurementDevice* device = new MeasurementDevice(name, unit, minValue, maxValue, material);
        devices->push_back(device);
        listBoxDevices->Items->Add(gcnew String(name.c_str()));
      }
      catch (FormatException^ e) {
        MessageBox::Show("Please enter valid numeric values for Min Value and Max Value.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
      }
      catch (Exception^ e) {
        MessageBox::Show("An error occurred while creating the device: " + e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
      }
    }

  private:
    System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
      if (listBoxDevices->SelectedIndex != -1) {
        int selectedIndex = listBoxDevices->SelectedIndex;
        delete (*devices)[selectedIndex];
        devices->erase(devices->begin() + selectedIndex);
        listBoxDevices->Items->RemoveAt(selectedIndex);
      }
    }

  private:
    System::Void listBoxDevices_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
      // Handle selection changes if needed
    }

  private:
    System::Void printButton_Click(System::Object^ sender, System::EventArgs^ e) {
      if (listBoxDevices->SelectedIndex != -1) {
        MeasurementDevice* selectedDevice = (*devices)[listBoxDevices->SelectedIndex];
        PrintForm^ printForm = gcnew PrintForm(selectedDevice);
        printForm->Show();
      }
    }

  private:
    System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
  };
}
