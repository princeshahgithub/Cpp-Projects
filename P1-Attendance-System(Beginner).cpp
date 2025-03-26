#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string name;
    int rollNo;
    bool present;
};

vector<Student> students;

void addStudent() {
    Student s;
    cout << "Enter student name: ";
    cin >> s.name;
    cout << "Enter roll number: ";
    cin >> s.rollNo;
    s.present = false;
    students.push_back(s);
    cout << "Student added successfully!\n";
}

void markAttendance() {
    int rollNo, found = 0;
    cout << "Enter roll number to mark attendance: ";
    cin >> rollNo;

    for (auto &s : students) {
        if (s.rollNo == rollNo) {
            s.present = true;
            cout << "Attendance marked for " << s.name << " (Roll No: " << s.rollNo << ")\n";
            found = 1;
            break;
        }
    }
    if (!found) cout << "Student not found!\n";
}

void displayAttendance() {
    if (students.empty()) {
        cout << "No students in the record!\n";
        return;
    }

    cout << "\nAttendance Record:\n";
    for (const auto &s : students) {
        cout << "Name: " << s.name << " | Roll No: " << s.rollNo << " | Status: "
             << (s.present ? "Present" : "Absent") << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Add Student\n2. Mark Attendance\n3. Display Attendance\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: markAttendance(); break;
            case 3: displayAttendance(); break;
            case 4: return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}
