#include "cl_application.hpp"
cl_application::cl_application(cl_base* p_head) :cl_base(p_head)
{
}
void cl_application::build_tree_objects()
// Метод создания дерева объектов
{
	cl_base* p_sub = this;
	set_name("system");
	p_sub = new cl_input(this, "input");
	p_sub = new cl_logical_var(this, "various");
	p_sub = new cl_rev_pol(this, "reverse");
	p_sub = new cl_output(this, "output");
	p_sub = new cl_func_value(this, "value");
	this->set_connect(SIGNAL_D(cl_application::signal_f),
		get_sub_object("input"),
		HANDLER_D(cl_input::handler_f));
	//-----------------------------------------------------------------------
	get_sub_object("input")->set_connect(SIGNAL_D(cl_input::signal_f),
			this,
			HANDLER_D(cl_application::handler_f));
	get_sub_object("input")->set_connect(SIGNAL_D(cl_input::signal_f),
			get_sub_object("various"),
			HANDLER_D(cl_logical_var::handler_f));
	get_sub_object("input")->set_connect(SIGNAL_D(cl_input::signal_f),
			get_sub_object("output"),
			HANDLER_D(cl_output::handler_f));
	get_sub_object("input")->set_connect(SIGNAL_D(cl_input::signal_f),
			get_sub_object("reverse"),
			HANDLER_D(cl_rev_pol::handler_f));
	//-----------------------------------------------------------------------
	get_sub_object("various") -> set_connect(SIGNAL_D(cl_logical_var::signal_f),
			get_sub_object("input"),
			HANDLER_D(cl_input::handler_f));
	//-----------------------------------------------------------------------
		get_sub_object("reverse")->set_connect(SIGNAL_D(cl_rev_pol::signal_f),
			get_sub_object("output"),
			HANDLER_D(cl_output::handler_f));
	get_sub_object("reverse")->set_connect(SIGNAL_D(cl_rev_pol::signal_f),
		get_sub_object("value"),
		HANDLER_D(cl_func_value::handler_f));
	//-----------------------------------------------------------------------
		get_sub_object("value")->set_connect(SIGNAL_D(cl_func_value::signal_f),
			get_sub_object("output"),
			HANDLER_D(cl_output::handler_f));
}
int cl_application::exec_app()
{
	all_obj_ready();
	s_cmd = "ON";
	while (true)
	{
		if (s_cmd == "OFF") exit(0);
		emit_signal(SIGNAL_D(cl_application::signal_f), s_cmd);
	}
	return 0;
}
int cl_application::get_class()
{
	return 1;
}
void cl_application::signal_f(std::string& s_msg)
// Метод сигнала
{
}
void cl_application::handler_f(std::string s_msg)
// Метод обработчика
{
	if (s_msg == "." || s_msg == "")
	{
		s_cmd = ("OFF");
	}
	if (s_msg == "SHOWTREE")
	{
		print_brunches_readiness();
		s_cmd = ("OFF");
	}
}
