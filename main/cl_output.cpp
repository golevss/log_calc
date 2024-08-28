#include "cl_output.hpp"
cl_output::cl_output(cl_base* p_head, std::string s_name) :cl_base(p_head, s_name)
{
}
void cl_output::signal_f(std::string& s_msg)
// Метод сигнала
{
}
void cl_output::handler_f(std::string s_msg)
// Метод обработчика
{
	if (s_msg == ".") return;
	if (s_msg[0] == '.')
	{
		std::cout << std::endl << "Values: " << s_msg.substr(1);
	}
	else if (s_msg.find('.') == std::string::npos && !(s_msg == "true" || s_msg == "false"))
	{
		std::cout << std::endl << "Polish Notation: " << s_msg;
	}
	else if (s_msg == "true" || s_msg == "false")
	{
		std::cout << std::endl << "Result: " << s_msg << std::endl << std::endl;
	}
	else return;
}
int cl_output::get_class()
// Метод возвращает номер класса
{
	return 5;
}