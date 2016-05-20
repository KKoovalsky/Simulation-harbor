/********************************************//**
 * \file   canalstate.h
 * \brief  Deklaracja typu enumeracyjnego reprezentujacego stan kanalu, zalezacy od czasu ostatniego uzycia oraz kierunku uzycia kanalu.
 * \author Kacper Kowalski
 ***********************************************/

#ifndef SRC_CANALSTATE_H_
#define SRC_CANALSTATE_H_

enum CanalState{
	//!Dla statku, ktory plynie w tym samym kierunku, co ostatni w danym kanale w ciagu ostatnich 10min.
	SameWay = -1,
	//!Gdy kanal nie byl uzywany przez ostatnie 10min.
	NotUsed = 0,
	//!Dla statku, ktory plynie w przeciwnym kierunku, co ostatni w danym kanale w ciagu ostatnich 10min.
	OppositeWay = 1
};



#endif /* SRC_CANALSTATE_H_ */
