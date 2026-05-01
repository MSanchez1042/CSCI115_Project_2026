    #include"mySClist.h"
    #include<iostream>    
    mySCList::mySCList() {
        head = nullptr;
        size = 0;
        tail = nullptr;
    }
    mySCList::~mySCList() {
        NodeSC *currentNode = head;
        while (currentNode)
        {
            NodeSC *next = currentNode -> next;
            delete currentNode;
            currentNode = next;
        }
    } 
    mySCList::mySCList(const mySCList& other): size(0), head(nullptr), tail(nullptr) {
        NodeSC* current = other.head;
        while (current)
        {
            createNode(current->data);
            current = current->next;
        }
    }
    mySCList& mySCList::operator=(const mySCList& other) {
        if (this == &other)
        {
            return *this;
        }
        NodeSC* current = head;
        while (current)
        {
            NodeSC* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
        current = other.head;
        while (current)
        {
            createNode(current->data);
            current = current->next;
        }
        return *this;
    }
    mySCList::mySCList(mySCList&& other) noexcept 
    : size(other.size), head(other.head), tail(other.tail) {
        other.size = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }
    mySCList& mySCList::operator=(mySCList&& other) noexcept {
        if (this == &other)
        {
            return *this;
        }
        NodeSC* current = head;
        while (current)
        {
            NodeSC* next = current->next;
            delete current;
            current = next;
        }
        size = other.size;
        head = other.head;
        tail = other.tail;

        other.size = 0;
        other.head = nullptr;
        other.tail = nullptr;
        return *this;
    }
    void mySCList::createNode(int value) {
        NodeSC *temp = new NodeSC(value);
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        } else {
            tail -> next = temp;
            tail = temp;
        }
        size++;
    }
    bool mySCList::searchITE(int value) {
        NodeSC *current = head;
        bool found = false;
        while (current != nullptr && !found) {
            if (current->data == value) {
                found = true;
            } else {
                current = current->next;
            }
        }
       return found; 
    }
    bool mySCList::searchRECHelper(NodeSC* current, int value) {
        if (current == nullptr) {return false;}
        if (current->data == value) {return true;}
        return searchRECHelper(current->next, value);
    }

    bool mySCList::searchREC(int value) {
       return searchRECHelper(head, value); 
    }
    
    void mySCList::insertMiddle(int value) {
       NodeSC* temp = new NodeSC(value);
        if (head == nullptr) {
            //insert at the head (empty list)
            head = temp;
            tail = temp;
        } else if (head -> data > value) {
            temp -> next = head;
            head = temp;
        } else {
            NodeSC* cursor = head->next;
            NodeSC* prev = head;
            while (cursor != nullptr && cursor->data < value) {
                prev = prev -> next;
                cursor = cursor -> next;
            }
            if (cursor == nullptr) {
                //inserting at the lest element
                prev -> next = temp;
                tail = temp;
            } else {
                //insert middle
                prev -> next = temp;
                temp -> next = cursor;
            }
        }
        size++;   
    }
    void mySCList::insert(int value) {
        insertMiddle(value);
    }
    void mySCList::insertFirst(int value) {
        NodeSC* tmp = new NodeSC(value, head);
        head = tmp;
        if (tail == nullptr)
        {
            tail = head;
        }
        size++;
    }
    void mySCList::insertLast(int value) {
        createNode(value);
    }
    void mySCList::insertPosition(int position, int value) {
        if (position < 0 || position > size) return;
    
        if (position == 0) {
            insertFirst(value);
            return;
        }
        if (position == size) {
            insertLast(value);
            return;
        }

        NodeSC* prev = head;
        NodeSC* current = head->next;

        for (int i = 1; i < position; i++) {
            prev = current;
            current = current->next;
        }

        NodeSC* temp = new NodeSC(value);
        prev->next = temp;
        temp->next = current;
        size++;
    }
    void mySCList::deleteFirst() {
        NodeSC *temp;
        temp = head;
        head = head->next;
        delete temp;
         if (head == nullptr)
        {
            tail = nullptr;
        }       
        size--;
    }
    void mySCList::deleteLast() {
        if (head == nullptr)
        {
            return;
        }
        
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            size = 0;
            tail = nullptr;
            return;
        }
        
        NodeSC *current = head->next;
        NodeSC *prev = head;
        while (current->next != nullptr)
        {
           prev = current;
           current = current->next; 
        }
       prev->next = nullptr;
       delete current;
       tail = prev;
       size--;
    }
    void mySCList::deletePos(int position) {
        if (position < 0 || position >= size || head == nullptr) {return;}
        if (position == 0) {
            deleteFirst();
            return;
        }
       
        NodeSC *current = head->next;
        NodeSC *prev = head;
        for (size_t i = 1; i < position; i++) {
           prev = current;
           current = current->next; 
        }
        prev->next = current->next;
        if (current == tail)
        {
            tail = prev;
        }
        delete current;
        size--;
    }

    void mySCList::display() {
        NodeSC *temp;
        temp = head;
        std::cout << "List Size: " << size << std::endl;
        std::cout << "Head: ";
        if (head != nullptr)
        {
            std::cout << head->data << std::endl;
        } else {
            std::cout << "NULL" << std::endl;
        }
        
        std::cout << "Last: ";
        if (tail != nullptr)
        {
            std::cout << tail->data << std::endl;
        } else {
            std::cout << "NULL" << std::endl;
        }
        
        int i = 0;
        while (temp) {
           std::cout << "(" << i << ")";
           if (temp->next != nullptr) {
                std::cout << temp->data << "->" << temp->next->data << std::endl;
           } else {
                std::cout << temp->data << "->"  << "NULL" << std::endl;
           }
           temp = temp->next;
           i++; 
        }
    }