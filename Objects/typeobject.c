#include "Python.h"

static void type_dealloc(PyTypeObject *type)
{

}

PyTypeObject PyType_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,      /* ob_size */
  "type", /* tp_name */
  sizeof(PyHeapTypeObject), /* tp_basicsize */
  0,      /* tp_itemsize */
  (destructor)type_dealloc, /* tp_dealloc */
  0,      /* tp_as_number */
};