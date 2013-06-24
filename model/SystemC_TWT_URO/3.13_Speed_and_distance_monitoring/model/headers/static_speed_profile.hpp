/*
 * static_speed_profile.hpp
 *
 *  Created on: 23.06.2013
 *      Author: benni
 */

#ifndef STATIC_SPEED_PROFILE_HPP_
#define STATIC_SPEED_PROFILE_HPP_
#include <vector>



struct static_speed_profile_subelement
{
	uint cant_deficiency_ssp_category;
	uint other_specific_ssp_category;
	uint max_speed;
};

enum SSP_category{
	CANT_DEFICIENCY_CATEGORY = 0,
	OTHER_CATEGORY_REPLACES_CANT = 1,
	OTHER_CATEGORY_NOT_REPLACES_CANT =2
};

struct static_speed_profile_element
{
	double begin;
	bool train_length_compansated;
	uint basic_max_speed;
	std::vector<static_speed_profile_subelement> ssp_category_elements;

};


#endif /* STATIC_SPEED_PROFILE_HPP_ */
