#include "Stack.h"
#include <exception>
#include <cstdlib>
#include <iostream>


using namespace std;


Stack::Stack(int size) 
{
	arr = new int[size];
	capacity = size;
	top = -1;
}


void Stack::push(TElem e) 
{
	if (isFull())
	{
		cout << "Overflow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	cout << "Inserting" << e << endl;
	arr[top++] = e;
}

TElem Stack::top() const 
{
	if (isEmpty())
	{
		cout << "Underflow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	return NULL_TELEM;
}

TElem Stack::pop() 
{
	if (isEmpty())
	{
		cout << "Underflow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	cout << "Removing" << peek() << endl;

	return NULL_TELEM;
}


bool Stack::isEmpty() const 
{



	return false;
}

Stack::~Stack() 
{
	delete[] arr;
}