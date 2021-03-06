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
#include <algorithm>



SC_MODULE(Supervision_limits)
{

	const double c_ebi = (dV_ebi_max - dV_ebi_min)/(V_ebi_max - V_ebi_min);

	sc_core::sc_in<parabola_curve> EBD;

	sc_core::sc_in<double> V_MRSP;
	sc_core::sc_in<double> V_est;
	sc_core::sc_in<double> V_ura;
	sc_core::sc_in<double> V_target;
	sc_core::sc_in<double> T_traction_cut_off;
	sc_core::sc_in<double> T_bs2;
	sc_core::sc_in<double> T_be;

	sc_core::sc_in<double> A_est;

	//A_traction



	sc_core::sc_out<double> d_V_ebi_ceil;
	sc_core::sc_out<double> d_V_ebi_targ;

	sc_core::sc_out<double> d_EBI;
	sc_core::sc_out<double> d_SBI2;
	sc_core::sc_out<double> d_FLOI;


	SC_CTOR(Supervision_limits)
	{
		SC_METHOD(braking_to_target);

		sensitive << EBD;
		sensitive << V_est;
		sensitive << V_ura;
		sensitive << V_target;
		sensitive << T_traction_cut_off;
		sensitive << T_bs2;
		sensitive << T_be;
		sensitive << A_est;

		SC_METHOD(calc_ceiling_supervision_limits);
		sensitive << EBD;
		sensitive << V_MRSP;


	}


	void calc_ceiling_supervision_limits();
	void braking_to_target();

};


#endif /* SUPERVISION_LIMITS_HPP_ */
