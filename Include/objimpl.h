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

PyAPI_FUNC(PyObject *) PyObject_Init(PyObject *, PyTypeObject *);

/* 根据PyTypeObject生成PyObject */
PyAPI_FUNC(PyObject *) _PyObject_New(PyTypeObject *);

#define PyObject_New(type, typeobj) ((type *)_PyObject_New(typeobj))

/* 和PyObject_Init函数功能一样，只不过函数版本提供额外的错误处理 */
#define PyObject_INIT(op, typeobj)            \
  ((op)->ob_type = (typeobj), _Py_NewReference((PyObject *)(op)), (op))

#define _PyObject_SIZE(typeobj) ((typeobj)->tp_basicsize)

#define PyObject_NEW(type, typeobj)           \
  ((type *)PyObject_Init(                     \
    (PyObject *)PyObject_MALLOC(_PyObject_SIZE(typeobj)), (typeobj)))

#ifdef __cplusplus
}
#endif
#endif