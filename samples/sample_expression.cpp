
#include <iostream>
#include "../containers/unordered_table.h"
#include "../containers/method_chain.h"
#include "../containers/avl_trees.h" 




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

	
	
	AVLTree<int, int> tree;
	for (int i = 0; i < 7; ++i) {
		tree.insert(i * (int)pow(-1, i), i);
	}
	//    tree.print();
	AVLTree<int, int> tree2(tree);
	tree2.remove(0);
	tree2.insert(5, 9);
	tree2.print();
	std::cout << tree.find(-3);
	tree.print();
	return 0;


	/*auto ut = HashTable<std::string, int>();
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

	ut.print();*/



}
