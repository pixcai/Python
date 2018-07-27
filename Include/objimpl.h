#ifndef Py_OBJIMPL_H
#define Py_OBJIMPL_H

#include "pyport.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 内存的分配、重新分配与释放函数 */
PyAPI_FUNC(void *) PyObject_Malloc(size_t);
PyAPI_FUNC(void *) PyObject_Realloc(void *, size_t);
PyAPI_FUNC(void) PyObject_Free(void *);

/* 宏版本的内存操作函数，使用时应该用这些，不去关心具体如何实现 */
#define PyObject_MALLOC  PyObject_Malloc
#define PyObject_REALLOC PyObject_Realloc
#define PyObject_FREE    PyObject_Free

#define PyObject_Del PyObject_Free
#define PyObject_DEL PyObject_FREE

PyAPI_FUNC(PyObject *) PyObject_Init(PyObject *, PyTypeObject *);
PyAPI_FUNC(PyVarObject *) PyObject_InitVar(PyVarObject *, PyTypeObject *, Py_ssize_t);

/* 根据PyTypeObject生成PyObject */
PyAPI_FUNC(PyObject *) _PyObject_New(PyTypeObject *);
PyAPI_FUNC(PyVarObject *) _PyObject_NewVar(PyTypeObject *, Py_ssize_t);

#define PyObject_New(type, typeobj) ((type *)_PyObject_New(typeobj))
#define PyObject_NewVar(type, typeobj, n) ((type *)_PyObject_New((typeobj), (n)))

/* 和PyObject_Init函数功能一样，只不过函数版本提供额外的错误处理 */
#define PyObject_INIT(op, typeobj)            \
  ((op)->ob_type = (typeobj), _Py_NewReference((PyObject *)(op)), (op))
#define PyObject_INIT_VAR(op, typeobj, size)  \
  ((op)->ob_size = (size), PyObject_INIT((op), (typeobj)))

#define _PyObject_SIZE(typeobj) ((typeobj)->tp_basicsize)
#define _PyObject_VAR_SIZE(typeobj, nitems)   \
  (size_t)(((typeobj)->tp_basicsize +         \
    (nitems) * (typeobj)->tp_itemsize +       \
      (SIZEOF_VOID_P - 1)) & ~(SIZEOF_VOID_P - 1))

#define PyObject_NEW(type, typeobj)           \
  ((type *)PyObject_Init(                     \
    (PyObject *)PyObject_MALLOC(_PyObject_SIZE(typeobj)), (typeobj)))
#define PyObject_NEW_VAR(type, typeobj, n)    \
  ((type *)PyObject_InitVar(                  \
      (PyVarObject *)PyObject_MALLOC(_PyObject_VAR_SIZE((typeobj), (n))), (typeobj), (n)))

#ifdef __cplusplus
}
#endif
#endif