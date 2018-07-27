#include "Python.h"

/**
 * 初始化PyObject的引用计数为1
 * 函数的功能需要和PyObject_INIT宏保持一致
 */
PyObject *PyObject_Init(PyObject *op, PyTypeObject *tp)
{
  if (op == NULL) {
    return NULL;
  }
  op->ob_type = tp;
  _Py_NewReference(op);
  return op;
}

/**
 * 初始化PyVarObject的引用计数为1
 * 函数的功能需要和PyObject_INIT_VAR宏保持一致
 */
PyVarObject *PyObject_InitVar(PyVarObject *op, PyTypeObject *tp, Py_ssize_t size)
{
  if (op == NULL) {
    return NULL;
  }
  op->ob_size = size;
  op->ob_type = tp;
  _Py_NewReference((PyObject *)op);
  return op;
}

/* 根据PyTypeObject提供的数据构造PyObject */
PyObject *_PyObject_New(PyTypeObject *tp)
{
  PyObject *op;
  op = (PyObject *)PyObject_MALLOC(_PyObject_SIZE(tp));
  if (op == NULL) {
    return NULL;
  }
  return PyObject_INIT(op, tp);
}

/* 根据PyTypeObject提供的数据构造PyVarObject */
PyVarObject *_PyObject_NewVar(PyTypeObject *tp, Py_ssize_t nitems)
{
  PyVarObject *op;
  const size_t size = _PyObject_VAR_SIZE(tp, nitems);
  op = (PyVarObject *)PyObject_MALLOC(size);
  if (op == NULL) {
    return NULL;
  }
  return PyObject_INIT_VAR(op, tp, nitems);
}

/* 将对象的地址作为哈希值 */
long _Py_HashPointer(void *p)
{
  return (long)p;
}

long PyObject_Hash(PyObject *v)
{
  PyTypeObject *tp = v->ob_type;
  if (tp->tp_hash != NULL) {
    return (*tp->tp_hash)(v);
  }
  return -1;
}

void *PyMem_Malloc(size_t nbytes)
{
  return PyMem_MALLOC(nbytes);
}

void *PyMem_Realloc(void *p, size_t nbytes)
{
  return PyMem_REALLOC(p, nbytes);
}

void PyMem_Free(void *p)
{
  PyMem_FREE(p);
}