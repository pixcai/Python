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

  s = PyString_FromString("str: ");
  fputs("Welcome to Python (Use Ctrl+C to exit)\n", stdout);

  while (1)
  {
    fputs(">>> ", stdout);
    fgets(input, BUFSIZ, stdin);
    /* 计算10以内的四则运算，例如：1+2、6+9 */
    v = PyInt_FromLong(atol(&input[0]));
    w = PyInt_FromLong(atol(&input[2]));
    input[3] = '\0';
    PyString_ConcatAndDel(&s, PyString_FromFormat("%s, ", input));
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
    fprintf(stdout, "%ld\n", ((PyIntObject *)x)->ob_ival);
    fprintf(stdout, "%s\n", PyString_AS_STRING(s));
    PyInt_Type.tp_dealloc(v);
    PyInt_Type.tp_dealloc(w);
    PyInt_Type.tp_dealloc(x);
  }
  PyString_Type.tp_dealloc(s);

  return 0;
}