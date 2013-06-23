/*
 * tools.hpp
 *
 *  Created on: 10.06.2013
 *      Author: benni
 */

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <iostream>
#include "gnuplot_i.hpp"
#include "parabola_curve.hpp"
#include "step_function.hpp"

#define MODULE_OUT std::cout << "time: " << sc_core::sc_time_stamp() << " | deltacycle: "<< sc_core::sc_delta_count()  << " | " << name() << std::string(" | ")

extern std::ostream cnull;

#ifdef DEBUG
#define MODULE_DEBUG_OUT MODULE_OUT
#else
#define MODULE_DEBUG_OUT cnull
#endif

void print_deceleration_curve_with_gnuplot(Gnuplot & plot ,const parabola_curve &curve, std::string label,bool svg);
void print_step_function(Gnuplot & plot , const step_function & function, std::string label,bool svg);

#endif /* TOOLS_HPP_ */
