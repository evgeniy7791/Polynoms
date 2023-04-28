#ifndef ORDERED_TABLE_H
#define ORDERED_TABLE_H

#include <vector>

template<typename Key, typename Value>
class OrderedTable {
private:
    std::vector< std::pair<Key, Value>> Otable;
public:
    OrderedTable() = default;

    OrderedTable(const OrderedTable& t) = default;
    OrderedTable& operator= (const OrderedTable& t) = default;

    ~OrderedTable() = default;

    Value* find(const Key& key) {
        for (auto& p : Otable) {
            if (p.first == key) {
                return &p.second;
            }
        }
        return nullptr;
    }

    void remove(Key key) {
        auto it = Otable.begin();
        while (it != Otable.end()) {
            if (it->first == key) {
                it = Otable.erase(it);
                return;
            }
            else {
                ++it;
            }
        }
    }



    void insert(const std::pair<Key, Value> & value) {
        auto it = Otable.begin();
        for (; it != Otable.end(); ++it) {
            if (it->first == value.first) {
                it->second = value.second;
                return;
            }
            else if (it->first > value.first) {
                break;
            }
        }
        Otable.insert(it, std::pair<Key, Value>(value.first, value.second));
    }
   
    void insert(Key key, Value val) {
        size_t i = 0;
        while (i < Otable.size() && Otable[i].first < key) {
            ++i;
        }
        Otable.insert(Otable.begin() + i, std::make_pair(key, val));
    }

    std::size_t size() const {
        return Otable.size();
    }

    Value& operator[](const Key& key) {
        for (auto& p : Otable) {
            if (p.first == key) {
                return p.second;
            }
        }
        Otable.push_back(std::pair<Key, Value> (key, Value()));
        return Otable.back().second;
    }

    void print() const {
        for (const auto& elem : Otable) {
            std::cout << elem.first << ", " << elem.second << std::endl;
        }
    }
};


#endif