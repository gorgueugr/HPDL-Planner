// --------------------------------------------------------------------------------------------
// Definición del tipo SdxLiteral que equivale a la clase Literal para python.
// --------------------------------------------------------------------------------------------

#include "hpdl/common/constants.hh"
#include "hpdl/py/pythonWrapper.hh"
#include <structmember.h>
#include "hpdl/lang/literal.hh"
#include "hpdl/parser/papi.hh"
#include "hpdl/lang/effects/literaleffect.hh"
#include "hpdl/domain/domain.hh"
#include "hpdl/domain/problem.hh"
#include "hpdl/lang/goals/literalgoal.hh"
#include "pyUTable.cpp"
#include "hpdl/planner/plan.hh"
using namespace std;

#ifdef PYTHON_FOUND

#define domain parser_api->domain
#define problem parser_api->problem
#define termtable parser_api->termtable

extern Plan * current_plan;

/**
 * Estructura que define el tipo
 */
typedef struct {
    PyObject_HEAD
    Literal * l;  /*El literal l almacenado en el objeto python */
} SdxLiteral;

/**
 * Liberar la memoria ocupada por el tipo
 */
static void SdxLiteral_dealloc(SdxLiteral * self)
{
    delete self->l;
    self->l = 0;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

/**
 * Inicialización del tipo.
 */
static PyObject * SdxLiteral_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    SdxLiteral *self;

    self = (SdxLiteral *)type->tp_alloc(type, 0);
    self->l = 0;
    return (PyObject *)self;
}

/**
 * Inicialización de la estructura
 */
static int SdxLiteral_init(SdxLiteral *self, PyObject *args, PyObject *kwds)
{
    PyObject * n;
    const char * name;
    Meta * mt;

    self->l = 0;

    // Capturamos la inicialización dada por el usuario
    if (! PyArg_ParseTuple(args, "O", &n)){
        return -1;
    }

    if(!PyUnicode_Check(n)){
	return -1;
    }

    name = PyUnicode_AsUTF8(n);

    // buscamos si el literal ya está definido en el diccionario de
    // nombres de literales (debería estarlo)
    ldictionaryit posit = SearchDictionary(&(domain->ldictionary),name);
    if(posit != (domain->ldictionary).end()) {
	self->l = new LiteralGoal(posit->second,domain->metainfo.size());
	mt = new Meta(name,0,-1);
	domain->metainfo.push_back(mt);
    }
    else
    {
	self->l = new LiteralGoal(posit->second,domain->metainfo.size());
	mt = new Meta(name,0,-1);
	domain->metainfo.push_back(mt);
	(domain->ldictionary).insert(make_pair(self->l->getName(), self->l->getId()));
    }

    return 0;
}

/**
 * wrapper función de impresión.
 */
static PyObject * SdxLiteral_str(SdxLiteral * self){
    PyObject * result;
    ostringstream s;

    if(self->l){
	self->l->printL(&s);
	result = PyUnicode_FromString(s.str().c_str());
    }
    else{
	result = PyUnicode_FromString("");
    }
    return result;
};

static int SdxLiteral_print(SdxLiteral * self, FILE * fp, int flags){
    ostringstream s;

    if(self->l){
	self->l->printL(&s);
	fprintf(fp,"%s",s.str().c_str());
    }
    return 0;
};

/**
 * Cambiar el signo del literal
 */
static PyObject * SdxLiteral_negate(SdxLiteral * self){
    if(self->l){
	if(self->l->getPol())
	    self->l->setPol(false);
	else
	    self->l->setPol(true);
    }
    return PyLong_FromLong(0);
};

static PyObject * SdxLiteral_add_arg(SdxLiteral * self, PyObject *args){
    PyObject * n;
    SdxTerm * t;
    PyTypeObject * sptr = &SdxTermType;

    if(self->l == NULL)
		return PyLong_FromLong(-1);

    // Capturamos la inicialización dada por el usuario
    if (! PyArg_ParseTuple(args, "O", &n)){
		return PyLong_FromLong(-1);
    }


    if(PyObject_IsInstance(n,(PyObject *) sptr)){
		pkey term = ((SdxTerm *)n)->t;
		self->l->addParameter(term);
    }
    else {
		// Si el objeto no es un término entonces
		// tratamos de crear uno con el argumento dado.
		// Esto aporta más flexibilidad a la sintaxis
		t = PyObject_New(SdxTerm,sptr);
		if(SdxTerm_init(t, args,NULL)){
	    	return PyLong_FromLong(-1);
		}
		pkey term = t->t;
		self->l->addParameter(term);
    }

    return PyLong_FromLong(0);
};

static PyObject * SdxLiteral_set_arg(SdxLiteral * self, PyObject *args){
    PyObject * n;
    SdxTerm * t;
    int pos;
    PyTypeObject * sptr = &SdxTermType;

    if(self->l == NULL)
		return PyLong_FromLong(-1);

    // Capturamos la inicialización dada por el usuario
    if (! PyArg_ParseTuple(args, "iO", &pos, &n)){
		return PyLong_FromLong(-1);
    }


    if(PyObject_IsInstance(n,(PyObject *) sptr)){
		pkey term = ((SdxTerm *)n)->t;
		self->l->setParameter(pos,term);
    }
    else {
		// Si el objeto no es un término entonces
		// tratamos de crear uno con el argumento dado.
		// Esto aporta más flexibilidad a la sintaxis
		t = PyObject_New(SdxTerm,(PyTypeObject *) sptr);
		if(SdxTerm_init(t, args,NULL)){
		    return PyLong_FromLong(-1);
		}
		pkey term = t->t;
		self->l->setParameter(pos,term);
    }

    return PyLong_FromLong(0);
};

/**
 * Obtiene los literales del estado que unifican con self.
 * Self puede tener variables por lo tanto puede hacer unificaciones.
 */
static PyObject * SdxLiteral_get_unifiers(SdxLiteral * self){
    UnifierTable * ut;
    pair<unsigned int, unsigned int> p(0,0);

    if(self->l == NULL){
	Py_INCREF(Py_None);
	return Py_None;
    }

    if(!problem){
	Py_INCREF(Py_None);
	return Py_None;
    }

    if(!current_plan->getState()){
	Py_INCREF(Py_None);
	return Py_None;
    }

    // El literal almacenado puede ser tanto un literalgoal como
    // un literaleffect. El único que es capaz de extraer unificaciones
    // es el literalgoal por lo tanto si me encuentro un literaleffect
    // Es necesario transformarlo antes.
    if(!self->l->isLEffect()){
	ut = ((LiteralGoal *)self->l)->getUnifiers(current_plan->getState(),0,true,&p);
    }
    else {
	LiteralGoal * tmp = new LiteralGoal(self->l->getId(),self->l->getMetaId(),self->l->getParameters(),self->l->getPol());
	ut = tmp->getUnifiers(current_plan->getState(),0,true,&p);
	delete tmp;
    }
    PyObject * n = (PyObject *) PyObject_New(SdxUTable, &SdxUTableType);
    ((SdxUTable *) n)->ut = ut;
    ((SdxUTable *) n)->init = false;

    return n;
}

static PyObject * SdxLiteral_insert_into_state(SdxLiteral * self){

    if(self->l == NULL){
	return PyLong_FromLong(-1);
    }

    if(!problem){
	return PyLong_FromLong(-1);
    }

    if(!current_plan->getState()){
	return PyLong_FromLong(-1);
    }

    // Lo único que podemos insertar en el estado es un literaleffect.
    LiteralEffect * tmp = new LiteralEffect(self->l->getId(),self->l->getMetaId(),self->l->getParameters(),self->l->getPol());
    current_plan->addToState((LiteralEffect *)tmp);

    return PyLong_FromLong(0);
}

static PyObject * SdxLiteral_delete_from_state(SdxLiteral * self){

    if(self->l == NULL){
	return PyLong_FromLong(-1);
    }

    if(!current_plan){
	return PyLong_FromLong(-1);
    }

    int ret = current_plan->deleteFromState(self->l->getId(),self->l->getParameters());

    return PyLong_FromLong(ret);

}

static PyMemberDef SdxLiteral_members[] = {
    {NULL}  /* Sentinel */
};


static PyMethodDef SdxLiteral_methods[] = {
    {"str", (PyCFunction)SdxLiteral_str, METH_NOARGS,
	"Return a string representation of the object.",
    },
    {"add_arg", (PyCFunction)SdxLiteral_add_arg, METH_VARARGS,
	"Adds an argument to the literal.",
    },
    {"set_arg", (PyCFunction)SdxLiteral_set_arg, METH_VARARGS,
	"Changes an argument to the literal. The first argument is an integer from 1 to n. The second the new value for the arg.",
    },
    {"negate", (PyCFunction)SdxLiteral_negate, METH_NOARGS,
	"Change the polarity of the literal.",
    },
    {"insert_into_state", (PyCFunction)SdxLiteral_insert_into_state, METH_NOARGS,
	"Inserts this literal in the current state.",
    },
    {"delete_from_state", (PyCFunction)SdxLiteral_delete_from_state, METH_NOARGS,
	"Deletes this literal from the current state.",
    },
    {"get_unifiers", (PyCFunction)SdxLiteral_get_unifiers, METH_NOARGS,
	"Return a list of literals that unify with the self literal.",
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject SdxLiteralType = {
    PyVarObject_HEAD_INIT(NULL, 0)
};

/**
 * Inicialización del módulo
 */
static void SdxLiteral_initModule(PyObject * m){
    SdxLiteralType.tp_name      = "siadex.SdxLiteral";
    SdxLiteralType.tp_basicsize = sizeof(SdxLiteral);
    SdxLiteralType.tp_dealloc   = (destructor) SdxLiteral_dealloc;
    SdxLiteralType.tp_str       = (reprfunc) SdxLiteral_str;
    SdxLiteralType.tp_flags     = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    SdxLiteralType.tp_doc       = "Siadex literal";
    SdxLiteralType.tp_methods   = SdxLiteral_methods;
    SdxLiteralType.tp_members   = SdxLiteral_members;
    SdxLiteralType.tp_init      = (initproc) SdxLiteral_init;
    SdxLiteralType.tp_new       = SdxLiteral_new;

    if (PyType_Ready(&SdxLiteralType) < 0)
        return;
    Py_INCREF(&SdxLiteralType);
    PyModule_AddObject(m, "SdxLiteral", (PyObject *) &SdxLiteralType);
}

#endif
