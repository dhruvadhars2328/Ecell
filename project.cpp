#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Student {
private:
    int id;
    string name;
    int age;
    string grade;

public:
    Student(int id, string name, int age, string grade)
        : id(id), name(name), age(age), grade(grade) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGrade() const { return grade; }

    void setName(const string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setGrade(const string& newGrade) { grade = newGrade; }

    void display() const {
        cout << setw(5) << id
             << setw(20) << name
             << setw(5) << age
             << setw(10) << grade << endl;
    }
};

class StudentManager {
private:
    vector<Student> students;
    string filename;

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            int id, age;
            string name, grade;
            while (file >> id >> ws) {
                getline(file, name);
                file >> age >> ws;
                getline(file, grade);
                students.push_back(Student(id, name, age, grade));
            }
            file.close();
        }
    }

    void saveToFile() const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& student : students) {
                file << student.getId() << endl
                     << student.getName() << endl
                     << student.getAge() << endl
                     << student.getGrade() << endl;
            }
            file.close();
        }
    }

public:
    StudentManager(const string& filename) : filename(filename) {
        loadFromFile();
    }

    ~StudentManager() {
        saveToFile();
    }

    void addStudent() {
        int id;
        string name;
        int age;
        string grade;

        cout << "Enter student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter student name: ";
        getline(cin, name);
        cout << "Enter student age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter student grade: ";
        getline(cin, grade);

        students.push_back(Student(id, name, age, grade));
    }

    void removeStudent() {
        int id;
        cout << "Enter student ID to remove: ";
        cin >> id;
        auto it = remove_if(students.begin(), students.end(),
                            [id](const Student& s) { return s.getId() == id; });
        if (it != students.end()) {
            students.erase(it, students.end());
            cout << "Student removed successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }
    }

    void updateStudent() {
        int id;
        cout << "Enter student ID to update: ";
        cin >> id;
        auto it = find_if(students.begin(), students.end(),
                          [id](const Student& s) { return s.getId() == id; });
        if (it != students.end()) {
            string name;
            int age;
            string grade;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter new grade: ";
            getline(cin, grade);

            it->setName(name);
            it->setAge(age);
            it->setGrade(grade);
            cout << "Student updated successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }
    }

    void displayAllStudents() const {
        cout << setw(5) << "ID"
             << setw(20) << "Name"
             << setw(5) << "Age"
             << setw(10) << "Grade" << endl;
        for (const auto& student : students) {
            student.display();
        }
    }

    void searchStudent() const {
        int id;
        cout << "Enter student ID to search: ";
        cin >> id;
        auto it = find_if(students.begin(), students.end(),
                          [id](const Student& s) { return s.getId() == id; });
        if (it != students.end()) {
            cout << setw(5) << "ID"
                 << setw(20) << "Name"
                 << setw(5) << "Age"
                 << setw(10) << "Grade" << endl;
            it->display();
        } else {
            cout << "Student not found." << endl;
        }
    }
};

int main() {
    StudentManager manager("students.txt");
    int choice;
    do {
        cout << "\nStudent Management System"
             << "\n1. Add Student"
             << "\n2. Remove Student"
             << "\n3. Update Student"
             << "\n4. Display All Students"
             << "\n5. Search Student"
             << "\n6. Exit"
             << "\nEnter your choice: ";
        cin >> choice;

