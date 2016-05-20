/********************************************//**
 * \file   dischargedev.h
 * \brief  Deklaracja typu enumeracyjnego reprezentujacego rozladunkowe i zaladunkowe narzedzia portowe. Liczby przypisane typom reprezentuja ilosc przenoszonego ladunku przez narzedzie.
 * \author Kacper Kowalski
 ***********************************************/


#ifndef SRC_DISCHARGEDEV_H_
#define SRC_DISCHARGEDEV_H_

enum DischargeDev{

	//!Trap/Rampa
	Ramp = 0,

	//!Dzwig
	Crane = 1,

	//!Tasmociag
	Carousel = 2,

	//!Prowadnica
	Gib = 3,

	//!Rurociag
	Pipeline = 4

};

#endif /* SRC_DISCHARGEDEV_H_ */
