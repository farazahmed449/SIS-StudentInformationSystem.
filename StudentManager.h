#pragma once
#include "pch.h"
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

ref class Student {
public:
    String^ Name;
    String^ Age;

    Student(String^ name, String^ age) {
        Name = name;
        Age = age;
    }
};

ref class StudentManager {
private:
    List<Student^>^ students;

public:
    StudentManager() {
        students = gcnew List<Student^>();
    }

    // Create / Add
    void AddStudent(String^ name, String^ age) {
        students->Add(gcnew Student(name, age));
    }

    // Read / Get all
    List<Student^>^ GetStudents() {
        return students;
    }

    // Update
    void UpdateStudent(int index, String^ name, String^ age) {
        if (index >= 0 && index < students->Count) {
            students[index]->Name = name;
            students[index]->Age = age;
        }
    }

    // Delete
    void DeleteStudent(int index) {
        if (index >= 0 && index < students->Count) {
            students->RemoveAt(index);
        }
    }

    // Save to file
    void SaveToFile(String^ filename) {
        StreamWriter^ file = gcnew StreamWriter(filename);
        for each (Student ^ s in students) {
            file->WriteLine(s->Name + "," + s->Age);
        }
        file->Close();
    }

    // Load from file
    void LoadFromFile(String^ filename) {
        students->Clear();
        if (!File::Exists(filename)) return;

        array<String^>^ lines = File::ReadAllLines(filename);
        for each (String ^ line in lines) {
            array<String^>^ parts = line->Split(',');
            if (parts->Length >= 2)
                AddStudent(parts[0], parts[1]);
        }
    }
};
