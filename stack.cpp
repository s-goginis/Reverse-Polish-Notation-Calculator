//Shreya Gogini
//stack.cpp
//Description: cpp file for the methods and holds the stack implementation


#include <iostream>
#include "stack.h"

#include <stdexcept>

using namespace std;

//desc : Constructor for the Stack class
//pre : a top pointer should be initialized
//post : sets the top of the stack to null
Stack :: Stack(){
    top = nullptr;
}

//desc: copy constructor that initializes the constructing instance with an
//      independent copy of the input's elements
//pre: a valid list from Stack should exist
//post : none
Stack :: Stack(Stack const &other){
    top = nullptr;
    *this = other;
}

//desc : destructor to deallocate the memory
//pre : stack exists
//post : none
Stack :: ~Stack(){
    
    while(!is_empty()){
        pop();
    }

}

//desc : Overwrites the contents of the instance with an
//      independent copy of the inputs methods
//pre : A valid list from Stack should exist
//post : Only the values from the list should be copied over, not the pointers
void Stack :: operator = (Stack const &other){
  
   //deallocates the list to use other
   this ->~Stack();
   //creates a temp to store the elements in the correct order
   Stack tempStack;
   Node *current = other.top;
   while(current !=nullptr){
    tempStack.push(current->data);
    current = current ->next;
   }
   //temp stack becomes the current stack
   current = tempStack.top;
   while(current != nullptr){
    push(current->data);
    current = current->next;
   }
}

//desc : adds the input value to the instance's collection of elements
//pre : a valid node exists
//post : none
void Stack :: push (int value){
    Node *temp = new Node();
    temp -> data = value;
    temp -> next = top;
    top = temp;   
}

//desc : removes and returns whichever element in the instance's
//      collection which was most recently added.
//pre : the stack has values otherwise error is thrown
//post : returns most recent element
int Stack :: pop(){
   
   //int return_value;
   //checks for run_time error
   if(is_empty()){
    throw runtime_error("No elements in stack to pop");
   }
   int return_val = top->data;
    Node *temp;
    temp = top;
    //return_value = temp->data;
    top = top->next;
    delete temp;
    return return_val;
   
   //returns the top value before the pop
   /*cout << return_value << " popped from stack" << endl;
   return return_value;*/
   
}

//desc : checks is the stack is empty
//pre : a stack exists
//post : returns true if stack is empty and false if not
bool Stack :: is_empty(){
    if (top == nullptr){
        return true;
    }
    else{
        return false;
    }
}

//returns the top value in the stack
int Stack :: top_return(){
    return top->data;
}

//displays the stack
void Stack :: display(){
    if (is_empty()){
        //cout << endl;
        return;
    }
    int x = top_return();
    // Pop the top element of the stack
    pop();
    // Recursively call the function PrintStack
    display();
    // Print the stack element starting
    // from the bottom
    cout << x << ", ";
    if(is_empty()){
        cout << "";
    }
    // Push the same element onto the stack
    // to preserve the order
    push(x);
}

//desc : pops the two top values from the stack and pushed the sum of the value
//pre : a stack exists so that there is no pop error
//post : the top values are popped and a new value is pushed
void Stack :: add(){
    int a = pop();
    int b = pop();
    push(a+b);
}

//desc : pops the two top values from the stack and pushes the difference
//pre : a stack exists so that there is no pop error
//post : the top values are popped and a new value is pushed
void Stack :: sub(){
    int a = pop();
    int b = pop();
    push(b-a);
}

//desc : pops the two top values from the stack and pushes the product
//pre : a stack exists so that there is no pop error
//post : the top values are popped and a new value is pushed
void Stack :: mul(){
    int a = pop();
    int b = pop();
    push(a*b);
}

//desc : pops the two top values from the stack and pushes the difference
//pre : a stack exists so that there is no pop error
//post : the top values are popped and a new value is pushed
void Stack :: div(){
    int a = pop();
    int b = pop();
    //checks for out of bound error in numbers
    if(b==0){
        cout << "Divide by zero error" << endl;
    }
    else{
        push(b/a);
    }
}

//desc : gets the current top value
//pre : stack exists
//post : prints the top value
void Stack :: top_output(){
    int top_value = top_return();
    cout << top_value << endl;
}

//desc : gets the current top value
//pre : stack exists
//post : prints the top value
void Stack :: dup(){
    int top_value = top_return();
    push(top_value);
}

//desc : pops the three top values from the stack;
//       if c is non-zero, a is pushed, otherwise b is pushed
//pre : a stack exists so that there is no pop error
//post : the top values are popped and a new value is pushed
void Stack ::  cond(){
    int c = pop();
    int b = pop();
    int a = pop();
    if(c!=0){
        push(a);
    }
    else if(c==0){
        push(b);
    }
}
