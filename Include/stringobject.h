#ifndef Py_StringOBJECT_H
#define Py_StringOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

typedef struct {
  PyObject_VAR_HEAD
  long ob_shash;
  char ob_sval[1];
} PyStringObject;

PyAPI_DATA(PyTypeObject) PyString_Type;

#define PyString_Check(op) PyObject_TypeCheck(op, &PyString_Type)
#define PyString_CheckExact(op) ((op)->ob_type == &PyString_Type)

PyAPI_FUNC(PyObject *) PyString_FromStringAndSize(const char *, Py_ssize_t);
PyAPI_FUNC(PyObject *) PyString_FromString(const char *);
PyAPI_FUNC(PyObject *) PyString_FromFormatV(const char*, va_list);
PyAPI_FUNC(PyObject *) PyString_FromFormat(const char*, ...);
PyAPI_FUNC(Py_ssize_t) PyString_Size(PyObject *);
PyAPI_FUNC(char *) PyString_AsString(PyObject *);
PyAPI_FUNC(void) PyString_Concat(PyObject **, PyObject *);
PyAPI_FUNC(void) PyString_ConcatAndDel(PyObject **, PyObject *);
PyAPI_FUNC(int) _PyString_Resize(PyObject **, Py_ssize_t);

#define PyString_AS_STRING(op) (((PyStringObject *)(op))->ob_sval)
#define PyString_GET_SIZE(op) (((PyStringObject *)(op))->ob_size)

#ifdef __cplusplus
}
#endif
#endif