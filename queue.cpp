//Shreya Gogini
//queue.cpp
//Description : cpp file for the methods and holds the queue implementation

#include <iostream>
#include "queue.h"

using namespace std;

//desc : Constructor for the Queue Class
//pre : a head and tail pointer should be initialized
//post : sets the head and tail of the queue to nullptr
Queue :: Queue(){
    head = nullptr;
    tail = nullptr;
}

//desc : copy constructor that initializes the constructing instance 
//       with an independent copy of the input's elements
//pre : a valid list from Queue should exist
//post :: none
Queue :: Queue(Queue const& other){
    head = nullptr;
    *this = other;
}

//desc : destructor to deallocate memory
//pre : queue exists
//post : none
Queue :: ~Queue(){
  
    while(!is_empty()){
        dequeue();
    }
}

//desc : Overwrites the contents of the instance with an independent copy
//pre : a valid list from Queue should exist
//post : pointers should not be copied, a deep copy should be made
void Queue :: operator=(Queue const &other){
    //deallocates the list to use other
   this ->~Queue();
   //creates a temp stack
   Queue temp;
   Node *current = other.head;
   while(current != nullptr){
    temp.enqueue(current->data);
    current = current->next;
   }
   //temp queue becomes current queue
   current = temp.head;
   while(current != nullptr){
    enqueue(current->data);
    current= current->next;
   }
}

//desc : adds the input value to the instances collection of elements
//pre : a valid list exists
//post : queue is updated with new value
void Queue :: enqueue(int value){
    
    Node *temp = new Node;
    temp->data = value;
    temp->next = nullptr;

    if(is_empty()){
        head = temp;
        tail = temp;
    }
    else{
        tail ->next = temp;
        tail = temp;
    }
}

//desc : removes and returns the recently added element
//pre : queue has values
//post : if queue is empty, error is thrown, else returns element
int Queue :: dequeue(){
   
     Node *temp = nullptr;
     int value = 0;

    //checks for runtime error
     if(is_empty()){
        throw runtime_error("The queue is empty");
     }
     else{
        value = head->data;
        temp = head;
        head = head->next;
        delete temp;
     }
     return value;
}

//desc : checks if the queue is empty
//pre : a queue exists
//post : returns the state of the queue
bool Queue :: is_empty(){
    bool is_empty = false;
    if(head == nullptr){
        is_empty = true;
    }
    return is_empty;
}


//desc : returns the integer at the head of the queue
//pre : queue exists
//post : integer is returned
int Queue :: front_return(){
    return head->data;
}

//desc : displays the queue
//pre : queue exists
//post : none
void Queue :: display(){
    Node *temp = new Node;
    if(is_empty()){
        return;
    }
    else{
        temp = head;
        while(temp){
            cout << temp->data << ", ";
            if(is_empty()){
                cout << "";
            }
            temp = temp->next;
        }
    }
   
}
