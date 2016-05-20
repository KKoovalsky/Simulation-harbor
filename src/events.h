/*
 * 	\file	events.h
 * 	\brief	Klasa reprezentujaca zdarzenia czasowe.
 *  \author Kacper Kowalski
 */

#ifndef SRC_EVENTS_H_
#define SRC_EVENTS_H_

class Event
{

	//WskaŸniki potrzebne do zaimplementowania listy zdarzeñ.
	Event *next, *prev;

public:

	//!Moment obs³ugi.
	double event_time;

	//!Konstruktor.
	Event(double);

	//Destruktor.
	virtual ~Event();


	virtual void execute() = 0;


	friend class EventList;
};

class EventList
{
	Event *first, *last;

public:

	//!Konstruktor.
	EventList();

	//!Destruktor.
	~EventList();

	//Dodanie zdarzenia do listy zdarzeñ.
	void add_Event(Event*);

	//Zwrócenie pierwszego w kolejnoœci zdarzenia do obs³u¿enia.
	Event* throw_last();


};

//!	Wydarzenie - gdy pojawia sie statek.
class ShipArrives : public Event
{
public:

	//! Tablica zbierajaca dane nt. rozkladu odstepu czasu pojawiania sie statkow.
	static int hist_appear_interval[30];

	static double mult_factor;

	ShipArrives(double);

	void execute();
};


//!	Wydarzenie - gdy statek wyplywa z kanalu, przed obsluga.
class ShipTrackQuitIn : public Event
{
	//!	Indeks do toru, ktory jest opuszczany.
	int track_nr;

public:

	//! Dodatkowy konstruktor w celu ustawienia indeksu do toru.
	ShipTrackQuitIn(double, int);

	void execute();
};


//!	Wydarzenie - gdy statek wyplywa z kanalu, po obsludze.
class ShipTrackQuitOut : public Event
{
	//!	Indeks do toru, ktory jest opuszczany.
	int track_nr;

public:

	//! Dodatkowy konstruktor w celu ustawienia indeksu do toru.
	ShipTrackQuitOut(double, int);

	void execute();
};

//!	Wydarzenie - gdy nastapil koniec obslugi statku.
class ShipServEnd : public Event
{
public:

	ShipServEnd(double);

	void execute();
};



#endif /* SRC_EVENTS_H_ */
