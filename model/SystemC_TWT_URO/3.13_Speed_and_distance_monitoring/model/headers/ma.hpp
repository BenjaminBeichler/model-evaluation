/*
 * ma.hpp
 *
 *  Created on: 07.07.2013
 *      Author: benni
 */

#ifndef MA_HPP_
#define MA_HPP_
#include <systemc>

struct ma
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
};


#endif /* MA_HPP_ */
