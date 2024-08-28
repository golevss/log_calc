#ifndef __CL_APLICATION__H
#define __CL_APLICATION__H
#include "cl_base.hpp"
#include "cl_input.hpp"
#include "cl_logical_var.hpp"
#include "cl_rev_pol.hpp"
#include "cl_output.hpp"
#include "cl_func_value.hpp"
class cl_application :public cl_base
{
private:
	std::string s_cmd;
public:
	cl_application(cl_base* p_head);
	void build_tree_objects();
	int exec_app();
	//-----
	int get_class();
	void signal_f(std::string& s_msg);
	void handler_f(std::string s_msg);
};
#endif