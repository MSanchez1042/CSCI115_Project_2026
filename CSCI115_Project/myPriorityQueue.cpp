#include"myPriorityQueue.h"
#include<iostream>

myPriorityQueue::myPriorityQueue() {
    capacity = 0;
    nElements = 0;
    queue = nullptr;
    table = nullptr;
}
myPriorityQueue::myPriorityQueue(int c) {
    capacity = c;
    nElements = 0;
    queue = new myData[capacity];
    table = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = -1;
        queue[i].index = -1;
        queue[i].value = __DBL_MAX__;
    }
}
myPriorityQueue::~myPriorityQueue() {
    delete[] queue;
    delete[] table;
}
bool myPriorityQueue::isEmpty() {
    return nElements == 0;
}
bool myPriorityQueue::isFull() {
    return nElements == capacity;
}
int myPriorityQueue::getParent(int child) {
    if (child % 2 == 0) {   
        return (child / 2) - 1;
    } else {
        return child / 2;
    }
}
int myPriorityQueue::getLeftChild(int parent) {
    return (2 * parent) + 1;
}
int myPriorityQueue::getRightChild(int parent) {
    return (2 * parent) + 2;
}
void myPriorityQueue::minHeapify(int i, int size) {
    int left, right, smallest;
    left = 2 * i + 1;
    right = 2 * i + 2;
    smallest = i;
    if ((left < size) && queue[left].value < queue[smallest].value) {
        smallest = left;
    }     
    if ((right < size) && queue[right].value < queue[smallest].value) {
        smallest = right;
    }
    if (smallest != i) {
        myData tmp = queue[i];
        queue[i] = queue[smallest];
        table[queue[i].index] = i;
        queue[smallest] = tmp;
        table[queue[smallest].index] = smallest;
        minHeapify(smallest, size);        
    }
}
void myPriorityQueue::push(int index, double value) {
    if (nElements < capacity) {
        myData x;
        x.index = index;
        x.value = value;
        
        int i = nElements;
        bool movingUp = (i > 0);
        while (movingUp) {
            int parent = getParent(i);
            
            if (x.value < queue[parent].value) {
                queue[i] = queue[parent];
                table[queue[i].index] = i;
                i = parent;
                movingUp = (i > 0);        
            } else {
                movingUp = false;
            }
        }
        queue[i] = x;
        table[queue[i].index] = i;
        nElements++;
    } else {
        std::cout << "out of capacity" << std::endl;
    }
}
myData myPriorityQueue::pop() {
    if (nElements > 0) {
        myData tmp = queue[0];
        table[tmp.index] = -1;
        
        queue[0] = queue[nElements - 1]; 
        nElements--;
        
        if (nElements > 0) {
            table[queue[0].index] = 0;
            minHeapify(0, nElements);
        }
        
        return tmp;
    } else {
        myData tmp;
        tmp.index = -1;
        tmp.value = -1;
        return tmp;
    }
}
void myPriorityQueue::decreaseKey(int index, double value) {
    if (index < 0 || index >= capacity) {
        throw std::out_of_range("decreaseKey: bad vertex index");
    } 
    
    int child = table[index];
    
    if (child < 0 || child >= nElements) {
        throw std::out_of_range("decreaseKey: bad heap position");
    }

    if (value >= queue[child].value) {
        return;
    }
    
    queue[child].value = value;
    
    bool movingUp = (child > 0);
    
    while (movingUp) {
        int parent = getParent(child);
        
        if((queue[child].value < queue[parent].value)) {
            myData tmp = queue[child];
            queue[child] = queue[parent];
            queue[parent] = tmp;
            
            table[queue[child].index] = child;
            table[queue[parent].index] = parent;

            child = parent;
            movingUp = (child > 0);
        } else {
            movingUp = false;
        }
    }
}
void myPriorityQueue::buildMinHeap() {
    for (int i = nElements / 2 - 1; i >= 0; i++) {
        minHeapify(i, nElements);
    }
}
void myPriorityQueue::display() {
    std::cout << "priority queue: " << std::endl;
    std::cout << "\t capacity: " << capacity << std::endl;
    std::cout << "\t number of elements" << nElements << std::endl;
    for (int i = 0; i < nElements; i++) {
        std::cout << i << " : (" << queue[i].index << "," << queue[i].value << ")";
    }
    std::cout << std::endl; 
}
void myPriorityQueue::enqueue(const myData& item) {
    // if the queue is full exit
    if (isFull()){return;}
    //if the queue is empty just append the value
    int i = nElements - 1;
    //shift all elements untile the correct position of the value is found
    while (i >= 0 && queue[i].value > item.value) {
        queue[i + 1] = queue[i];
        i--;
    }
    //insert queue at correct position
    queue[i + 1] = item;
    nElements++;
}
myData myPriorityQueue::dequeue() {
    if (isEmpty()){throw std::out_of_range("priority queue is empty");}
    
    myData removed = queue[0];
    for (int i = 1; i < nElements; i++) {
        queue[i - 1] = queue[i];
    }
    nElements--;
    return removed; 
}
