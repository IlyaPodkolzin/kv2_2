#ifndef __CL_BASE__H
#define __CL_BASE__H
#define SIGNAL_D(signal_f) TYPE_SIGNAL(&signal_f)
#define HANDLER_D(handler_f) TYPE_HANDLER(&handler_f)
#include <iostream>
#include <vector>
using namespace std;


class cl_base
{
protected:
	typedef void (cl_base::* TYPE_SIGNAL) (string&);
	typedef void (cl_base::* TYPE_HANDLER) (string&);
	struct o_sh
	{
		TYPE_SIGNAL p_signal;
		cl_base* p_cl_base;
		TYPE_HANDLER p_handler;
	};
	vector<o_sh*> connects;
	string s_object_name;
	cl_base* p_head_object = nullptr;
	int s_ready_mark = 0;
	unsigned short s_class_type = 0;
	void printCurrentBranch(int tabs_count, bool need_ready_mark);

public:
	vector<cl_base*> subordinate_objects;
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object");
	~cl_base();
	bool refactorName(string s_object_name);
	string getName();
	cl_base* getPHeadObject();
	void printTree();
	cl_base* getSObject(string s_object_name);
	cl_base* getSObjectFromBranch(string s_object_name);
	cl_base* getSObjectFromTree(string s_object_name);
	void printBranch();
	void printBranchWithReadyMark();
	void setReadyMark(int s_ready_mark);
	bool relocate(cl_base* p_new_head_object);
	void deleteObject(string s_object_name);
	cl_base* getSObjectByCoordinates(string coordinate);
	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler);
	void delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler);
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command, cl_base* p_object = nullptr);
	string get_absolute_path_way();
	void setReadyMarkForAll(int s_ready_mark);
	void setClassType(unsigned short s_class_type);
	unsigned short getClassType();
	int getSReadyMark();
};
#endif