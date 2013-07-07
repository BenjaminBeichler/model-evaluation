/*
 * static_speed_profile.hpp
 *
 *  Created on: 23.06.2013
 *      Author: benni
 */

#ifndef STATIC_SPEED_PROFILE_HPP_
#define STATIC_SPEED_PROFILE_HPP_
#include <vector>
#include <systemc>



struct static_speed_profile_subelement
{
	uint cant_deficiency_ssp_category;
	uint other_specific_ssp_category;
	uint max_speed;
	int ssp_category;

	inline bool operator == (const static_speed_profile_subelement & rhs) const {
	return (this->cant_deficiency_ssp_category == rhs.cant_deficiency_ssp_category) &&
			(this->other_specific_ssp_category == rhs.other_specific_ssp_category) &&
			(this->ssp_category == rhs.ssp_category) &&
			(this->max_speed == rhs.max_speed);

	}
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

	inline bool operator == (const static_speed_profile_element & rhs) const {
	      return (this->begin == rhs.begin) &&
	    		 (this->train_length_compansated == rhs.train_length_compansated)&&
	    		 (this->basic_max_speed == rhs.basic_max_speed)&&
	    		 (this->ssp_category_elements == rhs.ssp_category_elements);
	    }

};

void sc_trace(sc_core::sc_trace_file *tf, const std::vector<static_speed_profile_element> &v, const std::string &NAME );
std::ostream& operator<<(std::ostream &os, const std::vector<static_speed_profile_element> &obj);

#endif /* STATIC_SPEED_PROFILE_HPP_ */
