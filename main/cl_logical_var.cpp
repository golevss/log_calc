#include "cl_logical_var.hpp"
cl_logical_var::cl_logical_var(cl_base* p_head, std::string s_name) :cl_base(p_head, s_name)
{
}
void cl_logical_var::signal_f(std::string& s_msg)
// Метод сигнала
{
}
void cl_logical_var::handler_f(std::string s_msg)
// Метод обработчика
{
	if (s_msg == ".") return;
	if (s_msg[s_msg.size() - 1] != '.') return;
	std::string s_in_msg;
	getline(std::cin, s_in_msg);
	s_in_msg = logical_var_output(s_in_msg);
	for (int i = 0; i < s_in_msg.size(); i++)
	{
		if (s_in_msg[i] == '1')
		{
			s_in_msg.erase(i, 1);
			s_in_msg.insert(i, "true");
		}
		if (s_in_msg[i] == '0')
		{
			s_in_msg.erase(i, 1);
			s_in_msg.insert(i, "false");
		}
	}
	s_in_msg = s_msg + s_in_msg;
	emit_signal(SIGNAL_D(cl_logical_var::signal_f), s_in_msg);
}
int cl_logical_var::get_class()
// Метод возвращает номер класса
{
	return 3;
}
