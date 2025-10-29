//
// Created by winstonthebaker on 10/3/25.
//

#ifndef AVLMAP_H
#define AVLMAP_H
#include <iostream>
#include <utility>
#include <algorithm>

template<typename Key, typename Value>
class AVLTree {
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node* parent;
        int height;

        Node(const Key& k, const Value& v)
            : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
    };

    Node* root = nullptr;
    size_t node_count = 0;

public:
    using value_type = std::pair<const Key, Value>;
    using key_type = Key;
    using mapped_type = Value;

    class iterator {
        Node* node;
        const AVLTree* tree;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<const Key&, Value&>;
        using pointer = value_type*;
        using reference = value_type;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator(Node* n, const AVLTree* t) : node(n), tree(t) {}
        iterator() : node(nullptr), tree(nullptr) {}

        bool operator==(const iterator& other) const { return node == other.node; }
        bool operator!=(const iterator& other) const { return node != other.node; }

        std::pair<const Key&, Value&> operator*() {  return std::pair<const Key&, Value&>(node->key, node->value); }

        iterator& operator++() {
            node = tree->findNext(node);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--() {
            if (!node)
                node = tree->findMax(tree->root);
            else
                node = tree->findPrev(node);
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        friend class AVLTree;
    };

    AVLTree() = default;
    ~AVLTree() { clear(root); }

    iterator begin() const { return iterator(findMin(root), this); }
    iterator end() const { return iterator(nullptr, this); }

    std::pair<iterator, bool> insert(const value_type& pair) {
        bool inserted = false;
        root = insertNode(root, nullptr, pair.first, pair.second, inserted);
        Node* n = findNode(root, pair.first);
        return { iterator(n, this), inserted };
    }

    std::pair<iterator, bool> insert(const Key& k, const Value& v) {
        return insert(std::make_pair(k, v));
    }

    void erase(const Key& k) {
        root = eraseNode(root, k);
    }

    iterator find(const Key& k) {
        Node* n = findNode(root, k);
        if (!n)  // key not found
            return end();
        return iterator(n, this);
    }

    iterator find(const Key& k) const {
        Node* n = findNode(root, k);
        if (!n)  // key not found
            return end();
        return iterator(n, this);
    }

    Value& operator[](const Key& k) {
        std::pair<iterator, bool> p = insert(k, Value());
        return p.first.node->value;
    }

    size_t size() const { return node_count; }
    bool empty() const { return size() == 0; }

private:
    Node* findNode(Node* n, const Key& k) const {
        while (n) {
            if (k < n->key)
                n = n->left;
            else if (k > n->key)
                n = n->right;
            else
                return n;
        }
        return nullptr;
    }

    int height(Node* n) const { return n ? n->height : 0; }

    int getBalance(Node* n) const { return n ? height(n->left) - height(n->right) : 0; }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;
        if (T2) T2->parent = y;
        x->parent = y->parent;
        y->parent = x;
        if (x->parent == nullptr) {
            root = x;
        }
        y->height = 1 + std::max(height(y->left), height(y->right));
        x->height = 1 + std::max(height(x->left), height(x->right));
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;
        if (T2) T2->parent = x;
        y->parent = x->parent;
        x->parent = y;

        if (y->parent == nullptr) {
            root = y;
        }
        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));
        return y;
    }

    Node* balance(Node* n) {
        if (!n) return n;
        n->height = 1 + std::max(height(n->left), height(n->right));
        int balanceFactor = getBalance(n);

        if (balanceFactor > 1 && getBalance(n->left) >= 0)
            return rotateRight(n);
        if (balanceFactor > 1 && getBalance(n->left) < 0) {
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (balanceFactor < -1 && getBalance(n->right) <= 0)
            return rotateLeft(n);
        if (balanceFactor < -1 && getBalance(n->right) > 0) {
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Node* insertNode(Node* node, Node* parent, const Key& k, const Value& v, bool& inserted) {
        if (!node) {
            inserted = true;
            Node* n = new Node(k, v);
            n->parent = parent;
            ++node_count;
            return n;
        }

        if (k < node->key)
            node->left = insertNode(node->left, node, k, v, inserted);
        else if (k > node->key)
            node->right = insertNode(node->right, node, k, v, inserted);
        else
            return node;

        return balance(node);
    }

    Node* eraseNode(Node* n, const Key& k) {
        if (!n) return nullptr;

        if (k < n->key)
            n->left = eraseNode(n->left, k);
        else if (k > n->key)
            n->right = eraseNode(n->right, k);
        else {
            --node_count;

            if (!n->left || !n->right) {
                Node* child = n->left ? n->left : n->right;
                if (child) child->parent = n->parent;
                delete n;
                return child;
            }

            Node* successor = findMin(n->right);
            n->key = successor->key;
            n->value = successor->value;
            n->right = eraseNode(n->right, successor->key);
        }

        return balance(n);
    }

    Node* findMin(Node* n) const {
        while (n && n->left)
            n = n->left;
        return n;
    }

    Node* findMax(Node* n) const {
        while (n && n->right)
            n = n->right;
        return n;
    }

    Node* findNext(Node* n) const {
        if (!n) return nullptr;
        if (n->right) {
            n = n->right;
            while (n->left) n = n->left;
            return n;
        }
        Node* p = n->parent;
        while (p && n == p->right) {
            n = p;
            p = p->parent;
        }
        return p;
    }

    Node* findPrev(Node* n) const {
        if (!n) return nullptr;
        if (n->left) {
            n = n->left;
            while (n->right) n = n->right;
            return n;
        }
        Node* p = n->parent;
        while (p && n == p->left) {
            n = p;
            p = p->parent;
        }
        return p;
    }

    void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
        node_count = 0;
    }
};
#endif //AVLMAP_H