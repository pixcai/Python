#include "Python.h"

int PyType_IsSubType(PyTypeObject *a, PyTypeObject *b)
{
  return 1;
}

static void type_dealloc(PyTypeObject *type)
{

}

PyTypeObject PyType_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,      /* ob_size */
  "type", /* tp_name */
  sizeof(PyHeapTypeObject),   /* tp_basicsize */
  0,      /* tp_itemsize */
  (destructor)type_dealloc,   /* tp_dealloc */
  (hashfunc)_Py_HashPointer,  /* tp_hash */
  0,      /* tp_as_number */
};