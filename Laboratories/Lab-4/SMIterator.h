#pragma once
#include "SortedMap.h"
#include <stack>

//DO NOT CHANGE THIS PART
class SMIterator
{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	Node* current;
	std::stack<Node*> stack;


public:

	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

