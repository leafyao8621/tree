#include <Python.h>
#include <iostream>
#include "core/core.h"

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

struct module_state {
    PyObject* error;
};

static PyObject* run(PyObject* self, PyObject* args) {
    const char *fn;
    long iter;
    int verbose;
    if (!PyArg_ParseTuple(args,
                          "slp",
                          &fn,
                          &iter,
                          &verbose)) {
        return NULL;
    }
    try {
        Core::Tree tree(fn);
        for (long i = 0; i < iter; ++i) {
            if (verbose) {
                std::cout << "iter: " << i <<
                " max_down: " << tree.max_sum_down() <<
                " max_up: " << tree.max_sum_up() << '\n';
            }
        }
    } catch (Core::Tree::Err err) {
        switch (err) {
        case Core::Tree::Err::FILE_ACCESS:
            PyErr_SetString(PyExc_RuntimeError, "FILE_ACCESS");
            return NULL;
        case Core::Tree::Err::EMPTY_TREE:
            PyErr_SetString(PyExc_RuntimeError, "EMPTY_TREE");
            return NULL;
        }
    }
    Py_RETURN_NONE;
}


static PyMethodDef _base_methods[] = {
    {"run", (PyCFunction)run, METH_VARARGS, NULL},
    {0}
};

static int _base_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int _base_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "tree.cpp._base",
    NULL,
    sizeof(struct module_state),
    _base_methods,
    NULL,
    _base_traverse,
    _base_clear,
    NULL
};

PyMODINIT_FUNC PyInit__base(void) {
    PyObject *module = PyModule_Create(&moduledef);
    if (!module) return NULL;
    return module;
}
