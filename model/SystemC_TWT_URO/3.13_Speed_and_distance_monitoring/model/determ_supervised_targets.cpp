/*
 * determ_supervised_targets.cpp
 *
 *  Created on: 22.07.2013
 *      Author: benni
 */
#include "headers/determ_supervised_targets.hpp"
#include "headers/step_function.hpp"

void determ_supervised_targets::eval()
{
	step_function local_mrsp = mrsp.read();

	targets.clear();

	auto it = local_mrsp.get_iterator_on_step(max_safe_front_end.read());

	double last_mrsp_speed_restriction = it->second;

	for (; it != local_mrsp.get_end_iterator();it++)
	{
		if(last_mrsp_speed_restriction > it->second) targets.emplace_back(it->first,it->second,true);
	};

	if(ma.read().V_LOA == 0 )
	{
		targets.emplace_back(ma.read().D_DP, ma.read().V_LOA );

	}


};


