#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Queue
{
public:
    Queue();
    ~Queue();

	void enqueue(int);
	int dequeue();

	//int peek() const;
	bool isEmpty() const;

    void printQueue();


private:
    Node* front;
    Node* rear;
};

#endif