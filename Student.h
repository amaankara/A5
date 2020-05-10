/*
Amaan Karachiwala
2326810
Karachiwala@chapman.edu
CPSC 350-01
*/

#include <iostream>
using namespace std;

class Student{
  private:
  public:
    Student();
    Student(int id, string name, string year, string major, double gpa, int advisor);
    ~Student();

    int studentID;
    string studentName;
    string studentYear;
    string major;
    double gpa;
    int advisorID;

    void setAdvisor(int id);
    int getAdvisor();
    string getMajor();
    double getGPA();
    void printStudentInfo();
};

Student::Student(){

}

Student::~Student(){

}

Student::Student(int id, string name, string year, string major, double gpa, int advisor){
  studentID = id;
  studentName = name;
  studentYear = year;
  major = major;
  gpa = gpa;
  advisorID = advisor;
}

void Student::setAdvisor(int id){
  advisorID = id;
}

int Student::getAdvisor(){
  return advisorID;
}

string Student::getMajor(){
  return major;
}

double Student::getGPA(){
  return gpa;
}

void Student::printStudentInfo(){
  cout << "Student ID: " << studentID << ", ";
  cout << "Student Name: " << studentName << ", ";
  cout << "Grade: " << studentYear << ", ";
  cout << "Major: " << major << ", ";
  cout << "GPA: " << gpa << ", ";
  cout << "Advisor ID: " << advisorID << ", ";
  cout<<endl;
}
