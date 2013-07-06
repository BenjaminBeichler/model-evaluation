/*
 * calc_MRSP.cpp
 *
 *  Created on: 05.07.2013
 *      Author: benni
 */
#include "headers/calc_mrsp.hpp"
#include <algorithm>

void calc_mrsp::eval()
{
	step_function mrsp_local;

	//initialize with train max speed
	mrsp_local[0]=train_related_max_speed;

	// all profiles are considered to be sorted by there begin
	auto local_ssp = static_speed_profile.read();

	// axle load subelements are also considered to be sorted by there category
	auto local_asp = axle_load_speed_profile.read();
	auto it_ssp = local_ssp.begin();
	auto it_asp = local_asp.begin();


	// do train length compansation (add L_TRAIN to length when indicated) and remove non applicable axle load restrictions (to low axle load category)
	auto it_asp_tlc = local_asp.begin();
	while (it_asp_tlc != local_asp.end()) {
		// if the lowest category in profile is higher than train axle load category, delete restriction (see §3.11.4.4)
		if (it_asp_tlc->subelements[0].axle_load_category
				> train_axle_load_category) {
			it_asp_tlc = local_asp.erase(it_asp_tlc);
		} else {
			if (it_asp_tlc->train_length_compansated) {
				it_asp_tlc->length += L_TRAIN;
			}
			it_asp_tlc++;
		}

	}

	double iterated_position = 0;
	static_speed_profile_element current_active_ssp;


	if(it_ssp->begin < it_asp->begin)
	{
		iterated_position=it_ssp->begin;
		current_active_ssp = *it_ssp;
		mrsp_local[it_ssp->begin] = std::min(get_restrictive_speed_from_ssp(*it_ssp),train_related_max_speed.read());

	}
	if(it_ssp->begin > it_asp->begin)
	{
		iterated_position=it_asp->begin;
		mrsp_local[it_asp->begin]=std::min(get_restrictive_speed_from_asp(*it_asp),train_related_max_speed.read());
	}



	while(it_ssp != local_ssp.end() && it_asp != local_asp.end())
	{




	}



};

uint calc_mrsp::get_restrictive_speed_from_asp(axle_load_speed_profile_element asp_element)
{
	uint resulting_speed;
	for (auto i : asp_element.subelements)
	{
		if(i.axle_load_category <= train_axle_load_category)
			resulting_speed = i.max_speed;
		else
		{
			break;
		}
	}
	return resulting_speed;
}

uint calc_mrsp::get_restrictive_speed_from_ssp(static_speed_profile_element ssp_elem)
{
	uint resulting_cant = ssp_elem.basic_max_speed;
	uint resulting_other = ssp_elem.basic_max_speed;
	bool other_replaces_cant=false;
	uint resulting_other_repl = ssp_elem.basic_max_speed;

	for (auto i : ssp_elem.ssp_category_elements)
	{
		switch (i.ssp_category){
		//implements §3.11.3.2.3
		case CANT_DEFICIENCY_CATEGORY:
			if (i.cant_deficiency_ssp_category <= train_cant_deficiency_category)
			{
				resulting_cant = i.max_speed;
			}
			break;
		case OTHER_CATEGORY_REPLACES_CANT:
			//see §7.5.1.84 (Definition of NC_TRAIN)
			if ( (NC_TRAIN & 1 << i.other_specific_ssp_category) && resulting_other_repl > i.max_speed)
			{
				resulting_other_repl = i.max_speed;
				other_replaces_cant=true;
			}
		 break;
		case OTHER_CATEGORY_NOT_REPLACES_CANT:
			if ( (NC_TRAIN & 1 << i.other_specific_ssp_category) && resulting_other > i.max_speed)
			{
				resulting_other = i.max_speed;
			}
		};



	}

	//ISSUE:
	/*it is not clear from §3.11.3.2.6 whether the elements marked with OTHER_CATEGORY_NOT_REPLACES_CANT(⁼2)
	*should be taken into account if at least one OTHER_CATEGORY_REPLACES_CANT is there
	*/
	if(other_replaces_cant)
	{
		return resulting_other_repl;
	}
	else
	{
		return std::min(resulting_other,resulting_cant);
	}



};
