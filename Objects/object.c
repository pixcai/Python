#include "Python.h"

/**
 * 构造一个PyObject并初始化引用计数为1
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

PyObject *_PyObject_New(PyTypeObject *tp)
{
  PyObject *op;
  op = (PyObject *)PyObject_MALLOC(_PyObject_SIZE(tp));
  if (op == NULL) {
    return NULL;
  }
  return PyObject_INIT(op, tp);
}