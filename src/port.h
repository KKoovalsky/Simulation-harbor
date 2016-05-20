/********************************************//**
 * \file   	port.h
 * \brief	Plik zawiera deklaracje klasy Port, reprezentujaca port.
 * \author	Kacper Kowalski
 ***********************************************/


#ifndef SRC_PORT_H_
#define SRC_PORT_H_

#define NUM_OF_DEV_TYPES 5
#define NUM_OF_TRACKS 4

class Queue;
class PriorityQueue;

class Port
{
	//!Calkowita liczba narzedzi portowych danego typu.
	const int total_dev_amount[NUM_OF_DEV_TYPES];

	/*!	Aktualnie dostepna liczba poszczegolnych narzedzi w porcie.
		Uzywana dla sprawdzenia dostepnosci urzadzen portowych. */
	int actual_dev_aval[NUM_OF_DEV_TYPES];

	//!Aktualnie uzywana liczba narzedzi w porcie.
	int actual_dev_used[NUM_OF_DEV_TYPES];

	//!Ostatni moment zmiany liczby urzadzen uzywanych.
	double dev_last_use_time[NUM_OF_DEV_TYPES];

	/*!	Akumulatory zliczajace czas uzywania poszczegolnych urzadzen portowych.
	 *	W celu obliczenia procentu wykorzystania kanalu nalezy po przeprowadzeniu symulacji
	 *	podzielic te wartosc przez calkowita liczbe narzedzi danego typu (odpowiedni indeks w total_dev_amount)
	 *	oraz czas symulacji(global_time).
	 */
	double dev_total_use_time[NUM_OF_DEV_TYPES];


public:

	//!Konstruktor domyslny.
	Port();

	//!Destruktor dla kolejek.
	~Port();

	//!Kolejki do poszczegolnych typow narzedzi.
	Queue* toDevQueue[NUM_OF_DEV_TYPES];

	//!Tory w kanale wodnym.
	CanalTrack *Tracks[NUM_OF_TRACKS];

	//!Kolejka do kanalu wodnego.
	Queue* toCanalQueueIn;
	Queue* toCanalQueueOut;

	//!Kolejka w porcie do konca obslugi
	PriorityQueue* inPortQueue;

	/*!	Zapytanie o dostepnosc narzedzi portowych.
		Gdy zwroci prawde, przydziela zasoby. */
	bool is_dev_aval(Ship*);

	//!Sprawdzenie czy port nie obsluguje zadnego ze statkow.
	bool is_inPortQueue_empty();

	//!Dodanie statku do kolejki do kanalu.
	void add_toCanalQueue(Ship *);

	//!Dodanie statku do kolejki do narzedzi.
	void add_toDevQueue(Ship *);

	//!Umieszczenie statku obslugiwanego.
	void add_toinPortQueue(Ship *);

	//!Wygenerowanie nowego statku.
	Ship* generate_ship();

	//!Metoda wywolywana przy opuszczeniu przez jeden ze statkow jednego z kanalow, przy wplywaniu do portu.
	Ship* on_track_leavingIn(int);

	//!Metoda wywolywana przy opuszczeniu przez jeden ze statkow jednego z kanalow, przy wyplywaniu z portu.
	Ship* on_track_leavingOut(int);

	//!Metoda wywolywana przy koncu obslugi statku.
	Ship* on_serv_ending();

	//!Zajecie toru
	void track_taking(int, Ship*);

	//!Informacja o ostatnim czasie obslugi.
	double inf_last_service_end_time();

	//!Wypisanie uzyskanych statystyk symulacji
	void get_statistics();

	//!Wypisanie statystyk dotyczacych maksymalnego i sredniego czasu oczekiwania na wplyniecie do toru
	void get_part_statistics();

	//!Wypisanie statystyk zwiazanych z rozkladami generowanymi przez generatory.
	void get_hist_gen_statistic();

	//!Wyzerowanie zmiennych globalnych statystycznych i statycznych
	void reset_statistic();
	void reset_all_statistic();
};

#endif /* SRC_PORT_H_ */
