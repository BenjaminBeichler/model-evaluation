/*
 * tools.cpp
 *
 *  Created on: 10.06.2013
 *      Author: benni
 */
#include "headers/tools.hpp"

std::ostream cnull(0);

void print_deceleration_curve_with_gnuplot(Gnuplot & plot ,const parabola_curve &curve, std::string label, bool svg)
{
	try{
	std::ostringstream function;

	std::vector<double> points_begin;
	std::vector<double> points_speed;

	for (auto i : curve.arcs)
	{
		function << "((x>=" << i.second.begin << ")&&(x<" << i.second.end << "))? ";
		function << "(2*("<< -i.second.slope << ")*(x-" << i.second.begin << ")+" << i.second.value << "**(2))**(1.0/2.0)";
		function << ":";

		points_begin.push_back(i.first);
		points_speed.push_back(i.second.value);
	}

	function << "1/0" ;


	if(svg)
	{
	plot << "set terminal svg fname 'Verdana' fsize 10 ";
	plot << "set object 1 rect from screen 0, 0, 0 to screen 1, 1, 0 behind";
	plot << "set object 1 rect fc  rgb \"white\"  fillstyle solid 1.0";
	std::string output("set output '");
	output += label;
	output += ".svg'";
	plot << output;
	}
	else
	{
		plot << "set term wxt";
	}

	plot.set_style("lines");

	plot.set_yautoscale();
	plot.plot_equation(function.str(),label);

	if(svg)
	plot.set_style("points lc -1 pt 7");
	else
	plot.set_style("points lc 7 pt 7");

	plot.plot_xy(points_begin,points_speed,"Begin of Arcs");
	}
	catch (const GnuplotException & e) {
		std::cout << "Error while plotting with Gnuplot (" << e.what() <<")" << std::endl;

	}
}

void print_step_function(Gnuplot & plot , const step_function & function, std::string label,bool svg)
{

	try{
		std::ostringstream function_string;

		auto i = function.step_values.begin();
		auto j = ++function.step_values.begin();
		for (;j != function.step_values.end();i++,j++)
		{
			function_string << "((x>=" << i->first << ")&&(x<" << j->first << "))? ";
			function_string << i->second;
			function_string << ":";
		}

		function_string << "((x>=" << i->first << ")&&(x<" << i->first + (i->first/10) << "))?";
		function_string << i->second;
		function_string << ": 1/0";



		if(svg)
			{
			plot << "set terminal svg fname 'Verdana' fsize 10 ";
			plot << "set object 1 rect from screen 0, 0, 0 to screen 1, 1, 0 behind";
			plot << "set object 1 rect fc  rgb \"white\"  fillstyle solid 1.0";
			std::string output("set output '");
			output += label;
			output += ".svg'";
			plot << output;
			}
			else
			{
				plot << "set term wxt";
			}

		plot.set_style("fsteps");
		plot.set_xrange(0,i->first + (i->first/10));
		plot.set_yautoscale();
		plot.set_xlabel("Position [m]");
		plot.set_ylabel("Acceleration [m/s²]");
		plot.plot_equation(function_string.str(),label);


		}
		catch (const GnuplotException & e) {
			std::cout << "Error while plotting with Gnuplot (" << e.what() <<")" << std::endl;

		}


}

