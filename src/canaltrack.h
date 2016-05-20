/********************************************//**
 * \file   canaltrack.h
 * \brief  Deklaracja klasy Canal reprezentujacej tor w kanale wodnym.
 * \author Kacper Kowalski
 ***********************************************/


#ifndef SRC_CANALTRACK_H_
#define SRC_CANALTRACK_H_

class Ship;

class CanalTrack
{
	//!Glebokosc toru.
	const int deepness;

	//!Akumulator czasu uzywania toru.
	double total_use_time;

	//!Zajetosc aktualna kanalu.
	bool is_busy;

	//!Kierunek ostatniego uzycia (jezeli prawda to tor byl wykorzystywany do wplyniecia, jezeli falsz to do wyplyniecia).
	bool were_to_port;

	//!Ostatni czas wyplyniecia z toru
	int last_use_time;

	//!Aktualnie znajdujacy sie statek w torze.
	Ship *actualShipPtr;

	//!Zmienna pomocnicza uzywana do zapamietania dlugosci czasu aktualnego przeplyniecia przez tor.
	int actual_track_use_time;

public:

	//!Konstruktor nadajacy glebokosc torowi.
	CanalTrack(int);

	//!Destruktor, w razie gdyby w momencie przerwania symulacji jakis statek znajdowal sie w torze.
	~CanalTrack();

	//!Sprawdzenie czy tor jest dostepny.
	bool is_track_aval();

	//!Aktualizacja ostatniego czasu uzycia.
	void update_track_lut();

	//!Sprawdzenie w jakim stanie znajduje sie tor, w zaleznosci od kierunku plyniecia statku.
	enum CanalState check_actual_state(Ship *);

	//!Przeliczenie czasu przeplyniecia przez tor.
	double calc_swim_time();

	//!Zajecie toru w kanale wodnym.
	void take_track(Ship *);

	//!Opuszczenie toru przez statek.
	Ship* track_leaving();

	//!Zwrocenie kirunku w ktorym ostatnio byl wykorzystany byl kanal
	bool last_dir();

	//!Wypisanie uzyskanych statystyk.
	void get_statistics();

	friend class Port;

};

#endif /* SRC_CANALTRACK_H_ */
