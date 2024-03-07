#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	first();
}

// Move the iterator to the first node in the table
void MapIterator::first() 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(n)
	//            avarage:    O(n)

	currentPosition = 0;
	currentCount = 0;
	while (currentCount < map.m_size && map.nodes[currentPosition].deleted) 
	{
		currentPosition++;
	}

}

// Move the iterator to the next non-deleted node in the table
void MapIterator::next() 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(n)
	//            avarage:    O(n)

	if (!valid()) 
	{
		throw std::runtime_error("Invalid iterator state");
	}

	currentCount++;
	currentPosition++;
	while (currentPosition < map.capacity && (map.nodes[currentPosition].deleted || map.nodes[currentPosition].key == NULL_TVALUE)) 
	{
		currentPosition++;
	}

}


TElem MapIterator::getCurrent()
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	if (!valid()) 
	{
		throw std::runtime_error("Invalid iterator state");
	}

	return TElem(map.nodes[currentPosition].key, map.nodes[currentPosition].value);

}


bool MapIterator::valid() const 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	return currentCount < map.m_size;

}



