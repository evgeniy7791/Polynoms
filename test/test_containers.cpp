#include "../containers/unordered_table.h"
#include "../containers/method_chain.h"
#include "../containers/open_adress.h"
#include "../containers/avl_trees.h" 
#include "../containers/ordered_table.h"
#include "polynom.h"


#include <gtest.h>



TEST(UnorderedTable, can_create_ut) 
{
	UnorderedTable<int,int> u;
	ASSERT_NO_THROW(u);
}

TEST(UnorderedTable, uniqueness_of_the_key)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	ASSERT_ANY_THROW(u.insert(1, 200););
}

TEST(UnorderedTable, square_brackets)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	EXPECT_EQ(u[1],100);
}

TEST(UnorderedTable, square_brackets_2)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	u[1] = 200;
	EXPECT_EQ(u[1], 200);
}

TEST(UnorderedTable, find)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	u.insert(2, 100);
	u.insert(5, 100);
	u.insert(7, 100);
	ASSERT_NO_THROW(u.find(5));
}

TEST(UnorderedTable, find2)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	u.insert(2, 100);
	u.insert(5, 700);
	u.insert(7, 100);
	EXPECT_EQ(( * u.find(7)).second, 100);
}

TEST(UnorderedTable, contains)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	u.insert(2, 100);
	u.insert(5, 700);
	u.insert(7, 100);
	EXPECT_EQ(u.contains(2), 1);
}

TEST(UnorderedTable,key_not_found)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	u.insert(2, 100);
	u.insert(5, 700);
	u.insert(7, 100);
	ASSERT_ANY_THROW(u.remove(10));
}


TEST(UnorderedTable, copy)
{
	UnorderedTable<int, int> u;
	u.insert(1, 100);
	u.insert(2, 100);
	u.insert(5, 700);
	u.insert(7, 100);
	UnorderedTable<int, int> t;
	t = u;
	EXPECT_EQ(( * t.find(5)).second, 700);
}



TEST(AVLTreeTest, InsertionTest) {
    AVLTree<int, std::string> tree;
    tree.insert(3, "three");
    tree.insert(1, "one");
    tree.insert(5, "five");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.insert(6, "six");
    EXPECT_EQ(tree.size(), 6);
 
}

TEST(AVLTreeTest, RemovalTest) {
	AVLTree<int, std::string> tree;
	tree.insert(3, "three");
	tree.insert(1, "one");
	tree.insert(5, "five");
	tree.insert(2, "two");
	tree.insert(4, "four");
	tree.insert(6, "six");
	EXPECT_EQ(tree.size(), 6);

	tree.remove(3);
	EXPECT_EQ(tree.size(), 5);


	tree.remove(5);
	EXPECT_EQ(tree.size(), 4);


	tree.remove(1);
	EXPECT_EQ(tree.size(), 3);

	tree.remove(4);
	EXPECT_EQ(tree.size(), 2);


	tree.remove(6);
	EXPECT_EQ(tree.size(), 1);


}


TEST(HashTable_ChainMethod,can_create)
{
	HashTable<std::string, int> ht;
	ASSERT_NO_THROW(ht);
}

TEST(HashTable_ChainMethod, uniqueness_of_the_key)
{
	HashTable<std::string, int> ht;
	ht.insert("kot", 9087);
	ASSERT_ANY_THROW(ht.insert("kot", 9087));
}

TEST(HashTable_ChainMethod, key_not_found)
{
	HashTable<std::string, int> ht;
	ht.insert("kot", 9087);
	ASSERT_ANY_THROW(ht.remove("jkk"));
}

TEST(HashTable_ChainMethod, remove_key)
{
	HashTable<std::string, int> ht;
	ht.insert("kot", 9087);
	ASSERT_NO_THROW(ht.remove("kot"));
}

TEST(HashTable_ChainMethod, square_brackets)
{
	HashTable<std::string, int> ht;
	ht.insert("h", 100);
	EXPECT_EQ(ht["h"], 100);
}

TEST(HashTable_ChainMethod, square_brackets_2)
{
	HashTable<int, int> ht;
	ht.insert(1, 100);
	ht[1] = 200;
	EXPECT_EQ(ht[1], 200);
}

TEST(HashTable_ChainMethod, contains)
{
	HashTable<int, int> u;
	u.insert(1, 100);
	u.insert(2, 100);
	u.insert(5, 700);
	u.insert(7, 100);
	EXPECT_EQ(u.contains(2), 1);
}

TEST(HashTable_ChainMethod, new_test)
{
	HashTable<int, Polinom> u;
	Monom m(2, 3, 1, 1);
	Polinom p;
	p.add(m);
	ASSERT_NO_THROW(u.insert(1, p));
}









TEST(Polinom, can_create_empty_polinom)
{
    EXPECT_NO_THROW(Polinom p1);
}

TEST(Polinom, can_add_monom_to_polinom)
{
    Monom m(2, 1, 1, 1);
    Polinom p;
    EXPECT_NO_THROW(p.add(m));
}

TEST(Polinom, can_calc_polinom_with_single_monom)
{
    Monom m(2, 1, 1, 1);
    Polinom p;
    p.add(m);
    EXPECT_NO_THROW(p.calc());
}

TEST(Polinom, can_calc_polinom_with_single_monom_correctly)
{
    Monom m(2, 1, 1, 1);
    Polinom p;
    p.add(m);
    int res = p.calc(2, 1, 1);
    EXPECT_EQ(4, res);
}

TEST(Polinom, can_add_second_monom_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    p.add(m);
    EXPECT_NO_THROW(p.add(m1));
}

TEST(Polinom, can_add_second_monom_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    p.add(m);
    p.add(m1);
    int res = p.calc(2, 1, 1);
    EXPECT_EQ(16, res);
}

TEST(Polinom, can_add_second_monom_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    p.add(m);
    EXPECT_NO_THROW(p.add(m1));
}

TEST(Polinom, can_add_second_monom_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    p.add(m);
    p.add(m1);
    int res = p.calc(2, 1, 1);
    EXPECT_EQ(10, res);
}

TEST(Polinom, can_plus_empty_polinoms)
{
    Polinom p;
    Polinom p1;
    EXPECT_NO_THROW(p + p1);
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p + p1);
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p + p1).calc(2, 1, 1), p.calc(2, 1, 1) + p1.calc(2, 1, 1));
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p + p1);
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p + p1).calc(2, 1, 1), p.calc(2, 1, 1) + p1.calc(2, 1, 1));
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p * p1);
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(24, p.calc(2, 1, 1) * p1.calc(2, 1, 1));
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p * p1);
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(48, p.calc(2, 1, 1) * p1.calc(2, 1, 1));
}

TEST(Polinom, can_mult_polinoms_in_different_points_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(384, p.calc(2, 1, 1) * p1.calc(2, 2, 2));
}

TEST(Polinom, can_mult_polinoms_in_same_points_correctly_2)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_LE(abs(((p * p1).calc(2, 2, 2)) - 1536), 1e-7);
}

TEST(Polinom, can_mult_polinoms_in_different_points)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW((p * p1).calc(2, 2, 2));
}

TEST(Polinom, can_minus_empty_polinoms)
{
    Polinom p;
    Polinom p1;
    EXPECT_NO_THROW(p - p1);
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p - p1);
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p - p1).calc(2, 1, 1), p.calc(2, 1, 1) - p1.calc(2, 1, 1));
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p - p1);
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p - p1).calc(2, 1, 1), p.calc(2, 1, 1) - p1.calc(2, 1, 1));
}

TEST(Polinom, can_div_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p / p1);
}

TEST(Polinom, can_div_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(6, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(2, p.calc(2, 1, 1) / p1.calc(2, 1, 1));
}

TEST(Polinom, can_div_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p / p1);
}

TEST(Polinom, can_div_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(6, 2, 2, 2);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(4, p.calc(2, 1, 1) / p1.calc(2, 1, 1));
}

TEST(Polinom, can_div_polinoms_in_different_points_correctly)
{
    Monom m(9, 2, 2, 2);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(1.5, p.calc(2, 1, 1) / p1.calc(2, 2, 2));
}


TEST(Polinom, can_div_polinoms_in_same_points_correctly)
{
    Monom m(6, 3, 3, 3);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_LE(abs(((p / p1).calc(2, 2, 2)) - 16), 1e-7);
}

TEST(Polinom, can_div_polinoms_in_different_points)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW((p / p1).calc(2, 2, 2));
}

TEST(Polinom, div_polinoms_1)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 2, 2);
    Monom m2(10, 3, 3, 3);
    Monom k(4, 1, 1, 1);
    Polinom p;
    Polinom p1;
    Polinom p2;
    p.add(m);
    p1.add(m1);
    p.add(m2);
    p2.add(k);
    EXPECT_EQ((p / p1).calc(1, 1, 1), p2.calc(1, 1, 1));
}

TEST(Polinom, div_polinoms_2)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 2, 2);
    Monom m2(10, 3, 3, 3);
    Monom k(4, 1, 1, 1);
    Polinom p;
    Polinom p1;
    Polinom p2;
    p.add(m);
    p1.add(m1);
    p.add(m2);
    p2.add(k);
    EXPECT_EQ((p / p1).calc(1, 1, 1), p2.calc(1, 1, 1));
}

TEST(Monom, monoms_pow1)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 3, 2);
    int res = m.getX();
    int res1 = m1.getY();
    //EXPECT_EQ(3, m.getX());
    EXPECT_EQ(res, res1);
}

TEST(Monom, monoms_pow)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 3, 2);
    //int res = m.getX();
    //auto res1 = m1.getY();
      //EXPECT_EQ(3, m.getX());
    EXPECT_NO_THROW(m.getX());
}


TEST(OrderedTableTest, InsertAndFindTest) {
    OrderedTable<int, std::string> table;

    // проверяем вставку элементов и их поиск
    table.insert(5, "Five");
    table.insert(2, "Two");
    table.insert(7, "Seven");

    EXPECT_EQ(*table.find(5), "Five");
    EXPECT_EQ(*table.find(2), "Two");
    EXPECT_EQ(*table.find(7), "Seven");
}

TEST(OrderedTableTest, InsertAndRemoveTest) {
    OrderedTable<int, std::string> table;

    // проверяем вставку элементов и их удаление
    table.insert(5, "Five");
    table.insert(2, "Two");
    table.insert(7, "Seven");

    table.remove(2);
    EXPECT_EQ(table.size(), 2);

    table.remove(5);
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(*table.find(7), "Seven");
}

TEST(OrderedTableTest, SubscriptOperatorTest) {
    OrderedTable<int, std::string> table;

    // проверяем оператор []
    table[5] = "Five";
    table[2] = "Two";
    table[7] = "Seven";

    EXPECT_EQ(table.size(), 3);
    EXPECT_EQ(*table.find(5), "Five");
    EXPECT_EQ(*table.find(2), "Two");
    EXPECT_EQ(*table.find(7), "Seven");
}


///////

TEST(HashTable2Test, InsertAndFind) {
    HashTable2<int, std::string> hashTable;
    hashTable.insert(1, "One");
    hashTable.insert(2, "Two");
    hashTable.insert(3, "Three");
    hashTable.insert(4, "Four");
    hashTable.insert(5, "Five");
    std::string value;
    EXPECT_TRUE(hashTable.find(1, value));
    EXPECT_EQ("One", value);
    EXPECT_TRUE(hashTable.find(2, value));
    EXPECT_EQ("Two", value);
    EXPECT_TRUE(hashTable.find(3, value));
    EXPECT_EQ("Three", value);
    EXPECT_TRUE(hashTable.find(4, value));
    EXPECT_EQ("Four", value);
    EXPECT_TRUE(hashTable.find(5, value));
    EXPECT_EQ("Five", value);
}

TEST(HashTable2Test, Remove) {
    HashTable2<int, std::string> hashTable;
    hashTable.insert(1, "One");
    hashTable.insert(2, "Two");
    hashTable.insert(3, "Three");
    hashTable.insert(4, "Four");
    hashTable.insert(5, "Five");
    hashTable.remove(3);
    std::string value;
    EXPECT_FALSE(hashTable.find(3, value));
    hashTable.remove(1);
    EXPECT_FALSE(hashTable.find(1, value));
    EXPECT_TRUE(hashTable.find(2, value));
    EXPECT_EQ("Two", value);
    EXPECT_TRUE(hashTable.find(4, value));
    EXPECT_EQ("Four", value);
    EXPECT_TRUE(hashTable.find(5, value));
    EXPECT_EQ("Five", value);
}

TEST(HashTable2Test, IndexOperator) {
    HashTable2<int, std::string> hashTable;
    hashTable[1] = "One";
    hashTable[2] = "Two";
    hashTable[3] = "Three";
    hashTable[4] = "Four";
    hashTable[5] = "Five";
    std::string value;
    EXPECT_TRUE(hashTable.find(1, value));
    EXPECT_EQ("One", value);
    EXPECT_TRUE(hashTable.find(2, value));
    EXPECT_EQ("Two", value);
    EXPECT_TRUE(hashTable.find(3, value));
    EXPECT_EQ("Three", value);
    EXPECT_TRUE(hashTable.find(4, value));
    EXPECT_EQ("Four", value);
    EXPECT_TRUE(hashTable.find(5, value));
    EXPECT_EQ("Five", value);
}

TEST(HashTable2Test, Rehash) {
    HashTable2<int, std::string> hashTable;
    for (int i = 0; i < 100; i++) {
        hashTable.insert(i, std::to_string(i));
    }
    EXPECT_EQ(100, hashTable.getSize());
}



