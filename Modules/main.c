#include "Python.h"

/**
 * 命令行的真正入口
 * 函数声明在pyport.h中，在python.c中被使用
 */
int Py_Main(int argc, char **argv)
{
  char input[BUFSIZ];
  PyObject *v, *w, *x;
  PyObject *s;

  fputs("Welcome to Python (Use Ctrl+C to exit)\n", stdout);

  while (1)
  {
    fputs(">>> ", stdout);
    fgets(input, BUFSIZ, stdin);
    /* 计算10以内的四则运算，例如：1+2、6+9 */
    v = PyInt_FromLong(atol(&input[0]));
    w = PyInt_FromLong(atol(&input[2]));
    s = PyString_FromStringAndSize(input, 3);
    switch (input[1])
    {
      case '+':
        x = PyInt_Type.tp_as_number->nb_add(v, w);
        break;
      case '-':
        x = PyInt_Type.tp_as_number->nb_subtract(v, w);
        break;
      case '*':
        x = PyInt_Type.tp_as_number->nb_multiply(v, w);
        break;
      case '/':
        x = PyInt_Type.tp_as_number->nb_divide(v, w);
        break;
    }
    fprintf(stdout, "%s=%ld\n", PyString_AsString(s), ((PyIntObject *)x)->ob_ival);
    fprintf(stdout, "<class '%s'>\n", x->ob_type->tp_name);
    PyInt_Type.tp_dealloc(v);
    PyInt_Type.tp_dealloc(w);
    PyInt_Type.tp_dealloc(x);
    PyString_Type.tp_dealloc(s);
  }

  return 0;
}