#include "SetIterator.h"
#include "Set.h"

#include <iostream>


SetIterator::SetIterator(const Set& s) : set(s)
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)
	
	first();
}


void SetIterator::first() 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)
	current = set.first;
}


void SetIterator::next() 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)
	
	if (!valid()) 
	{
		throw std::exception();
	}
	else 
	{
		this->current = this->set.nextLink[this->current];
	}
}


TElem SetIterator::getCurrent()
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)
	
	if (!valid()) 
	{
		throw std::exception();
	}
	else 
	{
		return this->set.e[this->current];
	}
}

bool SetIterator::valid() const 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	//return (this->current != -1);
	// Return true if the current node is a valid node index, false otherwise
	return current >= 0 && current < set.capacity&& set.prevLink[current] != -2;
}



