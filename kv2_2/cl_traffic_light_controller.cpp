#include "cl_traffic_light_controller.h"
#include "cl_traffic_light.h"


cl_traffic_light_controller::cl_traffic_light_controller(cl_base* p_head_object, cl_traffic_light* tl_object, string s_object_name) : cl_base(p_head_object, s_object_name)
{
	this->tl_object = tl_object;
}


void cl_traffic_light_controller::set_color(unsigned short color)
{
	if (color >= 0 && color < 4) tl_object->current_color = color;
}


void cl_traffic_light_controller::set_tacts(unsigned tacts, unsigned short color)
{
	if (tacts >= 2)
	{
		if (color == 0) tl_object->tacts_green = tacts;
		else if (color == 2) tl_object->tacts_red = tacts;
	}
}


void cl_traffic_light_controller::handler_method(string& command)
{
	if (command == "Display the system status")
	{
		string helper_str = command;
		emit_signal(SIGNAL_D(cl_traffic_light_controller::signal_method), helper_str);
	}

	if (command.find("Switching traffic lights ") != string::npos)
	{
		unsigned tacts = stoi(command.substr(command.rfind(" ") + 1));
		command.find("green") != string::npos ? tl_object->tacts_green = tacts : tl_object->tacts_red = tacts;
	}

	tacts_counter++;
	unsigned short current_color = tl_object->get_color();

	if (tacts_counter > 2 && (current_color == 1 || current_color == 3)
		|| current_color == 0 && tacts_counter > tl_object->tacts_green
		|| current_color == 2 && tacts_counter > tl_object->tacts_red)
	{
		set_color((current_color + 1) % 4);
		tacts_counter = 1;
	}
}


void cl_traffic_light_controller::signal_method(string& command)
{
	command = "Traffic light color is " + tl_object->get_string_color();
}
