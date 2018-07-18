#include "Python.h"

void *PyObject_Malloc(size_t nbytes)
{
  return malloc(nbytes);
}

void PyObject_Free(void *p)
{
  free(p);
}

void *PyObject_Realloc(void *p, size_t nbytes)
{
  void *bp = NULL;

  if (p == NULL) {
    return PyObject_Malloc(nbytes);
  }
  /* 因为realloc(p, 0)会释放p，所以必须判断nbytes大于0 */
  if (nbytes) {
    bp = realloc(p, nbytes);
  }
  /* 保证不返回NULL */
  return bp ? bp : p;
}