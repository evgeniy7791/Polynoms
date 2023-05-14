
#pragma once

#include "TABLE.h"

#include <iostream>

#include <vector>





template <class K, class V>

struct avlNode {

public:

    K key;

    V val;

    int height;

    avlNode<K, V>* left, * right, * parent;



    avlNode(const K& k, const V& v, avlNode<K, V>* l, avlNode<K, V>* r, avlNode<K, V>* p, int h) :

        key(k), val(v), left(l), right(r), parent(p), height(h) {}

    avlNode(const K& k, const V& v) : Node(k, v, nullptr, nullptr, nullptr, 1) {}

    avlNode(const avlNode<K, V>& node) = default;

    ~avlNode() = default;

};



template <typename K, typename V>

class AVLTree : public TABLE<K, V> {

private:

    avlNode<K, V>* root;



    int get_h_node(avlNode<K, V>* node) {

        return node ? node->height : 0;

    }



    int get_bf(avlNode<K, V>* node) {

        return get_h_node(node->right) - get_h_node(node->left);

    }



    void fix_height(avlNode<K, V>* node) {

        node->height = std::max(get_h_node(node->right), get_h_node(node->left)) + 1;

    }



    avlNode<K, V>* rotate_left(avlNode<K, V>* dad) {

        auto node = dad->right;

        node->parent = dad->parent;

        dad->parent = node;

        dad->right = node->left;

        node->left = dad;

        fix_height(dad);

        fix_height(node);

        return node;

    }



    avlNode<K, V>* rotate_right(avlNode<K, V>* dad) {

        auto node = dad->left;

        node->parent = dad->parent;

        dad->parent = node;

        dad->left = node->right;

        node->right = dad;

        fix_height(dad);

        fix_height(node);

        return node;

    }



    avlNode<K, V>* balance(avlNode<K, V>* node) {

        if (!node)

            return nullptr;



        fix_height(node);

        if (get_bf(node) == 2) {

            if (get_bf(node->right) < 0)

                node->right = rotate_right(node->right);

            node = rotate_left(node);

        }

        else if (get_bf(node) == -2) {

            if (get_bf(node->left) > 0)

                node->left = rotate_right(node->left);

            node = rotate_right(node);

        }

        return node;

    }



    avlNode<K, V>* insert_node(avlNode<K, V>* node, const K& k, const V& v) {

        if (!node)

            return new avlNode<K, V>(k, v, nullptr, nullptr, nullptr, 1);

        if (k <= node->key) {

            node->left = insert_node(node->left, k, v);

            node->left->parent = node;

        }

        else {

            node->right = insert_node(node->right, k, v);

            node->right->parent = node;

        }

        return balance(node);

    }



    avlNode<K, V>* find_node(avlNode<K, V>* node, const K& k) {

        if (!node)

            return nullptr;

        if (k == node->key) {

            return node;

        }

        else if (k < node->key) {

            return find_node(node->left, k);

        }

        else {

            return find_node(node->right, k);

        }

    }



    avlNode<K, V>* remove_node(avlNode<K, V>* node, const K& k) {

        if (!node)

            return nullptr;

        if (k < node->key) {

            node->left = remove_node(node->left, k);

            return balance(node);

        }

        if (k > node->key) {

            node->right = remove_node(node->right, k);

            return balance(node);

        }



        if (!node->left && !node->right) {

            delete node;

            return nullptr;

        }



        if (!node->left || !node->right) {

            auto child = node->left ? node->left : node->right;

            child->parent = node->parent;

            delete node;

            return child;

        }

        auto cur = node->right;

        while (cur->left)

            cur = cur->left;

        node->key = cur->key;

        node->val = cur->val;

        node->right = remove_node(node->right, cur->key);

        return balance(node);

    }



    void print_node(avlNode<K, V>* node, int level) const {

        if (node->right) {

            print_node(node->right, level + 1);

        }

        for (int i = level; i > 0; --i)

            std::cout << "\t\t";

        std::cout << "(" << node->key << ", " << node->val << ")" << "\n";

        if (node->left) {

            print_node(node->left, level + 1);

        }

    }



    void destroyRecursive(avlNode<K, V>* node) {

        if (node) {

            destroyRecursive(node->left);

            destroyRecursive(node->right);

            delete node;

        }

    }



    void copyRecursive(avlNode<K, V>* node) {

        if (node) {

            root = insert_node(root, node->key, node->val);

            copyRecursive(node->left);

            copyRecursive(node->right);

        }

    }

public:

    AVLTree(const K& k, const V& v) : root(new avlNode<K, V>(k, v)) {}



    AVLTree() : root(nullptr) {}



    ~AVLTree() {

        destroyRecursive(root);

    }





    AVLTree(AVLTree const& other) : root(nullptr) {

        copyRecursive(other.root);

    }



    int get_h() {

        return get_h_node(root);

    }



    void insert(const K& k, const V& v) {

        root = insert_node(root, k, v);

    }



    void insert(std::pair<K, V> p) {

        this->insert(p.first, p.second);

    }



    V& find(const K& k) {

        return find_node(root, k)->val;

    }

    V& operator[](const K& k) {

        return find(k);

    }



    void remove(const K& k) {

        root = remove_node(root, k);

    }



    void print() const {

        print_node(root, 0);

    }



};