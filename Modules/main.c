#include "Python.h"

/**
 * 命令行的真正入口
 * 函数声明在pyport.h中，在python.c中被使用
 */
int Py_Main(int argc, char **argv)
{
  char input[BUFSIZ];
  PyObject v = {PyObject_HEAD_INIT(NULL)};

  fputs("Welcome to Python (Use Ctrl+C to exit)\n", stdout);

  while (1)
  {
    fputs(">>> ", stdout);
    fgets(input, BUFSIZ, stdin);
    Py_INCREF(&v);
    fprintf(stdout, "%s[ob_refcnt: %ld]\n", input, v.ob_refcnt);
  }

  return 0;
}