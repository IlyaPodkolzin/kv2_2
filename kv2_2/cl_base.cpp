#include "cl_base.h"


cl_base::cl_base(cl_base* p_head_object, string s_object_name)
{
	if (!refactorName(s_object_name))
		delete this;
	else
	{
		this->p_head_object = p_head_object;
		this->s_object_name = s_object_name;
		if (p_head_object)
			p_head_object->subordinate_objects.push_back(this);
	}
}


cl_base::~cl_base()
{
	connects.clear();
	p_head_object = nullptr;
}


bool cl_base::refactorName(string s_object_name)
{
	if (p_head_object)
		if (p_head_object->getSObject(s_object_name))
			return false;

	this->s_object_name = s_object_name;
	return true;
}


string cl_base::getName()
{
	return s_object_name;
}


cl_base* cl_base::getPHeadObject()
{
	return p_head_object;
}


void cl_base::printTree()
{
	if (subordinate_objects.size() != 0)
	{
		cout << endl << s_object_name;
		for (cl_base* s_obj : subordinate_objects)
			cout << "  " << s_obj->getName();
		if (subordinate_objects.size() != 0) subordinate_objects.back()->printTree();
	}
}


cl_base* cl_base::getSObject(string s_object_name)
{
	for (cl_base* s_obj : subordinate_objects)
		if (s_obj->getName() == s_object_name)
			return s_obj;

	return nullptr;
}


cl_base* cl_base::getSObjectFromBranch(string s_object_name)
{
	cl_base* res = nullptr;
	cl_base* result = nullptr;
	bool already_found = false;

	if (this->s_object_name == s_object_name)
		return this;

	else if (subordinate_objects.size() != 0)
	{
		for (cl_base* subordinate_object : subordinate_objects)
		{
			res = subordinate_object->getSObjectFromBranch(s_object_name);
			if (res != nullptr && !already_found)
			{
				already_found = true;
				result = res;
			}
			else if (res != nullptr && already_found)
				return nullptr;
			else if (subordinate_object->getSObject(s_object_name) != nullptr)
				return nullptr;
		}
		if (already_found)
			return result;

		return res;
	}

	else
		return nullptr;
}


cl_base* cl_base::getSObjectFromTree(string s_object_name)
{
	cl_base* p_tree_head = this;
	while (p_tree_head->p_head_object != nullptr)
	{
		p_tree_head = p_tree_head->p_head_object;
	}
	return p_tree_head->getSObjectFromBranch(s_object_name);
}


void cl_base::printBranch()
{
	printCurrentBranch(0, false);
}


void cl_base::printBranchWithReadyMark()
{
	printCurrentBranch(0, true);
}


void cl_base::printCurrentBranch(int tabs_count, bool need_ready_mark)
{
	for (int i = 0; i < tabs_count; i++)
		cout << "    ";
	cout << this->s_object_name;
	if (need_ready_mark)
		if (this->s_ready_mark != 0) cout << " is ready";
		else cout << " is not ready";

	for (cl_base* p_subordinate_object : subordinate_objects)
	{
		cout << endl;
		p_subordinate_object->printCurrentBranch(tabs_count + 1, need_ready_mark);
	}
}


void cl_base::setReadyMark(int s_ready_mark)
{
	if (s_ready_mark == 0)
	{
		this->s_ready_mark = 0;
		for (cl_base* subordinate_object : subordinate_objects)
			subordinate_object->setReadyMark(0);
	}

	else
	{
		cl_base* p_head_object = this;

		while (p_head_object->p_head_object != nullptr)
		{
			p_head_object = p_head_object->p_head_object;
			if (p_head_object->s_ready_mark == 0)
				return;
		}

		this->s_ready_mark = s_ready_mark;

	}
}


bool cl_base::relocate(cl_base* p_new_head_object)
{
	if (p_head_object == nullptr)
		return false;

	if (p_new_head_object == nullptr)
		return false;

	if (p_new_head_object->getSObject(s_object_name) != nullptr)
		return false;

	if (getSObjectFromBranch(p_new_head_object->s_object_name) == p_new_head_object)
		return false;

	for (unsigned i = 0; i < p_head_object->subordinate_objects.size(); i++)
		if (p_head_object->subordinate_objects[i] == this)
		{
			p_head_object->subordinate_objects.erase(p_head_object->subordinate_objects.begin() + i);
			break;
		}

	p_head_object = p_new_head_object;
	p_head_object->subordinate_objects.push_back(this);

	return true;
}


void cl_base::deleteObject(string s_object_name)
{
	cl_base* object_to_delete = getSObjectFromBranch(s_object_name);
	if (object_to_delete->p_head_object != nullptr)
	{
		for (cl_base* subordinate_object : object_to_delete->subordinate_objects)
			subordinate_object->relocate(object_to_delete->p_head_object);

		for (unsigned i = 0; i < object_to_delete->p_head_object->subordinate_objects.size(); i++)
			if (object_to_delete->p_head_object->subordinate_objects[i]->getName() == object_to_delete->getName())
			{
				object_to_delete->p_head_object->subordinate_objects.erase(object_to_delete->p_head_object->subordinate_objects.begin() + i);
				break;
			}

		delete object_to_delete;
	}
}


cl_base* cl_base::getSObjectByCoordinates(string coordinate)
{
	if (coordinate == "")
		return nullptr;

	if (coordinate == "//")
		return nullptr;

	if (coordinate.find("//") == 0)
		return getSObjectFromTree(coordinate.substr(2));

	if (coordinate == ".")
		return this;

	if (coordinate[0] == '.')
		return getSObjectFromBranch(coordinate.substr(1));

	if (coordinate.find('/') != string::npos)
	{
		cl_base* res_pointer = this;
		string current_path_object_name;

		if (coordinate[0] == '/')
		{
			while (res_pointer->p_head_object != nullptr)
				res_pointer = res_pointer->p_head_object;

			if (coordinate == "/")
				return res_pointer;
		}

		else
		{
			current_path_object_name = coordinate.substr(0, coordinate.find('/'));
			res_pointer = this->getSObject(current_path_object_name);
			if (res_pointer == nullptr)
				return res_pointer;
		}

		coordinate = coordinate.substr(coordinate.find('/') + 1);

		while (coordinate.find('/') != string::npos)
		{
			current_path_object_name = coordinate.substr(0, coordinate.find('/'));
			res_pointer = res_pointer->getSObject(current_path_object_name);
			if (res_pointer == nullptr)
				return res_pointer;
			coordinate = coordinate.substr(coordinate.find('/') + 1);
		}

		res_pointer = res_pointer->getSObject(coordinate);
		return res_pointer;
	}

	return this->getSObject(coordinate);
}


void cl_base::set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler)
{
	for (unsigned int i = 0; i < connects.size(); i++)
		if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base == p_object && connects[i]->p_handler == p_ob_handler)
			return;

	o_sh* p_value = new o_sh();
	p_value->p_signal = p_signal;
	p_value->p_cl_base = p_object;
	p_value->p_handler = p_ob_handler;
	connects.push_back(p_value);
}


void cl_base::delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler)
{
	for (unsigned int i = 0; i < connects.size(); i++)
		if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base == p_object && connects[i]->p_handler == p_ob_handler)
		{
			connects.erase(connects.begin() + i);
			return;
		}
}


void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command, cl_base* p_object)
{
	if (this->s_ready_mark == 0) return;

	TYPE_HANDLER p_handler;
	cl_base* h_object;

	(this->*p_signal) (s_command);

	for (unsigned int i = 0; i < connects.size(); i++)
		if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base->s_ready_mark != 0 && (!p_object || connects[i]->p_cl_base == p_object))
		{
			p_handler = connects[i]->p_handler;
			h_object = connects[i]->p_cl_base;
			(h_object->*p_handler)(s_command);
		}
}


string cl_base::get_absolute_path_way()
{
	if (getPHeadObject() == nullptr)
		return "/";

	string full_path = s_object_name;

	if (getPHeadObject()->getPHeadObject() != nullptr)
		full_path = getPHeadObject()->get_absolute_path_way() + '/' + full_path;

	else full_path = '/' + full_path;

	return full_path;
}


void cl_base::setReadyMarkForAll(int s_ready_mark)
{
	setReadyMark(s_ready_mark);
	for (cl_base* subordinate_object : subordinate_objects)
		subordinate_object->setReadyMarkForAll(s_ready_mark);
}


void cl_base::setClassType(unsigned short s_class_type)
{
	this->s_class_type = s_class_type;
}


unsigned short cl_base::getClassType()
{
	return s_class_type;
}


int cl_base::getSReadyMark()
{
	return s_ready_mark;
}
