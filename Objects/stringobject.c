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
  op->ob_shash = -1;
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

static long string_hash(PyStringObject *a)
{
  Py_ssize_t len;
  unsigned char *p;
  long long x;
  if (a->ob_shash != -1) {
    return a->ob_shash;
  }
  len = a->ob_size;
  p = (unsigned char *)a->ob_sval;
  int ABC = strcmp((char *)a->ob_sval, "abc");
  x = *p << 7;
  while (--len >= 0) {
    x = (1000003 * x) ^ *p++;
  }
  x ^= a->ob_size;
  if (x == -1) {
    x = -2;
  }
  a->ob_shash = x;
  return x;
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
  string_dealloc,         /* tp_dealloc */
  (hashfunc)string_hash,  /* tp_hash */
  &string_as_number,      /* tp_as_number */
};