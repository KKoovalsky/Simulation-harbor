/********************************************//**
 * \file   	queue.cpp
 * \author	Kacper Kowalski
 ***********************************************/

#include "sc.h"

Queue::Queue() : first(NULL), last(NULL), ships_amount(0), itr(NULL) {}

Queue::~Queue()
{
	//Usuwanie elementow od poczatku kolejki.

	if(!first) return;
	last = itr = NULL;
	while(first->next)
	{
		first = first->next;
		delete first->prev;
	}
	delete first;
	first = NULL;
}

void Queue::add(Ship *sPtr)
{
	if(!sPtr) return;
	if(!first)
	{
		first = last = sPtr;
		ships_amount++;
		return;
	}
	sPtr->next = first;
	first = sPtr;
	sPtr->next->prev = first;
	ships_amount++;
}

Ship* Queue::throw_first()
{
	if(!first) return NULL;
	Ship* tempShipPtr = first;
	if(first == last)
	{
		first = last = NULL;
		ships_amount--;
		return tempShipPtr;
	}
	first = first->next;
	first->prev = NULL;
	tempShipPtr->next = NULL;
	ships_amount--;
	return tempShipPtr;
}

Ship* Queue::throw_last()
{
	if(!first) return NULL;
	Ship* tempShipPtr = last;
	if(first == last)
	{
		first = last = NULL;
		ships_amount--;
		return tempShipPtr;
	}
	last = last->prev;
	tempShipPtr->prev = NULL;
	last->next = NULL;
	ships_amount--;
	return tempShipPtr;
}

Ship* Queue::throw_itr()
{
	if(!itr) return NULL;
	if(itr == last)
	{
		itr = itr->prev;
		return throw_last();
	}
	if(itr == first)
	{
		itr = NULL;
		return throw_first();
	}
	Ship* tempShipPtr = itr;
	itr = itr->prev;
	itr->next = tempShipPtr->next;
	tempShipPtr->next->prev = itr;
	tempShipPtr->next = tempShipPtr->prev = NULL;
	ships_amount--;
	return tempShipPtr;
}

int Queue::inf_length()
{
	return ships_amount;
}

void Queue::reset_itr()
{
	itr = last;
}

void Queue::operator -- (int)
{
	if(!itr) assert(false);			//Program dziala niepoprawnie jezeli uzyto operatora -- gdy itr pokazuje na nic.
	itr = itr->prev;
}

bool Queue::is_empty()
{
	return ((ships_amount == 0) ? true : false);
}

Ship* Queue::show_last()
{
	return last;
}

void PriorityQueue::add(Ship *sPtr)
{
	if(!sPtr) return;
	if(!first)
	{
		first = last = sPtr;
		ships_amount++;
		return;
	}
	if(first->serv_end_time < sPtr->serv_end_time)
	{
		sPtr->next = first;
		first = sPtr;
		sPtr->next->prev = first;
		ships_amount++;
		return;
	}

	Ship* tempShipPtr = first->next;

	for(int i = 1; i < ships_amount; i++)
	{
		if(sPtr->serv_end_time >= tempShipPtr->serv_end_time)
		{
			sPtr->next = tempShipPtr;
			sPtr->prev = tempShipPtr->prev;
			sPtr->next->prev = sPtr->prev->next = sPtr;
			ships_amount++;
			return;
		}
		tempShipPtr = tempShipPtr->next;
	}

	//Do zrobienia w przypadku przejscia petli do konca.
	last->next = sPtr;
	sPtr->prev = last;
	last = last->next;
	ships_amount++;
}

double PriorityQueue::inf_last_serv_end_time()
{
	return last->inf_serv_end_time();
}



