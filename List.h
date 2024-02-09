/*
 * Name: Owen Merwarth
 * Date Submitted: 1/24/2024
 * Lab Section: 003
 * Assignment Name: Lab 1: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List() {
  if (start != nullptr) {
    Node<T> * head = start;

    //Initialize mySize to 0
    mySize = 0; 
  }
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List() {
  Node<T> * current = start;
  Node<T> * next;

  //Navigating through the linked list
  while(current->next != nullptr) {
    next = current->next;

    delete(current);

    //Sets the value of current onto the next pointer
    current = next;
  }
}

//Return the size of this list
template <class T>
int List<T>::size() {
  return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty() {
  //Check to see if the start pointer points to a vlid node
  if (start == nullptr) {
    return true;
  } else {
    return false;
  }
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value) {
  //Dynamically allocated new node
  Node<T> * newNode = new Node<T>(value);

  newNode->next = start;

  start = newNode;

  mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value) {
  //Checking special case: list is empty
  if (start == nullptr) {
    insertStart(value);
    return;
  }
  
  //Dynamically allocated new node
  Node<T> * newNode = new Node<T>(value);

  Node<T> * current = start;

  //Traversing to the end of the linked list
  while(current->next != nullptr) {
    current = current->next;
  }

  current->next = newNode;
  
  mySize++;
}


//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j) {
  //Checking special case: looks for first element in list
  if (j <= 0) {
    insertStart(value);
    return;
  }
  
  int count = 0;

  //Dynamically allocated new node
  Node<T> * newNode = new Node<T>(value);

  Node<T> * current = start;

  //Checks to make sure it gets to the index to insert or if it reaches end of list
  while(count != j-1 && current->next != nullptr) {
    current = current->next;

    count++;
  }

  Node<T> * temp = current->next;

  current->next = newNode;

  newNode->next = temp;  

  mySize++;
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart() {
  //Checking special case: list is empty
  if (start != nullptr) {
    //Checking special case: list has one item
    if (start->next == nullptr) {
      start = nullptr;
      return;
    }

    //Create temp so that the memory can be freed after unlinking node
    Node<T> * temp = start;

    start = start->next;
  
    delete temp;

    mySize--;
  }
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd() {
  Node<T> * current = start;

  //Checking special case: list is empty    
  if (start != nullptr) {
    //Checking special case: list has one item 
    if (current->next == nullptr) {
      removeStart();
      return;
    }

    //Must stop two nodes before the end of the linked list
    while(current->next->next != nullptr) {
      current = current->next;
    }

    Node<T> * temp = current->next;
    
    current->next = nullptr;
  
    delete temp;

    mySize--;
  }
}
  
//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j) {
  //Special case: If the target index is 0
  if (j <= 0) {
    removeStart();
    return;
  }
  
  Node<T> * current = start;

  //Checking special case: list is empty    
  if (start != nullptr) {
    int count = 0;

    //Checking to reduce memory leaks
    while(count < j-1 && current != nullptr && current->next != nullptr) {
      current = current->next;
      count++;
    }

    Node<T> * temp = current->next;

    current->next = current->next->next;
    
    delete temp;

    mySize--;
  }
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst() {
  //Checking special case: list is empty  
  if (start == nullptr) {
    return T();
  }

  return start->value;
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast() {
  Node<T> * current = start;

  //Checking special case: list is empty  
  if (current == nullptr) {
    return T();
  }

  //Checking for special case: list has one element
  if (current->next == nullptr) {
    return getFirst();
  }
  
  while(current->next != nullptr) {
    current = current->next;
  }

  return current->value;
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j) {
  Node<T> * current = start;

  //Checking special case: list is empty
  if (current == nullptr) {
    return T();
  }
  
  int count = 0;
  
  while(count != j) {
    current = current->next;

    count++;
  }

  return current->value;
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key) {
  Node<T> * current = start;

  int count = 0;

  //Checking special case: list is empty    
  while (current != nullptr) {
    if (current->value == key) {
      return count;
    }

    current = current->next;

    count++;
  }

  return -1;
}
