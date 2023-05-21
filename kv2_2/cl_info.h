#ifndef __CL_INFO__H
#define __CL_INFO__H
#include "cl_base.h"


class cl_info : public cl_base
{
public:
	cl_info(cl_base* p_head_object, string s_object_name = "Base_object");
	void handler_method(string& text);
};
#endif
