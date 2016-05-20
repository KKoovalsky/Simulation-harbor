/********************************************//**
 * \file   	sc.h
 * \brief	Glowny plik naglowkowy.
 * \author	Kacper Kowalski
 ***********************************************/

#ifndef SRC_SC_H_
#define SRC_SC_H_

//!Standardowe biblioteki C/C++.
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>

//!Uzyta standardowa przestrzen nazw.
using namespace std;

//!Pliki naglowkowe projektu.
#include "dischargedev.h"
#include "dischcapability.h"
#include "shiptype.h"
#include "canalstate.h"
#include "canaltrack.h"
#include "events.h"
#include "port.h"
#include "queue.h"
#include "ship.h"
#include "rng.h"
#include "confidenceintestimation.h"


//!Czas potrzebny do okreslenia wspolczynnika reprezentowanego przez metode actual_state w klasie reprezentujacej kanal.
#define ACTIVE_TIME 10

//!Liczba typow narzedzi w porcie.
#define NUM_OF_DEV_TYPES 5

//!Liczba torow w kanale wodnym
#define NUM_OF_TRACKS 4

//!Liczba typow statkow
#define NUM_OF_SHIPS_TYPE 5

//!Globalny czas symulacji.
extern double global_time;

//!Lista zdarzen.
extern EventList *Agenda;

//!Port
extern Port *MainPort;

//!Akumulatory zliczajace wszystkie czasy oczekiwania poszczegolnych typow statkow na obsluge.
extern double total_wait_time[NUM_OF_SHIPS_TYPE];

//!Najwiekszy czas oczekiwania na obsluge statku.
extern double max_wait_time;

//!Ilosc statkow poszczegolnych typow, ktore wplynely do kanalu wodnego.
extern int ships_after_canal_impact[NUM_OF_SHIPS_TYPE];

//!Ilosc wszystkich wygenerowanych statkow.
extern int ships_generated;

//!Ilosc wygenerowanych statkow poszczegolnych typow.
extern int ships_generated_type[NUM_OF_SHIPS_TYPE];

//!Zmienna globalna, okreslajaca liczbe statkow ktore juz wplynely do kanalu poza faza przejsciowa.
extern int ships_after_track_impact;

//!Zmienna globalna, okreslajaca liczbe statkow ktore juz wplynely do kanalu.
extern int ships_after_track_impact_all_exp;

//!Intensywnosc rozkladu wykladniczego, dla odstepow czasu pojawiania sie statkow.
extern double expDistIntensity;

//!Czas konca fazy przejsciowej.
extern int steady_start;

//------------------------------------------
//	Nasiona dla generatorow pseudolosowych.
//------------------------------------------

//!Dla typu statku generowanego.
extern int shipGenSeed;

//!Dla odstepow czasu pojawiania sie statkow.
extern int shipGenTimeSeed;

//!Dla masy statkow poszczegolnych typow.
extern int weightSeed[NUM_OF_SHIPS_TYPE];

//!Dla zaladowania statku w porcie.
extern int chargeProbSeed[NUM_OF_SHIPS_TYPE];

//!Zmienna boolowska odpowiedzialna za wyswietlanie na biezaca srednich czasow oczekiwania na wplynecie statku do kanalu.
extern bool search_transient_phase;

//!Zmienna boolowska odpowiadajaca za wskazywanie fazy przejsciowej
extern bool gather_stats;

//!Strumien wykorzystywany do zapisu srednich i maksymalnych czasow oczekiwania dla zadanej liczby symulacji
extern ofstream mean_max_wait_time;

//!Strumien wykorzystywany do znalezienia fazy przejsciowej.
extern ofstream transient_phase;

//!Strumien wykorzystywany do zapisania wynikow symulacji typu zajetosc nardzedzi, torow itp.
extern ofstream overall_result;

//!Strumien wykorzystywany do zapisania wartosci zwracanych przez generatory.
extern ofstream hist_generators;

//!Strumien wykorzystywany do wyznaczenia przedzialow ufnosci.
extern ofstream model_stats;

//!Strumien wykorzystywany do wyznaczenia statystyk zwiazanych ze statkami.
extern ofstream client_stats;

//!Funkcja zamieniajaca liczbe calkowita na lanuch tekstowy
//\author Krzystof Bakowski
template<class T>
inline string to_string(const T& t)
{
     ostringstream stream;
     stream << t;
     return stream.str();
}

#endif /* SRC_SC_H_ */
