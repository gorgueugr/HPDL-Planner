#include "hpdl/common/constants.hh"
#include <iostream>
#include <stdlib.h>
#include "hpdl/debug/debugger.hh"
#include "hpdl/common/termTable.hh"
#include "hpdl/py/pythonWrapper.hh"
#include <time.h>
#include "hpdl/parser/papi.hh"
#include "hpdl/domain/problem.hh"
#include <stdio.h>
#include <stdlib.h>
#include "hpdl/common/clock.hh"

using namespace std;
using namespace Pocima;

//Cabeceras

void startInterface(void);

bool loadDomain(char *domainf);

char * printDomain(void);

char * getName(void);

const char * getTypes(void);

const char * getRootTypes(void);

const char * getChildsOfType(int ParentId);

const char * getConstants(void);

const char * getTermName(int tid);

bool isFunction(int pid);

const char * getLiteralArgsList(int pid);

const char * getLiteralName(int pid);

const char * getPredicates(void);

const char * getAxioms(void);

const char * getAxiomName(int pid);

const char * getAxiomArgsList(int pid);

const char * getLiterals(void);

const char * getFunctions(void);

const char * getTaskName(int tid, int mid);

bool existsTask(int tid, int mid);

const char * getTasksNames(void);

bool isCompoundTask(int id, int metaid);

char * getMethodName(int id, int metaid, int m_metaid);

char * getMethodsFromCompoundTask(int id, int metaid);

char * getPreconditionsFromTask(int id, int metaid);

char * getEffectsFromTask(int id, int metaid);

char * getTaskListFromMethod(int id, int metaid, int m_metaid);

char * getPreconditionsFromMethod(int id, int metaid, int m_metaid);

char * domainToPDDL(int ind);

char * domainWarnings();

void setTaskName(int id, int metaid, const char *n);

int getNumOfParameters(int id, int metaid);

char * getParameter(int id, int metaid, int index);
