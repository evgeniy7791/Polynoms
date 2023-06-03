
#ifndef ORDERED_TABLE_H

#define ORDERED_TABLE_H

#include "TABLE.h"

#include "polynom.h"

#include <vector>
#include<string>


template<typename Key, typename Value>

class OrderedTable : public TABLE<Key, Value> {

private:

    std::vector< std::pair<Key, Value> > Otable;

public:

    OrderedTable() = default;



    OrderedTable(const OrderedTable& t) = default;

    OrderedTable& operator= (const OrderedTable& t) = default;



    ~OrderedTable() = default;



    /*Value* find(const Key& key) {

        for (auto& p : Otable) {

            if (p.first == key) {

                return &p.second;

            }

        }

        return nullptr;

    }

    */
    Value* find(const Key& key) {
        bool flag = false;
        int l = 0;
        int r = Otable.size();
        int mid;
        while (l <= r && flag != true)
        {
            mid = (l + r) / 2;
            if (Otable[mid].first == key)
                return &Otable[mid].second;
            if (Otable[mid].first > key) r = mid - 1;
            else l = mid + 1;
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







    void insert(const std::pair<Key, Value>& value) {

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



    void insert(const Key& key, const Value& val) {

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

        Otable.push_back(std::pair<Key, Value>(key, Value()));

        return Otable.back().second;

    }



    void print() const {

        for (const auto& elem : Otable) {

            std::cout << elem.first << ", ";

            std::cout << elem.second/*.toString()*/ << std::endl;





        }

    }

};





#endif