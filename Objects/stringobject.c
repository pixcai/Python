#include "Python.h"

PyObject *PyString_FromStringAndSize(const char *str, Py_ssize_t size)
{
  PyStringObject *op;
  assert(size >= 0);
  op = (PyStringObject *)PyObject_MALLOC(sizeof(PyStringObject) + size);
  if (op == NULL) {
    return NULL;
  }
  PyObject_INIT_VAR(op, &PyString_Type, size);
  if (str != NULL) {
    Py_MEMCPY(op->ob_sval, str, size);
  }
  op->ob_sval[size] = '\0';
  return (PyObject *)op;
}

PyObject *PyString_FromString(const char *str)
{
  size_t size;
  assert(str != NULL);
  size = strlen(str);
  return PyString_FromStringAndSize(str, size);
}

Py_ssize_t PyString_Size(PyObject *op)
{
  return ((PyStringObject *)op)->ob_size;
}

char *PyString_AsString(PyObject *op)
{
  return ((PyStringObject *)op)->ob_sval;
}

static void string_dealloc(PyObject *op)
{
  PyObject_FREE(op);
}

static PyNumberMethods string_as_number = {
  0,          /* nb_add */
  0,          /* nb_subtract */
  0,          /* nb_multiply */
  0,          /* nb_divide */
};

PyTypeObject PyString_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,
  "str",
  sizeof(PyStringObject),
  sizeof(char),
  string_dealloc,
  &string_as_number,
};