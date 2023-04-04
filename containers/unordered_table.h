#pragma once

#include <iostream>
#include <vector>

template <typename K, typename V>
class UnorderedTable {
private:
	std::vector<std::pair<K, V>> table;

public:
	UnorderedTable() = default;
	UnorderedTable(const UnorderedTable& t) = default;
	UnorderedTable& operator= (const UnorderedTable& t) = default;
	~UnorderedTable() = default;

	auto find(K key) -> decltype(table.begin()) {
		for (auto p = table.begin(); p != table.end(); ++p) {
			if (key == (*p).first) {
				return p;
			}
		}
		return table.end();
	}

	bool contains(K key) {
		return find(key) != table.end();
	}

	V& operator[] (K key) {
		for (auto& p : table) {
			if (key == p.first) {
				return p.second;
			}
		}
		throw std::domain_error("Key not found");
	}

	void add(std::pair<K, V> p) {
		if (contains(p.first)) {
			throw std::logic_error("Key already exists");
		}
		table.push_back(p);
	}

	void add(K key, V val) {
		if (contains(key)) {
			throw std::logic_error("Key already exists");
		}
		table.push_back({ key, val });
	}

	void remove(K key) {
		auto it = find(key);
		if (it == table.end()) {
			throw std::domain_error("Key not found");
		}
		std::swap(*it, table[table.size() - 1]);
		table.pop_back();
	}

	class iterator {
		decltype(table.end()) curr;
	public:
		iterator(decltype(table.end()) first) : curr(first) {}

		void operator++ (int) {
			 ++curr;
		}
		void operator++ () {
			 ++curr;
		}
		iterator  operator+ (int n) {
			return curr + n;
		}
		void operator+= (int n) {
			for (size_t i = 0; i < n && curr; ++i) {
				curr += n;
			}
		}

		bool operator!= (const iterator& it) {
			return curr != it.curr;
		}

		bool operator== (const iterator& it) {
			return curr == it.curr;
		}

		std::pair<K, V>& operator* () {
			return *curr;
		}
	};

	iterator begin() {
		return iterator(table.begin());
	}

	iterator end() {
		return iterator(table.end());
	}

	void print(std::ostream& out = std::cout) {
		out << "UnorderedTable {";
		for (auto p : *this) {
			out << " (key=" << p.first << "," << "value=" << p.second << "),";
		}
		out << "}\n";
	}
	size_t size() {
		return table.size();
	}

};


