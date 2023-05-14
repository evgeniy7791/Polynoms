#pragma once

#include "TABLE.h"

#include <iostream>

#include <vector>

#include "unordered_table.h"





template<typename K, typename V>

class HashTable : public TABLE<K, V> {

private:

    std::vector<UnorderedTable<K, V> > table;

    size_t hash(K key, size_t size) {

        std::hash<K> hash_K;

        return hash_K(key) % size;

    }

    void resize() {

        auto newTable = decltype(table)(table.size() * 2 + 1);

        for (auto list : table) {

            for (auto p : list) {

                newTable[hash(p.first, newTable.size())].insert(p.first, p.second);

            }

        }

        table = newTable;

    }

public:

    HashTable() {

        table = std::vector<UnorderedTable<K, V> >(3);

    }

    HashTable(HashTable& ht) {

        this->table = ht.table;

    }

    ~HashTable() = default;



    bool contains(K key) {

        return table[hash(key)].contains(key);

    }



    V& operator[] (const K& key) {

        return table[hash(key)][key];

    }



    std::pair<K, V>& get(K key) {

        return table[hash(key)][key];

    }





    size_t hash(K key) {

        return hash(key, table.size());

    }



    void insert(const K& key, const V& val) {

        table[hash(key)].insert(key, val);

        if (table[hash(key)].size() >= table.size()) {

            resize();

        }

    }



    /*void insert(std::pair<K, V> p) {

        insert(p.first, p.second);

    }

*/

    void remove(K key) {

        table[hash(key)].remove(key);

    }



    void print() const//(std::ostream& out = std::cout)

    {

        cout << "HashTable {";

        for (auto ut : table) {

            for (auto p : ut) {

                cout << " (key=" << p.first << "," << "value=" << p.second << "),";

            }

        }

        cout << "}\n";

    }

};

