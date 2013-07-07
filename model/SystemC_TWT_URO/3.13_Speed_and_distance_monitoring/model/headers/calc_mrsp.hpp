/*
 * calc_mrsp.hpp
 *
 *  Created on: 23.05.2013
 *      Author: benni
 */

#ifndef CALC_MRSP_HPP_
#define CALC_MRSP_HPP_
#include "static_speed_profile.hpp"
#include "axle_load_speed_profile.hpp"
#include "step_function.hpp"

#include <systemc>
#include <vector>

SC_MODULE(calc_mrsp)
{
	sc_core::sc_in<std::vector<static_speed_profile_element> > static_speed_profile;
	sc_core::sc_in<std::vector<axle_load_speed_profile_element> > axle_load_speed_profile;
	sc_core::sc_in<uint> train_related_max_speed;
	sc_core::sc_in<uint> train_cant_deficiency_category;
	sc_core::sc_in<uint> train_axle_load_category;
	sc_core::sc_in<uint> L_TRAIN;
	sc_core::sc_in<uint> NC_TRAIN;

	sc_core::sc_out<step_function> mrsp;


	SC_CTOR(calc_mrsp)
	{
		SC_METHOD(eval);
		sensitive << static_speed_profile;
		sensitive << axle_load_speed_profile;
		sensitive << train_related_max_speed;
	}

	void eval();
private:
	uint get_restrictive_speed_from_ssp(static_speed_profile_element ssp_elem);
	uint get_restrictive_speed_from_asp(axle_load_speed_profile_element asp_element);
	step_function &apply_axle_load_profile_to_mrsp(step_function &mrsp,std::vector<axle_load_speed_profile_element> &asp);
	step_function &apply_static_speed_profile_to_mrsp(step_function &mrsp,std::vector<static_speed_profile_element> &ssp);

};


#endif /* CALC_MRSP_HPP_ */
