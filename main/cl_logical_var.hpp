#ifndef __LOGICAL_VAR__H
#define __LOGICAL_VAR__H
#include "cl_base.hpp"
class cl_logical_var :public cl_base
{
public:
	cl_logical_var(cl_base* p_head, std::string s_name);
	void signal_f(std::string& s_msg);// ����� �������
	void handler_f(std::string s_msg);// ����� �����������
	int get_class(); // ����� ���������� ����� ������
};
#endif
