#ifndef __CL_INPUT__H
#define __CL_INPUT__H
#include "cl_base.hpp"
class cl_input :public cl_base
{
public:
	cl_input(cl_base* p_head, std::string s_name);
	void signal_f(std::string& s_msg);// Метод сигнала
	void handler_f(std::string s_msg);// Метод обработчика
	int get_class(); // Метод возвращает номер класса
};
#endif
