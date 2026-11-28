
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
public:
    int id, age;
    string name, course;
    float english = -1, maths = -1, science = -1;
};

vector<Student> students;

// Save Data
void saveData() {
    ofstream f("students.txt");
    for (Student s : students)
        f << s.id << "|" << s.name << "|" << s.age << "|"
          << s.course << "|" << s.english << "|"
          << s.maths << "|" << s.science << "\n";
}

// Load Data
void loadData() {
    ifstream f("students.txt");
    Student s;
    char ch;

    while (f >> s.id) {
        f.ignore();
        getline(f, s.name, '|');
        f >> s.age;
        f.ignore();
        getline(f, s.course, '|');
        f >> s.english;
        f.ignore();
        f >> s.maths;
        f.ignore();
        f >> s.science;
        students.push_back(s);
    }
}

// Find Student
int findStudent(int id) {
    for (int i = 0; i < students.size(); i++)
        if (students[i].id == id) return i;
    return -1;
}

// Input Student Details
void inputDetails(Student &s) {
    cout << "Enter Name: ";
    getline(cin >> ws, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cout << "Enter Course: ";
    getline(cin >> ws, s.course);
}

// Display Student
void display(Student s) {
    cout << "\nID: " << s.id
         << "\nName: " << s.name
         << "\nAge: " << s.age
         << "\nCourse: " << s.course
         << "\nEnglish: " << s.english
         << "\nMaths: " << s.maths
         << "\nScience: " << s.science << "\n";
}
 
// MODULE 1: Add Student
void addStudent() {
    Student s;

    cout << "Enter Student ID: ";
    cin >> s.id;

    if (findStudent(s.id) != -1) {
        cout << "ID Already Exists!\n";
        return;
    }

    inputDetails(s);
    students.push_back(s);
    saveData();

    cout << "Student Added Successfully!\n";
}

// Update Student
void updateStudent() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int i = findStudent(id);

    if (i == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    inputDetails(students[i]);
    saveData();
    cout << "Student Updated Successfully!\n";
}

// MODULE 2: Search Student
void searchStudent() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int i = findStudent(id);

    if (i == -1) cout << "Student Not Found!\n";
    else display(students[i]);
}

// Display All Students
void displayAll() {
    if (students.empty()) {
        cout << "No Records Found!\n";
        return;
    }

    for (Student s : students)
        display(s);
}

// MODULE 3: Enter Marks
void enterMarks() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int i = findStudent(id);

    if (i == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    float e, m, s;
    cout << "Enter English Marks: ";
    cin >> e;
    cout << "Enter Maths Marks: ";
    cin >> m;
    cout << "Enter Science Marks: ";
    cin >> s;

    if (e < 0 || e > 100 || m < 0 || m > 100 ||
        s < 0 || s > 100) {
        cout << "Invalid Marks! Enter 0-100.\n";
        return;
    }

    students[i].english = e;
    students[i].maths = m;
    students[i].science = s;

    saveData();
    cout << "Marks Saved Successfully!\n";
}

// Calculate Grade
string grade(float p) {
    if (p >= 90) return "A+";
    if (p >= 80) return "A";
    if (p >= 70) return "B";
    if (p >= 60) return "C";
    if (p >= 40) return "D";
    return "F";
}

// MODULE 4: Generate Result
void generateReport() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int i = findStudent(id);

    if (i == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    Student s = students[i];

    if (s.english < 0 || s.maths < 0 || s.science < 0) {
        cout << "Enter All Marks First!\n";
        return;
    }

    float total = s.english + s.maths + s.science;
    float p = total / 3;

    cout << fixed << setprecision(2);
    cout << "\n--- STUDENT RESULT REPORT ---\n";
    cout << "Name       : " << s.name << "\n";
    cout << "ID         : " << s.id << "\n";
    cout << "Course     : " << s.course << "\n";
    cout << "English    : " << s.english << "\n";
    cout << "Maths      : " << s.maths << "\n";
    cout << "Science    : " << s.science << "\n";
    cout << "Total      : " << total << "/300\n";
    cout << "Percentage : " << p << "%\n";
    cout << "Grade      : " << grade(p) << "\n";
    cout << "Result     : " << (p >= 40 ? "PASS" : "FAIL") << "\n";
}

// Main Function
int main() {
    loadData();

    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Search Student\n";
        cout << "4. Display All Students\n";
        cout << "5. Enter Marks\n";
        cout << "6. Generate Result Report\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: searchStudent(); break;
            case 4: displayAll(); break;
            case 5: enterMarks(); break;
            case 6: generateReport(); break;
            case 7: cout << "Thank You!\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
