/********************************************//**
 * \file   	port.cpp
 * \author	Kacper Kowalski
 ***********************************************/


/*! \brief
 *
 *
 *	Przyjeto indeksy dla tablic odpowiadajace:
 *	0 - Trap/rampa (Ramp)
 *	1 - Dzwig (Crane)
 *	2 - Tasmociag (Carousel)
 *	3 - Prowadnice (Gib)
 *	4 - Rurociag (Pipeline)
 *
 *
 */

#include "sc.h"

Port::Port() : total_dev_amount{10, 5, 4, 8, 12}
{
	actual_dev_aval[0] = 10;
	actual_dev_aval[1] = 5;
	actual_dev_aval[2] = 4;
	actual_dev_aval[3] = 8;
	actual_dev_aval[4] = 12;

	for(int i = 0; i < NUM_OF_DEV_TYPES; i++)
	{
		toDevQueue[i] = new Queue();
		dev_last_use_time[i] = 0.0;
		dev_total_use_time[i] = 0.0;
		actual_dev_used[i] = 0;
	}

	Tracks[0] = new CanalTrack(8);
	Tracks[1] = new CanalTrack(12);
	Tracks[2] = new CanalTrack(20);
	Tracks[3] = new CanalTrack(25);

	toCanalQueueIn = new Queue();
	toCanalQueueOut = new Queue();
	inPortQueue = new PriorityQueue();
}

Port::~Port()
{
	for(int i = 0; i < NUM_OF_TRACKS; i++)
	{
		delete Tracks[i];
	}

	for(int i = 0; i < NUM_OF_DEV_TYPES; i++)
	{
		delete toDevQueue[i];
	}

	delete toCanalQueueIn;
	delete toCanalQueueOut;
	delete inPortQueue;

}



bool Port::is_dev_aval(Ship *sPtr)
{
	if(sPtr->inf_dev_needed_amount() > actual_dev_aval[(int)sPtr->inf_dev_needed()]) return false;
	else
	{
		int idx_dev = (int)sPtr->inf_dev_needed();
		dev_total_use_time[idx_dev] += ((global_time - dev_last_use_time[idx_dev]) * actual_dev_used[idx_dev]);
		dev_last_use_time[idx_dev] = global_time;
		actual_dev_aval[idx_dev] -= sPtr->inf_dev_needed_amount();
		actual_dev_used[idx_dev] += sPtr->inf_dev_needed_amount();
		return true;
	}
}

bool Port::is_inPortQueue_empty()
{
	return inPortQueue->is_empty();
}

Ship* Port::generate_ship()
{
	double rShip  = Uniform(shipGenSeed);
	ships_generated++;
	if(rShip < 0.2)
		return new Ro_ro;
	if(rShip < 0.3)
		return new Container_Ship_I;
	if(rShip < 0.5)
		return new Container_Ship_II;
	if(rShip < 0.75)
		return new Bulk_Carrier;
	return new Tanker;
}

void Port::add_toDevQueue(Ship *sPtr)
{
	toDevQueue[(int)sPtr->dev_needed]->add(sPtr);
}

void Port::add_toCanalQueue(Ship *sPtr)
{
	if(sPtr->toPort)
		toCanalQueueIn->add(sPtr);
	else
		toCanalQueueOut->add(sPtr);
}

void Port::add_toinPortQueue(Ship *sPtr)
{
	inPortQueue->add(sPtr);
}


Ship* Port::on_track_leavingIn(int idx_canal)
{
	Ship *sPtr = Tracks[idx_canal]->track_leaving();
	sPtr->toPort = false;

	sPtr->update_serv_end_time();
	return sPtr;
}

Ship * Port::on_track_leavingOut(int idx_canal)
{
	Ship *sPtr = Tracks[idx_canal]->track_leaving();
	return sPtr;
}

Ship* Port::on_serv_ending()
{
	Ship *sPtr = inPortQueue->throw_last();
	int idx_dev = (int)sPtr->dev_needed;

	//Mozliwosc ponownego zaladunku.
	if(!sPtr->were_serviced)
	{
		if(sPtr->again_charge_inPort())
		{
			sPtr->update_serv_end_time();
			inPortQueue->add(sPtr);
			return NULL;
		}
	}

	dev_total_use_time[idx_dev] += ((global_time - dev_last_use_time[idx_dev]) * actual_dev_used[idx_dev]);
	dev_last_use_time[idx_dev] = global_time;
	actual_dev_used[idx_dev] -= sPtr->dev_needed_amount;
	actual_dev_aval[idx_dev] += sPtr->dev_needed_amount;

	return sPtr;
}

void Port::track_taking(int canal_nr, Ship *sPtr)
{
	Tracks[canal_nr]->take_track(sPtr);
	if(Tracks[canal_nr]->actualShipPtr->inf_direction())
		Tracks[canal_nr]->actualShipPtr->update_canal_impact_time();
}

double Port::inf_last_service_end_time()
{
	return inPortQueue->inf_last_serv_end_time();
}

void Port::get_statistics()
{
	overall_result << endl << "Œredni czas oczekiwania dla statku typu:" << endl;
	overall_result << "RoRo: " << total_wait_time[0]/ships_after_canal_impact[0] << " min." << endl;
	overall_result << "Kontenerowca I typu: " << total_wait_time[1]/ships_after_canal_impact[1] << " min." << endl;
	overall_result << "Kontenerowca II typu: " << total_wait_time[2]/ships_after_canal_impact[2] << " min." << endl;
	overall_result << "Masowca: " << total_wait_time[3]/ships_after_canal_impact[3] << " min." << endl;
	overall_result << "Zbiornikowca: " << total_wait_time[4]/ships_after_canal_impact[4] << " min." << endl << endl;

	for(int i = 0; i < NUM_OF_TRACKS; i ++)
	{
		overall_result << "Tor " << i + 1 << ", procent wykorzystania: ";
		Tracks[i]->get_statistics();
	}

	overall_result << endl;

	overall_result << "Wykorzystanie procentowe narzêdzi: " << endl;
	overall_result << "Trap/Rampa: " << dev_total_use_time[0]/total_dev_amount[0]/global_time * 100.0 << "%." << endl;
	overall_result << "DŸwig: " << dev_total_use_time[1]/total_dev_amount[1]/global_time * 100.0 << "%." << endl;
	overall_result << "Taœmoci¹g: " << dev_total_use_time[2]/total_dev_amount[2]/global_time * 100.0 << "%." << endl;
	overall_result << "Prowadnica: " << dev_total_use_time[3]/total_dev_amount[3]/global_time * 100.0 << "%." << endl;
	overall_result << "Ruroci¹g: " << dev_total_use_time[4]/total_dev_amount[4]/global_time * 100.0 << "%." << endl;

	overall_result << endl;

	overall_result << "Maksymalny czas oczekiwania na wp³yniêcie do kana³u: " << max_wait_time << " min." << endl;
	overall_result << "Œredni czas oczekiwania na wp³yniêcie do kana³u: " << (total_wait_time[0] + total_wait_time[1] + total_wait_time[2] +
			total_wait_time[3] + total_wait_time[4])/ ships_after_track_impact << " min." << endl;

	overall_result << endl;
}

void Port::get_part_statistics()
{
	mean_max_wait_time << max_wait_time << ";" << (total_wait_time[0] + total_wait_time[1] + total_wait_time[2] +
			total_wait_time[3] + total_wait_time[4])/ ships_after_track_impact  << endl;

}

void Port::get_hist_gen_statistic()
{

	for(int i = 0; i < 30; i ++)
		hist_generators << (double)i/ShipArrives::mult_factor + 1.0/ShipArrives::mult_factor << ";" << ShipArrives::hist_appear_interval[i] << endl;

	hist_generators << endl << endl;

	for(int i = 0; i < 20; i ++)
		hist_generators << 5500 + i * 1000 << ";" << Tanker::hist_tanker_weight[i] << endl;

	hist_generators << endl << endl << "Procentowy udzia³ w wygenerowanych statkach statków typu [%]: " << endl;
	hist_generators << "Roro" << ";" << (double)ships_generated_type[0]/(double)ships_generated * 100.0 << endl;
	hist_generators << "Kontenerowiec I typu" << ";" << (double)ships_generated_type[1]/(double)ships_generated * 100.0 << endl;
	hist_generators << "Kontenerowiec II typu" << ";" << (double)ships_generated_type[2]/(double)ships_generated * 100.0 << endl;
	hist_generators << "Masowiec" << ";" << (double)ships_generated_type[3]/(double)ships_generated * 100.0 << endl;
	hist_generators << "Zbiornikowiec" << ";" << (double)ships_generated_type[4]/(double)ships_generated * 100.0 << endl;

}

void Port::reset_statistic()
{
	ships_after_track_impact = 0;

	for(int i = 0; i < NUM_OF_SHIPS_TYPE; i ++)
	{
		total_wait_time[i] = 0.0;
		ships_after_canal_impact[i] = 0;
	}

	Ship::mean_wait_time = 0.0;
}

void Port::reset_all_statistic()
{
	reset_statistic();

	global_time = 0.0;

	ships_generated = 0;

	max_wait_time = 0.0;

	Ship::mean_wait_time_all_exp = 0.0;

	ships_after_track_impact_all_exp = 0;

	for(int i = 0 ; i < NUM_OF_SHIPS_TYPE; i ++)
		ships_generated_type[i] = 0;

	for(int i = 0; i < 30; i ++)
		ShipArrives::hist_appear_interval[i] = 0;

	for(int i = 0; i < 20; i ++)
		Tanker::hist_tanker_weight[i] = 0;
}
