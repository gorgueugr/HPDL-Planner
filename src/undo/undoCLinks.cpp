#include "hpdl/undo/undoCLinks.hh"
#include "hpdl/planner/causalTable.hh"
#include "hpdl/htn/task.hh"

void UndoCLinks::print(ostream * os) const {
    *os <<  "UndoCLinks:: key = " << key << endl;
};

void UndoCLinks::undo(void) {
    causalTable.eraseCausalLinks(key);
};

void UndoCLinks::toxml(XmlWriter * writer) const{
};

