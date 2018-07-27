#ifndef Py_PYTHON_H
#define Py_PYTHON_H

/* 公共头文件 */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Python头文件 */
#include "pyport.h"
#include "pythonrun.h"
#include "object.h"
#include "objimpl.h"
#include "intobject.h"
#include "stringobject.h"
#include "listobject.h"

#define Py_CHARMASK(c) ((c) & 0xff)

#endif