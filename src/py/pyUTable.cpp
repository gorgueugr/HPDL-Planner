// --------------------------------------------------------------------------------------------
// Definición del tipo SdxUTable que equivale al Type para python.
// --------------------------------------------------------------------------------------------

#include "hpdl/common/constants.hh"
#include "hpdl/py/pythonWrapper.hh"
#include "hpdl/unify/unifierTable.hh"
#include <structmember.h>
#include "pyTerm.cpp"
using namespace std;

#ifdef PYTHON_FOUND
#ifndef SDX_TYPE
#define SDX_TYPE

/**
 * Estructura que define el tipo
 */
typedef struct {
    PyObject_HEAD
    UnifierTable * ut;
    bool init;
    unifierit it;
} SdxUTable;

/**
 * Liberar la memoria ocupada por el tipo
 */
static void SdxUTable_dealloc(SdxUTable * self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}


/**
 * Inicialización del tipo.
 */
static PyObject * SdxUTable_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    SdxUTable *self;

    self = (SdxUTable *)type->tp_alloc(type, 0);
    if (self != NULL) {
	self->ut = 0;
	self->init = false;
    }

    return (PyObject *)self;
}

/**
 * Inicialización de la estructura
 */
static int SdxUTable_init(SdxUTable *self, PyObject *args, PyObject *kwds)
{
    self->ut = 0;
    self->init = false;
    return 0;
}

static PyObject * SdxUTable_str(SdxUTable *self)
{
    ostringstream os;
    if(self->ut){
	self->ut->print(&os);
	return PyUnicode_FromString(os.str().c_str());
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * SdxUTable_next(SdxUTable * self){
    if(self->ut){
	if(!self->init){
	    self->init = true;
	    self->it = self->ut->getUnifierBegin();
	    if(self->it == self->ut->getUnifierEnd()){
		return PyLong_FromLong(0);
	    }

	}
	else if(self->it == self->ut->getUnifierEnd()){
	    return PyLong_FromLong(0);
	}
	else{
	    self->it++;
	    if(self->it == self->ut->getUnifierEnd()){
		return PyLong_FromLong(0);
	    }
	}
	return PyLong_FromLong(1);
    }
    else
	return PyLong_FromLong(0);
};

static PyObject * SdxUTable_get_substitution(SdxUTable * self, PyObject *args){
    PyObject * n;
    pkey term;
    const char * name;
    PyTypeObject * sptr = &SdxTermType;

    if(self->ut == NULL){
		Py_INCREF(Py_None);
		return Py_None;
    }
    if(!self->init){
		Py_INCREF(Py_None);
		return Py_None;
    }
    if(self->it == self->ut->getUnifierEnd()){
		Py_INCREF(Py_None);
		return Py_None;
    }

    // Capturamos la inicialización dada por el usuario
    if (! PyArg_ParseTuple(args, "O", &n)){
		Py_INCREF(Py_None);
		return Py_None;
    }

    if(PyObject_IsInstance(n,(PyObject *) sptr)){
	term = ((SdxTerm *)n)->t;
	if(parser_api->termtable->isVariable(term)){
	   if((*(self->it))->getSubstitution(term.first,&term)){
	       PyObject * t = (PyObject *) PyObject_New(SdxTerm,sptr);
	       ((SdxTerm *)t)->t = term;
	       return t;
	   }
	   else{
	       Py_INCREF(Py_None);
	       return Py_None;
	   }
	}
    }
    else if(PyUnicode_Check(n)){
	// Coger el nombre
	name = PyUnicode_AsUTF8(n);
	// Averiguar si es una variable o un símbolo.
	if(name[0] == '?'){
	   if((*(self->it))->getSubstitution(name,&term)){
	       //PyObject * t = (PyObject *) PyObject_New(SdxTerm, &SdxTermType);
	       //((SdxTerm *)t)->t = term;
	       //return t;
	       ostringstream s;
	       PrintKey pk = PrintKey(&s);
	       pk(term);
	       return PyUnicode_FromString(s.str().c_str());
	   }
	   else{
	       Py_INCREF(Py_None);
	       return Py_None;
	   }
	}
    }

    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject * SdxUTable_reset(SdxUTable * self){
    self->init=false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMemberDef SdxUTable_members[] = {
    {NULL}  /* Sentinel */
};


static PyMethodDef SdxUTable_methods[] = {
    {"next", (PyCFunction)SdxUTable_next, METH_NOARGS,
	"Return true if there is another substutution pending in the unifier table.",
    },
    {"reset", (PyCFunction)SdxUTable_reset, METH_NOARGS,
	"Sets the iterator to the begining.",
    },
    {"get_substitution", (PyCFunction)SdxUTable_get_substitution, METH_VARARGS,
	"Returns the substitution for a given var.",
    },
    {"str", (PyCFunction)SdxUTable_str, METH_NOARGS,
	"Return a string representation of the object.",
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject SdxUTableType = {
    PyVarObject_HEAD_INIT(NULL, 0)
};

/**
 * Inicialización del módulo
 */
static void SdxUTable_initModule(PyObject * m){
    SdxUTableType.tp_name      = "siadex.SdxUTable";
    SdxUTableType.tp_basicsize = sizeof(SdxUTable);
    SdxUTableType.tp_dealloc   = (destructor) SdxUTable_dealloc;
    SdxUTableType.tp_flags     = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    SdxUTableType.tp_doc       = "Siadex unifier table";
    SdxUTableType.tp_methods   = SdxUTable_methods;
    SdxUTableType.tp_members   = SdxUTable_members;
    SdxUTableType.tp_init      = (initproc) SdxUTable_init;
    SdxUTableType.tp_new       = SdxUTable_new;

    if (PyType_Ready(&SdxUTableType) < 0)
        return;
    Py_INCREF(&SdxUTableType);
    PyModule_AddObject(m, "SdxUTable", (PyObject *) &SdxUTableType);
}

#endif
#endif
