#ifndef __CL_CAR__H
#define __CL_CAR__H
#include "cl_base.h"
#include "cl_road.h"
#include "cl_application.h"


class cl_road;


class cl_car : public cl_base
{
	friend class cl_application;

private:
	int coord_x = 0;
	int coord_y = 0;
	unsigned short direction = 0;
	cl_road* current_road = nullptr;
	void move(string& request_result);
	void set_coords(int coord_x, int coord_y);

public:
	cl_car(cl_base* p_head_object, cl_road* road_object, string s_object_name = "Base_object");
	unsigned short get_direction();
	int get_x();
	int get_y();
	bool road_is_free();
	bool traffic_light_ok();
	void signal_method(string& text);
	void handler_method(string& text);
	void signal_method_to_output(string& text);
};
#endif
