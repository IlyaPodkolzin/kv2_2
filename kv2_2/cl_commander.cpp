#include "cl_commander.h"
#include <string>


cl_commander::cl_commander(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}


void cl_commander::signal_method(string& text) {}


void cl_commander::handler_method(string& text)
{
	getline(cin, text);
	emit_signal(SIGNAL_D(cl_commander::signal_method), text);
}
