/*
Amaan Karachiwala
2326810
Karachiwala@chapman.edu
CPSC 350-01
*/

#include <iostream>
#include <stack>
#include <string>
using namespace std;

template <class T>
class GenStack
{
  public:
    GenStack(int maxSize); // overloaded constructor
    ~GenStack(); // destructor

    //functions
    void push(T data); //insert
    T* pop(); //remove
    void increaseSize(); //increase size of array

    //helper functions
    int isFull();
    int isEmpty();
    T* peek();
    int mSize; //max size of the stack
    int top; //variable to keep track of indices reoresenting the top of our stack

    T *myArray; //declaring a pointer for the array and size will be added later (at runtime)
    T *newArray; //temp array to increase size

};

template <class T>
GenStack<T>::GenStack(int maxSize)
{
  myArray = new T[maxSize];
  mSize = maxSize;
  top = -1;
}

//destructor
template <class T>
GenStack<T>:: ~ GenStack()
{
  delete myArray;
}

template <class T>
int GenStack<T>::isFull(){
  return (top== mSize-1);
}

template <class T>
int GenStack<T>::isEmpty(){
  return(mSize == 0);
}

template <class T>
void GenStack<T>::push(T data)
{
  if(isFull()==mSize){
    //cout<<"The stack is full"<<endl;
    increaseSize();
    myArray[++top] = data;
  }
  else{
    myArray[++top] = data;
  }
}

template <class T>
T* GenStack<T>::pop(){
  if(isEmpty()==1){
    cout<<"The stack is empty"<<endl;
  }
  else{
    return myArray[top--];
  }
}

template <class T>
T* GenStack<T>::peek(){
  return myArray[top -=1];
}

template <class T>
void GenStack<T>::increaseSize(){
  newArray = new T[mSize];

  for(int i =0; i<mSize;++i){
    newArray[i]=myArray[i];
  }
  mSize++;
  myArray= new T[mSize];

  for(int i =0; i<mSize;++i){
    myArray[i]=newArray[i];
  }
}
