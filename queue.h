//Shreya Gogini
//queue.h
//Description : header file for the Queue class

#include <iostream>

class Queue{
    private:
    //struct for creating the linked list
    struct Node{
        int data;
        Node *next;
    };
    //creating the head and tail pointers for the queue
    Node *head;
    Node *tail;

    public:
    Queue();
    Queue(Queue const &other);
    ~Queue();

    void operator=(Queue const&other);

    void enqueue(int);
    int dequeue();
    bool is_empty();
    int front_return();
    void display();

    
};
