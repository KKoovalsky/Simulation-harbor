/********************************************//**
 * \file   	ship.h
 * \brief	Deklaracja klasy Ship i klas potomnych reprezentujacych statki wplywajace do portu.
 * \author	Kacper Kowalski
 ***********************************************/


#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_

class Ship
{
protected:

	//Wskazniki potrzebne do zaimplementowania kolejki.
	Ship *next, *prev;

	//!Moment konca obslugi w porcie.
	double serv_end_time;

	//!Moment pojawienia sie statku.
	const double appear_time;

	//!Moment wejscia statku do kanalu.
	double canal_impact_time;

	//!Górna i dolna granica masy statku.
	const int weight_low_bound, weight_high_bound;

	//!Prawdopodobienstwo zaladunku.
	const double charge_prob;

	//!Masa statku.
	int weight;

	//!Indeks pozwalajacy na wskazanie, od którego kanalu mozna rozpatrywac przydzielenie statku.
	int idx_tracks_possible;

	//!Liczba narzedzi portowych potrzebnych do rozladunku/zaladunku statku.
	int dev_needed_amount;

	//!Narzedzia potrzebne do rozladunku/zaladunku.
	enum DischargeDev dev_needed;
	enum DischargeCap dev_cap;

	//!Wplywanie/wyplywanie do portu.
	bool toPort;

	//!Obsluzono/nie obsluzono.
	bool were_serviced;

	/* !
	 *
	 * Indeks dla danego typu statku potrzebny do operowania na adresach do ziaren generatora oraz danych statystycznych:
	 *
	 * 0 - Roro
	 * 1 - Kontenerowiec I typu
	 * 2 - Kontenerowiec II typu
	 * 3 - Masowiec
	 * 4 - Zbiornikowiec
	 *
	 */
	enum ShipType ship_idx;

	//!Funkcja przyporzadkowujaca indeks do mozliwie najplytszego kanalu w ktory moze wplynac dany statek.
	void assign_track_idx(int);

public:

	//!Zmienna statyczna, dzieki ktorej na biezaco mozna sprawdzac sredni czas oczekiwania do obslugi statku, poza faza przejsciowa.
	static double mean_wait_time;

	//!Zmienna statyczna, dzieki ktorej na biezaco mozna sprawdzac sredni czas oczekiwania do obslugi statku.
	static double mean_wait_time_all_exp;

	//!Konstruktory.
	Ship(Ship *, Ship *, int, int, double, int, enum DischargeDev, enum DischargeCap, enum ShipType);

	//!Aktualizacja momentu wejscia statku do kanalu.
	void update_canal_impact_time();

	//A!ktualizacja konca czasu obslugi.
	void update_serv_end_time();

	//!Informacja o czasie konca obslugi.
	double inf_serv_end_time();

	//!Informacja o masie.
	int inf_weight();

	//!Informacja o najmniejszym indeksie do toru, ktory moze byc zajety przez dany statek.
	int inf_idx_tr_pos();

	//!Informacja o typie narzedzi potrzebnych do rozladunku/zaladunku.
	enum DischargeDev inf_dev_needed();

	//!Informacja o ilosci narzedzi danego typu potrzebnych do rozladunku/zaladunku.
	int inf_dev_needed_amount();

	//!Informacja o kierunku poruszania sie statku (do czy z portu).
	bool inf_direction();

	//!Losowanie ponownego zaladunku
	bool again_charge_inPort();

	friend class Queue;
	friend class PriorityQueue;
	friend class Port;
};

//!Klasa reprezentujaca masowiec.
class Bulk_Carrier : public Ship
{
public:
	Bulk_Carrier();

	friend class Port;
};


//!Klasa reprezentujaca kontenerowiec I typu.
class Container_Ship_I : public Ship
{
public:
	Container_Ship_I();

	friend class Port;
};


//!Klasa reprezentujaca kontenerowiec II typu
class Container_Ship_II : public Ship
{
public:
	Container_Ship_II();

	friend class Port;
};


//!Klasa reprezentujaca statek Ro-ro
class Ro_ro : public Ship
{
public:
	Ro_ro();

	friend class Port;
};

//!Klasa reprezentujaca zbiornikowiec.
class Tanker : public Ship
{
public:

	//!	Tablica pozwalajaca zebrac dane nt. rozkladu masy zbiornikowcow.
	static int hist_tanker_weight[20];

	Tanker();

	friend class Port;
};



#endif /* SRC_SHIP_H_ */
