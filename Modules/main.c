#include "Python.h"

/**
 * 命令行的真正入口
 * 函数声明在pyport.h中，在python.c中被使用
 */
int Py_Main(int argc, char **argv)
{
  PyObject o = {PyObject_HEAD_INIT(NULL)};
  printf("I am PyObject %p\n", &o);
  return 0;
}