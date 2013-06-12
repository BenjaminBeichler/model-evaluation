/*
 * supervision_limits.cpp
 *
 *  Created on: 13.06.2013
 *      Author: benni
 */
#include "headers/supervision_limits.hpp"


void Supervision_limits::calc_ceiling_supervision_limits()
{
	if(V_MRSP <= V_ebi_min)
	{
		d_V_ebi = dV_ebi_min;
	}
	else
	{
		const double c_ebi = (dV_ebi_max - dV_ebi_min)/(V_ebi_max - V_ebi_min);
		d_V_ebi = std::min(dV_ebi_min + c_ebi * (V_MRSP - V_ebi_min) ,dV_ebi_max);

	}
}

void Supervision_limits::braking_to_target()
{
	double T_traction = std::max(T_traction_cut_off - (T_warning + T_bs2),0.0);
	double T_berem = std::max(T_be - T_traction , 0.0);

	double A_est1 = A_est;
	double A_est2 = std::min(0.4,A_est.read());
	A_est2 = std::max(0.0,A_est2);

	//§3.13.9.3.2.10
	double V_delta0=V_ura;
	double V_delta1=A_est1 * T_traction;
	double V_delta2=A_est2 * T_berem;

	double V_bec = std::max((V_est + V_delta0 + V_delta1),V_target.read())+V_delta2;
	double D_bec = std::max((V_est + V_delta0 + (V_delta1/2.0)),V_target.read()) * T_traction
			+ (std::max((V_est + V_delta0 + V_delta1),V_target.read()) + V_delta2/2.0 ) * T_berem;


	//§3.13.9.3.2.12
	d_EBI= EBD.read().get_position_from_speed(V_bec) - D_bec;
	//3.13.9.3.3.2
	d_SBI2= EBD.read().get_position_from_speed(V_est) - V_est * T_bs2;

}

