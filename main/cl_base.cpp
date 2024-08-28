#include "cl_base.hpp"
cl_base::cl_base(cl_base* p_head, std::string s_name)
{
	//------------------
	this->s_name = s_name;
	this->p_head_object = p_head;
	//------------------
	if (p_head_object != nullptr)
	p_head_object->p_sub_objects.push_back(this);
}
cl_base::~cl_base()
{
	cl_base* p_root = this;
	while (p_root->get_head() != nullptr)
	{
		p_root = p_root->get_head();
	}
	p_root->delete_links(this);
	for (int i = 0; i < p_sub_objects.size(); i++)
		delete(p_sub_objects[i]);
}
bool cl_base::set_name(std::string s_new_name)
{
	if (p_head_object != nullptr)
		for (int i = 0; i < p_head_object->p_sub_objects.size(); i++)
			if (p_head_object->p_sub_objects[i]->get_name() == s_new_name)
				return false;
	this->s_name = s_new_name;
	return true;
}
std::string cl_base::get_name() { return this->s_name; }
cl_base* cl_base::get_head() { return this->p_head_object; }
cl_base* cl_base::get_sub_object(std::string s_name)
{
	for (int i = 0; i < this->p_sub_objects.size(); i++)
		if (p_sub_objects[i]->get_name() == s_name)
			return p_sub_objects[i];
	return nullptr;
}
cl_base* cl_base::search_object_on_branch(std::string s_name)
{
	//------------------
	std::queue <cl_base*> q;
	cl_base* p_found = nullptr;
	//------------------
	q.push(this);
	while (!q.empty())
	{
		if (q.front()->get_name() == s_name)
			if (p_found == nullptr) p_found = q.front();
			else return nullptr;
		for (auto p_sub_object : q.front()->p_sub_objects)
			q.push(p_sub_object);
		q.pop();
	}
	return p_found;
}
cl_base* cl_base::search_object_from_root(std::string s_name)
{
	cl_base* p_root = this;
	while (p_root->get_head() != nullptr)
	{
		p_root = p_root->get_head();
	}
	return p_root->search_object_on_branch(s_name);
}

void cl_base::print_brunches(int counts)
{
	std::cout << std::endl;
	for (int i = 0; i < counts; i++) { std::cout << " "; }
	std::cout << this->get_name();
	counts++;
	for (auto p_sub_object : p_sub_objects)
		p_sub_object->print_brunches(counts);
}

void cl_base::print_brunches_readiness(int counts)
{
	std::cout << std::endl;
	for (int i = 0; i < counts; i++) { std::cout << " "; }
	std::cout << this->get_name();
	if (this->i_state == 0)
		std::cout << " is not ready";
	else
		std::cout << " is ready";
	counts++;
	for (auto p_sub_object : p_sub_objects)
		p_sub_object->print_brunches_readiness(counts);
}

void cl_base::change_state(int i_new_state)
{
	if (this->get_head() == nullptr || this->get_head()->i_state != 0)
		this->i_state = i_new_state;
	else
		this->i_state = 0;
	if (i_new_state == 0)
		for (int i = 0; i < this->p_sub_objects.size(); i++)
			this->p_sub_objects[i]->change_state(0);
}

bool cl_base::change_head_object(cl_base* p_head)
{
	cl_base* p_root = p_head;
	bool i_sub = false;
	while (p_root->get_head() != nullptr)
	{
		if (p_root == this)
		{
			i_sub = true;
		}
		p_root = p_root->get_head();
	}
	//------------------
	if (this->get_head() == nullptr) return false; // Переопределение головного	для корневого(Redefining the head object failed)
		if (p_head == nullptr) return false; // Создание второго коревого объекта (Head object is not found)
		if (i_sub) return false; // Новый головной объект пренадледит к ветке текущего(Redefining the head object failed)
		if (p_head->get_sub_object(this->get_name()) != nullptr) return false;
	// Создание второго подчинённого с одинаковым наименованием (Dubbing the names of subordinate objects)
	//------------------
		std::vector <cl_base*> p_new_sub;
	for (auto p_sub_object : this->get_head()->p_sub_objects)
		if (p_sub_object->get_name() != this->get_name())
			p_new_sub.push_back(p_sub_object);
	this->get_head()->p_sub_objects = p_new_sub;
	this->p_head_object = p_head;
	p_head->p_sub_objects.push_back(this);
	return true;
}

void cl_base::del_sub_object(std::string s_sub_name)
{
	cl_base* p_currnet = this->get_sub_object(s_sub_name);
	for (int i = 0; i < p_sub_objects.size(); i++)
	{
		if (p_sub_objects[i] == p_currnet)
		{
			delete(this->p_sub_objects[i]);
			this->p_sub_objects.erase(this->p_sub_objects.begin() + i);
			return;
		}
	}
}

cl_base* cl_base::search_object_with_coord(std::string s_coord)
{
	//------------------
	std::string s_name;
	int i_end;
	cl_base* p_object = nullptr;
	//------------------
	//------------------
	cl_base* p_root = this;
	//------------------
	while (p_root->get_head() != nullptr)
		p_root = p_root->get_head();
	//------------------
	if (s_coord == "/")
		return p_root;
	else if (s_coord == ".")
		return this;
	else if (s_coord[0] == '/' && s_coord[1] == '/')
	{
		s_name = s_coord.substr(2);
		return p_root->search_object_on_branch(s_name);
	}
	else if (s_coord[0] == '.')
	{
		s_name = s_coord.substr(1);
		return this->search_object_on_branch(s_name);
	}
	//------------------
	i_end = s_coord.find('/', 1);
	//------------------
	if (s_coord[0] == '/')
	{
		if (i_end != std::string::npos)
		{
			//------------------
			s_name = s_coord.substr(1, i_end - 1);
			p_object = this->get_sub_object(s_name);
			//------------------
			if (p_object != nullptr)
				return p_object->search_object_with_coord(s_coord.substr(i_end + 1));
			else
				return nullptr;
		}
		else
		{
			s_name = s_coord.substr(1);
			return this->get_sub_object(s_name);
		}
	}
	else
		if (i_end != std::string::npos)
		{
			//------------------
			s_name = s_coord.substr(0, i_end);
			p_object = this->get_sub_object(s_name);
			//------------------
			if (p_object != nullptr)
				return p_object->search_object_with_coord(s_coord.substr(i_end + 1));
			else
				return nullptr;
		}
		else
		{
			s_name = s_coord;
			return this->get_sub_object(s_name);
		}
}

void cl_base::set_connect(TYPE_SIGNAL p_signal, cl_base*
	p_object, TYPE_HANDLER p_ob_handler)
{
	o_sh* p_value;
	for (unsigned int i = 0; i < connects.size(); i++)
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_cl_base == p_object &&
			connects[i]->p_handler == p_ob_handler)
		{
			return;
		}
	}
	p_value = new o_sh();
	p_value->p_signal = p_signal;
	p_value->p_cl_base = p_object;
	p_value->p_handler = p_ob_handler;
	connects.push_back(p_value);
}

void cl_base::delete_connection(TYPE_SIGNAL p_signal, cl_base* p_cl_base,TYPE_HANDLER p_handler)
{
	for (int i = 0; i < connects.size(); i++)
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_cl_base == p_cl_base &&
			connects[i]->p_handler == p_handler)
		{
			delete connects[i];
			connects.erase(connects.begin() + i);
			return;
		}
	}
}
void cl_base::emit_signal(TYPE_SIGNAL p_signal, std::string& s_command)
{
	if (this->i_state == 0) return;
	//-----------------------------------------------------------------------
	(this->*p_signal) (s_command); // вызов метода сигнала
	for (unsigned int i = 0; i < connects.size(); i++) // цикл по всем обработчикам
	{
	if (connects[i]->p_signal == p_signal) // определение допустимого обработчика
	{
	if (connects[i]->p_cl_base->i_state == 0) return;
	(connects[i]->p_cl_base->*connects[i]->p_handler) ( s_command); // вызов метода обработчика
	}
	}
}
std::string cl_base::get_full_coords()
{
	std::string s_full_coord = "";
	if (this->get_head() != nullptr)
	{
		s_full_coord += this->get_head()->get_full_coords();
		s_full_coord += '/' + this->get_name();
	}
	return s_full_coord;
}

void cl_base::all_obj_ready()
{
	this->i_state = 1;
	for (auto p_sub : p_sub_objects)
		p_sub->all_obj_ready();
}

int cl_base::get_class()
{
	return 0;
}

void cl_base::signal_f(std::string& msg)
{}
void cl_base::handler_f(std::string msg)
{}
void cl_base::delete_links(cl_base* p_target)
{
	for (int i = 0; i < this->connects.size(); i++)
	{
		if (this->connects[i]->p_cl_base == p_target)
		{
			delete this->connects[i];
			this->connects.erase(connects.begin() + i);
		}
	}
	for (auto p_sub : p_sub_objects)
	{
		p_sub->delete_links(p_target);
	}
}

std::vector<std::string> cl_base::split_array(std::string s_tokens)
{
	std::vector<std::string> vec_tokens;
	std::string s_new_token = "";
	while (s_tokens.find(' ') != std::string::npos)
	{
		vec_tokens.push_back(s_tokens.substr(0, s_tokens.find(' ')));
		s_tokens = s_tokens.erase(0, s_tokens.find(' ') + 1);
	}
	vec_tokens.push_back(s_tokens);
	return vec_tokens;
}
bool cl_base::oper(std::string s_symb)
{
	if (s_symb == "AND" || s_symb == "OR" || s_symb == "XOR" || s_symb == "NOT"	|| s_symb == "=>" || s_symb == "<=>")
		return true;
	return false;
}
int cl_base::priority(std::string s_symb)
{
	if (s_symb == "NOT") return 6;
	else if (s_symb == "AND") return 5;
	else if (s_symb == "XOR") return 4;
	else if (s_symb == "OR") return 3;
	else if (s_symb == "=>") return 2;
	else if (s_symb == "<=>") return 1;
	else return 0;
}
bool cl_base::value(std::vector<std::string> vector, std::string pos)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == pos)
		{
			if (vector[i + 2] == "true") return true;
			else return false;
		}
	}
	return false;
}

std::string cl_base::b_function(bool a, bool b, std::string func)
{
	if (func == "AND")
	{
		if (a == true && b == true) return "true";
		else return "false";
	}
	else if (func == "OR")
	{
		if (a == false && b == false) return "false";
		else return "true";
	}
	else if (func == "XOR")
	{
		if (a != b) return "true";
		else return "false";
	}
	else if (func == "=>")
	{
		if (a == true && b == false) return "false";
		else return "true";
	}
	else if (func == "<=>")
	{
		if (a == b) return "true";
		else return "false";
	}
	return "false";
}

std::string cl_base::b_function(bool a)
{
	if (a == true) return "false";
	else return "true";
}
std::string cl_base::logical_var_output(std::string s_msg)
{
	std::vector<char> w1;
	std::vector<char> w2;
	int position = 0;
	for (int i = 0; i < s_msg.size(); i++)
	{
		if (s_msg[i] == '=')
		{
			w1.push_back(s_msg[i - 2]);
			w2.push_back(s_msg[i + 2]);
		}
	}
	for (int i = 0; i < w1.size() - 1; i++)
	{
		for (int j = i + 1; j < w1.size(); j++)
		{
			if ((w1[i]) > (w1[j]))
			{
				std::swap(w1[i], w1[j]);
				std::swap(w2[i], w2[j]);
			}
		}
	}
	for (int i = 0; i < s_msg.size(); i++)
	{
		if (s_msg[i] == '=')
		{
			s_msg[i - 2] = w1[position];
			s_msg[i + 2] = w2[position];
			position++;
		}
	}
	return s_msg;
}