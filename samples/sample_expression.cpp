
#include <iostream>
#include "../containers/unordered_table.h"

int main() {
	auto ut = UnorderedTable<std::string, int>();
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

	ut.print();
	return 0;



}
