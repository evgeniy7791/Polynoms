
#include <iostream>
#include "../containers/unordered_table.h"
#include "../containers/ordered_table.h"
#include "../containers/method_chain.h"
#include "../containers/open_adress.h"
#include "../containers/avl_trees.h" 
#include "../containers/red_black_trees.h" 
#include "polynom.h"



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

	
	
	/*AVLTree<int, int> tree;
	for (int i = 0; i < 7; ++i) {
		tree.insert(i * (int)pow(-1, i), i);
	}
	    tree.print();
	AVLTree<int, int> tree2(tree);
	tree2.remove(0);
	tree2.insert(5, 9);
	tree2.print();
	std::cout << tree.find(-3);
	tree.print();
	return 0;*/




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

	/*HashTable <int, Polinom> f;
	Monom m1(2, 3, 1, 1);
	Monom m2(4, 3, 1, 1);
	Polinom p1,p2;
	p1.add(m1);
	p2.add(m2);
	cout << p1;
	f.insert(1, p1);
	f.insert(5, p2);
	f.print();


	OrderedTable<int, int> ot;
	for (int i = 0; i < 7; ++i) 
	{
		ot.insert(i * (int)pow(-1, i), i);
	}
	ot.remove(-3);
	ot.print();*/
	

	/*HashTable2<int, int> opad;
	for (int i = 0; i < 18; ++i)
	{
		opad.insert(i * (int)pow(-1, i), i);
	}
	opad.remove(-3);
	opad.insert(4,100);
	
	opad.print();*/

	RedBlackTree<int, int> rb;
	for (int i = 0; i < 7; ++i) {
		rb.insert(i * (int)pow(-1, i), i);
	}
	rb.print();


}
