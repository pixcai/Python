#include "Python.h"

/**
 * 命令行的真正入口
 * 函数声明在pyport.h中，在python.c中被使用
 */
int Py_Main(int argc, char **argv)
{
  char input[BUFSIZ];

  fputs("Welcome to Python (Use Ctrl+C to exit)\n", stdout);

  while (1)
  {
    fputs(">>> ", stdout);
    fgets(input, BUFSIZ, stdin);
    fputs(input, stdout);
  }

  return 0;
}