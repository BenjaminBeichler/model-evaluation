#include <stdio.h>
#include <stdlib.h>
#include <systemc>

#include "headers/tools.hpp"
#include "headers/gnuplot_i.hpp"
#include "headers/step_function.hpp"
#include "headers/Acc_due_to_gradient.hpp"
#include "headers/safe_deceleration.hpp"
#include "stimulator.hpp"
#include "headers/calc_EBD.hpp"
#include "headers/track_condition.hpp"

#include <string>
#include <vector>


int sc_main(int argc,char *argv[])
{



	/**************** INPUTs for acc_due_to_gradient *****************************/


	Acc_due_to_gradient acc_due_to_gradient_module("acceleration_gradient");
	Acc_due_to_gradient_stim acc_due_to_gradient_stim("gradient_stimulator");
	train_data_stim td_stim("train_data_stimulator");

	/**** signal definitions *****/

	sc_core::sc_signal<step_function> gradient_signal,A_gradient;

	sc_core::sc_signal<uint> L_TRAIN;
	sc_core::sc_signal<bool> nom_value_valid;
	sc_core::sc_signal<double> M_nom_val;
	sc_core::sc_signal<double> G_TSR;

	/******* signal bindings train data *************/
	acc_due_to_gradient_module.L_TRAIN(L_TRAIN);
	acc_due_to_gradient_module.M_rotating_nom(M_nom_val);
	acc_due_to_gradient_module.M_rotating_nom_valid(nom_value_valid);
	acc_due_to_gradient_module.G_TSR(G_TSR);

	td_stim.L_TRAIN(L_TRAIN);
	td_stim.M_nom_val(M_nom_val);
	td_stim.nom_value_valid(nom_value_valid);

	/*******signal binding gradients ****************/
	acc_due_to_gradient_module.gradients(gradient_signal);
	acc_due_to_gradient_stim.gradients(gradient_signal);
	acc_due_to_gradient_stim.G_TSR(G_TSR);

	/***********output signal bindings ***********/
	acc_due_to_gradient_module.A_Gradient(A_gradient);


/*******************INPUTS for safe_deceleration *****************************/

	safe_deceleration safe_decel("safe_deceleration");
	brake_model_stim bm_stim("safe_deceleration_stim");
	Track_Condition_stim tc_stim("Track_Condition_Stimulator");
	DMI_stim dmi_stim("DMI_Stimulator");

	/**** signal definitions *****/

	sc_core::sc_signal<double> EBD_foot;
	sc_core::sc_signal<double> d_est_front;

	// vector is addressed via a binary selector Enum
	sc_core::sc_vector< sc_core::sc_signal<step_function> > A_break_emergency_models("top_model_brake_model_vector",ALL_BRAKES) ;
	sc_core::sc_signal<bool> regenerative_brake_status;
	sc_core::sc_signal<bool> eddy_current_brake_status;
	sc_core::sc_signal<bool> magnetic_shoe_brake_status;
	sc_core::sc_signal<bool> electro_pneumatic_brake_status;

	sc_core::sc_signal<brake_position_type> brake_position;

	sc_core::sc_vector<sc_core::sc_signal<step_function_f> > Kdry_rst("top_model_kdry_signals",ALL_BRAKES);
	sc_core::sc_vector<sc_core::sc_signal<step_function> > Kwet_rst("top_model_kwet_signals",ALL_BRAKES);
	sc_core::sc_signal<double> M_NVEBCL;
	sc_core::sc_signal<double> M_NVAVADH;

	sc_core::sc_signal<std::list<track_condition> > track_conditions;

	sc_core::sc_vector< sc_core::sc_signal<double> > A_NVMAXREDADH("top_model_red_adh_signals",ALL_BRAKES);
	sc_core::sc_signal<bool> slippery_rail_selected_by_driver;

	sc_core::sc_signal< step_function_f> A_save;


	/***** Input signal bindings **********/
	safe_decel.A_gradient(A_gradient);
	safe_decel.EBD_foot(EBD_foot);
	safe_decel.L_TRAIN(L_TRAIN);

	/**** signal bindings braking model *****/
	bm_stim.A_NVMAXREDADH.bind(A_NVMAXREDADH);
	bm_stim.A_break_emergency_models.bind(A_break_emergency_models);
	bm_stim.Kdry_rst.bind(Kdry_rst);
	bm_stim.Kwet_rst.bind(Kwet_rst);
	bm_stim.M_NVAVADH(M_NVAVADH);
	bm_stim.M_NVEBCL(M_NVEBCL);
	bm_stim.brake_position(brake_position);
	bm_stim.eddy_current_brake_status(eddy_current_brake_status);
	bm_stim.electro_pneumatic_brake_status(electro_pneumatic_brake_status);
	bm_stim.magnetic_shoe_brake_status(magnetic_shoe_brake_status);
	bm_stim.regenerative_brake_status(regenerative_brake_status);

	safe_decel.A_NVMAXREDADH.bind(A_NVMAXREDADH);
	safe_decel.A_break_emergency_models(A_break_emergency_models);
	safe_decel.Kdry_rst(Kdry_rst);
	safe_decel.Kwet_rst(Kwet_rst);
	safe_decel.M_NVAVADH(M_NVAVADH);
	safe_decel.M_NVEBCL(M_NVEBCL);
	safe_decel.brake_position(brake_position);
	safe_decel.eddy_current_brake_status(eddy_current_brake_status);
	safe_decel.electro_pneumatic_brake_status(electro_pneumatic_brake_status);
	safe_decel.magnetic_shoe_brake_status(magnetic_shoe_brake_status);
	safe_decel.regenerative_brake_status(regenerative_brake_status);

	/**** signal bindings track condition *****/
	tc_stim.track_conditions(track_conditions);
	safe_decel.track_conditions(track_conditions);

	/**** signal bindings DMI  *****/
	dmi_stim.slippery_rail_selected_by_driver(slippery_rail_selected_by_driver);
	safe_decel.slippery_rail_selected_by_driver(slippery_rail_selected_by_driver);

	/**** output signal bindings *****/
	safe_decel.A_safe(A_save);

	/*******************INPUTS for calc EBD *****************************/
	Calc_ebd calc_ebd("Calculation_EBD");
	EBD_stim ebd_stim("EBD_stimulator");
	Moving_train_stim moving_train("moving_train_stim");
	Output_stim out("output");

	/********* INPUT signal bindings *******/
	calc_ebd.A_save(A_save);


	/**** signal definitions ******/

	sc_core::sc_signal<double> target_position;
	sc_core::sc_signal<double> target_speed;

	sc_core::sc_signal<bool> MRSP_AND_NOT_LOA_TARGET;


	sc_core::sc_signal<parabola_curve> EBD;

	/**** signal bindings target *****/
	ebd_stim.MRSP_AND_NOT_LOA_TARGET(MRSP_AND_NOT_LOA_TARGET);
	ebd_stim.target_position(target_position);
	ebd_stim.target_speed(target_speed);

	calc_ebd.MRSP_AND_NOT_LOA_TARGET(MRSP_AND_NOT_LOA_TARGET);
	calc_ebd.target_position(target_position);
	calc_ebd.target_speed(target_speed);

	/***** signal binding moving train **********/
	calc_ebd.d_est_front(d_est_front);
	moving_train.d_est_front(d_est_front);

	/**** OUTPUT Signal bindings ********/
	calc_ebd.EBD(EBD);
	calc_ebd.EBD_foot(EBD_foot);
	out.EBD(EBD);

	sc_start(1,sc_core::SC_NS);

	try{
	Gnuplot plot_EBD;
	Gnuplot plot_A_Gradient;
	print_deceleration_curve_with_gnuplot(plot_EBD,EBD.read(),"EBD");
	print_step_function(plot_A_Gradient,A_gradient.read(),"A_gradient");
	std::cout << "Press ENTER to leave simulation ...";
	std::cin.ignore();

	}
	catch (GnuplotException e) {
		std::cout << "Error while plotting EBD with Gnuplot (" << e.what() <<")" << std::endl;
	}



	//sc_close_vcd_trace_file(fp);
	return(0);
};

