/*
 * determ_supervised_targets.hpp
 *
 *  Created on: 07.07.2013
 *      Author: benni
 */

#ifndef DETERM_SUPERVISED_TARGETS_HPP_
#define DETERM_SUPERVISED_TARGETS_HPP_
#include <systemc>

SC_MODULE(determ_supervised_targets)
{


	sc_core::sc_in<step_function> mrsp;
	sc_core::sc_in<movement_authority> ma;
	sc_core::sc_in<double> max_safe_front_end;


	sc_core::sc_out<double> target_position;
	sc_core::sc_out<double> target_speed;



	SC_CTOR(determ_supervised_targets)
		{
			SC_METHOD(eval);
		}


	void eval();


};

#endif /* DETERM_SUPERVISED_TARGETS_HPP_ */
