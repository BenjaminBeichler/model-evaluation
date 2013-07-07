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
	mrsp_local[0] = train_related_max_speed;

	std::vector<axle_load_speed_profile_element> asp_local = axle_load_speed_profile.read();
	std::vector<static_speed_profile_element> ssp_local = static_speed_profile.read();

	// all profiles are considered to be sorted by there begin
	apply_axle_load_profile_to_mrsp(mrsp_local,asp_local);
	apply_static_speed_profile_to_mrsp(mrsp_local,ssp_local);

	mrsp.write(mrsp_local);

};


//TODO the way using at apply ssp is much more readably, convert this impl
step_function &calc_mrsp::apply_axle_load_profile_to_mrsp(step_function &mrsp,std::vector<axle_load_speed_profile_element> &asp)
{
	auto it_asp_tlc = asp.begin();
	while (it_asp_tlc != asp.end()) {
			// if the lowest category in profile is higher than train axle load category, delete restriction (see §3.11.4.4)
			if (it_asp_tlc->subelements[0].axle_load_category
					> train_axle_load_category) {
				continue;
			}

			double lowest_speed = get_restrictive_speed_from_asp(*it_asp_tlc);

			double end_axle_load_restriction = it_asp_tlc->begin
					+ it_asp_tlc->length;
			//
			if (it_asp_tlc->train_length_compansated) {
				end_axle_load_restriction += L_TRAIN;
			}

			//write old value on end of the modifications of current axle load speed restriction
			if (mrsp.get_value(end_axle_load_restriction) > lowest_speed) {
				mrsp[end_axle_load_restriction] = mrsp.get_value(
						end_axle_load_restriction);
			}

			auto mrsp_it = mrsp.get_iterator_on_step(
					end_axle_load_restriction);

			//iterate over the piece of mrsp, check whether this asp-element is more restictive
			while (mrsp_it != mrsp.get_begin_iterator()
					&& (mrsp_it->first >= it_asp_tlc->begin)) {
				if (mrsp_it->second > lowest_speed) {
					mrsp[mrsp_it->first] = lowest_speed;
				}
				mrsp_it--;
			}

			//place the first change of asp, when it is not on the boundary of the current iterator
			if (mrsp_it->first < it_asp_tlc->begin
					&& mrsp.get_value(it_asp_tlc->begin) > lowest_speed) {
				mrsp[it_asp_tlc->begin] = lowest_speed;
			}

		}
	return mrsp;

}

step_function &calc_mrsp::apply_static_speed_profile_to_mrsp(step_function &mrsp,std::vector<static_speed_profile_element> &ssp)
{

	//convert ssp to step_function
	step_function ssp_step_function;

	//init this step_function also with train max_speed, as every time restrictive speed, could theoretically be +infinity
	ssp_step_function[0]=train_related_max_speed;


	for(auto i = ssp.begin();i!= ssp.end(); i++)
	{
		//TODO ISSUE: if ssp elements are smaller than train length, there are much more complicated cornercases, because it has to be looked all ssp-elements in train length
		if((i-1)->train_length_compansated)
		{
			ssp_step_function[i->begin] = std::min(get_restrictive_speed_from_ssp(*i),
					std::min(get_restrictive_speed_from_ssp(*(i-1)),train_related_max_speed.read()));

			ssp_step_function[i->begin+L_TRAIN] = std::min(get_restrictive_speed_from_ssp(*i),train_related_max_speed.read());
		}
		else
		{
			ssp_step_function[i->begin] = std::min(get_restrictive_speed_from_ssp(*i),train_related_max_speed.read());
		}


	}

	step_function::max_of_both(mrsp,mrsp,ssp_step_function);

	return mrsp;



}
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
