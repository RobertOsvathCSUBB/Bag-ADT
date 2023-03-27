#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->first();
}

void BagIterator::first()
{
	this->i = 0;
}


void BagIterator::next() 
{
	if (this->valid())
		this->i++;
	else
		throw exception();
}


bool BagIterator::valid() const 
{
	if (this->i < this->bag.size())
		return true;
	return false;
}



TElem BagIterator::getCurrent() const
{
	if (!this->valid())
		throw exception();
	return this->bag.unique[this->bag.positions[i]];
}
