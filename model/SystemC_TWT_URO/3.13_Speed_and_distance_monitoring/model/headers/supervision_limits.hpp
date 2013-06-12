/*
 * supervision_limits.hpp
 *
 *  Created on: 12.06.2013
 *      Author: benni
 */

#ifndef SUPERVISION_LIMITS_HPP_
#define SUPERVISION_LIMITS_HPP_
#include <systemc>
#include "parabola_curve.hpp"
#include "fixed_values.hpp"

SC_MODULE(Supervision_limits)
{
	sc_core::sc_in<parabola_curve> EBD;

	sc_core::sc_in<double> V_MRSP;

	sc_core::sc_out<double> d_V_ebi;


	SC_CTOR(Supervision_limits)
	{

	}


	void calc_ceiling_supervision_limits();


};


#endif /* SUPERVISION_LIMITS_HPP_ */
