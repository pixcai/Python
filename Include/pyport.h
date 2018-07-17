#ifndef Py_PYPORT_H
#define Py_PYPORT_H

#include <sys/types.h>

typedef ssize_t Py_ssize_t;

/* 用于声明公共方法 */
#ifndef PyAPI_FUNC
#define PyAPI_FUNC(RTYPE) RTYPE
#endif
/* 用于声明公共数据 */
#ifndef PyAPI_DATA
#define PyAPI_DATA(RTYPE) extern RTYPE
#endif

#endif