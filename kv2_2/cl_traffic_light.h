#ifndef __CL_TRAFFIC_LIGHT__H
#define __CL_TRAFFIC_LIGHT__H
#include "cl_base.h"
#include "cl_traffic_light_controller.h"


class cl_traffic_light : public cl_base
{
	friend class cl_traffic_light_controller;

private:
	unsigned short current_color = 0;
	unsigned tacts_green = 5;
	unsigned tacts_red = 5;
	unsigned short get_color();

public:
	cl_traffic_light(cl_base* p_head_object, string s_object_name = "Base_object");
	string get_string_color();
};
#endif
