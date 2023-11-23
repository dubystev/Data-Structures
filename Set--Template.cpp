// Set--Template.cpp : Defines the entry point for the console application.
//
//Copyright (C) ADUBI STEPHEN 21-07-2014

#include "stdafx.h"
#include <string>
#include <conio.h>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
struct Node
{
	T item;
	Node<T>* link;
};

template <class T>
class Set
{
	Node<T>* head;
	Node<T>* search(T target) const;

public:
	Set() {head = NULL;}
	Set(const Set<T>& a_Set);
	~Set();
	void add(T data);
	Set<T> Union(const Set<T>& otherSet);
	Set<T> Intersection(const Set<T>& otherSet);
	bool contains(T data) const;
	Set<T> difference(const Set<T>& otherSet);
	int Cardinality();
	void remove(T data);
	template <class T> friend ostream& operator <<(ostream& outs, const Set<T>& theSet);
};

template <class T>
Set<T>::Set(const Set<T>& a_Set)
{
	if(a_Set.head == NULL)
		head = NULL;
	else
	{
		Node<T>* temp = a_Set.head;
		Node<T>* end;
		end = new Node<T>;
		end->item = temp->item;
		head = end;

		temp = temp->link;
		while(temp != NULL)
		{
			end->link = new Node<T>;
			end = end->link;
			end->item = temp->item;
			temp = temp->link;
		}

		end->link = NULL;
	}
}

template<class T>
Set<T>::~Set( )
{
	Node<T> *toDelete = head;
	while (head != NULL)
	{
		head = head->link;
		delete toDelete;
		toDelete = head;
	}
}

template <class T>
Node<T>* Set<T>::search(T target) const
{
	Node<T> *iter = head;
	Node<T> *prev = head;
	while(iter != NULL)
	{
		if(iter->item == target)
			break;
		else
		{
			prev = iter;
			iter = iter->link;
		}
	}

	if(iter == NULL)
		prev = iter;

	return prev;
}

template <class T>
void Set<T>::add(T data)
{
	if(!contains(data))
	{
		Node<T>* temp = new Node<T>;
		temp->link = head;
		temp->item = data;
		head = temp;
	}
}

template <class T>
Set<T> Set<T>::Union(const Set<T>& otherSet)
{
	Set<T> newSet;
	Node<T>* iterator = head;
	while(iterator != NULL)
	{
		newSet.add(iterator->item);
		iterator = iterator->link;
	}

	iterator = otherSet.head;

	while(iterator != NULL)
	{
		newSet.add(iterator->item);
		iterator = iterator->link;
	}

	return newSet;
}

template <class T>
Set<T> Set<T>::Intersection(const Set<T>& otherSet)
{
	Set<T> newSet;
	Node<T>* iterator = head;
	while(iterator != NULL)
	{
		if(otherSet.contains(iterator->item))
			newSet.add(iterator->item);
		iterator = iterator->link;
	}

	return newSet;
}

template <class T>
bool Set<T>::contains(T data) const
{
	bool flag = false;
	Node<T>* iter;
	iter = search(data);
	if(iter != NULL)
		flag = true;

	return flag;
}

template <class T>
Set<T> Set<T>::difference(const Set<T>& otherSet)
{
	Set<T> newSet;
	Node<T>* iter = head;
	for(iter = head; iter != NULL; iter = iter->link)
	{
		if(!otherSet.contains(iter->item))
			newSet.add(iter->item);
	}

	return newSet;
}

template <class T>
int Set<T>::Cardinality()
{
	int counter = 0;
	Node<T>* iter = head;
	while(iter != NULL)
	{
		counter++;
		iter = iter->link;
	}

	return counter;
}

template <class T>
void Set<T>::remove(T target)
{
	Node<T>* before_me;
	Node<T>* after_me;
	if(this->contains(target))
	{
		Node<T>* toDelete = search(target);
		if((toDelete == head) && (toDelete->item == target))
		{
			head = toDelete->link;
			delete toDelete;
		}
		else
		{
			before_me = toDelete;
			toDelete = before_me->link;
			after_me = toDelete->link;
			before_me->link = after_me;
			delete toDelete;
		}
	}
}

template <class T>
ostream& operator <<(ostream& outs, const Set<T>& theSet)
{
	Node<T>* iter;
	iter = theSet.head;
	while(iter != NULL)
	{
		outs<<iter->item<<" ";
		iter = iter->link;
	}

	return outs;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Set<string> round; //round things
	Set<string> green; //green things

	round.add("Ball");
	round.add("Peas");
	round.add("Orange");
	round.add("Grape");
	green.add("Peas");
	green.add("Grass");
	green.add("Grass");
	green.add("Grape");

	cout<<"\n\nRound things: "<<round;
	cout<<"\n\nGreen things: "<<green;
	cout<<"\n\nBall in set round: "<<round.contains("Ball");
	cout<<"\n\nPeas in set round: "<<round.contains("Peas");
	cout<<"\n\nGrass in set green: "<<green.contains("Grass");
	cout<<"\n\nBall in set green: "<<green.contains("Ball");
	cout<<"\n\ncontents of set(round U green): "<<round.Union(green);
	cout<<"\n\ncontents of set(round ^ green): "<<round.Intersection(green);
	cout<<"\n\ngreen - round: "<<green.difference(round);
	cout<<"\n\nround - green: "<<round.difference(green);
	cout<<"\n\nNumber of items in set round: "<<round.Cardinality();
	cout<<"\n\nNumber of items in set green: "<<green.Cardinality();

	cout<<endl;
	_getch();
	return 0;
}

