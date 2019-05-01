#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "LinkedListInterface.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
using std::endl;


template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) {
            data = d;
            next = nullptr;
        }
        Node(const T& d, Node* n) {
            data = d;
            next = n;
        }
    };
    Node* head;
    
public:
    LinkedList() {
        head = nullptr;
    }
    
    virtual ~LinkedList() {
        clear();
    }
    
   
    virtual bool insertHead(T value) {
        Node* searchNode = head;
        while (searchNode != nullptr) {
            if (searchNode->data == value) {
                return false;
            }
            searchNode = searchNode->next;
        }
        
        if (head == nullptr) {  
            head = new Node(value);
        }
        else {
             head = new Node(value, head);
        }
        return true;
    }
    
    virtual bool insertTail(T value) {
        Node* searchNode = head;
        while (searchNode != nullptr) {
            if (searchNode->data == value) {
                return false;
            }
            searchNode = searchNode->next;
        }
        
        if (head == nullptr) { 
            return insertHead(value);
        }
        
        Node* nodePtr = head;
        while (nodePtr->next != nullptr) {
            nodePtr = nodePtr->next;
        }
        
        nodePtr->next = new Node(value);
        return true;
    }
    
    virtual bool insertAfter(T matchNode, T node) {
        if (matchNode == node) {
            return false;
        }
        Node* searchNode = head;
        while (searchNode != nullptr) {
            if (searchNode->data == node) {
                return false;
            }
            searchNode = searchNode->next;
        }
        
        searchNode = head;
        if (searchNode == nullptr) {
            insertHead(node);
            return true;
        }
        while (searchNode != nullptr) {         
            if (searchNode->data != matchNode) {
                searchNode = searchNode->next;
            }
            else {
                break;
            }
        }
        Node* newNode = new Node(node, searchNode->next);   
        searchNode->next = newNode;
        return true;
        return false;
    }
    
    virtual bool remove(T value) {
        Node* temp = head;
        bool isFound = false;
        while (temp != nullptr) {       
            if (temp-> data == value) {
                isFound = true;
                break;
            }
            temp = temp->next;
        }
        if (!isFound) {        
            return false;
        }
        temp = head;
        if (head->next == nullptr) {    
            delete head;
            head = nullptr;
            return true;
        }
        if (head->data == value) {  
            Node* temp2 = head;
            head = head->next;
            delete temp2;
            temp2 = nullptr;
            return true;
        }
        
        while (temp->next->data != value) {  
            temp = temp->next;
        }
        Node* nodeToRemove = temp->next;           
        temp->next = nodeToRemove->next;           
        delete nodeToRemove;
        
        return true;
    }
    
    virtual bool clear() {
        while (head != nullptr) {
            remove(head->data);     
        }
        return true;
    }
    
    virtual T at(size_t index) {
        Node* searchNode = head;
        if (index >= size() || index < 0) { 
            throw 1;
        }
        
        while (index > 0) { 
            index--;
            searchNode = searchNode->next;  
        }
        return searchNode->data;   
    }
    
    virtual size_t size() const {
        Node* searchNode = head;
        size_t counter = 0;
        while(searchNode != nullptr) {  
            searchNode = searchNode->next;
            counter += 1;
        }
        return counter;
    }
    
    virtual string toString() const {
        stringstream ss;
        if (size() != 0) {  
            Node* searchNode = head;
            while (searchNode != nullptr) {
                ss << searchNode->data << " ";
                searchNode = searchNode->next;
            }
        }
        else {  
            return "Empty";
        }
        
        return ss.str();   
    }
    
    friend std::ostream& operator<< (std::ostream& os, const LinkedList<T>& myLinkedList) {
        os << myLinkedList.toString();
        return os;
    }
};

#endif //LINKEDLIST_H
