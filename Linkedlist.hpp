#ifndef LINKEDLIST_QU_HPP
#define LINKEDLIST_QU_HPP

#include <iostream>
#include <stdexcept>

// Node class
template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* previous;
    
    Node(T d, Node* n = nullptr, Node* p = nullptr);
    Node* getPrevious() const;
    Node* getNext() const;
    T getData() const;
};

// LinkedList class
template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int length;
public:
    LinkedList();
    ~LinkedList();
    void AddToFront(T data);
    void AddToEnd(T data);
    void AddAtIndex(T data, int index);
    void AddBefore(Node<T>* node, T data);
    void AddAfter(Node<T>* node, T data);
    T RemoveFromFront();
    T RemoveFromEnd();
    T RemoveTheFirst(T data);
    void RemoveAllOf(T data);
    T RemoveBefore(Node<T>* node);
    T RemoveAfter(Node<T>* node);
    bool ElementExists(T data) const;
    Node<T>* Find(T data) const;
    int IndexOf(T data) const;
    T RetrieveFront() const;
    T RetrieveEnd() const;
    T Retrieve(int index) const;
    void PrintList() const;
    int Length() const;
    void Empty();
    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }
};

// Node class method implementations
template<typename T>
Node<T>::Node(T d, Node* n, Node* p) : data(d), next(n), previous(p) {}

template<typename T>
Node<T>* Node<T>::getPrevious() const {
    return previous;
}

template<typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template<typename T>
T Node<T>::getData() const {
    return data;
}

// LinkedList class method implementations
template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template<typename T>
LinkedList<T>::~LinkedList() {
    Empty();
}

template<typename T>
void LinkedList<T>::AddToFront(T data) {
    Node<T>* newNode = new Node<T>(data, head);
    if (head) head->previous = newNode;
    head = newNode;
    if (!tail) tail = head;
    length++;
}

template<typename T>
void LinkedList<T>::AddToEnd(T data) {
    Node<T>* newNode = new Node<T>(data, nullptr, tail);
    if (tail) tail->next = newNode;
    tail = newNode;
    if (!head) head = tail;
    length++;
}

template<typename T>
void LinkedList<T>::AddAtIndex(T data, int index) {
    if (index < 0 || index > length) throw std::out_of_range("Index out of range");
    if (index == 0) AddToFront(data);
    else if (index == length) AddToEnd(data);
    else {
        Node<T>* current = head;
        for (int i = 0; i < index - 1; i++) current = current->next;
        Node<T>* newNode = new Node<T>(data, current->next, current);
        current->next->previous = newNode;
        current->next = newNode;
        length++;
    }
}

template<typename T>
void LinkedList<T>::AddBefore(Node<T>* node, T data) {
    if (node == head) AddToFront(data);
    else {
        Node<T>* newNode = new Node<T>(data, node, node->previous);
        node->previous->next = newNode;
        node->previous = newNode;
        length++;
    }
}

template<typename T>
void LinkedList<T>::AddAfter(Node<T>* node, T data) {
    if (node == tail) AddToEnd(data);
    else {
        Node<T>* newNode = new Node<T>(data, node->next, node);
        node->next->previous = newNode;
        node->next = newNode;
        length++;
    }
}

template<typename T>
T LinkedList<T>::RemoveFromFront() {
    if (!head) throw std::out_of_range("List is empty");
    Node<T>* oldHead = head;
    T data = oldHead->data;
    head = head->next;
    if (head) head->previous = nullptr;
    else tail = nullptr;
    delete oldHead;
    length--;
    return data;
}

template<typename T>
T LinkedList<T>::RemoveFromEnd() {
    if (!tail) throw std::out_of_range("List is empty");
    Node<T>* oldTail = tail;
    T data = oldTail->data;
    tail = tail->previous;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete oldTail;
    length--;
    return data;
}

template<typename T>
T LinkedList<T>::RemoveTheFirst(T data) {
    Node<T>* current = head;
    while (current && !(current->data == data)) current = current->next;
    if (!current) throw std::out_of_range("Element not found");
    T removedData = current->data;
    if (current == head) RemoveFromFront();
    else if (current == tail) RemoveFromEnd();
    else {
        current->previous->next = current->next;
        current->next->previous = current->previous;
        delete current;
        length--;
    }
    return removedData;
}

template<typename T>
void LinkedList<T>::RemoveAllOf(T data) {
    Node<T>* current = head;
    while (current) {
        Node<T>* nextNode = current->next;
        if (current->data == data) {
            if (current == head) RemoveFromFront();
            else if (current == tail) RemoveFromEnd();
            else {
                current->previous->next = current->next;
                current->next->previous = current->previous;
                delete current;
                length--;
            }
        }
        current = nextNode;
    }
}

template<typename T>
T LinkedList<T>::RemoveBefore(Node<T>* node) {
    if (node == head) throw std::out_of_range("No element before head");
    return RemoveTheFirst(node->previous->data);
}

template<typename T>
T LinkedList<T>::RemoveAfter(Node<T>* node) {
    if (node == tail) throw std::out_of_range("No element after tail");
    return RemoveTheFirst(node->next->data);
}

template<typename T>
bool LinkedList<T>::ElementExists(T data) const {
    Node<T>* current = head;
    while (current) {
        if (current->data == data) return true;
        current = current->next;
    }
    return false;
}

template<typename T>
Node<T>* LinkedList<T>::Find(T data) const {
    Node<T>* current = head;
    while (current) {
        if (current->data == data) return current;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
int LinkedList<T>::IndexOf(T data) const {
    Node<T>* current = head;
    int index = 0;
    while (current) {
        if (current->data == data) return index;
        current = current->next;
        index++;
    }
    return -1;
}

template<typename T>
T LinkedList<T>::RetrieveFront() const {
    if (!head) throw std::out_of_range("List is empty");
    return head->data;
}

template<typename T>
T LinkedList<T>::RetrieveEnd() const {
    if (!tail) throw std::out_of_range("List is empty");
    return tail->data;
}

template<typename T>
T LinkedList<T>::Retrieve(int index) const {
    if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
    Node<T>* current = head;
    for (int i = 0; i < index; i++) current = current->next;
    return current->data;
}

template<typename T>
void LinkedList<T>::PrintList() const {
    std::cout << "Size: " << Length() << "::";
    Node<T>* current = head;
    while (current) {
        std::cout << current->data;
        if(current->next != nullptr)
        {
            std::cout << "=";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
int LinkedList<T>::Length() const {
    return length;
}

template<typename T>
void LinkedList<T>::Empty() {
    while (head) RemoveFromFront();
}

#endif