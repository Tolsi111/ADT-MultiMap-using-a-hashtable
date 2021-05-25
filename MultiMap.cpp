#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
	this->nbElems = 0;
	this->m = 101;
	this->arr = new Node*[101];
	for (int i = 0; i < 101; i++)
		this->arr[i] = NULL;
	/*
	* theta(101)
	*/
}

void MultiMap::resize()
{
	int newCap = this->m * 2 + 1;
	Node** newArr = new Node * [newCap];

	for (int i = 0; i < newCap; i++)
		newArr[i] = NULL;

	for (int i = 0; i < this->m; i++)///reHash
	{
		while (this->arr[i] != NULL)
		{
			
			Node* newNode = new Node;///create the node to be added
			newNode->elem.first = this->arr[i]->elem.first;
			newNode->elem.second = this->arr[i]->elem.second;

			int hValue;///perform hFunction on the TKey
			if(newNode->elem.first < 0)
				hValue = (newNode->elem.first *-1) % newCap;
			else
				hValue = newNode->elem.first % newCap;

			if (newArr[hValue])///add
				newNode->next = newArr[hValue];
			else
				newNode->next = NULL;
			newArr[hValue] = newNode;

			this->arr[i] = this->arr[i]->next;
		}
	}

	for (int i = 0; i < this->m; i++)///delete the current data
		delete arr[i];
	delete[] arr;

	this->arr = newArr;
	this->m = newCap;

	/*
	* theta(n)
	*/
}

void MultiMap::add(TKey c, TValue v) {

	if (this->nbElems == this->m)
		resize();

	Node* newNode = new Node;///create the node to be added
	newNode->elem.first = c;
	newNode->elem.second = v;

	int hValue = hFunction(c);

	if (arr[hValue])
		newNode->next = arr[hValue];
	else
		newNode->next = NULL;

	arr[hValue] = newNode;///head = newNode;

	this->nbElems++;
	/*
	* theta(1)
	*/
}

bool MultiMap::remove(TKey c, TValue v) {
	
	int hValue = hFunction(c);

	if (arr[hValue] != NULL)///then, look for the TElem in the linked list
	{
		Node* current = arr[hValue];
		Node* prev = NULL;
		while (current && current->elem.second != v)
		{
			prev = current;
			current = current->next;
		}
		if (current == NULL)///the TElem was not in the linked list
		{
			delete[] current;
			return false;
		}
		else if(prev == NULL)///remove the head
		{
			arr[hValue] = arr[hValue]->next;
			this->nbElems--;
			delete[] current;
			delete[] prev;
			return true;
		}
		else///remove the link
		{
			prev->next = current->next;
			this->nbElems--;
			delete[] current;
			return true;
		}
	}
	else///the key is clearly not in there
		return false;
	/*
	* Best case: theta(1)
	* Worst case: theta(n)
	* Total complexity: O(n)
	*/
}

vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> result;
	int hValue = hFunction(c);
	Node* copyHead = arr[hValue];
	while (copyHead)
	{
		if (copyHead->elem.first == c)
			result.push_back(copyHead->elem.second);

		copyHead = copyHead->next;
	}
	//delete[] copyHead;

	return result;

	/*
	* Best case: theta(1)
	* Worst case: theta(n)
	* Total complexity: O(n)
	*/
}

int MultiMap::size() const {
	return this->nbElems;
	/*
	* theta(1)
	*/
}

bool MultiMap::isEmpty() const {
	if (this->nbElems == 0)
		return true;
	return false;
	/*
	* theta(1)
	*/
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
	for (int i = 0; i < this->m; i++)
		delete arr[i];
	delete[] arr;
	/*
	* theta(n)
	*/
}

