/*
 *	\file	 Events.cpp
 *	\author  Kacper Kowalski
 */

#include "sc.h"

Event::Event(double time) : next(NULL), prev(NULL), event_time(time) {}

int ShipArrives::hist_appear_interval[30];

double ShipArrives::mult_factor = 0.2;

//!Definicja destruktora w klasach dziedziczacych.
Event::~Event() {}

//!Pusta funkcja wirtualna, poniewaz klasa jest abstrakcyjna.
void Event::execute() {}

EventList::EventList() : first(NULL), last(NULL) {}

EventList::~EventList()
{
	if(!first) return;
	last = NULL;
	while(first->next)
	{
		first = first->next;
		delete first->prev;
	}
	delete first;
	first = NULL;

}

void EventList::add_Event(Event *ePtr)
{
	if(!ePtr) assert(false);
	if(!first)
	{
		first = last = ePtr;
		return;
	}
	if(ePtr->event_time > first->event_time)
	{
		first->prev = ePtr;
		ePtr->next = first;
		first = first->prev;
		return;
	}
	Event *temp = first;
	while(temp->next)
	{
		if(ePtr->event_time >= temp->next->event_time)
		{
			ePtr->next = temp->next;
			ePtr->prev = temp;
			ePtr->prev->next = ePtr;
			ePtr->next->prev = ePtr;
			return;
		}
		temp = temp->next;
	}

	temp->next = ePtr;
	ePtr->prev = temp;
	last = last->next;
}

Event* EventList::throw_last()
{
	if(!first) return NULL;
	Event *tempEventPtr = last;
	if(first == last)
	{
		first = last = NULL;
		return tempEventPtr;
	}
	last = last->prev;
	tempEventPtr->prev = NULL;
	last->next = NULL;
	return tempEventPtr;
}

ShipArrives::ShipArrives(double time) : Event(time) {

	int temp = (int)((time - global_time) * mult_factor);
	if(temp >= 30) return;
	hist_appear_interval[temp]++;
}

ShipServEnd::ShipServEnd(double time) : Event(time) {}

ShipTrackQuitIn::ShipTrackQuitIn(double time, int t_nr) : Event(time), track_nr(t_nr) {}

ShipTrackQuitOut::ShipTrackQuitOut(double time, int t_nr) : Event(time), track_nr(t_nr) {}


void ShipArrives::execute()
{
	Agenda->add_Event(new ShipArrives(global_time + Exponential(expDistIntensity, shipGenTimeSeed)));

	Ship *sPtr = MainPort->generate_ship();

	MainPort->add_toDevQueue(sPtr);
}

void ShipTrackQuitIn::execute()
{
	Ship *sPtr = MainPort->on_track_leavingIn(track_nr);

	MainPort->add_toinPortQueue(sPtr);

	Agenda->add_Event(new ShipServEnd(sPtr->inf_serv_end_time()));
}

void ShipServEnd::execute()
{
	Ship *sPtr = MainPort->on_serv_ending();

	//Je¿eli doszlo do zaladunku.
	if(!sPtr)
	{
		Agenda->add_Event(new ShipServEnd(MainPort->inf_last_service_end_time()));
		return;
	}

	MainPort->add_toCanalQueue(sPtr);
}

void ShipTrackQuitOut::execute()
{
	Ship *sPtr = MainPort->on_track_leavingOut(track_nr);

	delete sPtr;
}



