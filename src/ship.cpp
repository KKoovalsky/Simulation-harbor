/********************************************//**
 * \file   	ship.cpp
 * \author	Kacper Kowalski
 ***********************************************/

#include "sc.h"

Ship::Ship(Ship *n, Ship *p, int w_L_b, int w_H_b, double a_c_p, int d_n_a,
		enum DischargeDev d_d, enum DischargeCap d_c, enum ShipType s_i) :
next(n), prev(p), serv_end_time(0.0), appear_time(global_time), canal_impact_time(0),
	 weight_low_bound(w_L_b), weight_high_bound(w_H_b), charge_prob(a_c_p), weight(-1), idx_tracks_possible(-1),
		 dev_needed_amount(d_n_a), dev_needed(d_d), dev_cap(d_c), toPort(true), were_serviced(false), ship_idx(s_i) {}

double Ship::mean_wait_time = 0.0;
double Ship::mean_wait_time_all_exp = 0.0;

int Tanker::hist_tanker_weight[20];

void Ship::assign_track_idx(int immersion)
{
	if(immersion <= 8)									//Przez zaokraglenie w gore, trzeba wziac pod uwage dla rownej glebokosci
	{
		idx_tracks_possible = 0;
		return;
	}
	if(immersion <= 12)
	{
		idx_tracks_possible = 1;
		return;
	}
	if(immersion < 20)
	{
		idx_tracks_possible = 2;
		return;
	}
	idx_tracks_possible = 3;
}

void Ship::update_canal_impact_time()
{
	canal_impact_time = global_time;

	double wait_time = (canal_impact_time - appear_time);

	if(wait_time > max_wait_time) max_wait_time = wait_time;

	total_wait_time[(int)ship_idx] += wait_time;

	mean_wait_time += wait_time;
	mean_wait_time_all_exp += wait_time;

	ships_after_track_impact++;
	ships_after_track_impact_all_exp++;

	ships_after_canal_impact[(int)ship_idx]++;

	if(search_transient_phase)
		transient_phase << ships_after_track_impact_all_exp << ";" << mean_wait_time_all_exp/ships_after_track_impact_all_exp << endl;

	if(!search_transient_phase && gather_stats)
		client_stats << mean_wait_time_all_exp/ships_after_track_impact_all_exp << endl;
}

enum DischargeDev Ship::inf_dev_needed()
{
	return dev_needed;
}

int Ship::inf_dev_needed_amount()
{
	return dev_needed_amount;
}

int Ship::inf_weight()
{
	return weight;
}

bool Ship::inf_direction()
{
	return toPort;
}

void Ship::update_serv_end_time()
{
	serv_end_time = global_time + (0.7 * weight) / ((int)dev_cap) / dev_needed_amount * 60.0;
}

double Ship::inf_serv_end_time()
{
	return serv_end_time;
}

int Ship::inf_idx_tr_pos()
{
	return idx_tracks_possible;
}

bool Ship::again_charge_inPort()
{
	were_serviced = true;
	if(Uniform(chargeProbSeed[(int)ship_idx]) < charge_prob)
	{
		return true;
	}
	else
	{
		weight = 0.3 * weight;
		idx_tracks_possible = 0; 			// najwieksza mozliwa waga * 0.3 < 8000 czyli kazdy statek po oproznieniu bedzie mogl zajac jakikolwiek kanal
		return false;
	}
}

Bulk_Carrier::Bulk_Carrier() : Ship(NULL, NULL, 1500, 15000, 0.2, -1 , Carousel, Carousel_C, Bulk) {

	weight = (int) Uniform(weightSeed[(int)ship_idx]) * (weight_high_bound - weight_low_bound) + weight_low_bound;
	int immersion = (int) (weight / 1000) + 1;
	dev_needed_amount = ((int)(weight/5000) + 1);
	assign_track_idx(immersion);
	ships_generated_type[(int)ship_idx]++;
}


Container_Ship_I::Container_Ship_I() : Ship(NULL, NULL, 500, 3000, 0.05, 1, Crane, Crane_C, Cont1) {

	weight = (int) (Uniform(weightSeed[(int)ship_idx]) * (weight_high_bound - weight_low_bound)) + weight_low_bound;
	int immersion = (int) (weight / 1000) + 1;
	assign_track_idx(immersion);
	ships_generated_type[(int)ship_idx]++;
}

Container_Ship_II::Container_Ship_II() : Ship(NULL, NULL, 3000, 12000, 0.02, -1, Gib, Gib_C, Cont2) {

	weight = (int) (Uniform(weightSeed[(int)ship_idx]) * (weight_high_bound - weight_low_bound)) + weight_low_bound;
	int immersion = (int) (weight / 1000) + 1;
	dev_needed_amount = (int)(weight/6000) + 1;
	assign_track_idx(immersion);
	ships_generated_type[(int)ship_idx]++;
}

Ro_ro::Ro_ro() : Ship(NULL, NULL, 500, 2500, 0.75, 2, Ramp, Ramp_C, Roro) {

	weight = (int) (Uniform(weightSeed[(int)ship_idx]) * (weight_high_bound - weight_low_bound)) + weight_low_bound;
	int immersion = (int) (weight / 1000) + 1;
	assign_track_idx(immersion);
	ships_generated_type[(int)ship_idx]++;
}

Tanker::Tanker() : Ship(NULL, NULL, 5000, 25000, 0.0, -1, Pipeline, Pipeline_C, Tank) {

	weight = (int) (Uniform(weightSeed[(int)ship_idx]) * (weight_high_bound - weight_low_bound)) + weight_low_bound;
	hist_tanker_weight[(int)((weight - weight_low_bound)/1000)]++;
	int immersion = (int) (weight / 1000) + 1;
	dev_needed_amount = (int)(weight/10000) + 1;
	assign_track_idx(immersion);
	ships_generated_type[(int)ship_idx]++;
}




