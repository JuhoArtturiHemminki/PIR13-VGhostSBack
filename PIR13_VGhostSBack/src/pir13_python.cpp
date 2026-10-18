#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "pir13_core.h"

static PyObject* py_pir13_platform_create(PyObject* self, PyObject* args) {
    Py_ssize_t gigabytes;
    if (!PyArg_ParseTuple(args, "n", &gigabytes)) {
        return NULL;
    }
    void* platform = pir13_platform_create(static_cast<size_t>(gigabytes));
    if (!platform) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to allocate PIR13 Platform.");
        return NULL;
    }
    return PyCapsule_New(platform, "pir13_platform_ctx", NULL);
}

static PyObject* py_pir13_platform_process(PyObject* self, PyObject* args) {
    PyObject* capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return NULL;
    }
    void* platform = PyCapsule_GetPointer(capsule, "pir13_platform_ctx");
    if (!platform) {
        return NULL;
    }
    
    Py_BEGIN_ALLOW_THREADS
    pir13_platform_process(platform);
    Py_END_ALLOW_THREADS
    
    Py_RETURN_NONE;
}

static PyObject* py_pir13_platform_get_latency(PyObject* self, PyObject* args) {
    PyObject* capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return NULL;
    }
    void* platform = PyCapsule_GetPointer(capsule, "pir13_platform_ctx");
    if (!platform) {
        return NULL;
    }
    return PyFloat_FromDouble(pir13_platform_get_latency(platform));
}

static PyObject* py_pir13_platform_get_gflops(PyObject* self, PyObject* args) {
    PyObject* capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return NULL;
    }
    void* platform = PyCapsule_GetPointer(capsule, "pir13_platform_ctx");
    if (!platform) {
        return NULL;
    }
    return PyFloat_FromDouble(pir13_platform_get_gflops(platform));
}

static PyObject* py_pir13_platform_run_diagnostics(PyObject* self, PyObject* args) {
    PyObject* capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return NULL;
    }
    void* platform = PyCapsule_GetPointer(capsule, "pir13_platform_ctx");
    if (!platform) {
        return NULL;
    }
    pir13_platform_run_diagnostics(platform);
    Py_RETURN_NONE;
}

static PyObject* py_pir13_platform_destroy(PyObject* self, PyObject* args) {
    PyObject* capsule;
    if (!PyArg_ParseTuple(args, "O", &capsule)) {
        return NULL;
    }
    void* platform = PyCapsule_GetPointer(capsule, "pir13_platform_ctx");
    if (platform) {
        pir13_platform_destroy(platform);
    }
    Py_RETURN_NONE;
}

static PyMethodDef Pir13Methods[] = {
    {"create", py_pir13_platform_create, METH_VARARGS, NULL},
    {"process", py_pir13_platform_process, METH_VARARGS, NULL},
    {"get_latency", py_pir13_platform_get_latency, METH_VARARGS, NULL},
    {"get_gflops", py_pir13_platform_get_gflops, METH_VARARGS, NULL},
    {"run_diagnostics", py_pir13_platform_run_diagnostics, METH_VARARGS, NULL},
    {"destroy", py_pir13_platform_destroy, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pir13module = {
    PyModuleDef_HEAD_INIT,
    "pir13_vghost",
    NULL,
    -1,
    Pir13Methods
};

PyMODINIT_FUNC PyInit_pir13_vghost(void) {
    return PyModule_Create(&pir13module);
}
