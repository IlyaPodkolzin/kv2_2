#include "cl_road.h"
#include "cl_car.h"


cl_road::cl_road(cl_base* p_head_object, cl_traffic_light* traffic_light, string s_object_name) : cl_base(p_head_object, s_object_name)
{
	this->traffic_light = traffic_light;
}


int cl_road::get_size()
{
	return road_size;
}


cl_traffic_light* cl_road::get_traffic_light()
{
	return traffic_light;
}


void cl_road::set_size(unsigned road_size)
{
	if (road_size >= 2)
	{
		this->road_size = road_size;
		cars_direction_1 = vector<unsigned short>(road_size * 2 + 1, 0);
		cars_direction_2 = vector<unsigned short>(road_size * 2 + 1, 0);
		cars_direction_3 = vector<unsigned short>(road_size * 2 + 1, 0);
		cars_direction_4 = vector<unsigned short>(road_size * 2 + 1, 0);
	}
}


void cl_road::include_car(cl_car* new_car)
{
	int x = new_car->get_x();
	int y = new_car->get_y();
	int direction = new_car->get_direction();

	if (direction == 1)
		cars_direction_1[x + road_size]++;

	else if (direction == 2)
		cars_direction_2[y + road_size]++;

	else if (direction == 3)
		cars_direction_3[x + road_size]++;

	else
		cars_direction_4[y + road_size]++;
}


void cl_road::exclude_car(cl_car* car_to_exclude)
{
	int x = car_to_exclude->get_x();
	int y = car_to_exclude->get_y();
	int direction = car_to_exclude->get_direction();

	if (direction == 1)
		cars_direction_1[x + road_size]--;

	else if (direction == 2)
		cars_direction_2[y + road_size]--;

	else if (direction == 3)
		cars_direction_3[x + road_size]--;

	else if (direction == 4)
		cars_direction_4[y + road_size]--;
}
