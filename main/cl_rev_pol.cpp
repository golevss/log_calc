#include "cl_rev_pol.hpp"
cl_rev_pol::cl_rev_pol(cl_base* p_head, std::string s_name) :cl_base(p_head,
	s_name)
{
}
void cl_rev_pol::signal_f(std::string& s_msg)
// Метод сигнала
{
}
void cl_rev_pol::handler_f(std::string s_msg)
// Метод обработчика
{
	if (s_msg == ".") return;
	if (s_msg[0] != '.' && s_msg[s_msg.size() - 1] != '.')
	{
		while (s_msg[0] == '(')
		{
			s_msg.erase(s_msg.find('('), 2);
			s_msg.erase(s_msg.rfind(')') - 1, 2);
		}
		//------------------
		std::string s_formul = s_msg.substr(0, s_msg.find('.'));
		std::vector<std::string> vec_tokens = split_array(s_formul);
		std::stack<std::string> stack;
		std::string s_pol_not = "";
		//------------------
		for (std::string elem : vec_tokens)
		{
			if (elem == "(")
			{
				stack.push("(");
			}
			else if (elem == ")")
			{
				while (true)
				{
					if (stack.top() == "(")
					{
						stack.pop();
						break;
					}
					else
					{
						s_pol_not += stack.top();
						stack.pop();
						if (!stack.empty()) s_pol_not += " ";
					}
				}
				if (stack.top() == "NOT")
				{
					s_pol_not += stack.top() + " ";
					stack.pop();
				}
			}
			else if (oper(elem))
			{
				if (stack.empty())
				{
					stack.push(elem);
				}
				else if (priority(stack.top()) < priority(elem) || (stack.top() == "NOT" && elem == "NOT"))
				{
					stack.push(elem);
				}
				else if (priority(stack.top()) >= priority(elem))
				{
					s_pol_not += stack.top() + " ";
					stack.pop();
					stack.push(elem);
				}
			}
			else if (!oper(elem))
			{
				s_pol_not += elem + " ";
			}
		}
		if (!stack.empty())
		{
			while (!stack.empty())
			{
				s_pol_not += stack.top();
				stack.pop();
				if (!stack.empty()) s_pol_not += " ";
			}
		}
		if (s_pol_not[s_pol_not.size() - 1] == ' ') {
			s_pol_not.erase(s_pol_not.size() - 1, 1);
		}
		emit_signal(SIGNAL_D(cl_rev_pol::signal_f), s_pol_not);
		s_pol_not += s_msg.substr(s_msg.find('.'));
		emit_signal(SIGNAL_D(cl_rev_pol::signal_f), s_pol_not);
	}
}
int cl_rev_pol::get_class()
// Метод возвращает номер класса
{
	return 4;
}