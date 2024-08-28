#ifndef __CL_REV_POL__H
#define __CL_REV_POL__H
#include "cl_base.hpp"
class cl_rev_pol :public cl_base
{
public:
	cl_rev_pol(cl_base* p_head, std::string s_name);
	void signal_f(std::string& s_msg);// Метод сигнала
	void handler_f(std::string s_msg);// Метод обработчика
	int get_class(); // Метод возвращает номер класса
};
#endif
