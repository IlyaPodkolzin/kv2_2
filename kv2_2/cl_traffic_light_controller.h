#ifndef __CL_TRAFFIC_LIGHT_CONTROLLER__H
#define __CL_TRAFFIC_LIGHT_CONTROLLER__H
#include "string"
#include "cl_base.h"
#include "cl_traffic_light.h"


class cl_traffic_light;


class cl_traffic_light_controller : public cl_base
{
private:
	cl_traffic_light* tl_object = nullptr;
	unsigned tacts_counter = 0;
	void set_color(unsigned short color);
	void set_tacts(unsigned tacts, unsigned short color);

public:
	cl_traffic_light_controller(cl_base* p_head_object, cl_traffic_light* tl_object, string s_object_name = "Base_object");
	void handler_method(string& text);
	void signal_method(string& text);
};
#endif
