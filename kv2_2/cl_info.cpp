#include "cl_info.h"


cl_info::cl_info(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}


void cl_info::handler_method(string& text)
{
	cout << endl << text;
}
