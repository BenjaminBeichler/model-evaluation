/*
 * determ_supervised_targets.hpp
 *
 *  Created on: 07.07.2013
 *      Author: benni
 */

#ifndef DETERM_SUPERVISED_TARGETS_HPP_
#define DETERM_SUPERVISED_TARGETS_HPP_
#include <systemc>
#include "step_function.hpp"
#include "ma.hpp"
#include <vector>

struct supervised_target
{
	double begin;
	double permitted_speed;
	bool is_MRSP_target;
	supervised_target(double _begin,double _permitted_speed,bool _is_MRSP_target)
	{
		begin = _begin;
		permitted_speed = _permitted_speed;
		is_MRSP_target = _is_MRSP_target;

	}
};

SC_MODULE(determ_supervised_targets)
{


	sc_core::sc_in<step_function> mrsp;
	sc_core::sc_in<movement_authority> ma;
	sc_core::sc_in<double> max_safe_front_end;


	sc_core::sc_out<double> target_position;
	sc_core::sc_out<double> target_speed;

	std::vector<supervised_target> targets;



	SC_CTOR(determ_supervised_targets)
		{
			SC_METHOD(eval);
		}


	void eval();


};

#endif /* DETERM_SUPERVISED_TARGETS_HPP_ */
