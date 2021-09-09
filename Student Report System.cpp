#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//class that stores data about the students
class student
{
    int rollno;
    char name[50];
    int eng_marks, math_marks, sci_marks, lang_marks, cs_marks;
    double average;
    char grade;

    //all the functions that will be made that are used by the class
public:
    void getdata();
    void showdata();
    void calculate();
    int retrollno() const;
}

void student::calculate() //function that calculates the average from a student's grades
{
    average = (eng_marks + math_marks + sci_marks + lang_marks + cs_marks) / 5; //finding the average
    if (average >= 90) { //matching the averages to their grades
        grade = "A";
    }
    else if (average >= 80) {
        grade = "B";
    }
    else if (average >= 70) {
        grade = "C";
    }
    else if (average >= 60) {
        grade = "D";
    }
    else {
        grade = "F";
    }
    showdata();
}
void student::getdata()
{
    cout << "\nEnter student's roll number: ";
    cin >> rollno;
    cout << "\n\nEnter student name :"
        cin.ignore();
    cin.getline(name, 50);
    cout << "\nAll marks should be out of 100";
    cout << "\nEnter English marks: ";
    cin >> eng_marks;
    cout << "\nEnter Maths marks: ";
    cin >> math_marks;
    cout << "\nEnter Science marks: ";
    cin >> sci_marks;
    cout << "\nEnter Language marks: ";
    cin >> lang_marks;
    cout << "\nEnter Computer Science marks: ";
    cin >> cs_marks;
    calculate();
}
void student::showdata()
{
    cout << "\nRoll number of student: " << rollno;
    cout << "\nName of student: " << name;
    cout << "\nEnglish: " << eng_marks;
    cout << "\nMath: " << math_marks;
    cout << "\nScience: " << sci_marks;
    cout << "\nLanguage: " << lang_marks;
    cout << "\nComputer Science: " << cs_marks;
    cout << "\nAverage Marks: " << average;
    cout << "\nGrade: " << grade;
}
int main()
{
    getdata();
}