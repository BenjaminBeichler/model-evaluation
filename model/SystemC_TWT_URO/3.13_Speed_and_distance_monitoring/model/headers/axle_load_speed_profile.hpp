/*
 * axle_load_speed_profile.hpp
 *
 *  Created on: 24.06.2013
 *      Author: benni
 */

#ifndef AXLE_LOAD_SPEED_PROFILE_HPP_
#define AXLE_LOAD_SPEED_PROFILE_HPP_
#include <vector>


struct axle_load_speed_profile_subelement{
	uint axle_load_category;
	uint max_speed;
};

struct axle_load_speed_profile_element
{
	double begin;
	double length;
	bool train_length_compansated;
	std::vector<axle_load_speed_profile_subelement>;
};


#endif /* AXLE_LOAD_SPEED_PROFILE_HPP_ */
