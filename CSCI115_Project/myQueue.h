#ifndef MYQUEUE_H
#define MYQUEUE_H
#include"mySClist.h"

class myQueue
{

public:
    myQueue();
    ~myQueue();
    myQueue(int capacity);
    myQueue(const mySCList& list);
    bool isFull() const;
    bool isEmpty() const;
    void enqueue(int value);
    int dequeue();
    int frontQueue() const;
    int rearQueue() const;
    void queueDisplay() const;
private:
    NodeSC* front; 
    NodeSC* rear; 
    int size;
    int capacity;
};
#endif
