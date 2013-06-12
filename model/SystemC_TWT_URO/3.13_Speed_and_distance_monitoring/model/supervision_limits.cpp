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
		double d_V_ebi_help = dV_ebi_min + c_ebi * (V_MRSP - V_ebi_min);

		if(d_V_ebi_help < dV_ebi_max)
		{
			d_V_ebi = d_V_ebi_help;
		}
		else
		{
			d_V_ebi = dV_ebi_max;
		}
	}
}

