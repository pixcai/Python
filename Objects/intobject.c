#include "Python.h"

PyObject *PyInt_FromLong(long ival)
{
  PyIntObject *v;

  v = PyObject_NEW(PyIntObject, &PyInt_Type);
  v->ob_ival = ival;
  return (PyObject *)v;
}

static PyObject *int_add(PyIntObject *v, PyIntObject *w)
{
  return PyInt_FromLong(v->ob_ival + w->ob_ival);
}

static PyObject *int_sub(PyIntObject *v, PyIntObject *w)
{
  return PyInt_FromLong(v->ob_ival - w->ob_ival);
}

static PyObject *int_mul(PyIntObject *v, PyIntObject *w)
{
  return PyInt_FromLong(v->ob_ival * w->ob_ival);
}

static PyObject *int_classic_div(PyIntObject *v, PyIntObject *w)
{
  return PyInt_FromLong(v->ob_ival / w->ob_ival);
}

static void int_dealloc(PyIntObject *v)
{
  PyObject_FREE(v);
}

static PyNumberMethods int_as_number = {
  (binaryfunc)int_add,
  (binaryfunc)int_sub,
  (binaryfunc)int_mul,
  (binaryfunc)int_classic_div,
};

PyTypeObject PyInt_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,      /* ob_size */
  "int",  /* tp_name */
  sizeof(PyIntObject),      /* tp_basicsize */
  0,      /* tp_itemsize */
  (destructor)int_dealloc,  /* tp_dealloc */
  &int_as_number,           /* tp_as_number */
};