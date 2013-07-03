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
	inline bool operator == (const axle_load_speed_profile_subelement & rhs) const {
		return (this->axle_load_category == rhs.axle_load_category) &&
				(this->max_speed == rhs.max_speed);

		}
};

struct axle_load_speed_profile_element
{
	double begin;
	double length;
	bool train_length_compansated;
	std::vector<axle_load_speed_profile_subelement> subelements;
	inline bool operator == (const axle_load_speed_profile_element & rhs) const {
		      return (this->begin == rhs.begin) &&
		    		 (this->train_length_compansated == rhs.train_length_compansated)&&
		    		 (this->length == rhs.length)&&
		    		 (this->subelements == rhs.subelements);
		    }
};

void sc_trace(sc_core::sc_trace_file *tf, const std::vector<axle_load_speed_profile_element> &v, const std::string &NAME) ;
std::ostream& operator<<(std::ostream &os, const std::vector<axle_load_speed_profile_element> &obj);

#endif /* AXLE_LOAD_SPEED_PROFILE_HPP_ */
