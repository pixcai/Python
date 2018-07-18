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

#ifdef __cplusplus
}
#endif
#endif