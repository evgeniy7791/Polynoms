
#include <iostream>
#include "../containers/unordered_table.h"
#include "../containers/method_chain.h"
#include "../containers/avl_trees.h" 

template<class T>
int get_h(AVLTree<T>* node) {
	return node ? node->height : 0;
}

template<class T>
int get_bf(AVLTree<T>* node) {
	return get_h(node->right) - get_h(node->left);
}

template<class T>
void fix_height(AVLTree<T>* node) {
	node->height = std::max(get_h(node->right), get_h(node->left)) + 1;
}

template<class T>
AVLTree<T>* rotate_left(AVLTree<T>* root) {
	auto node = root->right;
	node->parent = root->parent;
	root->parent = node;
	root->right = node->left;
	node->left = root;
	fix_height(root);
	fix_height(node);
	return node;
}

template<class T>
AVLTree<T>* rotate_right(AVLTree<T>* root) {
	auto node = root->left;
	node->parent = root->parent;
	root->parent = node;
	root->left = node->right;
	node->right = root;
	fix_height(root);
	fix_height(node);
	return node;
}

template<class T>
AVLTree<T>* balance(AVLTree<T>* root) {
	if (! root)
		return nullptr;

	fix_height(root);
	if (get_bf(root) == 2) {
		if (get_bf(root->right) < 0)
			root->right = rotate_right(root->right);
		root = rotate_left(root);
	}
	else if (get_bf(root) == -2) {
		if (get_bf(root->left) > 0)
			root->left = rotate_right(root->left);
		root = rotate_right(root);
	}
	return root;
}

template<class T>
AVLTree<T>* insert(AVLTree<T>* root, const T& k) {
	if (!root)
		return new AVLTree<T>(k, nullptr, nullptr, nullptr, 1);
	if (k <= root->key) {
		root->left = insert(root->left, k);
		root->left->parent = root;
	}
	else {
		root->right = insert(root->right, k);
		root->right->parent = root;
	}
	return balance(root);
}

template<class T>
AVLTree<T>* find(AVLTree<T>* root, const T& k) {
	if (not root)
		return nullptr;
	if (k == root->key) {
		return root;
	}
	else if (k < root->key) {
		root->left = find(root->left, k);
	}
	else {
		root->right = find(root->right, k);
	}
	return nullptr;
}


template<class T>
AVLTree<T>* remove(AVLTree<T>* root, const T& k) {
	if (not root)
		return nullptr;
	if (k < root->key) {
		root->left = remove(root->left, k);
		return balance(root);
	}
	if (k > root->key) {
		root->right = remove(root->right, k);
		return balance(root);
	}

	if (not root->left and not root->right) {
		delete root;
		return nullptr;
	}

	if (not root->left or not root->right) {
		auto child = root->left ? root->left : root->right;
		child->parent = root->parent;
		delete root;
		return child;
	}
	auto cur = root->right;
	while (cur->left)
		cur = cur->left;
	root->key = cur->key;
	root->right = remove(root->right, cur->key);
	return balance(root);
}

template<class T>
void print(AVLTree<T>* root, int level) {
	if (root->right) {
		print(root->right, level + 1);
	}
	for (int i = level; i > 0; --i)
		std::cout << "\t";
	std::cout << root->key << "\n";
	if (root->left) {
		print(root->left, level + 1);
	}
}


int main() {
	/*auto ut = UnorderedTable<std::string, int>();
	ut.add({ "a", 1 });
	ut.add("b", 2);
	ut.add("c", 3);
	ut.add("d", 4);
	try {
		ut.add("a", 3);
	}
	catch (std::logic_error e) {
		std::cerr << e.what()<<std::endl;
	}
	ut.remove("a");

	ut["c"] = 3888;

	ut.print();*/

	
	
	/*AVLTree<int>* tree = nullptr;
	for (int i = 0; i < 7; ++i) {
		tree = insert(tree, i * (int)pow(1, i));
	}
	print(tree, 0);
	return 0;*/


	auto ut = HashTable<std::string, int>();
	ut.insert({ "a", 1 });
	ut.insert("b", 2);
	ut.insert("c", 3);
	ut.print();
	ut.insert("d", 4);
	try {
		ut.insert("a", 3);
	}
	catch (std::logic_error e) {
		std::cerr << e.what() << std::endl;
	}
	ut.print();
	ut.remove("a");

	ut["c"] = 3888;

	ut.print();



}
