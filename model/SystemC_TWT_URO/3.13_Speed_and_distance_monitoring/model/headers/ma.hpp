/*
 * ma.hpp
 *
 *  Created on: 07.07.2013
 *      Author: benni
 */

#ifndef MA_HPP_
#define MA_HPP_
#include <systemc>

struct movement_authority
{
	uint level;
	uint V_LOA;
	uint T_LOA;

	bool dangerpoint_exist;
	uint D_DP;
	uint v_RELEASEDP;

	bool overlap_exist;
	uint D_STARTOL;
	uint T_OL;
	uint V_RELEASEOL;

	inline bool operator == (const movement_authority & rhs) const {
		return (level == rhs.level)&&
		(T_LOA == rhs.T_LOA)&&
		(V_LOA == rhs.V_LOA)&&
		(dangerpoint_exist == rhs.dangerpoint_exist)&&
		(D_DP == rhs.D_DP)&&
		(v_RELEASEDP == rhs.v_RELEASEDP)&&
		(overlap_exist == rhs.overlap_exist)&&
		(D_STARTOL == rhs.D_STARTOL)&&
		(T_OL == rhs.T_OL)&&
		(V_RELEASEOL == rhs.V_RELEASEOL);
	}
};
void sc_trace(sc_core::sc_trace_file *tf, const movement_authority &v, const std::string &NAME );
std::ostream& operator<<(std::ostream &os, const movement_authority &obj);


#endif /* MA_HPP_ */
