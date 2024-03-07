#include "Set.h"
#include "SetITerator.h"

#include <iostream>


Set::Set() 
{
	//Complexity: best case:  Θ(1)
    //            worst case: Θ(1)
    //            avarage:    Θ(1)
    
    // initialize an empty set

    capacity = 16;
    e = new TElem[capacity];
    nextLink = new int[capacity];
    prevLink = new int[capacity];
    first = -1;
    firstEmpty = 0;
    for (int i = 0; i < capacity - 1; i++) {
        nextLink[i] = i + 1;
        prevLink[i + 1] = i;
    }
    prevLink[0] = -1;
    nextLink[capacity - 1] = -1;
    sizeSet = 0;
}

int Set::allocate()
{
    int newElement = firstEmpty;
    if (newElement != -1) 
    {
        firstEmpty = nextLink[firstEmpty];
        prevLink[newElement] = -1;
        nextLink[newElement] = -1;
    }
    return newElement;
}

void Set::deallocate(int i)
{
    prevLink[i] = -1;
    nextLink[i] = firstEmpty;
    firstEmpty = i;
}

int Set::createNode(TElem e)
{
    int poz = allocate();
    this->e[poz] = e;
    prevLink[poz] = -1;
    nextLink[poz] = -1;
    return poz;
}

void Set::resize() 
{
    int newCapacity = 2 * capacity;
    TElem* newElems = new TElem[newCapacity];
    int* newNextLink = new int[newCapacity];
    int* newPrevLink = new int[newCapacity];

    // Copy the elements and links from the old arrays to the new ones
    for (int i = 0; i < capacity; i++) {
        newElems[i] = e[i];
        newNextLink[i] = nextLink[i];
        newPrevLink[i] = prevLink[i];
    }

    // Initialize the rest of the new arrays
    for (int i = capacity; i < newCapacity; i++) {
        newNextLink[i] = i + 1;
        newPrevLink[i] = i - 1;
    }
    newNextLink[newCapacity - 1] = -1;
    newPrevLink[capacity] = -1;
    firstEmpty = capacity;

    // Update the set's properties
    capacity = newCapacity;
    delete[] e;
    delete[] nextLink;
    delete[] prevLink;
    e = newElems;
    nextLink = newNextLink;
    prevLink = newPrevLink;
}

bool Set::add(TElem elem) 
{
	//Complexity: best case:  Θ(1)
    //            worst case: Θ(n)
    //            avarage:    O(n)

    // Check if the element is already in the set
    int current = first;
    while (current != -1) 
    {
        if (e[current] == elem) 
        {
            return false;
        }
        current = nextLink[current];
    }

    // If we get here, the element is not in the set, so we need to add it
    int newNodeIndex = allocate();
    e[newNodeIndex] = elem;
    nextLink[newNodeIndex] = first;
    prevLink[newNodeIndex] = -1;
    if (first != -1) 
    {
        prevLink[first] = newNodeIndex;
    }
    first = newNodeIndex;
    sizeSet++;

    // If the set is full, resize it
    if (sizeSet == capacity) 
    {
        resize();
    }

    return true;

}


bool Set::remove(TElem elem) 
{
    //Complexity: best case:  Θ(1)
    //            worst case: Θ(n)
    //            avarage:    O(n)

    // Find the node corresponding to the given element
    int current = first;
    while (current != -1) 
    {
        if (e[current] == elem) 
        {
            // Remove the node
            if (prevLink[current] == -1) 
            {
                first = nextLink[current];
            }
            else 
            {
                nextLink[prevLink[current]] = nextLink[current];
            }
            if (nextLink[current] != -1) {
                prevLink[nextLink[current]] = prevLink[current];
            }
            deallocate(current);
            sizeSet--;
            return true;
        }
        current = nextLink[current];
    }
    return false;
}

bool Set::search(TElem elem) const 
{
    //Complexity: best case:  Θ(1)
    //            worst case: Θ(n)
    //            avarage:    O(n)
    
    // search for the element in the array
    /*int current = first;
    while (current != -1 && this->e[current] != elem)
        current = nextLink[current];

    return current != -1;*/

    int current = first;
    while (current != -1) 
    {
        if (e[current] == elem) 
        {
            return true;
        }
        current = nextLink[current];
    }
    return false;
}


int Set::size() const 
{
    //Complexity: best case:  Θ(1)
    //            worst case: Θ(1)
    //            avarage:    Θ(1)

    return sizeSet;
}


bool Set::isEmpty() const 
{
    //Complexity: best case:  Θ(1)
    //            worst case: Θ(1)
    //            avarage:    Θ(1)

    return sizeSet == 0;
}


Set::~Set() 
{
    //Complexity: best case:  Θ(1)
    //            worst case: Θ(1)
    //            avarage:    Θ(1)
    
   // Deallocate all nodes in the set
    int current = first;
    while (current != -1) 
    {
        int next = nextLink[current];
        deallocate(current);
        current = next;
    }
    delete[] e;
    delete[] nextLink;
    delete[] prevLink;
}


SetIterator Set::iterator() const 
{
    //Complexity: best case:  Θ(1)
    //            worst case: Θ(1)
    //            avarage:    Θ(1)

	return SetIterator(*this);
}


