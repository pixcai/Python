#ifndef Py_INTOBJECT_H
#define Py_INTOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  PyObject_HEAD
  long ob_ival;
} PyIntObject;

PyAPI_DATA(PyTypeObject) PyInt_Type;

PyAPI_FUNC(PyObject *) PyInt_FromLong(long);

#ifdef __cplusplus
}
#endif
#endif