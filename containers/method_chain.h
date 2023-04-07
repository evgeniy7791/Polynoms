#pragma once

#include <iostream>
#include <vector>
#include "unordered_table.h"


template<typename K, typename V>
class HashTable {
private:
	std::vector<UnorderedTable<K, V>> table;
	size_t hash(K key, size_t size) {
		return std::hash<K>{}(key) % size;
	}
	void resize() {
		auto newTable = decltype(table)(table.size() * 2 + 1);
		for (auto list : table) {
			for (auto p : list) {
				newTable[hash(p.first, newTable.size())].insert(p);
			} 
		} 
		table = newTable;
	}
public:
	HashTable() {
		table = std::vector<UnorderedTable<K, V>>(3);
	}
	HashTable(HashTable& ht) {
		this->table = ht.table;
	}
	~HashTable() = default;

	bool contains(K key) {
		return table[hash(key)].contains(key);
	}

	V& operator[] (K key) {
		return table[hash(key)][key];
	}

	std::pair<K, V>& get (K key) {
		return table[hash(key)][key];
	}


	size_t hash(K key) {
		return hash(key, table.size());
	}

	void insert(K key, V val) {
		table[hash(key)].insert(std::pair<K, V>(key, val));
		if (table[hash(key)].size() >= table.size()) {
			resize();
		}
	}

	void insert(std::pair<K, V> p) {
		insert(p.first, p.second);
	}

	void remove(K key) {
		table[hash(key)].remove(key);
	}

	void print(std::ostream& out = std::cout) {
		out << "HashTable {";
		for (auto ut : table) {
			for (auto p : ut){
				out << " (key=" << p.first << "," << "value=" << p.second << "),";
			}
		}
		out << "}\n";
	}
};



