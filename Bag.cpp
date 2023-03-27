#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;

Bag::Bag()
{
	this->capacity = 2;
	this->uniqueCapacity = 2;
	this->length = 0;
	this->uniqueLength = 0;
	this->unique = new TElem[this->uniqueCapacity];
	this->positions = new TElem[this->capacity];
}


// Theta(new capacity)
TElem* Bag::resize(TElem* arr, int& capacity)
{
	int newCapacity = capacity * 2;
	TElem* aux = new TElem[newCapacity];
	for (int i = 0; i < capacity; i++)
		aux[i] = arr[i];
	capacity = newCapacity;

	delete[] arr;
	return aux;
}

// O(length of unique elements)
void Bag::add(TElem elem) 
{
	if (this->length == this->capacity)
		this->positions = this->resize(this->positions, this->capacity);

	if (this->uniqueLength == this->uniqueCapacity)
		this->unique = this->resize(this->unique, this->uniqueCapacity);

	int i = 0;
	while (i < this->uniqueLength)
	{
		if (this->unique[i] == elem)
			break;
		i++;
	}

	if (i >= this->uniqueLength)
		this->unique[this->uniqueLength++] = elem;
	this->positions[this->length++] = i;
}


// O(length of unique elements + 2 * length of positions)
bool Bag::remove(TElem elem) 
{
	int i = 0;
	while (i < this->uniqueLength)
	{
		if (this->unique[i] == elem)
			break;
		i++;
	}

	if (i >= this->uniqueLength)
		return false;

	int j = 0;
	while (j < this->length)
	{
		if (this->positions[j] == i)
			break;
		j++;
	}
	
	if (this->nrOccurrences(this->unique[i]) > 1)
		this->positions[j] = this->positions[--this->length];
	else
	{
		for (int x = 0; x < this->length; x++)
		{
			if (this->positions[x] == this->uniqueLength - 1)
			{
				this->positions[x] = i;
			}
		}
		this->positions[j] = this->positions[--this->length];
		this->unique[i] = this->unique[--this->uniqueLength];
	}

	return true;
}


// O(length of unique elements)
bool Bag::search(TElem elem) const 
{
	for (int i = 0; i < this->uniqueLength; i++)
		if (this->unique[i] == elem)
			return true;
	return false; 
}


// O(length of unique elements + length of positions)
int Bag::nrOccurrences(TElem elem) const 
{
	int nr = 0, i = 0;
	while (i < this->uniqueLength)
	{
		if (this->unique[i] == elem)
			break;
		i++;
	}
	if (i >= this->uniqueLength)
		return 0;

	for (int j = 0; j < this->length; j++)
	{
		if (this->positions[j] == i)
		{
			nr++;
		}
	}
	return nr;
}


// O(1)
int Bag::size() const 
{
	return this->length;
}


// O(1)
bool Bag::isEmpty() const 
{
	return (this->length == 0);
}


BagIterator Bag::iterator() const
{
	return BagIterator(*this);
}


Bag::~Bag() 
{
	delete[] this->unique;
	delete[] this->positions;
}

