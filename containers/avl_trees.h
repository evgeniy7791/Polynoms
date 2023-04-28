
#ifndef AVL_TREES_H
#define AVL_TREES_H

#include <iostream>
#include <vector>


template <class K, class V>
struct Node {
public:
	K key;
	V val;
	int height;
	Node<K, V>* left, * right, * parent;

	Node(const K& k, const V& v, Node<K, V>* l, Node<K, V>* r, Node<K, V>* p, int h) :
		key(k), val(v), left(l), right(r), parent(p), height(h) {}
	Node(const K& k, const V& v) : Node(k, v, nullptr, nullptr, nullptr, 1) {}
	Node(const Node<K, V>& node) = default;
	~Node() = default;
};

template <typename K, typename V>
class AVLTree {
private:
	Node<K, V>* root;

	int get_h_node(Node<K, V>* node) {
		return node ? node->height : 0;
	}

	int get_bf(Node<K, V>* node) {
		return get_h_node(node->right) - get_h_node(node->left);
	}

	void fix_height(Node<K, V>* node) {
		node->height = std::max(get_h_node(node->right), get_h_node(node->left)) + 1;
	}

	int count_nodes(const Node<K, V>* node) const {
		if (!node) {
			return 0;
		}
		return 1 + count_nodes(node->left) + count_nodes(node->right);
	}

	Node<K, V>* rotate_left(Node<K, V>* dad) {
		auto node = dad->right;
		node->parent = dad->parent;
		dad->parent = node;
		dad->right = node->left;
		node->left = dad;
		fix_height(dad);
		fix_height(node);
		return node;
	}

	Node<K, V>* rotate_right(Node<K, V>* dad) {
		auto node = dad->left;
		node->parent = dad->parent;
		dad->parent = node;
		dad->left = node->right;
		node->right = dad;
		fix_height(dad);
		fix_height(node);
		return node;
	}

	Node<K, V>* balance(Node<K, V>* node) {
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

	Node<K, V>* insert_node(Node<K, V>* node, const K& k, const V& v) {
		if (!node)
			return new Node<K, V>(k, v, nullptr, nullptr, nullptr, 1);
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

	Node<K, V>* find_node(Node<K, V>* node, const K& k) {
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

	Node<K, V>* remove_node(Node<K, V>* node, const K& k) {
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

		if (!node->left  && !node->right) {
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

	void destroyRecursive(Node<K, V>* node) {
		if (node) {
			destroyRecursive(node->left);
			destroyRecursive(node->right);
			delete node;
		}
	}

	void copyRecursive(Node<K, V>* node) {
		if (node) {
			root = insert_node(root, node->key, node->val);
			copyRecursive(node->left);
			copyRecursive(node->right);
		}
	}
public:
	AVLTree(const K& k, const V& v) : root(new Node<K, V>(k, v)) {}

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

	void remove(const K& k) {
		root = remove_node(root, k);
	}

	void print() {
		print_node(root, 0);
	}

	int size() const {
		return count_nodes(root);
	}

};

#endif