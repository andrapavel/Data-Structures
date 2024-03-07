#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& mapionar) : map(mapionar) 
{
	//Complexity: best case:  Θ(1)
	//            worst case: O(n)
	//            avarage:    O(log n)

	current = map.root;
	while (current != nullptr && current->left != nullptr) 
	{
		stack.push(current);
		current = current->left;
	}
}

void SMIterator::first()
{
	//Complexity: best case:  Θ(1)
	//            worst case: O(h)
	//            avarage:    O(h)

	while (!stack.empty()) 
	{
		stack.pop();
	}
	current = map.root;
	while (current != nullptr && current->left != nullptr) 
	{
		stack.push(current);
		current = current->left;
	}
}

void SMIterator::next()
{
	//Complexity: best case:  Θ(1)
	//            worst case: O(h)
	//            avarage:    O(h)

	if (!valid())
		throw std::exception("Invalid iterator!");

	if (current->right != nullptr) 
	{
		current = current->right;
		while (current->left != nullptr) 
		{
			stack.push(current);
			current = current->left;
		}
	}
	else if (!stack.empty()) 
	{
		current = stack.top();
		stack.pop();
	}
	else 
	{
		current = nullptr;
	}
}

bool SMIterator::valid() const
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	return current != nullptr;
}

TElem SMIterator::getCurrent() const
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	if (!valid())
		throw exception("Invalid iterator!");

	return current->elem;
}


