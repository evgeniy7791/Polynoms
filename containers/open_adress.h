#ifndef OPEN_ADRESS_H
#define OPEN_ADRESS_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <iostream>
#include <vector>
#include <functional>

template<typename Key, typename Value>
class HashTable2 {
private:
    std::vector<std::pair<Key, Value>> table;
    int size;

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % table.size();
    }

    void rehash() {
        // перехэширование
        int newSize = table.size() * 2;
        std::vector<std::pair<Key, Value>> newTable(newSize);
        for (auto& p : table) {
            int i = hash(p.first);
            while (newTable[i].first != Key{} && newTable[i].first != p.first) {
                i = (i + 1) % newSize;
            }
            newTable[i] = p;
        }
        table = std::move(newTable);
    }

public:
    HashTable2() : size(0), table(8) {}

    void insert2(const Key& key, const Value& value) {
        if (size >= table.size() * 0.7) {
            rehash();
        }
        int i = hash(key);
        while (table[i].first != Key{} && table[i].first != key) {
            i = (i + 1) % table.size();
        }
        table[i] = { key, value };
        size++;
    }

    void insert(const Key& key, const Value& value) {
        insert2(key, value);
    }

    bool find(const Key& key, Value& value) const {
        int i = hash(key);
        while (table[i].first != Key{}) {
            if (table[i].first == key) {
                value = table[i].second;
                return true;
            }
            i = (i + 1) % table.size();
        }
        return false;
    }

    void remove(const Key& key) {
        int i = hash(key);
        while (table[i].first != Key{}) {
            if (table[i].first == key) {
                table[i].first = Key{};
                size--;
                return;
            }
            i = (i + 1) % table.size();
        }
    }

    int getSize() const {
        return size;
    }

    Value& operator[](const Key& key) {
        int i = hash(key);
        while (table[i].first != Key{}) {
            if (table[i].first == key) {
                return table[i].second;
            }
            i = (i + 1) % table.size();
        }
        insert(key, Value{});
        return table[hash(key)].second;
    }

    void print() const {
        for (const auto& p : table) {
            if (p.first != Key{}) {
                std::cout << "Key: " << p.first << ", Value: " << p.second << std::endl;
            }
        }
    }
};



#endif