#include "cl_car.h"
#include "cl_road.h"
#include "cl_base.h"
#include "cl_application.h"
#include <string>


cl_car::cl_car(cl_base* p_head_object, cl_road* road_object, string s_object_name) : cl_base(p_head_object, s_object_name)
{
	this->current_road = road_object;
}


bool cl_car::road_is_free()
{
	int road_size = current_road->get_size();
	if (direction == 1)
		return (coord_x == 2 && current_road->cars_direction_4[1 + road_size] == 0 || coord_x != 2 && (coord_x == -1 * road_size || current_road->cars_direction_1[coord_x + road_size - 1] == 0));

	else if (direction == 2)
		return (coord_y == 2 && current_road->cars_direction_1[1 + road_size] == 0 || coord_y != 2 && (coord_y == -1 * road_size || current_road->cars_direction_2[coord_y + road_size - 1] == 0));

	else if (direction == 3)
		return (coord_x == -2 && current_road->cars_direction_2[-1 + road_size] == 0 || coord_x != -2 && (coord_x == road_size || current_road->cars_direction_3[coord_x + road_size + 1] == 0));

	else
		return (coord_y == -2 && current_road->cars_direction_3[-1 + road_size] == 0 || coord_y != -2 && (coord_y == road_size || current_road->cars_direction_4[coord_y + road_size + 1] == 0));

	return false;
}


bool cl_car::traffic_light_ok()
{
	string current_color = current_road->get_traffic_light()->get_string_color();

	if (current_color != "green" && (coord_x == 2 && coord_y == 1 || coord_x == -2 && coord_y == -1)) return false;

	if (current_color != "red" && (coord_x == -1 && coord_y == 2 || coord_x == 1 && coord_y == -2)) return false;

	return true;
}


void cl_car::move(string& request_result)
{
	if (request_result == "yes")
	{
		int road_size = current_road->get_size();
		if (direction == 1 && coord_x == -road_size || direction == 2 && coord_y == -road_size
			|| direction == 3 && coord_x == road_size || direction == 4 && coord_y == road_size)
		{
			request_result = s_object_name;

			setReadyMark(0);

			current_road->exclude_car(this);

			return;
		}

		current_road->exclude_car(this);

		if (direction == 1)
		{
			coord_x--;
			if (coord_x == 0) coord_x--;
		}
		else if (direction == 2)
		{
			coord_y--;
			if (coord_y == 0) coord_y--;
		}
		else if (direction == 3)
		{
			coord_x++;
			if (coord_x == 0) coord_x++;
		}
		else
		{
			coord_y++;
			if (coord_y == 0) coord_y++;
		}

		current_road->include_car(this);
	}
}


void cl_car::set_coords(int coord_x, int coord_y)
{
	this->coord_x = coord_x;
	this->coord_y = coord_y;

	if (coord_y == 1) direction = 1;
	else if (coord_x == -1) direction = 2;
	else if (coord_y == -1) direction = 3;
	else direction = 4;
}


unsigned short cl_car::get_direction()
{
	return direction;
}


int cl_car::get_x()
{
	return coord_x;
}


int cl_car::get_y()
{
	return coord_y;
}


void cl_car::signal_method(string& text)
{
	if (traffic_light_ok() && road_is_free()) text += " yes";
	else text += " no";
}


void cl_car::handler_method(string& text)
{
	string text_to_output = "";
	if (text == "Display the system status")
	{
		text_to_output = s_object_name + " ( " + to_string(coord_x) + ", " + to_string(coord_y) + " )";
		emit_signal(SIGNAL_D(cl_car::signal_method_to_output), text_to_output);
	}

	else if (text == "Car " + s_object_name)
	{
		text_to_output = "Car " + s_object_name + " ( " + to_string(coord_x) + ", " + to_string(coord_y) + " )";
		emit_signal(SIGNAL_D(cl_car::signal_method_to_output), text_to_output);
	}

	string car_name = s_object_name;
	emit_signal(SIGNAL_D(cl_car::signal_method), car_name);
}


void cl_car::signal_method_to_output(string& text) {}
