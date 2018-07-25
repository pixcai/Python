#include "Python.h"

/* size为列表的长度 */
PyObject *PyList_New(Py_ssize_t size)
{
  PyListObject *op;
  size_t nbytes;

  if (size < 0) {
    return NULL;
  }
  nbytes = size * sizeof(PyObject *);
  op = (PyListObject *)PyObject_MALLOC(_PyObject_SIZE(&PyList_Type));
  if (op == NULL) {
    return NULL;
  }
  PyObject_INIT(op, &PyList_Type);
  if (size <= 0) {
    op->ob_item = NULL;
  } else {
    /* 保存size个对象指针 */
    op->ob_item = (PyObject **)PyObject_MALLOC(nbytes);
    if (op->ob_item == NULL) {
      return NULL;
    }
    memset(op->ob_item, 0, nbytes);
  }
  op->ob_size = size;
  op->allocated = size;
  return (PyObject *)op;
}

Py_ssize_t PyList_Size(PyObject *op)
{
  if (!PyList_Check(op)) {
    return -1;
  }
  return ((PyListObject *)(op))->ob_size;
}

PyObject *PyList_GetItem(PyObject *op, Py_ssize_t i)
{
  if (!PyList_Check(op)) {
    return NULL;
  }
  if (i < 0 || i >= ((PyListObject *)op)->ob_size) {
    return NULL;
  }
  return ((PyListObject *)op)->ob_item[i];
}

int PyList_SetItem(PyObject *op, Py_ssize_t i, PyObject *newitem)
{
  PyObject *olditem;
  PyObject **p;

  if (!PyList_Check(op)) {
    Py_XDECREF(newitem);
    return -1;
  }
  if (i < 0 || i >= ((PyListObject *)op)->ob_size) {
    Py_XDECREF(newitem);
    return -1;
  }
  p = ((PyListObject *)op)->ob_item + i;
  olditem = *p;
  *p = newitem;
  Py_XDECREF(olditem);
  return 0;
}

static void list_dealloc(PyListObject *op)
{
  Py_ssize_t i;

  if (op->ob_item != NULL) {
    i = op->ob_size;
    while (--i >= 0) {
      Py_XDECREF(op->ob_item[i]);
    }
    PyObject_FREE(op->ob_item);
  }
  PyObject_FREE(op);
}

PyTypeObject PyList_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,
  "list",
  sizeof(PyListObject),
  0,
  (destructor)list_dealloc,
  0,
};