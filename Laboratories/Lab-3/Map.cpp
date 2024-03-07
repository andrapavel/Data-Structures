#include "Map.h"
#include "MapIterator.h"
#include <iostream>

Map::Map()
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	this->capacity = MAX_CAPACITY;
	this->m_size = 0;
	this->nodes = new Node[this->capacity];
	for (int i = 0; i < this->capacity; i++) 
	{
		this->nodes[i].key = NULL_TVALUE;
		this->nodes[i].value = NULL_TVALUE;
		this->nodes[i].deleted = false;
	}
	
}

Map::~Map() 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	delete[] this->nodes;
	
}

TValue Map::add(TKey c, TValue v)
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(n)
	//            avarage:    O(n)

	//Check if the hash table is full
	if (m_size == capacity) 
	{
		// Hash table is full, can't add new element
		return NULL_TVALUE;
	}

	//Initialize linear probing counter
	int j = 0;

	//Compute initial position using hash function
	int position = hash(c);

	//Search for an available position using linear probing
	while (!nodes[position].deleted && nodes[position].key != NULL_TVALUE && nodes[position].key != c) 
	{
		j++;
		position = nextPosition(position, j);
	}

	//If key already exists, update value and return old value
	if (nodes[position].key == c) 
	{
		TValue oldValue = nodes[position].value;
		nodes[position].value = v;
		return oldValue;
	}
	//If key doesn't exist, insert key-value pair at available position
	else 
	{
		nodes[position].key = c;
		nodes[position].value = v;
		nodes[position].deleted = false;
		m_size++;
		return NULL_TVALUE;
	}

}

TValue Map::search(TKey c) const
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(n)
	//            avarage:    O(n)

	int j = 0;
	int position = hash(c);

	//Search for the key using linear probing
	while (!nodes[position].deleted && nodes[position].key != NULL_TVALUE && nodes[position].key != c) 
	{
		j++;
		position = nextPosition(position, j);
	}

	//If key is found, return its corresponding value
	if (nodes[position].key == c) 
	{
		return nodes[position].value;
	}
	//If key is not found, return null value
	else
	{
		return NULL_TVALUE;
	}

}

TValue Map::remove(TKey c)
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(n)
	//            avarage:    O(n)

	int j = 0;
	int position = hash(c);

	//Search for the key using linear probing
	while (!nodes[position].deleted && nodes[position].key != NULL_TVALUE && nodes[position].key != c) 
	{
		j++;
		position = nextPosition(position, j);
	}

	//If key is found, remove it and return its corresponding value
	if (nodes[position].key == c) 
	{
		TValue oldValue = nodes[position].value;
		nodes[position].key = NULL_TVALUE;
		nodes[position].value = NULL_TVALUE;
		nodes[position].deleted = true;
		m_size--;
		return oldValue;
	}
	//If key is not found, return null value
	else 
	{

		return NULL_TVALUE;
	}

}


int Map::size() const 
{
	//Complexity: best case:  Θ(1)
    //            worst case: Θ(1)
    //            avarage:    Θ(1)
	 
	return m_size;
	
}

bool Map::isEmpty() const
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	return m_size == 0;

}

MapIterator Map::iterator() const 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	return MapIterator(*this);
}



