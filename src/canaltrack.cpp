/********************************************//**
 * \file   canaltrack.cpp
 * \author Kacper Kowalski
 ***********************************************/

#include "sc.h"

//Inicjalizacja pola were_to_port powoduje, ze czas przeplyniecia toru, ktory bedzie wyliczony jako pierwszy, bedzie o 5min dluzszy niz powinien.
CanalTrack::CanalTrack(int d) : deepness(d), total_use_time(0), is_busy(false), were_to_port(true), last_use_time(0), actualShipPtr(NULL), actual_track_use_time (0){}

CanalTrack::~CanalTrack()
{
	if(actualShipPtr)
	{
		delete actualShipPtr;
		actualShipPtr = NULL;
	}
}

bool CanalTrack::is_track_aval()
{
	return !is_busy;
}

void CanalTrack::update_track_lut()
{
	last_use_time = global_time;
}


enum CanalState CanalTrack::check_actual_state(Ship *sPtr)
{
	if((global_time - last_use_time) > ACTIVE_TIME)
		return NotUsed;
	if(sPtr->inf_direction() == were_to_port)
		return SameWay;
	else
		return OppositeWay;
}

double CanalTrack::calc_swim_time()
{
	/*
	 *	Logarytm o podstawie 5 z masy obliczono wg wlasnosci:
	 * 	Logarytm o podstawie a z liczby x jest rowny ilorazowi
	 * 	logarytmu o podstawie b z liczby x i logarytmu o podstawie b z liczby a
	 *
	 */
	int temp_weight = actualShipPtr->inf_weight();

	double temp = (9.5 + (temp_weight)/1000 * log10(temp_weight/100) / log10(5) + (int)(check_actual_state(actualShipPtr)) * 5);

	actual_track_use_time = temp;

	return temp;
}


void CanalTrack::take_track(Ship *sPtr)
{
	actualShipPtr = sPtr;
	is_busy = true;
}

Ship* CanalTrack::track_leaving()
{
	Ship* sPtr = actualShipPtr;
	actualShipPtr = NULL;
	update_track_lut();

	total_use_time += actual_track_use_time;

	is_busy = false;

	were_to_port = sPtr->inf_direction();

	return sPtr;
}

bool CanalTrack::last_dir()
{
	return were_to_port;
}

void CanalTrack::get_statistics()
{
	overall_result << total_use_time/global_time * 100.0 << "%." << endl;
}
