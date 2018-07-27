#include "Python.h"
#include <ctype.h>

PyObject *PyString_FromStringAndSize(const char *str, Py_ssize_t size)
{
  PyStringObject *op;
  assert(size >= 0);
  op = (PyStringObject *)PyObject_MALLOC(sizeof(PyStringObject) + size);
  if (op == NULL) {
    return NULL;
  }
  PyObject_INIT_VAR(op, &PyString_Type, size);
  if (str != NULL) {
    Py_MEMCPY(op->ob_sval, str, size);
  }
  op->ob_shash = -1;
  op->ob_sval[size] = '\0';
  return (PyObject *)op;
}

PyObject *PyString_FromString(const char *str)
{
  size_t size;
  assert(str != NULL);
  size = strlen(str);
  return PyString_FromStringAndSize(str, size);
}

PyObject *PyString_FromFormatV(const char *format, va_list vargs)
{
  va_list count;
  Py_ssize_t n = 0;
  const char* f;
  char *s;
  PyObject* string;

  Py_MEMCPY(count, vargs, sizeof(va_list));
  for (f = format; *f; f++) {
    if (*f == '%') {
      const char* p = f;
      while (*++f && *f != '%' && !isalpha(Py_CHARMASK(*f)));
      if ((*f == 'l' || *f == 'z') && (f[1] == 'd' || f[1] == 'u')) {
        ++f;
      }
      switch (*f) {
        case 'c':
          (void)va_arg(count, int);
        case '%':
          n++;
          break;
        case 'd': case 'u': case 'i': case 'x':
          (void)va_arg(count, int);
          n += 20;
          break;
        case 's':
          s = va_arg(count, char*);
          n += strlen(s);
          break;
        case 'p':
          (void)va_arg(count, int);
          n += 19;
          break;
        default:
          n += strlen(p);
          goto expand;
      }
    } else {
      n++;
    }
  }
expand:
  string = PyString_FromStringAndSize(NULL, n);
  if (!string) {
    return NULL;
  }
  s = PyString_AsString(string);
  for (f = format; *f; f++) {
    if (*f == '%') {
      const char* p = f++;
      Py_ssize_t i;
      int longflag = 0;
      int size_tflag = 0;
      n = 0;
      while (isdigit(Py_CHARMASK(*f))) {
        n = (n*10) + *f++ - '0';
      }
      if (*f == '.') {
        f++;
        n = 0;
        while (isdigit(Py_CHARMASK(*f))) {
          n = (n*10) + *f++ - '0';
        }
      }
      while (*f && *f != '%' && !isalpha(Py_CHARMASK(*f))) {
        f++;
      }
      if (*f == 'l' && (f[1] == 'd' || f[1] == 'u')) {
        longflag = 1;
        ++f;
      }
      if (*f == 'z' && (f[1] == 'd' || f[1] == 'u')) {
        size_tflag = 1;
        ++f;
      }
      switch (*f) {
        case 'c':
          *s++ = va_arg(vargs, int);
          break;
        case 'd':
          if (longflag) {
            sprintf(s, "%ld", va_arg(vargs, long));
          } else if (size_tflag) {
            sprintf(s, "%" PY_FORMAT_SIZE_T "d", va_arg(vargs, Py_ssize_t));
          } else {
            sprintf(s, "%d", va_arg(vargs, int));
          }
          s += strlen(s);
          break;
        case 'u':
          if (longflag) {
            sprintf(s, "%lu", va_arg(vargs, unsigned long));
          } else if (size_tflag) {
            sprintf(s, "%" PY_FORMAT_SIZE_T "u", va_arg(vargs, size_t));
          } else {
            sprintf(s, "%u", va_arg(vargs, unsigned int));
          }
          s += strlen(s);
          break;
        case 'i':
          sprintf(s, "%i", va_arg(vargs, int));
          s += strlen(s);
          break;
        case 'x':
          sprintf(s, "%x", va_arg(vargs, int));
          s += strlen(s);
          break;
        case 's':
          p = va_arg(vargs, char*);
          i = strlen(p);
          if (n > 0 && i > n) {
            i = n;
          }
          Py_MEMCPY(s, p, i);
          s += i;
          break;
        case 'p':
          sprintf(s, "%p", va_arg(vargs, void*));
          if (s[1] == 'X') {
            s[1] = 'x';
          }
          else if (s[1] != 'x') {
            memmove(s+2, s, strlen(s)+1);
            s[0] = '0';
            s[1] = 'x';
          }
          s += strlen(s);
          break;
        case '%':
          *s++ = '%';
          break;
        default:
          strcpy(s, p);
          s += strlen(s);
          goto end;
      }
    } else {
      *s++ = *f;
    }
  }
end:
  _PyString_Resize(&string, s - PyString_AS_STRING(string));
  return string;
}

PyObject *PyString_FromFormat(const char *format, ...)
{
  PyObject *ret;
  va_list vargs;

  va_start(vargs, format);
  ret = PyString_FromFormatV(format, vargs);
  va_end(vargs);
  return ret;
}

Py_ssize_t PyString_Size(PyObject *op)
{
  return ((PyStringObject *)op)->ob_size;
}

char *PyString_AsString(PyObject *op)
{
  return ((PyStringObject *)op)->ob_sval;
}

static PyObject *string_concat(PyStringObject *a, PyObject *bb)
{
  Py_ssize_t size;
  PyStringObject *op;
  if (!PyString_Check(bb)) {
    return NULL;
  }
#define b ((PyStringObject *)bb)
  if ((a->ob_size == 0 || b->ob_size == 0) &&
      PyString_CheckExact(a) && PyString_CheckExact(b)) {
    if (a->ob_size == 0) {
      Py_INCREF(bb);
      return bb;
    }
    Py_INCREF(a);
    return (PyObject *)a;
  }
  size = a->ob_size + b->ob_size;
  if (size < 0) {
    return NULL;
  }
  op = (PyStringObject *)PyObject_MALLOC(sizeof(PyStringObject) + size);
  if (op == NULL) {
    return NULL;
  }
  PyObject_INIT_VAR(op, &PyString_Type, size);
  op->ob_shash = -1;
  Py_MEMCPY(op->ob_sval, a->ob_sval, a->ob_size);
  Py_MEMCPY(op->ob_sval + a->ob_size, b->ob_sval, b->ob_size);
  op->ob_sval[size] = '\0';
  return (PyObject *)op;
#undef b
}

void PyString_Concat(PyObject **pv, PyObject *w)
{
  PyObject *v;
  if (*pv == NULL) {
    return;
  }
  if (w == NULL || !PyString_Check(*pv)) {
    Py_DECREF(*pv);
    *pv = NULL;
    return;
  }
  v = string_concat((PyStringObject *)*pv, w);
  Py_DECREF(*pv);
  *pv = v;
}

void PyString_ConcatAndDel(PyObject **pv, PyObject *w)
{
  PyString_Concat(pv, w);
  Py_XDECREF(w);
}

int _PyString_Resize(PyObject **pv, Py_ssize_t newsize)
{
  PyObject *v;
  PyStringObject *sv;
  v = *pv;
  if (!PyString_Check(v) || v->ob_refcnt != 1 || newsize < 0) {
    *pv = 0;
    Py_DECREF(v);
    return -1;
  }
  _Py_ForgetReference(v);
  *pv = (PyObject *)PyObject_REALLOC((char *)v, sizeof(PyStringObject) + newsize);
  if (*pv == NULL) {
    PyObject_Del(v);
    return -1;
  }
  _Py_NewReference(*pv);
  sv = (PyStringObject *)*pv;
  sv->ob_size = newsize;
  sv->ob_sval[newsize] = '\0';
  sv->ob_shash = -1;
  return 0;
}

static void string_dealloc(PyObject *op)
{
  PyObject_FREE(op);
}

static long string_hash(PyStringObject *a)
{
  Py_ssize_t len;
  unsigned char *p;
  long long x;
  if (a->ob_shash != -1) {
    return a->ob_shash;
  }
  len = a->ob_size;
  p = (unsigned char *)a->ob_sval;
  int ABC = strcmp((char *)a->ob_sval, "abc");
  x = *p << 7;
  while (--len >= 0) {
    x = (1000003 * x) ^ *p++;
  }
  x ^= a->ob_size;
  if (x == -1) {
    x = -2;
  }
  a->ob_shash = x;
  return x;
}

static PyNumberMethods string_as_number = {
  0,          /* nb_add */
  0,          /* nb_subtract */
  0,          /* nb_multiply */
  0,          /* nb_divide */
};

PyTypeObject PyString_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,
  "str",
  sizeof(PyStringObject),
  sizeof(char),
  string_dealloc,         /* tp_dealloc */
  (hashfunc)string_hash,  /* tp_hash */
  &string_as_number,      /* tp_as_number */
};