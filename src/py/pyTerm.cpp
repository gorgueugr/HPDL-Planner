// --------------------------------------------------------------------------------------------
// Definición del tipo SdxTerm que equivale al Term para python.
// --------------------------------------------------------------------------------------------

#include "hpdl/common/constants.hh"
#include "hpdl/py/pythonWrapper.hh"
#include "hpdl/parser/papi.hh"
#include "hpdl/domain/domain.hh"
#include "hpdl/common/type.hh"
#include <structmember.h>
#include "hpdl/common/constantsymbol.hh"
#include "hpdl/common/variablesymbol.hh"
using namespace std;

#ifdef PYTHON_FOUND

/**
 * Estructura que define el tipo
 */
typedef struct {
    PyObject_HEAD
    pkey t;
} SdxTerm;

/**
 * Liberar la memoria ocupada por el tipo
 */
static void SdxTerm_dealloc(SdxTerm * self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}


/**
 * Inicialización del tipo.
 */
static PyObject * SdxTerm_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    SdxTerm *self;
    self = (SdxTerm *)type->tp_alloc(type, 0);
    self->t = make_pair(-1,0);
    return (PyObject *)self;
}

/**
 * Inicialización de la estructura
 */
static int SdxTerm_init(SdxTerm *self, PyObject *args, PyObject *kwds)
{
    PyObject *n;
    const char * name;

    // Capturamos la inicialización dada por el usuario
    if (! PyArg_ParseTuple(args, "O", &n)){
        return -1;
    }

    if(PyUnicode_Check(n)){
	// Coger el nombre
	name = PyUnicode_AsUTF8(n);
	// Averiguar si es una variable o un símbolo.
	if(name[0] == '?'){
	    // Es una variable
	    int n = parser_api->domain->metainfo.size();
	    VariableSymbol * v = new VariableSymbol(-1,n);
	    Meta * mt = new Meta(name,0,-1);
	    self->t = parser_api->termtable->addVariable(v);
	    parser_api->domain->metainfo.push_back(mt);
	}
	else{
	    // Es un símbolo
	    // la constante debería haberse definido con anterioridad, en otro caso
	    // se trata de un error
	    ldictionaryit posit = (parser_api->domain->cdictionary).find(name);
	    if(posit != (parser_api->domain->ldictionary).end()) {
		// devolver el pkey de la constante
		self->t = make_pair((*posit).second, 0);
	    }
	    else {
                *errflow << "Python warning: Undefined constant `" << name;
                *errflow << "'. During term initialization. " << endl;
                ConstantSymbol * n = new ConstantSymbol(name,-1);
                n->setLineNumber(0);
                n->setFileId(-1);
                self->t = parser_api->termtable->addConstant(n);
	    }
	}
    }
    // chequear si es un flotante
    else if(PyFloat_Check(n)){
	self->t = make_pair(-1,(float)PyFloat_AsDouble(n));
    }
    // chequear si es un entero
    else if(PyLong_Check(n)){
	self->t = make_pair(-1,(float)PyLong_AsLong(n));
    }
    else{
	return -1;
    }

    return 0;
}

/**
 * Inicialización de la estructura
 */
static PyObject * SdxTerm_set_type(SdxTerm *self, PyObject *args, PyObject *kwds)
{
    PyObject *n;
    const char * name;

    // Mirar si soy una variable, si no lo soy no se me puede añadir un tipo
    if(!parser_api->termtable->isVariable(self->t)){
        return PyLong_FromLong(-1);
    };

    // Capturamos la inicialización dada por el usuario
    if (! PyArg_ParseTuple(args, "O", &n)){
        return PyLong_FromLong(-1);
    }

    if(PyUnicode_Check(n)){
	// Coger el nombre
	name = PyUnicode_AsUTF8(n);
	// Buscar ahora si hay un tipo con ese nombre
	Type * t = parser_api->domain->getModificableType(name);
	if(!t)
	    return PyLong_FromLong(-1);
	VariableSymbol * v = parser_api->termtable->getVariable(self->t);
	v->addType(t);
    }
    else{
        return PyLong_FromLong(-1);
    }
    return PyLong_FromLong(0);
};

/**
 * wrapper función de impresión.
 */
static PyObject * SdxTerm_str(SdxTerm * self){
    PyObject * result;
    ostringstream s;

    PrintKey pk = PrintKey(&s);
    pk(self->t);
    result = PyUnicode_FromString(s.str().c_str());
    return result;
};

static int SdxTerm_print(SdxTerm * self, FILE * fp, int flags){
    ostringstream s;

    PrintKey pk = PrintKey(&s);
    pk(self->t);
    fprintf(fp,"%s",s.str().c_str());
    return 0;
};


static PyMemberDef SdxTerm_members[] = {
    {NULL}  /* Sentinel */
};


static PyMethodDef SdxTerm_methods[] = {
    {"set_type", (PyCFunction)SdxTerm_set_type, METH_VARARGS,
	"Stablish a new type for a variable.",
    },
    {"str", (PyCFunction)SdxTerm_str, METH_VARARGS,
	"Returns a textual representation of the object.",
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject SdxTermType = {
    PyVarObject_HEAD_INIT(NULL, 0)
};

/**
 * Inicialización del módulo
 */
static void SdxTerm_initModule(PyObject * m){
    SdxTermType.tp_name      = "siadex.SdxTerm";
    SdxTermType.tp_basicsize = sizeof(SdxTerm);
    SdxTermType.tp_dealloc   = (destructor) SdxTerm_dealloc;
    SdxTermType.tp_str       = (reprfunc) SdxTerm_str;
    SdxTermType.tp_flags     = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    SdxTermType.tp_doc       = "Siadex term";
    SdxTermType.tp_methods   = SdxTerm_methods;
    SdxTermType.tp_members   = SdxTerm_members;
    SdxTermType.tp_init      = (initproc) SdxTerm_init;
    SdxTermType.tp_new       = SdxTerm_new;

    if (PyType_Ready(&SdxTermType) < 0)
        return;
    Py_INCREF(&SdxTermType);
    PyModule_AddObject(m, "SdxTerm", (PyObject *) &SdxTermType);
}

#endif
