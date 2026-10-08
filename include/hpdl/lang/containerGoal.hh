
#ifndef CONTAINERGOAL_HH
#define CONTAINERGOAL_HH

#include "hpdl/common/constants.hh"
#include "hpdl/lang/goals/goal.hh"

using namespace std;

/**
  * @author  Oscar
  * @description Esta clase representa la base para todos los posibles objetivos del planificador.
*/

class ContainerGoal : public Goal
{
    public:
	ContainerGoal() {};
	ContainerGoal(const Goal * o) :Goal(o) {};

        virtual void addGoal(const Goal * g) = 0;

        virtual void addGoalByRef(Goal * g) = 0;

	virtual ~ContainerGoal(void) {};
};

#endif
