#include <string>
#include "cl_application.h"
#include "cl_base.h"
#include "cl_car.h"
#include "cl_commander.h"
#include "cl_info.h"
#include "cl_traffic_light.h"
#include "cl_traffic_light_controller.h"


cl_application::cl_application(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}


void cl_application::build_tree_objects()
{
	s_object_name = "Intersection traffic system";

	cl_commander* commander_object = new cl_commander(this, "Input object");
	cl_traffic_light* tl_object = new cl_traffic_light(this, "Traffic light");
	cl_traffic_light_controller* tlc_object = new cl_traffic_light_controller(this, tl_object, "Traffic light controller");
	tl_object->relocate(tlc_object);
	cl_road* road_object = new cl_road(this, tl_object, "Road");
	current_road = road_object;
	cl_info* info_object = new cl_info(this, "Output object");
	setReadyMarkForAll(1);

	set_connect(SIGNAL_D(cl_application::signal_method), commander_object, HANDLER_D(cl_commander::handler_method));
	commander_object->set_connect(SIGNAL_D(cl_commander::signal_method), this, HANDLER_D(cl_application::handler_method));

	string command = "";

	emit_signal(SIGNAL_D(cl_application::signal_method), command);  // выдача сигнала объекту чтения, получение сигнала с введённой строкой
	road_object->set_size(stoi(command));

	string license_plate = "";
	int coord_x = 0;
	int coord_y = 0;
	cl_car* car_object = nullptr;

	emit_signal(SIGNAL_D(cl_application::signal_method), command);
	while (command != "End of cars")
	{
		license_plate = command.substr(0, command.find(" "));
		if (road_object->getSObject(license_plate))
			continue;

		coord_x = stoi(command.substr(command.find(" ") + 1, command.rfind(" ")));
		coord_y = stoi(command.substr(command.rfind(" ")));

		car_object = new cl_car(road_object, road_object, license_plate);
		car_object->set_coords(coord_x, coord_y);
		road_object->include_car(car_object);

		set_connect(SIGNAL_D(cl_application::signal_method), car_object, HANDLER_D(cl_car::handler_method));  // система - машина
		car_object->set_connect(SIGNAL_D(cl_car::signal_method), this, HANDLER_D(cl_application::handler_method_for_cars));
		car_object->set_connect(SIGNAL_D(cl_car::signal_method_to_output), info_object, HANDLER_D(cl_info::handler_method));  // машина - объект вывода
		for (unsigned i = 0; i < connects.size(); i++)
		{
			if (connects[i]->p_cl_base->getName().compare(license_plate) == 1)
			{
				connects.insert(connects.begin() + i, connects.back());
				connects.pop_back();
				break;
			}
		}

		set_connect(SIGNAL_D(cl_application::signal_method_for_cars), car_object, HANDLER_D(cl_car::move));  // система - машина

		emit_signal(SIGNAL_D(cl_application::signal_method), command);
	}

	tlc_object->set_connect(SIGNAL_D(cl_traffic_light_controller::signal_method), info_object, HANDLER_D(cl_info::handler_method));  // п/у светофора - объект вывод
	set_connect(SIGNAL_D(cl_application::signal_method), tlc_object, HANDLER_D(cl_traffic_light_controller::handler_method));  // система - п/у светофора
	connects.insert(connects.begin() + 1, connects.back());
	connects.pop_back();

	set_connect(SIGNAL_D(cl_application::signal_method_to_output), info_object, HANDLER_D(cl_info::handler_method));
}


int cl_application::exec_app()
{
	string command = "Ready to work";

	for (o_sh* connect : connects)
		connect->p_cl_base->setReadyMark(1);

	cout << command;

	while (command != "Turn off the system")
	{

		emit_signal(SIGNAL_D(cl_application::signal_method), command);

		if (command.find("Car") != string::npos)
		{
			string searched_lp = command.substr(command.find(" ") + 1);
			for (unsigned i = 0; i < drive_aways.size(); i++)
				if (drive_aways[i].compare(searched_lp) == 0)
				{
					command = searched_lp + " the car left the road section";
					emit_signal(SIGNAL_D(cl_application::signal_method_to_output), command);
					break;
				}
		}

		for (o_sh* connect : connects)
			if (connect->p_cl_base->getSReadyMark() == 0)
			{
				cl_base* obj = connect->p_cl_base;
				obj->delete_connect(SIGNAL_D(cl_car::signal_method), getSObject("Output object"), HANDLER_D(cl_info::handler_method));
				obj->delete_connect(SIGNAL_D(cl_car::signal_method), this, HANDLER_D(cl_application::handler_method_for_cars));
				delete_connect(SIGNAL_D(cl_application::signal_method_for_cars), obj, HANDLER_D(cl_car::move));
				delete_connect(SIGNAL_D(cl_application::signal_method), obj, HANDLER_D(cl_car::handler_method));

				string deleted_name = connect->p_cl_base->getName();
				drive_aways.push_back(deleted_name);
				deleteObject(deleted_name);
			}

		if (command == "SHOWTREE")
		{
			printBranchWithReadyMark();
			break;
		}
	}

	command = "Turn off the system";
	emit_signal(SIGNAL_D(cl_application::signal_method_to_output), command);

	return 0;
}


void cl_application::signal_method(string& text) {}


void cl_application::handler_method(string& text) {}


void cl_application::signal_method_for_cars(string& request_result) {}


void cl_application::handler_method_for_cars(string& car_name_plus_status)
{
	string car_name = car_name_plus_status.substr(0, car_name_plus_status.find(" "));
	string request_result = car_name_plus_status.substr(car_name_plus_status.find(" ") + 1);
	emit_signal(SIGNAL_D(cl_application::signal_method_for_cars), request_result, getSObjectFromTree(car_name));

	car_name_plus_status = request_result;
}


void cl_application::signal_method_to_output(string& text) {}