#ifndef RED_BLACK_TREES_H
#define RED_BLACK_TREES_H

enum Color { RED, BLACK };

template <typename Key, typename Value>
class RedBlackTree {
private:
    struct Node {
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;

        Node(const Key& k, const Value& v, Color c = RED)
            : key(k), value(v), color(c), left(nullptr), right(nullptr) {}
        ~Node() { delete left; delete right; }
    };

    Node* root;
    size_t count;

    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void flipColors(Node* node);
    bool isRed(Node* node) const;
    Node* find(Node* node, const Key& key) const;
    void insert(Node*& node, const Key& key, const Value& value);
    void remove(Node*& node, const Key& key);
   
 void print_node(Node<K, V>* node, int level) {
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

public:
    RedBlackTree() : root(nullptr), count(0) {}
    ~RedBlackTree() { delete root; }

    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    bool find(const Key& key) const;
    size_t size() const { return count; }
    Value& operator[](const Key& key);


    void print() const {
        print_node(root,0);
    }
};

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateLeft(Node*& node) {
    Node* child = node->right;
    node->right = child->left;
    child->left = node;
    child->color = node->color;
    node->color = RED;
    node = child;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateRight(Node*& node) {
    Node* child = node->left;
    node->left = child->right;
    child->right = node;
    child->color = node->color;
    node->color = RED;
    node = child;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::flipColors(Node* node) {
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::isRed(Node* node) const {
    return node != nullptr && node->color == RED;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node*
RedBlackTree<Key, Value>::find(Node* node, const Key& key) const {
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return find(node->left, key);
    }
    else {
        return find(node->right, key);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key,Value>::insert(Node*& node, const Key& key, const Value& value) {
    // Если узел пустой, создаем новый узел
    if (!node) {
        node = new Node(key, value);
        ++count;
        return;
    }

    // Иначе вставляем узел как в обычном бинарном дереве поиска
    if (key < node->key) {
        insert(node->left, key, value);
    }
    else if (key > node->key) {
        insert(node->right, key, value);
    }
    else {
        // Если ключ уже существует, просто обновляем значение
        node->value = value;
        return;
    }

    // Проверяем и исправляем нарушения свойств красно-черного дерева
    if (isRed(node->right) && !isRed(node->left)) {
        rotateLeft(node);
    }
    if (isRed(node->left) && isRed(node->left->left)) {
        rotateRight(node);
    }
    if (isRed(node->left) && isRed(node->right)) {
        flipColors(node);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key,Value>::remove(Node*& node, const Key& key) {
    if (!node) {
        return;
    }

    if (key < node->key) {
        remove(node->left, key);
    }
    else if (key > node->key) {
        remove(node->right, key);
    }
    else {
        // Если узел имеет только одного потомка, заменяем его на этого потомка
        if (!node->left) {
            Node* temp = node;
            node = node->right;
            temp->right = nullptr;
            delete temp;
            --count;
        }
        else if (!node->right) {
            Node* temp = node;
            node = node->left;
            temp->left = nullptr;
            delete temp;
            --count;
        }
        else {
            // Если узел имеет обоих потомков, заменяем его на минимальный элемент в правом поддереве
            Node* minNode = node->right;
            while (minNode->left) {
                minNode = minNode->left;
            }
            node->key = minNode->key;
            node->value = minNode->value;
            remove(node->right, minNode->key);
        }
    }

    // Проверяем и исправляем нарушения свойств красно-черного дерева
    if (isRed(node->right) && !isRed(node->left)) {
        rotateLeft(node);
    }
    if (isRed(node->left) && isRed(node->left->left)) {
        rotateRight(node);
    }
    if (isRed(node->left) && isRed(node->right)) {
        flipColors(node);
    }
}

template<typename Key, typename Value>
bool RedBlackTree<Key, Value>::find(const Key& key) const {
    return find(root, key) != nullptr;
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key& key, const Value& value) {
    insert(root, key, value);
    root->color = BLACK;
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::remove(const Key& key) {
    remove(root, key);
    if (root != nullptr)
        root->color = BLACK;
}


template<typename Key, typename Value>
Value& RedBlackTree<Key, Value>::operator[](const Key& key) {
    Node* node = find(root, key);
    if (node == nullptr) {
        insert(root, key, Value());
        node = find(root, key);
    }
    return node->value;
}




#endif
