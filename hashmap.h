//
// Created by winstonthebaker on 10/27/25.
//

#ifndef INVENTORYMANAGEMENT_HASHMAP_H
#define INVENTORYMANAGEMENT_HASHMAP_H
#include <iostream>
#include <functional>
template<typename Key, typename Value>
class HashMap {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;
        explicit Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    static constexpr size_t DEFAULT_BUCKET_COUNT = 10;
    static constexpr float  DEFAULT_MAX_LOAD_FACTOR = 0.6f;

    Node** table;
    size_t bucket_count;
    size_t num_elements;
    float max_load_factor;
    size_t get_index(const Key& k) const {
        return std::hash<Key>()(k) % bucket_count;
    }

public:
    HashMap(size_t bucket_count, float max_load_factor) :
    bucket_count(bucket_count),
    max_load_factor(max_load_factor),
    num_elements(0){
        table = new Node*[bucket_count];
        for (size_t i = 0; i < bucket_count; ++i) {
            table[i] = nullptr;
        }
    }
    HashMap() : HashMap(DEFAULT_BUCKET_COUNT, DEFAULT_MAX_LOAD_FACTOR) {}
    ~HashMap() {
        clear();
        delete[] table;
    }
    void insert(const Key& k, Value&& v);
    void insert(const Key& k, const Value& v);
    Value* find(const Key& k);
    bool erase(const Key& k);
    void clear();
    void rehash();
    size_t size() const { return num_elements; }
    void printAll();
    void printBuckets();

};

template<typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key& k, Value&& v) {
    size_t index = get_index(k);
    Node* head = table[index];

    for (Node* n = head; n!= nullptr; n = n->next) {
        if (n->key == k) {
            n->value = v;
            return;
        }
    }

    Node* newNode = new Node(k, v);
    newNode->next = head;
    table[index] = newNode;

    num_elements++;

    if (static_cast<float>(num_elements) / bucket_count > max_load_factor) {
        rehash();
    }
}

template<typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key& k, const Value& v) {
    size_t index = get_index(k);
    Node* head = table[index];

    for (Node* n = head; n != nullptr; n = n->next) {
        if (n->key == k) {
            n->value = v;
            return;
        }
    }

    Node* newNode = new Node(k, v);
    newNode->next = head;
    table[index] = newNode;

    num_elements++;

    if (static_cast<float>(num_elements) / bucket_count > max_load_factor) {
        rehash();
    }
}


template<typename Key, typename Value>
Value* HashMap<Key, Value>::find(const Key& k) {
    size_t index = get_index(k);
    Node* n = table[index];
    while (n) {

        if (n->key == k) {
            return &n->value;
        }
        n = n->next;
    }
    return nullptr;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::erase(const Key& k) {
    size_t index = get_index(k);
    Node* prev = nullptr;
    Node* n = table[index];
    while (n) {
        if (n->key == k) {
            if (prev) {
                prev->next = n->next;
            } else {
                table[index] = n->next;
            }
            delete n;
            num_elements--;
            return true;
        }
        prev = n;
        n = n->next;
    }
    return false;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::clear() {
    for (size_t i = 0; i < bucket_count; ++i) {
        Node* current = table[i];
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    num_elements = 0;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::rehash() {
    size_t new_size = bucket_count * 2;
    Node** new_table = new Node*[new_size];
    for (size_t i = 0; i < new_size; ++i) {
        new_table[i] = nullptr;
    }

    for (size_t i = 0; i < bucket_count; ++i) {
        Node* n = table[i];
        while (n) {
            Node* next = n->next;

            size_t index = std::hash<Key>()(n->key) % new_size;

            n->next = new_table[index];
            new_table[index] = n;

            n = next;
        }
    }

    delete[] table;
    table = new_table;
    bucket_count = new_size;
    //check
}

template<typename Key, typename Value>
void HashMap<Key, Value>::printAll() {
    for (size_t i = 0; i < bucket_count; ++i) {
        Node* n = table[i];
        while (n) {
            std::cout << n->key << " " << n->value << std::endl;
            n = n->next;
        }
    }
}
//debugging purposes ignore this
template<typename Key, typename Value>
void HashMap<Key, Value>::printBuckets() {
    for (size_t i = 0; i < bucket_count; ++i) {
        std::cout << "table index: " << i << std::endl;
        Node* n = table[i];
        while (n) {
            std::cout << n->key << std::endl;
            n = n->next;
        }
    }
}


#endif //INVENTORYMANAGEMENT_HASHMAP_H
