#pragma once
#include "MeasurementDevice.h"
#include <string>
#include <msclr/marshal_cppstd.h>

namespace oop_laba8 {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  public ref class PrintForm : public System::Windows::Forms::Form {
  public:
    PrintForm(MeasurementDevice* device) {
      InitializeComponent();
      this->device = device;
      updateStatus();
    }

  protected:
    ~PrintForm() {
      if (components) {
        delete components;
      }
    }

  private:
    MeasurementDevice* device;
    System::ComponentModel::Container^ components;
    System::Windows::Forms::Label^ nameLabel;
    System::Windows::Forms::Label^ unitLabel;
    System::Windows::Forms::Label^ minValueLabel;
    System::Windows::Forms::Label^ maxValueLabel;
    System::Windows::Forms::Label^ materialLabel;
    System::Windows::Forms::Label^ statusLabel;
    System::Windows::Forms::Button^ startButton;
    System::Windows::Forms::Button^ stopButton;
    System::Windows::Forms::Button^ printButton;

    void InitializeComponent(void) {
      this->nameLabel = (gcnew System::Windows::Forms::Label());
      this->unitLabel = (gcnew System::Windows::Forms::Label());
      this->minValueLabel = (gcnew System::Windows::Forms::Label());
      this->maxValueLabel = (gcnew System::Windows::Forms::Label());
      this->materialLabel = (gcnew System::Windows::Forms::Label());
      this->statusLabel = (gcnew System::Windows::Forms::Label());
      this->startButton = (gcnew System::Windows::Forms::Button());
      this->stopButton = (gcnew System::Windows::Forms::Button());
      this->printButton = (gcnew System::Windows::Forms::Button());
      this->SuspendLayout();
      // 
      // nameLabel
      // 
      this->nameLabel->AutoSize = true;
      this->nameLabel->Location = System::Drawing::Point(13, 13);
      this->nameLabel->Name = L"nameLabel";
      this->nameLabel->Size = System::Drawing::Size(35, 13);
      this->nameLabel->TabIndex = 0;
      this->nameLabel->Text = L"Name:";
      // 
      // unitLabel
      // 
      this->unitLabel->AutoSize = true;
      this->unitLabel->Location = System::Drawing::Point(13, 33);
      this->unitLabel->Name = L"unitLabel";
      this->unitLabel->Size = System::Drawing::Size(29, 13);
      this->unitLabel->TabIndex = 1;
      this->unitLabel->Text = L"Unit:";
      // 
      // minValueLabel
      // 
      this->minValueLabel->AutoSize = true;
      this->minValueLabel->Location = System::Drawing::Point(13, 53);
      this->minValueLabel->Name = L"minValueLabel";
      this->minValueLabel->Size = System::Drawing::Size(57, 13);
      this->minValueLabel->TabIndex = 2;
      this->minValueLabel->Text = L"Min Value:";
      // 
      // maxValueLabel
      // 
      this->maxValueLabel->AutoSize = true;
      this->maxValueLabel->Location = System::Drawing::Point(13, 73);
      this->maxValueLabel->Name = L"maxValueLabel";
      this->maxValueLabel->Size = System::Drawing::Size(60, 13);
      this->maxValueLabel->TabIndex = 3;
      this->maxValueLabel->Text = L"Max Value:";
      // 
      // materialLabel
      // 
      this->materialLabel->AutoSize = true;
      this->materialLabel->Location = System::Drawing::Point(13, 93);
      this->materialLabel->Name = L"materialLabel";
      this->materialLabel->Size = System::Drawing::Size(47, 13);
      this->materialLabel->TabIndex = 4;
      this->materialLabel->Text = L"Material:";
      // 
      // statusLabel
      // 
      this->statusLabel->AutoSize = true;
      this->statusLabel->Location = System::Drawing::Point(13, 113);
      this->statusLabel->Name = L"statusLabel";
      this->statusLabel->Size = System::Drawing::Size(40, 13);
      this->statusLabel->TabIndex = 5;
      this->statusLabel->Text = L"Status:";
      // 
      // startButton
      // 
      this->startButton->Location = System::Drawing::Point(16, 143);
      this->startButton->Name = L"startButton";
      this->startButton->Size = System::Drawing::Size(75, 23);
      this->startButton->TabIndex = 6;
      this->startButton->Text = L"Start";
      this->startButton->UseVisualStyleBackColor = true;
      this->startButton->Click += gcnew System::EventHandler(this, &PrintForm::startButton_Click);
      // 
      // stopButton
      // 
      this->stopButton->Location = System::Drawing::Point(16, 173);
      this->stopButton->Name = L"stopButton";
      this->stopButton->Size = System::Drawing::Size(75, 23);
      this->stopButton->TabIndex = 3;
      this->stopButton->Text = L"Stop";
      this->stopButton->UseVisualStyleBackColor = true;
      this->stopButton->Click += gcnew System::EventHandler(this, &PrintForm::stopButton_Click);
      // 
      // printButton
      // 
      this->printButton->Location = System::Drawing::Point(107, 143);
      this->printButton->Name = L"printButton";
      this->printButton->Size = System::Drawing::Size(75, 23);
      this->printButton->TabIndex = 7;
      this->printButton->Text = L"Print";
      this->printButton->UseVisualStyleBackColor = true;
      this->printButton->Click += gcnew System::EventHandler(this, &PrintForm::printButton_Click);
      // 
      // PrintForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(284, 230);
      this->Controls->Add(this->printButton);
      this->Controls->Add(this->startButton);
      this->Controls->Add(this->stopButton);
      this->Controls->Add(this->statusLabel);
      this->Controls->Add(this->materialLabel);
      this->Controls->Add(this->maxValueLabel);
      this->Controls->Add(this->minValueLabel);
      this->Controls->Add(this->unitLabel);
      this->Controls->Add(this->nameLabel);
      this->Name = L"PrintForm";
      this->Text = L"Print Device Info";
      this->ResumeLayout(false);
      this->PerformLayout();
    }

    void updateStatus() {
      this->statusLabel->Text = "Status: " + (device->isActive() ? "Active" : "Inactive");
    }

    void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
      device->startMeasuring();
      updateStatus();
    }

    void stopButton_Click(System::Object^ sender, System::EventArgs^ e) {
      device->stopMeasuring();
      updateStatus();
    }

    void printButton_Click(System::Object^ sender, System::EventArgs^ e) {
      if (!device->isActive()) {
        MessageBox::Show("Please start the device first!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
      }
      else {
        printDeviceInfo();
      }
    }

    void printDeviceInfo() {
      this->nameLabel->Text = "Name: " + gcnew String(device->getName().c_str());
      this->unitLabel->Text = "Unit: " + gcnew String(device->getUnit().c_str());
      this->minValueLabel->Text = "Min Value: " + device->getMinValue().ToString();
      this->maxValueLabel->Text = "Max Value: " + device->getMaxValue().ToString();
      this->materialLabel->Text = "Material: " + gcnew String(device->getMaterial().c_str());
    }
  };
}
