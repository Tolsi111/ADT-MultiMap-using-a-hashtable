#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->currentPos = 0;
	this->currentNode = c.arr[currentPos];
	while (this->col.arr[this->currentPos] == NULL && valid())
	{
		this->currentPos++;
		this->currentNode = c.arr[currentPos];
	}
	/*
	* Best case: theta(1)
	* Worst case: theta(n)
	* Total complexity: O(n)
	*/
}

TElem MultiMapIterator::getCurrent() const{
	if (!valid())
		throw std::exception();
	return this->currentNode->elem;
	/*
	* theta(1)
	*/
}

bool MultiMapIterator::valid() const {
	if(this->currentPos < 0 || this->currentPos >= this->col.m)
		return false;
	return true;
	/*
	* theta(1)
	*/
}

void MultiMapIterator::next() {
	if (!valid())
		throw std::exception();
	if (this->currentNode->next)
		this->currentNode = this->currentNode->next;
	else
	{
		this->currentPos++;
		this->currentNode = this->col.arr[this->currentPos];
		while (!this->currentNode && valid())///look for the next valid node
		{
			this->currentPos++;
			this->currentNode = this->col.arr[this->currentPos];
		}
	}
	/*
	* Best case: theta(1)
	* Worst case: theta(n)
	* Total complexity: O(n)
	*/
}

void MultiMapIterator::first() {
	this->currentPos = 0;///start from the begining
	this->currentNode = this->col.arr[currentPos];
	while (this->col.arr[this->currentPos] == NULL && valid())///look for the first valid node
	{
		this->currentPos++;
		this->currentNode = this->col.arr[currentPos];
	}
	/*
	* Best case: theta(1)
	* Worst case: theta(n)
	* Total complexity: O(n)
	*/
}

