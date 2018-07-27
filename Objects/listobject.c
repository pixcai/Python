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

static int list_resize(PyListObject *self, Py_ssize_t newsize)
{
  PyObject **items;
  size_t new_allocated;
  Py_ssize_t allocated = self->allocated;

  if (allocated >= newsize && newsize >= (allocated >> 1)) {
    assert(self->ob_item != NULL || newsize == 0);
    self->ob_size = newsize;
    return 0;
  }
  new_allocated = (newsize >> 3) + (newsize < 9 ? 3 : 6);
  if (new_allocated > PY_SIZE_MAX - newsize) {
    return -1;
  } else {
    new_allocated += newsize;
  }
  if (newsize == 0) {
    new_allocated = 0;
  }
  items = self->ob_item;
  if (new_allocated <= ((~(size_t)0) / sizeof(PyObject *))) {
    PyMem_RESIZE(items, PyObject *, new_allocated);
  } else {
    items = NULL;
  }
  if (items == NULL) {
    return -1;
  }
  self->ob_item = items;
  self->ob_size = newsize;
  self->allocated = new_allocated;
  return 0;
}

static int
ins1(PyListObject *self, Py_ssize_t where, PyObject *v)
{
  Py_ssize_t i, n = self->ob_size;
  PyObject **items;
  if (v == NULL) {
    return -1;
  }
  if (n == PY_SSIZE_T_MAX) {
    return -1;
  }
  if (list_resize(self, n + 1) == -1) {
    return -1;
  }
  if (where < 0) {
    where += n;
    if (where < 0) {
      where = 0;
    }
  }
  if (where > n) {
    where = n;
  }
  items = self->ob_item;
  for (i = n; --i >= where;) {
    items[i+1] = items[i];
  }
  Py_INCREF(v);
  items[where] = v;
  return 0;
}

int PyList_Insert(PyObject *op, Py_ssize_t where, PyObject *newitem)
{
  if (!PyList_Check(op)) {
    return -1;
  }
  return ins1((PyListObject *)op, where, newitem);
}

static int app1(PyListObject *self, PyObject *v)
{
  Py_ssize_t n = PyList_GET_SIZE(self);
  assert(v != NULL);
  if (n == PY_SSIZE_T_MAX) {
    return -1;
  }
  if (list_resize(self, n + 1) == -1) {
    return -1;
  }
  Py_INCREF(v);
  PyList_SET_ITEM(self, n, v);
  return 0;
}

int PyList_Append(PyObject *op, PyObject *newitem)
{
  if (PyList_Check(op) && (newitem != NULL)) {
    return app1((PyListObject *)op, newitem);
  }
  return -1;
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

static long list_nohash(PyObject *self)
{
  return -1;
}

PyTypeObject PyList_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,
  "list",
  sizeof(PyListObject),
  0,
  (destructor)list_dealloc, /* tp_dealloc */
  list_nohash,              /* tp_hash */
  0,
};