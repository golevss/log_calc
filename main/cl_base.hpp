#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(hendler_f)(TYPE_HANDLER)(&hendler_f)

class cl_base;
typedef void (cl_base ::* TYPE_SIGNAL) (std::string&);
typedef void (cl_base ::* TYPE_HANDLER) (std::string);
struct o_sh
{
	TYPE_SIGNAL p_signal;
	cl_base* p_cl_base;
	TYPE_HANDLER p_handler;
};
class cl_base
{
	std::string s_name;
	cl_base* p_head_object;
	std::vector <cl_base*> p_sub_objects;
	std::vector <o_sh*> connects;;
	int i_state = 0;
public:
	cl_base(cl_base* p_head, std::string s_name = "base_object");
	~cl_base();

	bool set_name(std::string s_new_name);// Метод осуществляет изменение имени объекта
	std::string get_name();// Метод возвращает имя объекта
	cl_base* get_head();// Метод возвращает указатель на головной объект
	cl_base* get_sub_object(std::string s_name);// Метод возвращает указатель на подчинённый объект
	cl_base* search_object_on_branch(std::string s_name);// Метод осуществляет поиск объекта от текущего по ветке
	cl_base* search_object_from_root(std::string s_name);// Метод осуществляет поиск объекта от корня
	void print_brunches(int counts = 0);// Метод выводи иерархию объетов
	void print_brunches_readiness(int counts = 0);// Метод выводи иерархию объетов и готовность объектов
	void change_state(int i_new_state);// Метод осуществляет изменение состояния объекта
	bool change_head_object(cl_base* p_head);// Метод переопределяет головной объект для текущего
	void del_sub_object(std::string s_sub_name);// Метод осуществляет удаление подчинённого объекта
	cl_base* search_object_with_coord(std::string s_name);// Метод осуществляет поиск объекта по координате
	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_object,
	TYPE_HANDLER p_ob_hendler); // Метод осущетвляет установку связи
	void delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target,
	TYPE_HANDLER p_handler); // Метод осущетвляет удаление связи
	void emit_signal(TYPE_SIGNAL p_signal, std::string& s_command);// Метод	осущетвляет выдачу сигнала
	std::string get_full_coords();// Метод возвращает абсолютный путь до объекта
	void all_obj_ready(); // Метод приводит все объекты в состояние готовности
	virtual int get_class();
	virtual void signal_f(std::string& msg);
	virtual void handler_f(std::string msg);
	void delete_links(cl_base* p_target); // Удаление связей, указывающих на объект p_target
	std::vector<std::string> split_array(std::string s_tokens);
	bool oper(std::string s_symb);
	int priority(std::string s_symb);
	bool value(std::vector<std::string> vector, std::string pos);
	std::string b_function(bool a, bool b, std::string func);
	std::string b_function(bool a);
	std::string logical_var_output(std::string s_msg);
};
#endif