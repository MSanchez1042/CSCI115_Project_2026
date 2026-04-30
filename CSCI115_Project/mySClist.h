#ifndef MYSCLIST_H
#define MYSCLIST_H

class NodeSC
{
    public:
        int data;
        NodeSC* next;
        NodeSC() {
            data = 0;
            next = nullptr;
        }
        NodeSC(int d) {
            data = d;
            next = nullptr;
        }
        NodeSC(int d, NodeSC* nxt){
            next = nxt;
            data = d;
        }
        ~NodeSC() {}
};


class mySCList {
    public:
        //constructors
        mySCList();
        ~mySCList();
        mySCList(const mySCList& other);
        mySCList& operator=(const mySCList& other);
        mySCList(mySCList&& other) noexcept;
        mySCList& operator=(mySCList&& other) noexcept;
        //helpers
        int getSize()const {return size;};
        void display();
        void createNode(int value);
        NodeSC* getHead() const {return head;}
        NodeSC* getTail() const {return tail;}
        //search functions
        bool searchITE(int value);
        bool searchREC(int value);
        //insert functions
        void insert(int value);
        void insertMiddle(int value);
        void insertFirst(int value);
        void insertLast(int value);
        void insertPosition(int position, int value);
        //delete functions
        void deleteFirst();
        void deleteLast();
        void deletePos(int value);
        void deleteMiddle(int value);
    private:
        int size;
        NodeSC* head;
        NodeSC* tail;
        bool searchRECHelper(NodeSC* current, int value);
};
#endif