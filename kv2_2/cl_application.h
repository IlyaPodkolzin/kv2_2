#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
#include "cl_car.h"
#include "cl_commander.h"
#include "cl_info.h"
#include "cl_road.h"
#include "cl_traffic_light.h"
#include "cl_traffic_light_controller.h"


class cl_car;


class cl_road;


class cl_application : public cl_base
{
private:
	string corrupted_head = "";
	vector<string> drive_aways;
	cl_road* current_road = nullptr;

public:
	cl_application(cl_base* p_head_object, string s_object_name = "Base_object");
	void build_tree_objects();
	int exec_app();
	void signal_method(string& unnecessary_text);
	void handler_method(string& unnecessary_text);
	void signal_method_for_cars(string& request_result);
	void handler_method_for_cars(string& car_name_plus_status);
	void signal_method_to_output(string& unnecessary_text);
};
#endif
