
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


class Student
{
private:
    int rollNo;
    string name;
    float marks;

public:

    
    Student(int r, string n, float m)
    {
        rollNo = r;
        name = n;
        marks = m;
    }

    
    int getRollNo()
    {
        return rollNo;
    }

    
    void display()
    {
        cout << "\nRoll Number: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
    }

    
    void save(ofstream &file)
    {
        file << rollNo << endl;
        file << name << endl;
        file << marks << endl;
    }
};


class StudentManagement
{
private:
    vector<Student> students;

public:

    
    void addStudent()
    {
        int r;
        string n;
        float m;

        cout << "\nEnter Roll Number: ";
        cin >> r;

        
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getRollNo() == r)
            {
                cout << "\nRoll Number Already Exists!";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, n);

        cout << "Enter Marks: ";
        cin >> m;

        if (cin.fail() || m < 0 || m > 100)
        {
            cout << "\nInvalid Marks!";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        Student s(r, n, m);
        students.push_back(s);

        saveData();

        cout << "\nStudent Added Successfully!";
    }

    
    void displayStudents()
    {
        if (students.empty())
        {
            cout << "\nNo Student Records Found!";
            return;
        }

        for (int i = 0; i < students.size(); i++)
        {
            students[i].display();
        }
    }

    
    void searchStudent()
    {
        int r;

        cout << "\nEnter Roll Number: ";
        cin >> r;

        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getRollNo() == r)
            {
                cout << "\nStudent Found!";
                students[i].display();
                return;
            }
        }

        cout << "\nStudent Not Found!";
    }

    
    void deleteStudent()
    {
        int r;

        cout << "\nEnter Roll Number to Delete: ";
        cin >> r;

        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getRollNo() == r)
            {
                students.erase(students.begin() + i);
                saveData();

                cout << "\nStudent Deleted Successfully!";
                return;
            }
        }

        cout << "\nStudent Not Found!";
    }

    
    void saveData()
    {
        ofstream file("students.txt");

        for (int i = 0; i < students.size(); i++)
        {
            students[i].save(file);
        }

        file.close();
    }

    
    void loadData()
    {
        ifstream file("students.txt");

        int r;
        string n;
        float m;

        while (file >> r)
        {
            file.ignore();
            getline(file, n);

            if (file >> m)
            {
                students.push_back(Student(r, n, m));
            }
        }

        file.close();
    }
};


int main()
{
    StudentManagement obj;

    obj.loadData();

    int choice;

    do
    {
        
        cout << "\n STUDENT RECORD MANAGEMENT SYSTEM";
        

        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                obj.addStudent();
                break;

            case 2:
                obj.displayStudents();
                break;

            case 3:
                obj.searchStudent();
                break;

            case 4:
                obj.deleteStudent();
                break;

            case 5:
                cout << "\nThank You!";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 5);

    return 0;
}
