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

	bool set_name(std::string s_new_name);// ����� ������������ ��������� ����� �������
	std::string get_name();// ����� ���������� ��� �������
	cl_base* get_head();// ����� ���������� ��������� �� �������� ������
	cl_base* get_sub_object(std::string s_name);// ����� ���������� ��������� �� ���������� ������
	cl_base* search_object_on_branch(std::string s_name);// ����� ������������ ����� ������� �� �������� �� �����
	cl_base* search_object_from_root(std::string s_name);// ����� ������������ ����� ������� �� �����
	void print_brunches(int counts = 0);// ����� ������ �������� �������
	void print_brunches_readiness(int counts = 0);// ����� ������ �������� ������� � ���������� ��������
	void change_state(int i_new_state);// ����� ������������ ��������� ��������� �������
	bool change_head_object(cl_base* p_head);// ����� �������������� �������� ������ ��� ��������
	void del_sub_object(std::string s_sub_name);// ����� ������������ �������� ����������� �������
	cl_base* search_object_with_coord(std::string s_name);// ����� ������������ ����� ������� �� ����������
	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_object,
	TYPE_HANDLER p_ob_hendler); // ����� ����������� ��������� �����
	void delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target,
	TYPE_HANDLER p_handler); // ����� ����������� �������� �����
	void emit_signal(TYPE_SIGNAL p_signal, std::string& s_command);// �����	����������� ������ �������
	std::string get_full_coords();// ����� ���������� ���������� ���� �� �������
	void all_obj_ready(); // ����� �������� ��� ������� � ��������� ����������
	virtual int get_class();
	virtual void signal_f(std::string& msg);
	virtual void handler_f(std::string msg);
	void delete_links(cl_base* p_target); // �������� ������, ����������� �� ������ p_target
	std::vector<std::string> split_array(std::string s_tokens);
	bool oper(std::string s_symb);
	int priority(std::string s_symb);
	bool value(std::vector<std::string> vector, std::string pos);
	std::string b_function(bool a, bool b, std::string func);
	std::string b_function(bool a);
	std::string logical_var_output(std::string s_msg);
};
#endif