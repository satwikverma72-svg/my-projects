#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;
class University {
private:
    string RollNo, Name, Subject, Address;
public:
    University() : RollNo(""), Name(""), Subject(""), Address("") {}
    void setRollNo(const string &rollNo) { RollNo = rollNo; }
    void setName(const string &name) { Name = name; }
    void setSubject(const string &subject) { Subject = subject; }
    void setAddress(const string &address) { Address = address; }
    string getRollNo() const { return RollNo; }
    string getName() const { return Name; }
    string getSubject() const { return Subject; }
    string getAddress() const { return Address; }
};
string trim(string s) {
    while (!s.empty() && s.front() == ' ')
        s.erase(s.begin());
    while (!s.empty() && s.back() == ' ')
        s.pop_back();
    return s;
}
void add(University &student) {
    string rollNo, name, subject, address;
    cout << "\tEnter Roll No: ";
    getline(cin >> ws, rollNo);
    cout << "\tEnter Name: ";
    getline(cin, name);
    cout << "\tEnter Subject: ";
    getline(cin, subject);
    cout << "\tEnter Address: ";
    getline(cin, address);
    student.setRollNo(rollNo);
    student.setName(name);
    student.setSubject(subject);
    student.setAddress(address);
    ofstream out("university.txt", ios::app);
    if (!out) {
        cout << "\tError: File Can't Open!\n";
        return;
    }
    out << student.getRollNo() << " : "
        << student.getName() << " : "
        << student.getSubject() << " : "
        << student.getAddress() << '\n';

    out.close();
    cout << "\n\tStudent Added Successfully!\n";
}
bool parseLine(string line,
               string &rollNo,
               string &name,
               string &subject,
               string &address) {
    size_t p1 = line.find(" : ");
    if (p1 == string::npos) return false;
    size_t p2 = line.find(" : ", p1 + 3);
    if (p2 == string::npos) return false;
    size_t p3 = line.find(" : ", p2 + 3);
    if (p3 == string::npos) return false;
    rollNo = trim(line.substr(0, p1));
    name = trim(line.substr(p1 + 3, p2 - p1 - 3));
    subject = trim(line.substr(p2 + 3, p3 - p2 - 3));
    address = trim(line.substr(p3 + 3));
    return true;
}
void searchStudent() {
    string targetRollNo;
    cout << "\tEnter Roll No: ";
    getline(cin >> ws, targetRollNo);
    ifstream in("university.txt");
    if (!in) {
        cout << "\tError: File Can't Open!\n";
        return;
    }
    string line;
    bool found = false;
    while (getline(in, line)) {
        string rollNo, name, subject, address;
        if (parseLine(line, rollNo, name, subject, address)) {
            if (rollNo == targetRollNo) {
                cout << "\n\tStudent Found:\n";
                cout << "\tRoll No : " << rollNo << '\n';
                cout << "\tName    : " << name << '\n';
                cout << "\tSubject : " << subject << '\n';
                cout << "\tAddress : " << address << '\n';
                found = true;
                break;
            }
        }
    }
    if (!found)
        cout << "\tStudent Not Found!\n";

    in.close();
}
void updateStudent() {
    string targetRollNo;
    cout << "\tEnter Roll No To Update: ";
    getline(cin >> ws, targetRollNo);
    ifstream in("university.txt");
    ofstream out("university_temp.txt");
    if (!in || !out) {
        cout << "\tError: File Can't Open!\n";
        return;
    }
    string line;
    bool found = false;
    while (getline(in, line)) {
        string rollNo, name, subject, address;
        if (parseLine(line, rollNo, name, subject, address)
            && rollNo == targetRollNo) {
            cout << "\n\tEnter New Name: ";
            getline(cin, name);
            cout << "\tEnter New Subject: ";
            getline(cin, subject);
            cout << "\tEnter New Address: ";
            getline(cin, address);
            out << rollNo << " : "
                << name << " : "
                << subject << " : "
                << address << '\n';

            found = true;
        }
        else {
            out << line << '\n';
        }
    }
    in.close();
    out.close();
    if (!found) {
        remove("university_temp.txt");
        cout << "\tStudent Not Found!\n";
        return;
    }
    remove("university.txt");
    rename("university_temp.txt", "university.txt");
    cout << "\n\tRecord Updated Successfully!\n";
}
int main() {
    University student;
    bool exitProgram = false;
    while (!exitProgram) {
        system("cls");
        int choice;
        cout << "\n\t===== UNIVERSITY MANAGEMENT SYSTEM =====\n";
        cout << "\t1. Add Student\n";
        cout << "\t2. Search Student\n";
        cout << "\t3. Update Student\n";
        cout << "\t4. Exit\n";
        cout << "\tEnter Choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            add(student);
            Sleep(3000);
            break;
        case 2:
            system("cls");
            searchStudent();
            Sleep(3000);
            break;
        case 3:
            system("cls");
            updateStudent();
            Sleep(3000);
            break;
        case 4:
            exitProgram = true;
            cout << "\n\tGood Luck!\n";
            Sleep(2000);
            break;
        default:
            cout << "\n\tInvalid Choice!\n";
            Sleep(2000);
        }
    }
    return 0;
}