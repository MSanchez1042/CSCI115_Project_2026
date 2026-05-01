#ifndef MYPRIORITYQUEUE_H
#define MYPRIORITYQUEUE_H

struct myData {
    int index;
    double value;
    myData() {
        index = -1; 
        value = 0;
    }
    myData(int i, double v) {
        index = i;
        value = v;
    }
    myData& operator=(const myData& other) {
        if (&other != this) {
            index = other.index;
            value = other.value;       
        }
        return *this;
    }
    myData(const myData& other) {
        index = other.index;
        value = other.value;
    }   
};

class myPriorityQueue {
public:
    myPriorityQueue();
    myPriorityQueue(int c);
    ~myPriorityQueue();
    int getNElements() {return nElements;}
    bool isEmpty();
    bool isFull();
    int getParent(int child);
    int getLeftChild(int parent);
    int getRightChild(int parent);
    void push(int index, double value);
    myData pop();
    void decreaseKey(int index, double value);
    void buildMinHeap();
    void display();
    void enqueue(const myData& item);
    myData dequeue();
private:
    void minHeapify(int i, int size);
    int capacity;
    int nElements;
    myData* queue;
    int* table;
};

#endif
