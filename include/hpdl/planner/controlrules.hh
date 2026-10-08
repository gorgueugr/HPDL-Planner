 #ifndef CONTROLRULES_HH
#define CONTROLRULES_HH 
 
 #include "hpdl/common/constants.hh"
#include <iostream>
#include <stdlib.h>
#include "hpdl/debug/debugger.hh"
#include "hpdl/common/termTable.hh"
#include "hpdl/py/pythonWrapper.hh"
#include <time.h>
#include "hpdl/parser/papi.hh"
#include "hpdl/domain/problem.hh"
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include "hpdl/common/clock.hh"

using namespace std;

class Controlrules
{

	public:
		Controlrules(void);
		~Controlrules();
		
	int selectPermutableTask(StackNode *context);
	
	int selectTaskExpansion(StackNode *context);
	
	int selectMethod(StackNode *context);
	
	int selectUnification(StackNode *context);
	
	int id;
	
};

#endif
