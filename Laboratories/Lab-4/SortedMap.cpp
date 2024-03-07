#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;


SortedMap::SortedMap(Relation r) 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	this->r = r;
	this->root = nullptr;
	this->_size = 0;
}

TValue SortedMap::add(TKey k, TValue v) 
{
	//Complexity: best case:  O(log n)
	//            worst case: O(n) - for adding an element / for searching an element
	//            avarage:    O(1)

	// Create a new node with the given key-value pair
	Node* newNode = new Node;
	newNode->elem = make_pair(k, v);
	newNode->left = nullptr;
	newNode->right = nullptr;

	if (root == nullptr) 
	{
		// If the BST is empty, make the new node the root
		root = newNode;
		_size++;
		return NULL_TVALUE;
	}

	Node* current = root;
	Node* parent = nullptr;

	while (current != nullptr) 
	{
		if (current->elem.first == k) 
		{
			// If the key already exists, update the value and return the old value
			TValue oldValue = current->elem.second;
			current->elem.second = v;
			delete newNode;
			return oldValue;
		}
		parent = current;

		if (r(k, current->elem.first))
			// If the new key is less than the current node's key, go to the left subtree
			current = current->left;
		else
			// If the new key is greater than the current node's key, go to the right subtree
			current = current->right;
	}

	// Attach the new node as a child of the appropriate parent
	if (r(k, parent->elem.first))
		parent->left = newNode;
	else
		parent->right = newNode;

	_size++;
	return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const 
{
	//Complexity: best case:  O(1) - The best case occurs when the search key is equal to the key of the root node. In this case, 
	//                               the complexity is constant time
	//            worst case: O(n) - In the worst case, when the BST becomes degenerate (e.g., skewed tree), each search operation may 
	//                               require traversing through n nodes, resulting in linear time complexity
	//            avarage:    O(log n) - On average, when the keys are randomly distributed and the BST remains balanced, 
	//                                   the height of the BST remains logarithmic, resulting in logarithmic complexity for search operations

	Node* current = root;
	while (current != nullptr) 
	{
		if (current->elem.first == k)
			// If the current node's key matches the search key, return the corresponding value
			return current->elem.second;
		if (r(k, current->elem.first))
			// If the search key is less than the current node's key, go to the left subtree
			current = current->left;
		else
			// If the search key is greater than the current node's key, go to the right subtree
			current = current->right;
	}

	// If the key is not found, return NULL_TVALUE
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) 
{
	//Complexity: best case:  O(1) - The best case occurs when the element to be removed is the root node
	//            worst case: O(n) - In the worst case, when the BST becomes degenerate
	//            avarage:    O(log n) - On average, when the keys are randomly distributed and the BST remains balanced, 
	//                                   the height of the BST remains logarithmic

	Node* current = root;
	Node* parent = nullptr;
	while (current != nullptr) 
	{
		if (current->elem.first == k) 
		{
			if (current == root)
				root = removeNode(current); // Remove the current node and update the root if necessary
			else if (r(k, parent->elem.first))
				parent->left = removeNode(current); // Remove the current node and update the left child of the parent
			else
				parent->right = removeNode(current); // Remove the current node and update the right child of the parent

			_size--;
			TValue oldValue = current->elem.second;
			delete current;

			return oldValue;
		}
		parent = current;

		if (r(k, current->elem.first))
			current = current->left; // If the search key is less than the current node's key, go to the left subtree
		else
			current = current->right; // If the search key is greater than the current node's key, go to the right subtree
	}
	return NULL_TVALUE;
}

Node* SortedMap::removeNode(Node* node) 
{
	//Complexity: best case:  O(1) - The best case occurs when the node has no children (leaf node)
	//            worst case: O(log n) - The worst case occurs when the BST is completely balanced, 
	//                                   and we need to find the minimum element in the right subtree. 
	//                                   This requires traversing the height of the subtree, which is logarithmic in the number of nodes
	//            avarage:    O(log n) - On average, when the keys are randomly distributed and the BST remains balanced, 
	//                                   the height of the BST remains logarithmic 

	if (node->left == nullptr && node->right == nullptr)
		return nullptr; // If the node has no children, return nullptr

	if (node->left == nullptr)
		return node->right; // If the node has only a right child, return the right child

	if (node->right == nullptr)
		return node->left; // If the node has only a left child, return the left child

	// If the node has both left and right children
	Node* successor = minimum(node->right); // Find the successor (smallest key in the right subtree)
	node->elem = successor->elem; // Replace the node's element with the successor's element
	node->right = removeMinimum(node->right); // Remove the successor node from the right subtree

	return node;
}

TKey SortedMap::minimum() const
{
	//Complexity: best case:  O(1) - The best case occurs when the root node is the minimum key
	//            worst case: O(log n) - The worst case occurs when the BST is completely unbalanced (skewed) to the right. 
	//                                   In this case, we need to traverse the height of the BST to reach the leftmost node, 
	//                                   which is logarithmic in the number of nodes
	//            avarage:    O(log n) - On average, when the keys are randomly distributed and the BST remains balanced, 
	//                                   the height of the BST remains logarithmic
	
	if (root == nullptr)
		throw exception("The SortedMap is empty.");  // Throw an exception if the SortedMap is empty

	Node* current = root;

	while (current->left != nullptr)
		current = current->left;  // Traverse to the leftmost node (smallest key)

	return current->elem.first;  // Return the key of the leftmost node
}


Node* SortedMap::minimum(Node* node) const
{
	//Complexity: best case:  O(1)
	//            worst case: O(log n)
	//            avarage:    O(log n)

	if (node == nullptr)
		return nullptr;  // Return nullptr if the given node is nullptr (empty subtree)

	while (node->left != nullptr)
		node = node->left;  // Traverse to the leftmost node (smallest key) in the subtree

	return node;  // Return the node with the minimum key
}


Node* SortedMap::removeMinimum(Node* node)
{
	//Complexity: best case:  O(1)
	//            worst case: O(log n)
	//            avarage:    O(log n)

	if (node->left == nullptr)
		return node->right;  // If the left child is nullptr, return the right child (promote the right subtree)

	node->left = removeMinimum(node->left);  // Recursively remove the minimum node from the left subtree

	return node;  // Return the updated subtree
}


int SortedMap::size() const 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	return _size;
}

bool SortedMap::isEmpty() const 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	return _size == 0;
}

SMIterator SortedMap::iterator() const 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	return SMIterator(*this);
}

SortedMap::~SortedMap() 
{
	//Complexity: best case:  Θ(1)
	//            worst case: Θ(1)
	//            avarage:    Θ(1)

	destroyBST(root);
}

void SortedMap::destroyBST(Node* node)
{
	//Complexity: best case:  O(1)
	//            worst case: O(n)
	//            avarage:    O(n)

	if (node != nullptr)
	{
		destroyBST(node->left);   // Recursively destroy the left subtree
		destroyBST(node->right);  // Recursively destroy the right subtree
		delete node;              // Delete the current node
	}
}