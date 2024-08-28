#include "cl_input.hpp"
cl_input::cl_input(cl_base* p_head, std::string s_name) :cl_base(p_head,s_name)
{
}
void cl_input::signal_f(std::string& s_msg)
// Метод сигнала
{
}
void cl_input::handler_f(std::string s_msg)
// Метод обработчика
{
	if (s_msg == "ON")
	{
		std::string s_in_formul;
		getline(std::cin, s_in_formul);
		emit_signal(SIGNAL_D(cl_input::signal_f), s_in_formul);
	}
	else if (s_msg.find('.') != std::string::npos)
	{
		std::string s_var = s_msg.substr(s_msg.find('.'));
		emit_signal(SIGNAL_D(cl_input::signal_f), s_var);
		emit_signal(SIGNAL_D(cl_input::signal_f), s_msg);
	}
	else
	{
		return;
	}
}
int cl_input::get_class()
// Метод возвращает номер класса
{
	return 2;
}