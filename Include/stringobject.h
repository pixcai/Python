#ifndef Py_StringOBJECT_H
#define Py_StringOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  PyObject_VAR_HEAD
  char ob_sval[1];
} PyStringObject;

PyAPI_DATA(PyTypeObject) PyString_Type;

#define PyString_Check(op) PyObject_TypeCheck(op, &PyString_Type)
#define PyString_CheckExact(op) ((op)->ob_type == &PyString_Type)

PyAPI_FUNC(PyObject *) PyString_FromStringAndSize(const char *, Py_ssize_t);
PyAPI_FUNC(PyObject *) PyString_FromString(const char *);
PyAPI_FUNC(Py_ssize_t) PyString_Size(PyObject *);
PyAPI_FUNC(char *) PyString_AsString(PyObject *);

#ifdef __cplusplus
}
#endif
#endif