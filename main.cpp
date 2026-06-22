#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

// Student Class
class Student {
private:
    int id;
    string name;
    int age;
    string course;

public:
    Student(int i, string n, int a, string c) {
        id = i;
        name = n;
        age = a;
        course = c;
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    string getCourse() {
        return course;
    }

    void setName(string n) {
        name = n;
    }

    void setAge(int a) {
        age = a;
    }

    void setCourse(string c) {
        course = c;
    }

    void display() {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age
             << " | Course: " << course << endl;
    }
};

// Global Student List
vector<Student> students;

// Function Declarations
void addStudent();
void searchStudent(int id);
void updateStudent(int id);
void deleteStudent(int id);
void saveToFile();
void loadFromFile();
int getValidInteger(string message);

// Function for Safe Integer Input
int getValidInteger(string message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input! Please enter numbers only.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Add Student
void addStudent() {
    int id, age;
    string name, course;

    id = getValidInteger("Enter Student ID: ");

    cout << "Enter Name: ";
    getline(cin, name);

    age = getValidInteger("Enter Age: ");

    cout << "Enter Course: ";
    getline(cin, course);

    students.push_back(Student(id, name, age, course));

    cout << "Student added successfully!\n";
}

// Search Student
void searchStudent(int id) {

    for (int i = 0; i < students.size(); i++) {

        if (students[i].getId() == id) {

            students[i].display();
            return;
        }
    }

    cout << "Student not found!\n";
}

// Update Student
void updateStudent(int id) {

    for (int i = 0; i < students.size(); i++) {

        if (students[i].getId() == id) {

            string name, course;
            int age;

            cout << "Enter new Name: ";
            getline(cin, name);

            age = getValidInteger("Enter new Age: ");

            cout << "Enter new Course: ";
            getline(cin, course);

            students[i].setName(name);
            students[i].setAge(age);
            students[i].setCourse(course);

            cout << "Student updated successfully!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

// Delete Student
void deleteStudent(int id) {

    for (int i = 0; i < students.size(); i++) {

        if (students[i].getId() == id) {

            students.erase(students.begin() + i);

            cout << "Student deleted successfully!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}

// Save Data to File
void saveToFile() {

    ofstream file("students.txt");

    for (int i = 0; i < students.size(); i++) {

        file << students[i].getId() << ","
             << students[i].getName() << ","
             << students[i].getAge() << ","
             << students[i].getCourse() << endl;
    }

    file.close();
}

// Load Data from File
void loadFromFile() {

    ifstream file("students.txt");

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        string idStr, name, ageStr, course;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, course, ',');

        int id = stoi(idStr);
        int age = stoi(ageStr);

        students.push_back(Student(id, name, age, course));
    }

    file.close();
}

// Main Function
int main() {

    loadFromFile();

    int choice = 0;
    int id;

    do {

        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Search Student\n";
        cout << "5. Exit\n";

        choice = getValidInteger("Enter your choice: ");

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            id = getValidInteger("Enter Student ID to update: ");
            updateStudent(id);
            break;

        case 3:
            id = getValidInteger("Enter Student ID to delete: ");
            deleteStudent(id);
            break;

        case 4:
            id = getValidInteger("Enter Student ID to search: ");
            searchStudent(id);
            break;

        case 5:
            saveToFile();
            cout << "Data saved. Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}


