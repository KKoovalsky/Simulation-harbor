/********************************************//**
 * \file   	queue.h
 * \brief	Deklaracja klasy Queue reprezentujaca kolejke (liste dwukierunkowa FIFO) oraz klasy Priority_Queue, ktora reprezentuje kolejke priorytetowa.
 * \author	Kacper Kowalski
 ***********************************************/


#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

class Ship;

class Queue
{
protected:
	//Pierwszy i ostatni element w kolejce.
	Ship *first, *last;

	//!Liczba statkow w kolejce.
	int ships_amount;

public:

	//Iterator
	Ship *itr;

	//!Konstruktor domyslny.
	Queue();

	//!Destruktor.
	virtual ~Queue();

	//!Dodanie statku do kolejki na poczatek.
	virtual void add(Ship *);

	//!Usuniecie statku, ktory byl najszybciej dodany, z kolejki.
	Ship* throw_first();

	//!Usuniecie statku, ktory byl najpozniej dodany, z kolejki.
	Ship* throw_last();

	//!Usuniecie statku pod indeksem itr.
	Ship* throw_itr();

	//!Informacja o dlugosci kolejki.
	int inf_length();

	//!Zaladowanie iteratora.
	void reset_itr();

	//!Przeciazenie operatora -- dla iteratora wewnatrz listy.
	void operator -- (int);

	//!Sprawdzenie czy kolejka jest pusta.
	bool is_empty();

	//!Zwrocenie wskaznika na ostatni element
	Ship *show_last();


	friend class Port;
};

class PriorityQueue : public Queue
{

public:

	/*!	Dodanie statku do kolejki wg priorytetu, ktorym jest
		suma czasu przebywania w kanale oraz czasu obslugi w porcie */
	void add(Ship *);

	//!	Informacja o czasie najszybszego ukonczenia obslugi.
	double inf_last_serv_end_time();

	friend class Port;
};

#endif /* SRC_QUEUE_H_ */
