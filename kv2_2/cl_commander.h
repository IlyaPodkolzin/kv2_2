#ifndef __CL_COMMANDER__H
#define __CL_COMMANDER__H
#include "cl_base.h"


class cl_commander : public cl_base
{
public:
	cl_commander(cl_base* p_head_object, string s_object_name = "Base_object");
	void signal_method(string& text);
	void handler_method(string& text);
};
#endif
