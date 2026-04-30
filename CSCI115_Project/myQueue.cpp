#include"myQueue.h"
#include"mySClist.h"
#include<iostream>

    myQueue::myQueue():size(0), capacity(0), front(nullptr), rear(nullptr){}
    myQueue::~myQueue(){
        while (!isEmpty())
        {
            dequeue();
        }
    }
    myQueue::myQueue(int cap): size(0), capacity(cap), front(nullptr), rear(nullptr){}
    bool myQueue::isFull() const {
        bool cap = (capacity > 0) && (size == capacity);
        return cap;
    }
    
    myQueue::myQueue(const mySCList& list)
    : size(0), capacity(0), front(nullptr), rear(nullptr) {
        NodeSC* current = list.getHead();

        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
}
    
    bool myQueue::isEmpty() const {
        return size == 0;
    }
    void myQueue::enqueue(int value) {
        if (isFull()){return;}
        NodeSC* temp = new NodeSC(value);
        temp->next = nullptr;
        if (isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
        size++;
    }
    int myQueue::dequeue() {
        if (isEmpty()){return -1;}
        NodeSC* temp = front;
        int value  = front->data;
        front = front->next;
        delete temp;
        size--;
        if (front == nullptr)
        {
            rear = nullptr; 
        }
        return value;
    }
    int myQueue::frontQueue() const {
        if (isEmpty()) {return -1;}
        return front->data;        
    }
    int myQueue::rearQueue() const {
        if (isEmpty()) {return -1;}
        return rear->data;
    }
    void myQueue::queueDisplay() const {
        std::cout << "Size: " << std::endl;
        NodeSC* current = front;
        int i = 0;

        while (current != nullptr) {
            std::cout << "Element: " << current->data << " at position " << i << std::endl;
            current = current->next;
            i++;
        }
        std::cout << std::endl;
    }