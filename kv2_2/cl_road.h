#ifndef __CL_ROAD__H
#define __CL_ROAD__H
#include "cl_base.h"
#include "cl_traffic_light.h"
#include "cl_application.h"
#include "cl_car.h"


class cl_car;


class cl_road : public cl_base
{
	friend class cl_application;
	friend class cl_car;

private:
	unsigned road_size = 2;
	cl_traffic_light* traffic_light = nullptr;
	void set_size(unsigned road_size);
	void include_car(cl_car* new_car);
	void exclude_car(cl_car* car_to_exclude);

public:
	vector<unsigned short> cars_direction_1;
	vector<unsigned short> cars_direction_2;
	vector<unsigned short> cars_direction_3;
	vector<unsigned short> cars_direction_4;
	cl_road(cl_base* p_head_object, cl_traffic_light* traffic_light, string s_object_name = "Base_object");
	int get_size();
	cl_traffic_light* get_traffic_light();
};
#endif
