#ifndef __FUNC_VALUE__H
#define __FUNC_VALUE__H
#include "cl_base.hpp"
class cl_func_value :public cl_base
{
public:
	cl_func_value(cl_base* p_head, std::string s_name);
	void signal_f(std::string& s_msg);// ����� �������
	void handler_f(std::string s_msg);// ����� �����������
	int get_class(); // ����� ���������� ����� ������
};
#endif