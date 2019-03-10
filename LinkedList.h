//
// Created by Jessica O'Dell on 2019-02-18.
//
#pragma once
#include <vector>
#include <iostream>

template <class T>

 class LinkedList {
public:
    //operators and constructors
    LinkedList(){
        nodeCount = 0;
        head = nullptr;
        tail = nullptr;
    }

    LinkedList(const T &list) {// copy constructor
       head = nullptr;
       tail = nullptr;
       this->nodeCount = list.nodeCount;
       this->head = head;
       this->tail = tail;
    };
    T &operator[](unsigned index) {
        Node *temp = head;
        unsigned int count = 0;
        while (temp->next != nullptr && count < index) {
            temp = temp->next;
            count++;
        }
        return temp->data;
    }
    const T &operator[](unsigned index) const {
        Node *temp = head;
        unsigned int count = 0;
        while (temp->next != nullptr && count < index) {
            temp = temp->next;
            count++;
        }
        return temp->data;
    }
    bool operator==(const LinkedList<T> &rhs) { //equality operator
        if (head == nullptr && rhs.head == nullptr) {
            return true;
        }
        Node *temp = head;
        Node *temp2 = rhs.head;
        while (temp != nullptr) {
            if (temp->data != temp2->data || nodeCount != rhs.nodeCount){
                return false;
            }
            else {
                temp = temp->next;
                temp2 = temp2->next;
            }
        }
        return true;
    }
    LinkedList<T> &operator=(const LinkedList<T> &rhs) {// assignment operator
        Clear();
        head = nullptr;
        tail = nullptr;
        this->nodeCount = rhs.nodeCount;
        this->head = rhs.head;
        this->tail = rhs.tail;
        return *this;
     }

     ~LinkedList() { // destructor
         Clear();

        /*Node *temp = head;

         while(temp != nullptr) {
             Node *temp2 = temp->next;
             delete temp;
             temp = temp2;
         }
         head = nullptr;
         tail = nullptr; */
    }
    // all the other functions
    struct Node {
        Node(const T&data, Node* next) {
            this->data = data;
            this->next = next;
        }
        T data;
        Node *next = nullptr;
        Node *prev = nullptr;

    };
    void AddTail(const T& data) {
        //if list is empty vs. list is full
        //add a singular node for first, that is head and tail
        //if head == nullptr, create new node for head. head = tail;
        if (head == nullptr) {
            Node *temp = new Node(data, head);
            head = temp;
            head->data = data;
            head->prev = nullptr;
            tail = head;
            tail->next = nullptr;
        }
        else {
            Node *temp = new Node(data, tail);
            tail = temp;
            tail->data = data;
            tail->next = nullptr;
            Node *temp2 = head;
            while (temp2->next != nullptr) {
                temp2 = temp2->next;
            }
            temp2->next = tail;
            tail->prev = temp2;
        }

    }
    void AddHead(const T& data) {
        Node *temp = new Node(data, head);
        head = temp;
        head->data = data;
        head->prev = nullptr;
        if (head->next != nullptr) {
            head->next->prev = head;
        }
    }
    void AddNodesHead(const T *data, unsigned count) {
        for (unsigned i = count-1; i > 0; i--) {
            AddHead(data[i]);
        }
        AddHead(data[0]);
        //for loop for array data, iterate through each i of the array and do AddHead function
    }
    void AddNodesTail(const T *data, unsigned count) {
        for (unsigned i = 0; i < count-1; i++) {
            AddTail(data[i]);
        }
        AddTail(data[count-1]);
    }
    Node FindAll(std::vector<Node * > &outData, const T&value) const {
        Node *found = nullptr;
        for (Node *temp = head; temp != nullptr; temp = temp->next) {
            if (temp->data == value) {
                outData.push_back(temp);
            }
        }
    }
    Node *Find(const T& d) {
        Node *found = nullptr;
        for (Node *temp = head; temp != nullptr; temp = temp->next) {
            if (temp->data == d) {
                found = temp;
            }
        }
        return found;
    }
    const Node *Find(const T& d) const {
        Node *found = nullptr;
        for (Node *temp = head; head != nullptr; temp = temp->next) {
            if (temp->data == d) {
                found = temp;
            }
        }
        return found;
    }
    Node *GetNode(unsigned index) {
        Node *temp = head;
        int count = 0;
        while (temp->next != nullptr && count < index) {
            temp = temp->next;
            count++;
        }
        if (temp != nullptr) {
        return temp;
        }
        else throw std::runtime_error("Error! Returned node was a nullptr.");
    }

    Node *GetNode(unsigned index) const {
        Node *temp = head;
        int count = 0;
        while (temp->next != nullptr && count < index) {
            temp = temp->next;
            count++;
        }
        return temp;
    }
    Node *Head() {
        return head;
    }
    const Node *Head() const {
        return head;
    }
    void InsertAt(const T&data, unsigned index) { // head is at [0]
        Node *temp = head;
        unsigned int count = 0;
        if (index < 0) {
            throw std::runtime_error("Error! Invalid index");
        }
        if (index == 0) {
            temp = new Node(data, head);
            temp->next = head;
            head = temp;
        } else {
            while (temp->next != nullptr && count < index - 1) {
                temp = temp->next;
                count++;
            }
            Node *temp2 = temp->next;
            temp->next = new Node(data, temp2);
        }
    }

    void InsertAfter(Node *node, const T& data) {
        Node *temp = head;
        while (temp != node) {
            temp = temp->next;
        }
        Node *temp2 = temp->next; // save spot directly after node
        Node *newNode = new Node(data, temp2);
        node->next = newNode;
        newNode->next = temp2;
        newNode->prev = node;

    }

    void InsertBefore(Node *node, const T& data) {
        Node *temp = head;
        int count = 0, i = 0;
        while (temp != node) {
            temp = temp->next;
            count++;
        }
        Node *temp2 = head;
        for (i = 0; i < count-1; i++) {
            temp2 = temp2->next;
        }
        Node *temp3 = temp2->next;
        temp2->next = new Node(data, temp3);
        temp2->next->prev = temp2;

    }
    unsigned int NodeCount() {
        nodeCount = 0;
        for (Node *temp = head; temp != nullptr; temp = temp->next) {
            nodeCount++;
        }
        return nodeCount;
    }
     void PrintForward() const {
         for(Node *temp = head; temp != nullptr; temp = temp->next) {
             std::cout << temp->data << std::endl;
         }
     }
     void PrintReverse() const {
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        while (temp != nullptr) {
            std::cout << temp->data << std::endl;
            temp = temp->prev;
        }
    }

     void PrintForwardRecursive(const Node* start) {
        const Node *temp = start;
        if (temp != nullptr) {
            std::cout << temp->data << std::endl;
            temp = temp->next;
            PrintForwardRecursive(temp);
        }
    }

    void PrintReverseRecursive(const Node* start) {
        const Node *temp = start;

        if (temp != nullptr) {
            std::cout << temp->data << std::endl;
            temp = temp->prev;
            PrintReverseRecursive(temp);
        }
    }
    /*void RecoverNode(int index){
        if (index == 0) {
            Node *temp = head->next;
            delete head;
            head = temp;
            return;
        }
        Node *temp = head;
        for (int count = 0;temp->next != nullptr && count < index-1; count++, temp = temp->next) {
            //want to stop at the one before index
        }
        Node *temp2 = temp->next->next; // skips over one you want to delete
        delete temp->next; // deletes the one at index
        temp->next = temp2; // sets the index-1's next to the one after the deleted item
    }*/

    bool RemoveHead() {
        Node *temp = head;
        if (temp != nullptr) {
            if (head == tail) {
                head->next = nullptr;
                head->prev = nullptr;
                head = head->next;
                delete temp;
            }
            else {
                head->prev = nullptr;
                head = head->next;
                delete temp;
                return true;
            }
        }
        else return false;

    }
    bool RemoveTail() {
        Node *temp = tail;
        if (temp == head) {
            head->next = nullptr;
            head->prev = nullptr;
            head = head->next;
            delete temp;
            return true;
        }
        if (temp->prev != nullptr) {
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            return true;
        }
        else return false;

    }
    unsigned Remove(const T& data) { // double check
        Node *temp = head;
        unsigned removeCount = 0;
        while (temp != nullptr) {
            if (temp->data == data) {
                Node *temp2 = temp;
                temp->prev->next = temp->next;
                temp = temp->next;
                delete temp2;
                removeCount++;

            }
            else temp = temp->next;
            return removeCount;
        }
    }

    bool RemoveAt(int index) {
        if (index == 0) {
            Node *temp = head->next;
            delete head;
            head = temp;
            return true;
        }
        Node *temp = head;
        int count = 0;
        for (count = 0;temp->next != nullptr && count < index-1; count++, temp = temp->next) {
            //want to stop at the one before index
        }
        if (count == index-1) {
        Node *temp2 = temp->next->next; // skips over one you want to delete
        delete temp->next; // deletes the one at index
        temp->next = temp2; // sets the index-1's next to the one after the deleted item
        return true;
        }
        else return false;
    }
    void Clear() {
        Node *temp = head;
        while (temp != nullptr) {
            Node *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
        head = nullptr;
        tail = nullptr;
        nodeCount = 0;

    }
    const Node *Tail() {
        return tail;
    }
    const Node *Tail() const {
        return tail;
    }

private:
    Node *head = nullptr;
    Node *tail = nullptr;
    unsigned nodeCount = 0;
};