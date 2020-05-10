/*
Amaan Karachiwala
2326810
Karachiwala@chapman.edu
CPSC 350-01
*/

#include <iostream>
using namespace std;

template <class T>
class TreeNode{
public:
  TreeNode();
  TreeNode(int key, T* value);
  //TreeNode(int k, <type> value);
  //~TreeNode();
  //when working with template classes
  virtual ~TreeNode();

  int key;
  T* value;
  TreeNode<T> *left;
  TreeNode<T> *right;

};

//TreeNode implementation
template <class T>
TreeNode<T>::TreeNode(){
  key = 0;
  left = NULL;
  right = NULL;
}
//overloaded constructor
template <class T>
TreeNode<T>::TreeNode(int k, T* v){
  key = k;
  value = v;
  left = NULL;
  right = NULL;
}
//destructor
template <class T>
TreeNode<T>::~TreeNode(){
  /*
  delete key;
  delete left;
  delete right;
  */
}

template <class T>
class BST{
  private:
  public:
    BST();
    ~BST();

    TreeNode<T>* search(int k); //search on id
    void insert(TreeNode<T> *value);  //Inserting value node. Make sure to make elements a node beofre inserting in BST and set ID as key
    bool deleteNode(int k);

    bool isEmpty();
    TreeNode<T>* getMin();
    TreeNode<T>* getMax();

    TreeNode<T>* getSuccessor(TreeNode<T> *d);
    void printTree(TreeNode<T> *node);

    TreeNode<T> *root;
};

template <class T>
//constructor
BST<T>::BST(){
  root = NULL;
}
template <class T>
//destructor
BST<T>::~BST(){
  //delete root;
}

//printTree
template <class T>
void BST<T>::printTree(TreeNode<T> *node){
  if(node == NULL){
    return;
  }
  //how to print??
  printTree(node->left);
  cout << node->key << endl;
  printTree(node->right);
}

//get max value
template <class T>
TreeNode<T>* BST<T>::getMax(){
  TreeNode<T> *curr = root;

  if(root=NULL){
    return NULL; //tree is isEmpty
  }
  while(curr->right != NULL){
    curr = curr->right;
  }
  return curr; //return the node on the extreme right
}
//get min value
template <class T>
TreeNode<T>* BST<T>::getMin(){
  TreeNode<T> *curr = root;

  if(root=NULL){
    return NULL; //tree is isEmpty
  }
  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr; //return the node on the extreme left
}

//is empty?
template <class T>
bool BST<T>::isEmpty(){
  return (root==NULL);
}

//insert a value
template <class T>
void BST<T>::insert(TreeNode<T> *value){
  //TreeNode *node = new TreeNode(value);
  if(root==NULL){
    root = value;
  }
  else{
    TreeNode<T> *curr = root;
    TreeNode<T> *parent; //empty node

    while(true){
      parent = curr;

      if(value->key < curr->key){
        //we go left
        curr = curr->left;
        if(curr == NULL){
          parent->left = value;
          break;
        }
      }
      else{
        //go right
        curr = curr->right;
        if(curr = NULL){
          parent->right = value;
        }
      }
    }
  }
}

//search for a value
template <class T>
TreeNode<T>* BST<T>::search(int value){ //value is key
  if(isEmpty()){
    return NULL;
  }
  else{
    //tree is not empty
    TreeNode<T> *curr = root;

    while(curr->key != value){
      if(value < curr->key){
        curr = curr->left;
      }
      else{
        curr = curr->right;
      }

      if(curr==NULL){
        return NULL;
      }
    }
    return curr;
  }
}

//delete node
template <class T>
bool BST<T>::deleteNode(int k ){
  if(isEmpty()){
    return false;
  }
  else if(!(search(k))){
    return false;
  }
  //tree not empty and value exists
  TreeNode<T> *curr = root;
  TreeNode<T> *parent = root;
  bool isLeft = true;

  while(curr->key != k){
    parent = curr;
    if(k < curr->key){
      isLeft = true;
      curr = curr->left;
    }
    else{
      isLeft = false;
      curr = curr->right;
    }
    if(curr==NULL){
      return false;
    }
  }
  //if we made it here we found node

  //no child, leaf node
  if(curr->left==NULL && curr->right==NULL){
    if(curr==root){
      root = NULL;
    }
    else if(isLeft){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
  }
  //if it is one child, left child
  else if(curr->right ==NULL){
    //root being deleted
    if(curr==root){
      root=curr->left;
    }
    else if(isLeft){
      parent->left = curr->left;
    }
    else{
      parent->right = curr->left;
    }
  }
  //if it is one child, right child
  else if(curr->left ==NULL){
    //root being deleted
    if(curr==root){
      root=curr->right;
    }
    else if(isLeft){
      parent->left = curr->right;
    }
    else{
      parent->right = curr->right;
    }
  }
  else{
    //node have 2 children
    TreeNode<T> *successor = getSuccessor(curr);

    if(curr==root){
      root= successor;
    }
    else if(isLeft){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }

    successor->left = curr->left;
    return true;
  }
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
  //d is the node to be deleted

  TreeNode<T> *sp=d;
  TreeNode<T> *successor = d;
  TreeNode<T> *curr = d->right;

  while(curr != NULL){
    sp = successor;
    successor = curr;
    curr = curr->left;
  }

  if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;
  }

  return successor;
}
