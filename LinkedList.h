//
// Created by huang on 6/5/2024.
//

#pragma once
#include <iostream>
#include <vector>
using namespace std;
template<typename T>


class LinkedList {
public:
    // NODE CLASS
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node(T dataPram) {
            data = dataPram;

            next = nullptr;
            prev = nullptr;
        }
    };


    // CONTRUCTORS AND DESTRUCTORS
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    LinkedList(const LinkedList &nodes) {
        head = nullptr;
        tail = nullptr;
        count = 0;
        const Node *newHead = nodes.Head();

        while(newHead != nullptr) {
            AddTail(newHead -> data);
            newHead = newHead -> next;
        }
    }

    ~LinkedList() {
        // Delete all the nodes created by the list
        Node *newHead = head;

        for(int i = 0; i < count; i++) {
            Node *newNewHead = newHead -> next;
            delete newHead;
            newHead = newNewHead;

        }
    }


    // BEHAVIORS
    void PrintForward() {
        Node *newHead = head;

        for(int i = 0; i < count; i++) {
            cout << newHead -> data << endl;
            newHead = newHead -> next;

        }
    }

    void PrintReverse() {
        Node *newTail = tail;

        for(int i = 0; i < count; i++) {
            cout << newTail -> data << endl;
            newTail = newTail -> prev;

        }
    }

    void PrintForwardRecursive(const Node* node) const {
        const Node *newHead = node;

        while (newHead != nullptr) {
            cout << newHead -> data << endl;
            newHead = newHead -> next;
            PrintForwardRecursive(newHead);
        }
    }

    void PrintReverseRecursive(const Node* node) const {
        const Node *newHead = node;

        while (newHead != nullptr) {
            cout << newHead -> data << endl;
            newHead = newHead -> prev;
            PrintForwardRecursive(newHead);
        }
    }


    // ACCESSORS
    Node *Head() {
        return head;
    }

    Node *Tail() {
        return tail;
    }

    const Node *Head() const {
        return head;
    }

    const Node *Tail() const {
        return tail;
    }

    Node *GetNode(int index) {
        if(0 < index && index < count) {
            Node *newHead = head;

            for(int i = 0; i < index; i++) {
                newHead = newHead -> next;
            }
            return newHead;
        }

        throw out_of_range("Node is out of range.");
    }

    const Node *GetNode(int index) const {
        if(0 < index && index < count) {
            Node *newHead = head;

            for(int i = 0; i < index; i++) {
                newHead = newHead -> next;
            }
            return newHead;
        }

        throw out_of_range("Node is out of range.");
    }

    int NodeCount() {
        return count;
    }

    const int NodeCount() const {
        return count;
    }

    Node *Find(T d) {
        Node *newHead = head;

        for(int i = 0; i < count; i++) {
            if (newHead -> data == d) {
                return newHead;
            }
            newHead = newHead -> next;
        }
        return nullptr;
    }

    const Node *Find(T d) const {
        Node *newHead = head;

        for(int i = 0; i < count; i++) {
            if (newHead -> data == d) {
                return newHead;
            }
            newHead = newHead -> next;
        }
        return nullptr;

    }

    void FindAll(vector<Node*> &vect, T d) {
        Node *newHead = head;

        for(int i = 0; i < count; i++) {
            if (newHead -> data == d) {
                vect.push_back(newHead);
            }
            newHead = newHead -> next;
        }
    }


    // INSERTIONS
    void AddHead(T nodeData) {
        // Create a node at the front to store the parameter
        auto *fronode = new Node(nodeData);

        if(head == nullptr) {
            head = fronode;
            tail = fronode;
            count += 1;
        } else {
            fronode -> next = head;
            head -> prev = fronode;
            head = fronode;
            count += 1;

        }
    }

    void AddTail(T nodeData) {
        // Create a node at the end to store the parameter
        auto *enode = new Node(nodeData);

        if(tail == nullptr) {
            head = enode;
            tail = enode;
            count += 1;
        } else {
            enode -> prev = tail;
            tail -> next = enode;
            tail = enode;
            count += 1;
        }
    }

    void AddNodesHead(T array[], int arraySize) {
        //Given an array of values, insert a node for each at the beginning list, keeping the order
        for(int i = arraySize-1; i >= 0; i--) {
            AddHead(array[i]);
        }
    }

    void AddNodesTail(T array[], int arraySize) {
        // Given an array of values, insert a node for each at the end list, keeping the order
        for(int i = 0; i < arraySize; i++) {
            AddTail(array[i]);
        }
    }

    void InsertAfter(Node *node, const T& d) {
        auto *newNode = new Node(d);
        if(node == tail) {
            AddTail(d);
        } else {
            newNode -> prev = node;
            newNode -> next = node -> next;
            node -> next -> prev = newNode;
            node -> next = newNode;
            count++;

        }
    }

    void InsertBefore(Node *node, const T& d) {
        auto *newNode = new Node(d);

        if(node == head) {
            AddHead(d);
        } else {
            newNode -> next = node;
            newNode -> prev = node -> prev;
            node -> prev -> next = newNode;
            node -> prev = newNode;
            count++;
        }
    }

    void InsertAt(const T& d, unsigned int index) {
        if(0 <= index && index <= count) {
            if(index == 0) {
                AddHead(d);

            } else if (index == count) {
                AddTail(d);

            } else {
                InsertBefore(GetNode(index), d);
            }
        }
    }


    //REMOVALS
    bool RemoveHead() {
        if(count == 0) {
            return false;
        }
        if(head == tail) {
            head == nullptr;
            tail == nullptr;
            count = 0;
        } else {
            Node *newHead = head;
            head = head -> next;
            delete newHead;
            count--;
            return true;
        }
    }

    bool RemoveTail() {
        if(count == 0) {
            return false;
        }
        if(head == tail) {
            head == nullptr;
            tail == nullptr;
            count = 0;
        } else {
            Node *newTail = tail;
            tail = tail -> prev;
            delete newTail;
            count--;
            return true;
        }
    }

    unsigned int Remove(const T&d) {
        Node *newHead = head;
        int counter = 0;

        for(int i = 0; i < count; i++) {
            Node *newNewHead = newHead -> next;
            if(newHead -> data == d) {
                newHead -> prev -> next = newHead -> next;
                newHead -> next -> prev = newHead -> prev;
                delete newHead;
                counter ++;
            }
            newHead = newNewHead;
        }
        count = count - counter;
        return counter;
    }

    bool RemoveAt(unsigned int index) {
        if(0 <= index && index <= count) {
            if(index == 0) {
              RemoveHead();
            } else if(index == count) {
              RemoveTail();
            } else {
                Node *newHead = head;
                for(int i = 0; i < index; i++) {
                    newHead = newHead -> next;
                }
                newHead -> prev -> next = newHead -> next;
                newHead -> next -> prev = newHead -> prev;
                delete newHead;
                count--;
                return true;
            }
        }
        return false;

    }

    void Clear() {
        Node *newHead = head;

        for(int i = 0; i < count; i++) {
            Node *newNewHead = newHead -> next;
            delete newHead;
            newHead = newNewHead;
        }
        head = nullptr;
        tail = nullptr;

        count = 0;
    }


    // OPERATORS
    T &operator[](int index) {
        if(0 <= index && index < count) {
            Node *newHead = head;

            for(int i = 0; i < index; i++) {
                newHead = newHead -> next;
            }

            return newHead -> data;
        }

        throw out_of_range("Node is out of range.");
    }

    const T &operator[](int index) const {
        if(0 <= index && index < count) {
            Node *newHead = head;

            for(int i = 0; i < index; i++) {
                newHead = newHead -> next;
            }
            return newHead -> data;
        }

        throw out_of_range("Node is out of range.");
    }

    LinkedList &operator=(const LinkedList &nodes) {
        Node *newDesHead = head;

        for(int i = 0; i < count; i++) {
            Node *newNewHead = newDesHead -> next;
            delete newDesHead;
            newDesHead = newNewHead;
        }

        if(this != &nodes) {
            head = nullptr;
            tail = nullptr;
            count = 0;
            const Node *newHead = nodes.Head();

            while(newHead != nullptr) {
                AddTail(newHead -> data);
                newHead = newHead -> next;
            }

            return *this;
        }
    }

    bool operator==(const LinkedList<T>&rhs) const {
        Node *newNode = head;
        const Node *newRHS = rhs.Head();

        if(count == rhs.NodeCount()) {
            for(int i = 0; i < count; i++) {
                if(newNode -> data != newRHS -> data) {
                    return false;
                }
                newNode = newNode -> next;
                newRHS =  newRHS -> next;
            }
        } else {
            return false;
        }
        return true;
    }

private:
    Node *head;
    Node *tail;
    int count;
};

