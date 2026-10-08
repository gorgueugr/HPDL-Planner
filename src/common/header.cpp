#include "hpdl/common/header.hh"
#include "hpdl/parser/papi.hh"
#include "hpdl/domain/domain.hh"

const char * Header::getName(void) const 
{return parser_api->domain->getMetaName(metaid);};

void Header::setName(const char * n) 
{parser_api->domain->setMetaName(metaid,n);};

