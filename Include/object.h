#ifndef Py_OBJECT_H
#define Py_OBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

/** 
 * 固定大小对象
 * ob_refcnt: 对象的引用计数，初始化为1，为0时对象被销毁
 * ob_type: 对象的类型对象
 */
#define PyObject_HEAD             \
  Py_ssize_t ob_refcnt;           \
  struct _typeobject *ob_type;

/**
 * 可变长度对象
 * ob_size: 对象的值的长度
 */
#define PyObject_VAR_HEAD         \
  PyObject_HEAD                   \
  Py_ssize_t ob_size;

/* 初始化对象的引用计数为1 */
#define PyObject_HEAD_INIT(type)  \
  1, type,

typedef struct _object {
  PyObject_HEAD
} PyObject;

typedef struct _typeobject {
  PyObject_VAR_HEAD
  /* 对象的名称 */
  const char *tb_name;
  /* 对象的字节大小 */
  Py_ssize_t tp_basicsize;
  /* 对于可变长度对象，此值为对象单个值的字节大小；对于固定长度对象，此值为0 */
  Py_ssize_t tp_itemsize;
} PyTypeObject;

#ifdef __cplusplus
}
#endif
#endif