/********************************************//**
 * \file   	dischcapability.h
 * \brief	Typ enumeracyjny okreslajacy mozliwosci rozladunkowe danego typu narzedzi portowych.
 * \author	Kacper Kowalski
 ***********************************************/


#ifndef SRC_DISCHCAPABILITY_H_
#define SRC_DISCHCAPABILITY_H_

enum DischargeCap{

	//Trap/Rampa
	Ramp_C = 500,

	//Dzwig
	Crane_C = 600,

	//Tasmociag
	Carousel_C = 800,

	//Prowadnica
	Gib_C = 1000,

	//Rurociag
	Pipeline_C = 2000

};

#endif /* SRC_DISCHCAPABILITY_H_ */
