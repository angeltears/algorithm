#pragma once

#include<iostream>

class HashTable;
class BucketNode
{
	typedef int Type;
	friend class HashTable;
public:
	BucketNode() :link(nullptr)
	{
		for (int i = 0; i < 3; i++)
			data[i] = 0;
	}
	BucketNode(Type d, BucketNode *l = nullptr)
		: link(l)
	{
		data[0] = d;
		data[1] = 0;
		data[2] = 0;
	}
	~BucketNode()
	{}
private:
	int data[3];
	BucketNode *link;
};

class HashTable
{
public:
	typedef int Type;
	typedef typename BucketNode* pointer;
	HashTable(){}
public:
	void Insert(const Type &key)
	{
		int index = Hash(key);
		if (hashtable[index] == nullptr)
		{
			pointer s = new BucketNode(key);
			hashtable[index] = s;
		}
		else
		{
			int i;
			pointer it = hashtable[index];
			for (i = 0; i < 3; i++)
			{
				if (it->data[i] == 0)
					break;
			}
			if (i == 3)
			{
				pointer s = new BucketNode(key);
				s->link = hashtable[index];
				hashtable[index] = s;
			}
			else
			{
				it->data[i] = key;
			}
		}
	}

	void Remove(const Type &key) 
	{}
	pointer find(const Type &key)
	{}

	void ShowHash()const
	{
		for (int i = 0; i<HASH_TABLE_SIZE; ++i)
		{
			std::cout << i << " : ";
			pointer p = hashtable[i];
			while (p)
			{
				std::cout << p->data << "-->";
				p = p->link;
			}
			std::cout << "Nul." << std::endl;
		}
	}
protected:
	int Hash(const Type &key)
	{
		return key % HASH_TABLE_SIZE;
	}
private:
	enum { HASH_TABLE_SIZE = 7 };
	static pointer hashtable[HASH_TABLE_SIZE]; //vector
};

BucketNode* HashTable::hashtable[HASH_TABLE_SIZE] =
{ 0,0,0,0,0,0,0 };