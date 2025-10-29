//
// Created by winstonthebaker on 9/8/25.
//

#ifndef PA_1_LINKEDLIST_H
#define PA_1_LINKEDLIST_H
#include <iostream>
#include <string>
#include <functional>
#include <bits/locale_facets_nonio.h>

template <typename  T, typename Comparator = std::equal_to<T>>
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;
        explicit Node(const T& value) : data(value), next(nullptr){}
    };

    Node* head;
    Comparator comp;

    public:
    LinkedList() : head(nullptr), comp(Comparator()) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insert_at(const T& value, int index) {
        Node* newNode = new Node(value);

        if (index == 0) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* prev = head;
        int i = 0;

        while (prev && i < index - 1) {
            prev = prev->next;
            i++;
        }

        if (!prev) {
            delete newNode;
            throw std::out_of_range("Index out of bounds");
        }

        newNode->next = prev->next;
        prev->next = newNode;
    }


    void insert_end(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;

    }

    void delete_front() {
        if (!head) {
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void delete_at(int index) {
        if (!head) {
            throw std::out_of_range("List is empty");
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* prev = head;
        int i = 0;

        while (prev && i < index - 1) {
            prev = prev->next;
            i++;
        }

        if (!prev || !prev->next) {
            throw std::out_of_range("Index out of bounds");
        }

        Node* temp = prev->next;
        prev->next = temp->next;
        delete temp;
    }

    void delete_end() {
        if (!head) {
            return;
        }
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node* prev = head;
        Node* current = head->next;
        while (current->next) {
            prev = current;
            current = current->next;
        }
        prev->next = nullptr;
        delete current;
    }


    bool is_empty() {
        return head == nullptr;
    }

    T read_front() {
        if (head) {
            return head->data;
        }
        else {
            throw std::out_of_range("Reading an empty list is not allowed.");
        }
    }

    T read_at(int index) {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        if (index == 0) {
            return head->data;
        }
        Node* current = head;
        int i = 0;
        while (current && i < index) {
            current = current->next;
            i++;
        }
        if (!current) {
            throw std::out_of_range("invalid index");
        }
        return current->data;
    }
    T read_end() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->data;
    }

    bool contains(const T& value) {
        Node* current = head;
        while (current) {
            if (comp(current->data, value)) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int find(const T& value) {
        Node* current = head;
        int i = 0;
        while (current) {
            if (comp(current->data, value)) {
                return i;
            }
            current = current->next;
            i++;
        }
        return -1;
    }

    bool erase(const T& value) {
        if (!head) {
            return false;
        }
        Node* next = head->next;
        Node* current = head;
        while (next) {
            if (comp(next->data, value)) {
                current->next = next->next;
                delete next;
                return true;
            }
            current = next;
            next = next->next;
        }
        return false;
    }

    void write_at(const T& value, int index) {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        if (index == 0) {
            head->data = value;
            return;
        }
        Node* current = head;
        int i = 0;
        while (current && i < index - 1) {
            current = current->next;
            i++;
        }
        if (!current) {
            throw std::out_of_range("Index out of bounds");
        }
        current->data = value;
    }
    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }


    int length() {
        if (!head) {
            return 0;
        }
        Node* current = head;
        int count = 1;
        while (current->next) {
            current = current->next;
            count++;
        }
        return count;
    }
public:
    // Iterator class
    class iterator {
        Node* current;
    public:
        explicit iterator(Node* node) : current(node) {}

        // Dereference operator
        T& operator*() { return current->data; }

        // Arrow operator
        T* operator->() { return &(current->data); }

        // Pre-increment
        iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        // Post-increment
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Equality / inequality
        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
    };

    // Begin / End methods
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};

#endif //PA_1_LINKEDLIST_H
