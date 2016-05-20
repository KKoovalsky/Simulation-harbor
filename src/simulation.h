/*
 * 	\file	simulation.h
 * 	\brief	Petla symulacyjna.
 *  \author Kacper Kowalski
 */


#ifndef SRC_SIMULATION_H_
#define SRC_SIMULATION_H_

void simulation()
{
	Event *ePtr;

	Agenda->add_Event(new ShipArrives(global_time));


	while(ships_generated < 3000)
	{
		ePtr = Agenda->throw_last();

		global_time = ePtr->event_time;

		ePtr->execute();

		delete ePtr;

		for(int i = 0; i < NUM_OF_DEV_TYPES; i ++)
		{
			if(!MainPort->toDevQueue[i]->is_empty())
			{
				while(MainPort->is_dev_aval(MainPort->toDevQueue[i]->show_last()))
				{
					MainPort->add_toCanalQueue(MainPort->toDevQueue[i]->throw_last());
					if(MainPort->toDevQueue[i]->is_empty()) break;
				}
			}
		}

		for(int i = 0; i < NUM_OF_TRACKS; i++)
		{
			if(MainPort->Tracks[i]->is_track_aval())
			{
				Queue *qPtr;
				if(MainPort->Tracks[i]->last_dir())
					qPtr = MainPort->toCanalQueueIn;
				else
					qPtr = MainPort->toCanalQueueOut;

				qPtr->reset_itr();

				for(int j = 0; j < 2; j ++)
				{
					while(qPtr->itr)
					{
						if(i >= qPtr->itr->inf_idx_tr_pos())
						{
							MainPort->track_taking(i, qPtr->throw_itr());
							if(qPtr == MainPort->toCanalQueueIn)
								Agenda->add_Event(new ShipTrackQuitIn(global_time + MainPort->Tracks[i]->calc_swim_time(), i));
							else
								Agenda->add_Event(new ShipTrackQuitOut(global_time + MainPort->Tracks[i]->calc_swim_time(), i));
							break;
						}
						(*qPtr)--;
					}

					if(MainPort->Tracks[i]->is_track_aval())
					{
						if(qPtr == MainPort->toCanalQueueIn)
							qPtr = MainPort->toCanalQueueOut;
						else
							qPtr = MainPort->toCanalQueueIn;
						qPtr->reset_itr();
					}
					else break;
				}
			}
		}
	}



	MainPort->reset_statistic();

	steady_start = global_time;

	gather_stats = false;


	while(ships_generated < 10000)
	{
		ePtr = Agenda->throw_last();

		global_time = ePtr->event_time;

		ePtr->execute();

		delete ePtr;

		for(int i = 0; i < NUM_OF_DEV_TYPES; i ++)
		{
			if(!MainPort->toDevQueue[i]->is_empty())
			{
				while(MainPort->is_dev_aval(MainPort->toDevQueue[i]->show_last()))
				{
					MainPort->add_toCanalQueue(MainPort->toDevQueue[i]->throw_last());
					if(MainPort->toDevQueue[i]->is_empty()) break;
				}
			}
		}

		for(int i = 0; i < NUM_OF_TRACKS; i++)
		{
			if(MainPort->Tracks[i]->is_track_aval())
			{
				Queue *qPtr;
				if(MainPort->Tracks[i]->last_dir())
					qPtr = MainPort->toCanalQueueIn;
				else
					qPtr = MainPort->toCanalQueueOut;

				qPtr->reset_itr();
				for(int j = 0; j < 2; j ++)
				{
					while(qPtr->itr)
					{
						if(i >= qPtr->itr->inf_idx_tr_pos())
						{
							MainPort->track_taking(i, qPtr->throw_itr());
							if(qPtr == MainPort->toCanalQueueIn)
								Agenda->add_Event(new ShipTrackQuitIn(global_time + MainPort->Tracks[i]->calc_swim_time(), i));
							else
								Agenda->add_Event(new ShipTrackQuitOut(global_time + MainPort->Tracks[i]->calc_swim_time(), i));
							break;
						}
						(*qPtr)--;
					}

					if(MainPort->Tracks[i]->is_track_aval())
					{
						if(qPtr == MainPort->toCanalQueueIn)
							qPtr = MainPort->toCanalQueueOut;
						else
							qPtr = MainPort->toCanalQueueIn;
						qPtr->reset_itr();
					}
					else break;
				}
			}
		}
	}

}



#endif /* SRC_SIMULATION_H_ */
