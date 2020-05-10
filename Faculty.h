/*
Amaan Karachiwala
2326810
Karachiwala@chapman.edu
CPSC 350-01
*/

#include <iostream>
using namespace std;

class Faculty{
  private:
  public:
    Faculty();
    ~Faculty();
    Faculty(int id, string name, string level, string department);

    int facultyID;
    string facultyName;
    string facultyLevel;
    string facultyDepartment;

    int *adviseeList;
    unsigned int adviseeNo;
    unsigned int maxSize;
    bool addAdvisee(int id);
    bool removeAdvisee(int id);

    void printFaculty();
    void printAdvisee();
};

Faculty::Faculty(){

}

Faculty::~Faculty(){

}

Faculty::Faculty(int id, string name, string level, string department){
  facultyID= id;
  facultyName = name;
  facultyLevel = level;
  facultyDepartment = department;

  adviseeList = new int[10];
  adviseeNo = 0;
  maxSize = 10;
}

void Faculty::printAdvisee(){
  if(adviseeNo==0){
    cout << "No Advisee "<<endl;
  }

  else{
    for(int i=0; i<adviseeNo;++i){
      cout << adviseeList[i] << ", ";
    }
    cout<<endl;
  }
}

void Faculty::printFaculty(){
  cout << "Faculty ID: " << facultyID << ", ";
  cout << "Faculty Name: " << facultyName << ", ";
  cout << "Level: " << facultyLevel << ", ";
  cout << "Department: " << facultyDepartment << ", ";
  cout << "Advisee ID: ";
  printAdvisee();
}

bool Faculty::addAdvisee(int id){
  if(adviseeNo!=maxSize){
    for(int i =0; i<adviseeNo;++i){
      if(adviseeList[i]==id){
        cout << "Advisee already exists in List" << endl;
        return false;
      }
    }
    adviseeList[adviseeNo] = id;
    ++adviseeNo;
    return true;
  }
  else if(adviseeNo==maxSize){
    int *newArray = new int[adviseeNo];
    for(int i=0; i<adviseeNo;++i){
      newArray[i]==adviseeList[i];
    }
    adviseeList = new int[adviseeNo+1];
    maxSize++;
    for(int i=0;i<adviseeNo;++i){
      adviseeList[i]=newArray[i];
    }
    adviseeList[adviseeNo] = id;
    ++adviseeNo;
    return true;
  }
}

bool Faculty::removeAdvisee(int id){
  for(int i =0; i<adviseeNo;++i){
    if(adviseeList[i]==id){
      adviseeList[i] = -1;
      --adviseeNo;
      return true;
    }
  }
  return false;
}
