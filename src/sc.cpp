/********************************************//**
 * \file   	sc.cpp
 * \brief	Glowny plik wykonawczy.
 * \author	Kacper Kowalski
 ***********************************************/


#include "sc.h"
#include "simulation.h"

//!Definicja zmiennych globalnych.
double global_time;

double total_wait_time[NUM_OF_SHIPS_TYPE];

double max_wait_time;

int ships_after_canal_impact[NUM_OF_SHIPS_TYPE];

int ships_generated;

int ships_generated_type[NUM_OF_SHIPS_TYPE];

int ships_after_track_impact;
int ships_after_track_impact_all_exp;

double expDistIntensity;

int steady_start;

int shipGenSeed;

int shipGenTimeSeed;

int weightSeed[NUM_OF_SHIPS_TYPE];
int chargeProbSeed[NUM_OF_SHIPS_TYPE];

ofstream mean_max_wait_time;
ofstream transient_phase;
ofstream overall_result;
ofstream hist_generators;
ofstream model_stats;
ofstream client_stats;

bool search_transient_phase = false;
bool gather_stats = true;

EventList *Agenda;

Port *MainPort;


int main()
{

	int num_of_sim = 10;

	int seeds[12];

	int seed = 1234, idx = 0;
	for(int i = 0; i < 12 * 10000; i++)
	{
		Uniform(seed);
		if(!(i % 10000))
		{
			seeds[idx++] = seed;
		}
	}

	shipGenSeed = seeds[0];
	shipGenTimeSeed = seeds[1];
	weightSeed[0] = seeds[2];
	weightSeed[1] = seeds[3];
	weightSeed[2] = seeds[4];
	weightSeed[3] = seeds[5];
	weightSeed[4] = seeds[6];
	chargeProbSeed[0] = seeds[7];
	chargeProbSeed[1] = seeds[8];
	chargeProbSeed[2] = seeds[9];
	chargeProbSeed[3] = seeds[10];
	chargeProbSeed[4] = seeds[11];

	ConfidenceIntervalEstimator MeanWaitTime;

	mean_max_wait_time.open("./output/mean_max_wait_time.csv", std::ios_base::out | std::ios_base::trunc);

	mean_max_wait_time << "Intensywnoœæ L" << ";" << "Czas koñca fazy przejœciowej" << ";"
			<< "Maksymalny czas oczekiwania" << ";" << "Œredni czas oczekiwania" << endl;


	model_stats.open("./output/model_stats.csv", std::ios_base::out | std::ios_base::trunc);

	model_stats << "intensity" << ";" << "mean_wait_time" << ";" << "delta" << endl;

	expDistIntensity = 0.076;


	for(int j = 0; j < 10; j++)
	{
		MeanWaitTime.reset();

		for(int i = 0; i < num_of_sim; i++)
		{

			client_stats.open(("./output/client_stats_" + to_string(static_cast<int>(j)) + "_" + to_string(static_cast<int>(i)) + ".csv").c_str(),
					std::ios_base::out | std::ios_base::trunc);

			client_stats << "service_duration" << endl;

			gather_stats = true;

			MainPort = new Port;

			Agenda = new EventList;

			simulation();

			mean_max_wait_time << expDistIntensity << ";" << steady_start << ";";

			MainPort->get_part_statistics();

			MeanWaitTime.add_realization(Ship::mean_wait_time/ships_after_track_impact);

			MainPort->reset_all_statistic();

			delete MainPort;

			delete Agenda;

			client_stats.close();
		}

		model_stats << expDistIntensity << ";" << MeanWaitTime.get_mu() << ";" <<
				MeanWaitTime.get_delta(ConfidenceIntervalEstimator::alpha0_005) << endl;

		expDistIntensity += 0.003;
	}

	model_stats.close();

	mean_max_wait_time.close();

	transient_phase.open("./output/transient_phase.csv", std::ios_base::out | std::ios_base::trunc);
	search_transient_phase = true;

	transient_phase << "Liczba statków po wp³yniêciu do kana³u" << ";" << "Œredni czas oczekiwania na wp³yniêcie" << endl;

	expDistIntensity = 0.09;

	MainPort = new Port;

	Agenda = new EventList;

	simulation();

	transient_phase.close();



	overall_result.open("./output/overall_result.txt", std::ios_base::out | std::ios_base::trunc);

	overall_result << "Symulacja przeprowadzona dla intensywnoœci L: " << expDistIntensity << endl;

	MainPort->get_statistics();

	overall_result.close();



	hist_generators.open("./output/hist_generators.csv", std::ios_base::out | std::ios_base::trunc);

	MainPort->get_hist_gen_statistic();

	hist_generators.close();




	delete MainPort;

	delete Agenda;



	return 0;
}


