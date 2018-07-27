#ifndef Py_PYMEM_H
#define Py_PYMEM_H

#include "pyport.h"

#ifdef __cplusplus
extern "C" {
#endif

PyAPI_FUNC(void *) PyMem_Malloc(size_t);
PyAPI_FUNC(void *) PyMem_Realloc(void *, size_t);
PyAPI_FUNC(void) PyMem_Free(void *);

#define PyMem_MALLOC(n) malloc((n) ? (n) : 1)
#define PyMem_REALLOC(p, n) realloc((p), (n) ? (n) : 1)
#define PyMem_FREE free

#define PyMem_New(type, n)  \
  (assert((n) <= PY_SIZE_MAX / sizeof(type)), \
  ((type *)PyMem_Malloc((n) * sizeof(type))))
#define PyMem_NEW(type, n)  \
  (assert((n) <= PY_SIZE_MAX / sizeof(type)), \
  ((type *)PyMem_MALLOC((n) * sizeof(type))))

#define PyMem_Resize(p, type, n)  \
  (assert((n) <= PY_SIZE_MAX / sizeof(type)), \
  ((p) = (type *)PyMem_Realloc((p), (n) * sizeof(type))))
#define PyMem_RESIZE(p, type, n)  \
  (assert((n) <= PY_SIZE_MAX / sizeof(type)), \
  ((p) = (type *)PyMem_REALLOC((p), (n) * sizeof(type))))

#define PyMem_Del PyMem_Free
#define PyMem_DEL PyMem_FREE

#ifdef __cplusplus
}
#endif
#endif