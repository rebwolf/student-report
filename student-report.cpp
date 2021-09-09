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
};

void student::calculate() //function that calculates the average from a student's grades
{
    average = (eng_marks + math_marks + sci_marks + lang_marks + cs_marks) / 5; //finding the average
    if (average >= 90) { //matching the averages to their grades
        grade = 'A';
    }
    else if (average >= 80) {
        grade = 'B';
    }
    else if (average >= 70) {
        grade = 'C';
    }
    else if (average >= 60) {
        grade = 'D';
    }
    else {
        grade = 'F';
    }
    showdata();
}
void student::getdata()
{
    student stud;
    cout << "\nEnter student's roll number: ";
    cin >> rollno;
    //added myself, checks to see if the roll number is already taken, if so, makes the user re-enter a roll no
    ifstream checkFile;
    checkFile.open("student.dat", ios::binary);
    if (checkFile) {
        while (checkFile.read(reinterpret_cast<char*>(&stud), sizeof(student))) {
            if (stud.retrollno() == rollno) {
                cout << "\nRoll number already assigned. Please enter a new one...";
                student stud;
                stud.getdata();
            }
        }
    }
    cout << "\n\nEnter student name :";
    cin.ignore(); //pauses the program until user presses the enter key
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
int student::retrollno() const //this function returns the rollno as it will need to be used in the code later on, needs its own function as the variables are private so cannot be accessed outside the class
{
    return rollno;
}
//declaring functions that will be made later
void create_student();
void display_sp(int); //display particular record
void display_all(); //display all records
void delete_student(int); //delete particular record
void change_student(int); //edit particular record

//main, where the code runs
int main()
{
    char ch = '0';
    cout << setprecision(2); //sets the decimal precision (to 2 decimal places??)
    do {
        int num;
        system("cls"); //clears the screen or console of any commands or outputs
        cout << "\n\n\nMENU";
        cout << "\n\n\t1. Create student record";
        cout << "\n\n\t2. Search student record";
        cout << "\n\n\t3. Display all student records";
        cout << "\n\n\t4. Delete student record";
        cout << "\n\n\t5. Modify student record";
        cout << "\n\n\t6. Exit";
        cout << "\n\nWhat is your choice (1/2/3/4/5/6) ";
        cin >> ch;
        system("cls"); //clear the system
        switch (ch) //switch case going through all the choices
        {
            case '1': create_student(); break; //ends the switch case
            case '2': cout << "\n\nEnter the roll number: "; cin >> num; display_sp(num); break;
            case '3': display_all(); break;
            case '4': cout << "\n\nEnter the roll number: "; cin >> num; delete_student(num); break;
            case '5': cout << "\n\nEnter the roll number: "; cin >> num; change_student(num); break;
            case '6': cout << "Exiting! Thank you!"; exit(0); //terminates process
        }
    } while (ch != '6'); // ch is the decision the teacher will make, when they choose 6, the system is closed, so this loop will continue to run until the system is exited
    return 0; //ends the main function
}
void create_student() //function to add a student's details and save to a file
{
    student stud; //create an object of the student class
    ofstream oFile; //create a new file
    oFile.open("student.dat", ios::binary | ios::app); //binary opens the file without changing anything, read exactly as it was made, app ensures all output operations are performed at the end of the file
    stud.getdata();
    oFile.write(reinterpret_cast<char*> (&stud), sizeof(student)); //may be changing the address of stud to a character? that will be then be written to the file (check file after it's made)
    oFile.close();
    cout << "\n\nStudent record has been created ";
    cin.ignore();
    cin.get(); //this may allow the user to press enter - check when code runs
}
//reading all the files of students
void display_all()
{
    student stud;
    ifstream inFile;
    inFile.open("student.dat", ios::binary); //opens the file allowing it to be read (binary)
    if (!inFile)
    {
        cout << "File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char*> (&stud), sizeof(student))) {
        stud.showdata();
        cout << "\n" << reinterpret_cast<char*> (&stud), sizeof(student);
        cout << "\n\n===========================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
    return;
}
//reading a specific record based on the roll number of the student
void display_sp(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile) {
        cout << "File could not be opened...Press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (iFile.read(reinterpret_cast<char*>(&stud), sizeof(student))) { //reads the file, ??Converts the class into a character array??, goes through the size of student
        if (stud.retrollno() == n) { //when the retroll no is found, (which is equal to n, the retroll number entered), the class found in the file is then used to show data about that student
            stud.showdata();
            cin.ignore();
            cin.get();
            flag = true;
        }
    }
    iFile.close(); //closing the file
    if (flag == false) { //if the retroll number doesn't exist within the file
        cout << "\n\nRecord doesn't exist";
        cin.ignore();
        cin.get();
    }
}
//modify record for a specified roll number
void change_student(int n)
{
    bool found = false;
    student stud;
    fstream fl;
    fl.open("student.dat", ios::binary | ios::out | ios::in);
    if (!fl) {
        cout << "File could not be opened...Press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    while (!fl.eof() && found == false) //.eof is true if the end of the file has been reached, and false if it hasn't
    {
        fl.read(reinterpret_cast<char*> (&stud), sizeof(student));
        if (stud.retrollno() == n) { //if the retroll number of the student has been found
            stud.showdata();
            cout << "\nEnter new student details: ";
            stud.getdata();
            int pos = (-1)*static_cast<int>(sizeof(stud)); //converting the size of the the object into an integer, which is multiplies by -1 and then stored in an integer called pos
            fl.seekp(pos, ios::cur); //searches from the start of the object to the end in the file (using pos, which is the size of the object)
            fl.write(reinterpret_cast<char*> (&stud), sizeof(student)); //write to the file over the original details
            cout << "\n\nRecord Updated";
            found = true;
        }
    }
    fl.close();
    if (found == false) { //if the file cannot be found
        cout << "\n\nRecord Not Found";
        cin.ignore();
        cin.get();
    }
}
void delete_student(int n) {
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile) {
        cout << "File could not be opened...Press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat", ios::out); //makes a new file which will become the new file, each record except from the one being deleted will be written to this file
    iFile.seekg(0, ios::beg); //sets the input position to the beginning of the file, so it can be read from the beginning
    while (iFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
    {
        if (stud.retrollno() != n) {
            oFile.write(reinterpret_cast<char*> (&stud), sizeof(student));
        }
        oFile.close();
        iFile.close();
        remove("student.dat"); //deletes the file
        rename("Temp.dat", "student.dat");
        cout << "\n\n\tRecord Deleted ..";
        cin.ignore();
        cin.get();
    }
}