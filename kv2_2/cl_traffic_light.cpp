#include "cl_traffic_light.h"


cl_traffic_light::cl_traffic_light(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}


unsigned short cl_traffic_light::get_color()
{
	return current_color;
}


string cl_traffic_light::get_string_color()
{
	if (current_color == 0) return "green";
	if (current_color == 1) return "yellow";
	if (current_color == 2) return "red";
	return "yellow";
}
