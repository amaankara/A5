/*
Amaan Karachiwala
2326810
Karachiwala@chapman.edu
CPSC 350-01
*/
#include <iostream>
#include <fstream>
#include "TreeNode.h"
#include "Faculty.h"
#include "Student.h"
//#include "Menu.h"
#include "GenStack.h"
using namespace std;

BST<Student> studentTree;
BST<Faculty> facultyTree;
int studentCount;
int facultyCount;

void importFile(){

  string line ="";
  int count = 1;
  //Faculty import
  int facultyImported=0;
  int fID;
  string fName;
  string fLevel;
  string fDep;
  int numAdvisee;

  //Student import;
  int studentImported = 0;
  int sID;
  string sName;
  string sYear;
  string sMajor;
  double sGPA;
  int sAdvisorID;

  ifstream myFacultyFile;
  myFacultyFile.open("FacultyData.txt");
  getline(myFacultyFile,line);
  if(line==""){
    cout<<"DataBase is empty " <<endl;
  }
  else{
    facultyCount=stoi(line);
  }

  while(getline(myFacultyFile,line)){
    switch(count){
      case 1: {
        if(line=="-x-"){
        }
        else{
          cout<<"Incorrect file format " <<endl;
        }
        break;
      }
      case 2: {
        fID = stoi(line);
        break;
      }
      case 3: {
        fName = line;
        break;
      }
      case 4: {
        fLevel = line;
        break;
      }
      case 5: {
        fDep=line;
        break;
      }
      case 6: {
        int adviseeNo = stoi(line);
        Faculty* f = new Faculty(fID, fName, fLevel, fDep);
        facultyImported++;
        while(adviseeNo!=0){
          getline(myFacultyFile,line);
          f->addAdvisee(stoi(line));
          --adviseeNo;
        }
        TreeNode<Faculty> *fNode = new TreeNode<Faculty>(fID,f);
        facultyTree.insert(fNode);
        break;
      }
      default :{
        break;
      }
    }
    count++;
    if(count>6){
      count = 1;
    }
    if(facultyCount==facultyImported){
      break;
    }
  }
  myFacultyFile.close();

  ifstream myStudentFile;
  myStudentFile.open("StudentData.txt");
  getline(myStudentFile,line);
  if(line==""){
    cout<<"DataBase is empty "<<endl;
  }
  else{
    studentCount=stoi(line);
  }
  while(getline(myStudentFile,line)){
    switch(count){
      case 1: {
        if(line=="-x-"){
        }
        else{
          cout<<"Incorrect file format "<<endl;
        }
        break;
      }
      case 2: {
        sID = stoi(line);
        break;
      }
      case 3: {
        sName = line;
        break;
      }
      case 4: {
        sYear = line;
        break;
      }
      case 5: {
        sMajor = line;
        break;
      }
      case 6: {
        sGPA = stoi(line);
        break;
      }
      case 7: {
        sAdvisorID = stoi(line);
        Student *s = new Student(sID,sName,sYear,sMajor,sGPA,sAdvisorID);
        TreeNode<Student> *sNode = new TreeNode<Student>(sID,s);
        studentTree.insert(sNode);
        studentImported++;
        break;
      }
      default : {
        break;
      }
    }
    count++;
    if(count>7){
      count=1;
    }
    if(studentCount==studentImported){
      break;
    }
  }
  myStudentFile.close();
}

void printStudentTree(TreeNode<Student> *sNode){
  if(sNode!=NULL){
    if(sNode->left!=NULL){
      printStudentTree(sNode->left);
    }
    sNode->value->printStudentInfo();
    if(sNode->right!= NULL){
      printStudentTree(sNode->right);
    }
  }
  else{
    cout<<"Student DataBase is empty "<<endl;
  }
}

void printFacultyTree(TreeNode<Faculty> *fNode){
  if(fNode!=NULL){
    if(fNode->left!=NULL){
      printFacultyTree(fNode->left);
    }
    fNode->value->printFaculty();
    if(fNode->right!= NULL){
      printFacultyTree(fNode->right);
    }
  }
  else{
    cout<<"Faculty Database is empty "<<endl;
  }
}

void findStudent(){
  int id;
  cout<<"enter the student id " << endl;
  cin>>id;
  TreeNode<Student>* sNode = studentTree.search(id);
  Student* s = sNode->value;
  if(s==NULL){
    cout << "Student ID does not exist in database " << endl;
  }
  else{
    s->printStudentInfo();
  }
}

void findFaculty(){
  int id;
  cout<<"enter the faculty id " << endl;
  cin>>id;
  TreeNode<Faculty>* fNode = facultyTree.search(id);
  Faculty* f = fNode->value;
  if(f==NULL){
    cout << "Faculty does not exist in database " << endl;
  }
  else{
    f->printFaculty();
  }
}

void displayAdvisor(){
  int id;
  cout<<"Enter Student ID to display faculty advisor " << endl;
  cin>>id;
  TreeNode<Student>* sNode = studentTree.search(id);
  Student* s = sNode->value;
  if(s==NULL){
    cout<<"Student does not exist in database " <<endl;
  }
  else{
    TreeNode<Faculty>* fNode = facultyTree.search(s->advisorID);
    Faculty* f = fNode->value;
    f->printFaculty();
  }
}

void displayAdvisee(){
  int id;
  cout<<"Enter Faculty ID to display Student advisees " << endl;
  cin>>id;
  TreeNode<Faculty>* fNode = facultyTree.search(id);
  Faculty* f = fNode->value;
  if(f==NULL){
    cout<<"Faculty does not exist in database " <<endl;
  }
  else{
    if(f->adviseeNo==0){
      cout<<"Faculty does not have any advisee " <<endl;
    }
    else{
      for(int i =0; i<f->adviseeNo; ++i){
        TreeNode<Student>* sNode = studentTree.search(f->adviseeList[i]);
        Student* s = sNode->value;
        s->printStudentInfo();
      }
    }
  }
}

void addStudent(){
  int id;
  string name;
  string year;
  string major;
  double gpa;
  int advisorID;

  cout<< "enter student's ID " <<endl;
  cin>>id;
  cout<<"enter student's name " <<endl;
  cin>>name;
  cout<<"enter student's year " <<endl;
  cin>>year;
  cout<<"enter student's major " << endl;
  cin>>major;
  cout<<"enter student's gpa" << endl;
  cin>>gpa;
  cout<<"enter advisor ID" << endl;
  cin>>advisorID;

  Student *s=new Student(id,name,year,major,gpa,advisorID);
  TreeNode<Student> *sNode = new TreeNode<Student>(id,s);
  studentTree.insert(sNode);
  studentCount++;
}

void deleteStudent(){
  int id;
  cout<<"Enter the ID of the student to be deleted " <<endl;
  cin>>id;
  studentTree.deleteNode(id);
}

void addFaculty(){
  int id;
  string name;
  string level;
  string dep;

  cout<<"enter faculty's ID " <<endl;
  cin>>id;
  cout<<"enter faculty's name " <<endl;
  cin>>name;
  cout<<"enter faculty's level " <<endl;
  cin>>level;
  cout<<"enter faculty's department " <<endl;
  cin>>dep;

  Faculty *f = new Faculty(id,name,level,dep);

  int adviseeNo;
  cout<<"how many advisee's does the faculty have " <<endl;
  cin>>adviseeNo;

  for(int i =0; i<adviseeNo; i++){
    int adviseeID = 0;
    cout<<"enter advisee ID " <<endl;
    cin>>adviseeID;
    f->addAdvisee(adviseeID);
  }

  TreeNode<Faculty> *fNode= new TreeNode<Faculty>(id,f);
  facultyTree.insert(fNode);
  facultyCount++;
}

void deleteFaculty(){
  int id;
  cout<<"Enter the ID of the faculty to be deleted " <<endl;
  cin>>id;

  facultyTree.deleteNode(id);
}

void changeAdvisor(){
  int id;
  int newID;
  cout<<"Enter Student ID to change Faculty advisor "<<endl;
  cin>>id;
  TreeNode<Student>* sNode = studentTree.search(id);
  Student* s = sNode->value;
  if(s==NULL){
    cout<<"Student does not exist in DataBase "<<endl;
  }
  else{
    bool loopCheck = false;
    while(loopCheck==false){
      cout<<"Enter new advisor ID " <<endl;
      cin>>newID;
      TreeNode<Faculty>* fNode = facultyTree.search(newID);
      if(fNode==NULL){
        cout<< "Faculty does not exist in DataBase " <<endl;
      }
      else{
            s->advisorID= newID;
            loopCheck=true;
      }
    }
  }
}

void removeAdvisee(){
  int id;
  int sID;
  cout<<"Enter Faculty ID to delete Student advisee "<<endl;
  cin>>id;
  TreeNode<Faculty>* fNode = facultyTree.search(id);
  Faculty* f = fNode->value;
  if(f==NULL){
    cout<<"faculty does not exist in DataBase "<<endl;
  }
  else{
    bool loopCheck=false;
    while(loopCheck==false){
      cout<<"Enter the Student ID of advisee to be deleted "<<endl;
      cin>>sID;
      TreeNode<Student>* sNode = studentTree.search(sID);
      if(sNode==NULL){
        cout<<"Student does not exist in Database " <<endl;
      }
      else{
        bool studentInList = f->removeAdvisee(sID);
        if(studentInList==true){
          loopCheck=true;
        }
        else{
          cout<<"Student is not a part of the Advisee list "<<endl;
        }
      }
    }
  }
}

void writeStudent(TreeNode<Student> *sNode){
  ofstream myStudentFile;
  myStudentFile.open("StudentData.txt");

  if(sNode!=NULL){
    myStudentFile<<"-x-"<<endl;
    myStudentFile<< sNode->value->studentID <<endl;
    myStudentFile<< sNode->value->studentName <<endl;
    myStudentFile<< sNode->value->studentYear <<endl;
    myStudentFile<< sNode->value->major <<endl;
    myStudentFile<< sNode->value->gpa <<endl;
    myStudentFile<< sNode->value->advisorID <<endl;

    if(sNode->left!=NULL){
      writeStudent(sNode->left);
    }
    if(sNode->right!=NULL){
      writeStudent(sNode->right);
    }
  }
  else{
    cout <<"Student DataBase is empty "<<endl;
  }

  myStudentFile.close();
}

void writeFaculty(TreeNode<Faculty> *fNode){
  ofstream myFacultyFile;
  myFacultyFile.open("FacultyData.txt");

  if(fNode!=NULL){
    myFacultyFile<<"-x-"<<endl;
    myFacultyFile<< fNode->value->facultyID <<endl;
    myFacultyFile<< fNode->value->facultyName <<endl;
    myFacultyFile<< fNode->value->facultyLevel <<endl;
    myFacultyFile<< fNode->value->facultyDepartment<<endl;

    for(int i=0;i<fNode->value->adviseeNo;++i){
      if(fNode->value->adviseeList[i]!=-1){
        myFacultyFile<< fNode->value->adviseeList[i] <<endl;
      }
    }

    if(fNode->left != NULL){
      writeFaculty(fNode->left);
    }
    if(fNode->right!=NULL){
      writeFaculty(fNode->right);
    }
  }
  else{
    cout<<"DataBase is empty "<<endl;
  }
  myFacultyFile.close();
}

void writeToFile(){
  ofstream myStudentFile;
  ofstream myFacultyFile;

  myStudentFile.open("StudentData.txt");
  myStudentFile<< studentCount <<endl;
  TreeNode<Student> *currStudent = studentTree.root;
  writeStudent(currStudent);
  myStudentFile.close();

  myFacultyFile.open("FacultyData.txt");
  myFacultyFile<< facultyCount << endl;
  TreeNode<Faculty> *currFaculty = facultyTree.root;
  writeFaculty(currFaculty);
  myFacultyFile.close();
}

void printMenu(){
  int input;
  bool exit = false;

  while(exit==false){
    cout<< "Enter the number of the menu option " <<endl;
    cout<< "1 - print all students and their info " << endl;
    cout<< "2 - print all faculty and their info " << endl;
    cout<< "3 - Find and display student info, given a Student ID " << endl;
    cout<< "4 - Find and display faculty info, given a faculty ID " << endl;
    cout<< "5 - Gvien a student ID, display advisor info " << endl;
    cout<< "6 - Given faculty ID, display all advisee info " << endl;
    cout<< "7 - Add student " << endl;
    cout<< "8 - Delete student with a given ID " << endl;
    cout<< "9 - Add faculty " << endl;
    cout<< "10 - Delete faculty with given ID " << endl;
    cout<< "11 - Change student advisor, student ID and new advisor ID needed " << endl;
    cout<< "12 - Remove advisee from faculty memeber's list, given the IDs " << endl;
    cout<< "13 - rollback (only for option 7,8,9 and 10)" << endl;
    cout<< "14 - exit " << endl;

    cin>>input;

    if(input<0&& input>15){
      cout<<"Invaild option selected " << endl;
    }
    else{
      if(input==1){
        if(studentTree.isEmpty()){
          cout<<"Student DataBase is empty "<<endl;
        }
        else{
          printStudentTree(studentTree.root);
        }
      }
      else if(input==2){
        if(facultyTree.isEmpty()){
          cout<<"Faculty Database is empty "<<endl;
        }
        else{
          printFacultyTree(facultyTree.root);
        }
      }
      else if(input==3){
        findStudent();
      }
      else if(input==4){
        findFaculty();
      }
      else if(input==5){
        displayAdvisor();
      }
      else if(input==6){
        displayAdvisee();
      }
      else if(input==7){
        addStudent();
      }
      else if(input==8){
        deleteStudent();
      }
      else if(input==9){
        addFaculty();
      }
      else if(input==10){
        deleteFaculty();
      }
      else if(input==11){
        changeAdvisor();
      }
      else if(input==12){
        removeAdvisee();
      }
      else if(input==13){
        //rollback();
      }
      else if(input==14){
        exit = true;
        writeToFile();
      }
    }

  }
}

int main(int argc,char** argv){
  studentCount=0;
  facultyCount = 0;
  importFile();
  printMenu();
  return 0;
}
