#pragma once
#include "StudentManager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;

namespace CppCLRWinFormsProject
{
    public ref class Form1 : public Form
    {
    public:
        Form1()
        {
            manager = gcnew StudentManager();
            InitializeComponent();
        }

    private:
        // GUI Controls
        DataGridView^ dgv;
        TextBox^ txtName;
        TextBox^ txtAge;
        Button^ btnAdd;
        Button^ btnUpdate;
        Button^ btnDelete;
        Button^ btnSave;
        Button^ btnLoad;

        // Manager
        StudentManager^ manager;

    private:
        void InitializeComponent()
        {
            this->Text = "Student Information System (SIS)";
            this->Width = 500;
            this->Height = 400;

            // GridView
            dgv = gcnew DataGridView();
            dgv->Location = Drawing::Point(20, 20);
            dgv->Width = 440;
            dgv->Height = 200;
            dgv->ColumnCount = 2;
            dgv->Columns[0]->Name = "Name";
            dgv->Columns[1]->Name = "Age";

            // TextBoxes
            txtName = gcnew TextBox();
            txtName->Location = Drawing::Point(20, 240);
            txtName->Width = 200;

            txtAge = gcnew TextBox();
            txtAge->Location = Drawing::Point(230, 240);
            txtAge->Width = 60;

            // Buttons
            btnAdd = gcnew Button();
            btnAdd->Text = "Add";
            btnAdd->Location = Drawing::Point(310, 240);
            btnAdd->Click += gcnew EventHandler(this, &Form1::AddRow);

            btnUpdate = gcnew Button();
            btnUpdate->Text = "Update";
            btnUpdate->Location = Drawing::Point(380, 240);
            btnUpdate->Click += gcnew EventHandler(this, &Form1::UpdateRow);

            btnDelete = gcnew Button();
            btnDelete->Text = "Delete";
            btnDelete->Location = Drawing::Point(310, 280);
            btnDelete->Click += gcnew EventHandler(this, &Form1::DeleteRow);

            btnSave = gcnew Button();
            btnSave->Text = "Save";
            btnSave->Location = Drawing::Point(380, 280);
            btnSave->Click += gcnew EventHandler(this, &Form1::SaveData);

            btnLoad = gcnew Button();
            btnLoad->Text = "Load";
            btnLoad->Location = Drawing::Point(220, 280);
            btnLoad->Click += gcnew EventHandler(this, &Form1::LoadData);

            this->Controls->Add(dgv);
            this->Controls->Add(txtName);
            this->Controls->Add(txtAge);
            this->Controls->Add(btnAdd);
            this->Controls->Add(btnUpdate);
            this->Controls->Add(btnDelete);
            this->Controls->Add(btnSave);
            this->Controls->Add(btnLoad);
        }

        // Button Handlers
    private:
        void AddRow(Object^ sender, EventArgs^ e)
        {
            if (txtName->Text == "" || txtAge->Text == "") {
                MessageBox::Show("Enter Name and Age!");
                return;
            }

            manager->AddStudent(txtName->Text, txtAge->Text);
            RefreshGrid();
            txtName->Clear();
            txtAge->Clear();
        }

        void UpdateRow(Object^ sender, EventArgs^ e)
        {
            if (dgv->SelectedRows->Count == 0) {
                MessageBox::Show("Select a row to update!");
                return;
            }

            int index = dgv->SelectedRows[0]->Index;
            manager->UpdateStudent(index, txtName->Text, txtAge->Text);
            RefreshGrid();
        }

        void DeleteRow(Object^ sender, EventArgs^ e)
        {
            if (dgv->SelectedRows->Count == 0) {
                MessageBox::Show("Select a row to delete!");
                return;
            }

            int index = dgv->SelectedRows[0]->Index;
            manager->DeleteStudent(index);
            RefreshGrid();
        }

        void SaveData(Object^ sender, EventArgs^ e)
        {
            // Get the folder where the program is running
            String^ currentDir = Directory::GetCurrentDirectory();

            // Go two folders up to reach the project folder
            String^ filename = Path::Combine(currentDir, "..\\..\\data.txt");

            // Save the student data
            manager->SaveToFile(filename);

            // Show message with file path
            MessageBox::Show("Data Saved!\nFile: " + filename);
        }


        void LoadData(Object^ sender, EventArgs^ e)
        {
            String^ currentDir = Directory::GetCurrentDirectory();
            String^ filename = Path::Combine(currentDir, "..\\..\\data.txt");

            manager->LoadFromFile(filename);
            RefreshGrid();

            MessageBox::Show("Data Loaded!\nFile: " + filename);
        }


        void RefreshGrid()
        {
            dgv->Rows->Clear();
            for each (Student ^ s in manager->GetStudents()) {
                dgv->Rows->Add(s->Name, s->Age);
            }
        }
    };
}
