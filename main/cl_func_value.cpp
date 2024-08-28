#include "cl_func_value.hpp"

cl_func_value::cl_func_value(cl_base* p_head, std::string s_name) :cl_base(p_head, s_name)
{
}
void cl_func_value::signal_f(std::string& s_msg)
// Метод сигнала
{
}
void cl_func_value::handler_f(std::string s_msg)
// Метод обработчика
{
	if (s_msg.find('.') == std::string::npos) return;
	std::vector<std::string> vec_formul =
		split_array(s_msg.substr(0, s_msg.find('.')));
	std::vector<std::string> vec_value =
		split_array(s_msg.substr(s_msg.find('.') + 1));
	std::stack<std::string> stack;
	std::string f_elem;
	std::string s_elem;
	vec_value.push_back("true");
	vec_value.push_back("=");
	vec_value.push_back("true");
	vec_value.push_back("false");
	vec_value.push_back("=");
	vec_value.push_back("false");
	for (std::string elem : vec_formul)
	{
		if (!oper(elem))
		{
			stack.push(elem);
		}
		else
		{
			if (elem == "NOT")
			{
				f_elem = stack.top();
				stack.pop();
				stack.push(b_function(value(vec_value, f_elem)));
			}
			else
			{
				f_elem = stack.top();
				stack.pop();
				s_elem = stack.top();
				stack.pop();
				stack.push(b_function(value(vec_value, s_elem), value(vec_value, f_elem), elem));
			}//else
		}//else
	}//for
	emit_signal(SIGNAL_D(cl_func_value::signal_f), stack.top());
}
int cl_func_value::get_class()
// Метод возвращает номер класса
{
	return 6;
}
