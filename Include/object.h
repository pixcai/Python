#ifndef Py_OBJECT_H
#define Py_OBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

/** 
 * 固定大小对象
 * ob_refcnt: 对象的引用计数，初始化时为1，为0时对象被销毁
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

typedef void (*destructor)(PyObject *);

typedef struct _typeobject {
  PyObject_VAR_HEAD
  /* 对象的名称 */
  const char *tb_name;
  /* 对象的字节大小 */
  Py_ssize_t tp_basicsize;
  /* 对于可变长度对象，此值为对象单个值的字节大小；对于固定长度对象，此值为0 */
  Py_ssize_t tp_itemsize;
  /* 析构函数 */
  destructor tp_dealloc;
} PyTypeObject;

/* 初始化与反初始化引用值 */
#define _Py_NewReference(op) ((op)->ob_refcnt = 1)
#define _Py_ForgetReference(op)

/* 对象析构 */
#define _Py_Dealloc(op) ((*(op)->ob_type->tp_dealloc)((PyObject *)(op)))

/* 增加与减少引用值 */
#define Py_INCREF(op) ((op)->ob_refcnt++)
#define Py_DECREF(op)             \
  if (--(op)->ob_refcnt <= 0) {   \
    _Py_Dealloc((PyObject *)(op)) \
  }

/* 非空指针时增加与减少引用值 */
#define Py_XINCREF(op) if ((op) != NULL) Py_INCREF(op)
#define Py_XDECINC(op) if ((op) != NULL) Py_DECREF(op)

#ifdef __cplusplus
}
#endif
#endif