#ifndef Py_LISTOBJECT_H
#define Py_LISTOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  PyObject_VAR_HEAD
  PyObject **ob_item;
  Py_ssize_t allocated;
} PyListObject;

PyAPI_DATA(PyTypeObject) PyList_Type;

#define PyList_Check(op) PyObject_TypeCheck(op, &PyList_Type)
#define PyList_CheckExact(op) ((op)->ob_type == &PyList_Type)

PyAPI_FUNC(PyObject *) PyList_New(Py_ssize_t);
PyAPI_FUNC(Py_ssize_t) PyList_Size(PyObject *);
PyAPI_FUNC(PyObject *) PyList_GetItem(PyObject *, Py_ssize_t);
PyAPI_FUNC(int) PyList_SetItem(PyObject *, Py_ssize_t, PyObject *);
PyAPI_FUNC(int) PyList_Insert(PyObject *, Py_ssize_t, PyObject *);
PyAPI_FUNC(int) PyList_Append(PyObject *, PyObject *);

/* 牺牲类型安全换取速度 */
#define PyList_GET_ITEM(op, i) (((PyListObject *)(op))->ob_item[i])
#define PyList_SET_ITEM(op, i, v) (((PyListObject *)(op))->ob_item[i] = (v))
#define PyList_GET_SIZE(op) (((PyListObject *)(op))->ob_size)

#ifdef __cplusplus
}
#endif
#endif