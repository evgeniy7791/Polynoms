
#pragma once

template<typename Key, typename Value>

class TABLE

{

public:

    virtual void insert(const Key& key, const Value& value) = 0;

    virtual void print() const = 0;

    virtual Value& operator[](const Key& k) = 0;



    //void insert(const K key, const V val)

    //void insert(Node*& node, const Key& key, const Value& value);

    //void insert(const Key key, const Value val)



};