#ifndef __CL_OUTPUT__H
#define __CL_OUTPUT__H
#include "cl_base.hpp"
class cl_output :public cl_base
{
public:
	cl_output(cl_base* p_head, std::string s_name);
	void signal_f(std::string& s_msg);// ����� �������
	void handler_f(std::string s_msg);// ����� �����������
	int get_class(); // ����� ���������� ����� ������
};
#endif