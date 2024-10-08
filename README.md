Логический калькулятор
===================================================================================================================================
Структура проекта
-----------
* `main.cpp` - файл запуска всего приложения;
* `cl_application.hpp` - файл с созданием дерева объектов и установкой связей;
* `cl_base` - файл с программными функциями;
* `cl_input.cpp` - файл осуществляющий считывание строки с формулой;
* `cl_logical_var.cpp` - файл осуществляющий формирование множества пропозициональных (логических) переменных;
* `cl_rev_pol.cpp` - файл осуществляющий формирование обратной польской нотации;
* `cl_func_value.cpp` - файл осуществляющий вычисление уравнения;
* `cl_output.cpp` - файл осуществляющий вывод значения переменных;

Используемые технологии:
-----------
* Дерево иерархии объектов;
* Общение объектов с помощью сигналов и обработчиков;
* Директивы препроцессора.

Функционал:
-----------
Программа принимает две строки, первая это само логическое уравнение(формула обязательно должна кончаться точкой), вторая это значение переменных.\
\
Пример:
```
c <=> NOT ( a XOR b OR a AND c ) => b XOR c.
a = 0 b = 1 c = 1
```
\
После чего в консоль выведется три строки : значение каждой переменной, заданное уравнение в обратной польской нотации, результат вычислений.\
\
Пример:
```
Values: a = false b = true c = true
Polish Notation: c a b XOR a c AND OR NOT b c XOR => <=>
Result: false
```
\
После выполнения вычислений пользователь может как внести ещё одно уравнение или завершить программу, для этого надо ввести символ ".".
