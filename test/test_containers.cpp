#include "../containers/unordered_table.h"
#include "../containers/method_chain.h"
#include "../containers/avl_trees.h" 



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










