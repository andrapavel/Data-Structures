#pragma once
#include <utility>
#include <cmath>
#include <stdexcept>
#include <iostream>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define MAX_CAPACITY 30000
#define NULL_TVALUE -111111
#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111)
#define INITIAL_SIZE 8
class MapIterator;


struct Node 
{
	TKey key;
	TValue value;
	bool deleted;
};

class Map 
{
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

private:
	//TODO - Representation

	Node* nodes;
	int capacity;
	int m_size;

	int hash(TKey key) const 
	{
		return abs(key) % this->capacity;
	}

	int probe(int i) const 
	{
		return i * i;
	}

	int nextPosition(int currentPosition, int step) const 
	{
		return (currentPosition + step) % capacity;
	}


	void resize() 
	{
		Node* newNodes = new Node[this->capacity * 2];
		//std::fill(newNodes, newNodes + (capacity * 2),NULL_TVALUE);
		for (int i = 0; i < this->capacity; i++) 
		{
			if (!this->nodes[i].deleted && this->nodes[i].key != NULL_TVALUE) 
			{
				int j = 0;
				int index = this->hash(this->nodes[i].key);
				while (newNodes[(index + this->probe(j)) % (this->capacity * 2)].key != NULL_TVALUE) 
				{
					j++;
				}
				newNodes[(index + this->probe(j)) % (this->capacity * 2)] = this->nodes[i];
			}
		}
		delete[] this->nodes;
		this->nodes = newNodes;
		this->capacity *= 2;
	}


public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

	// destructor
	~Map();

};



