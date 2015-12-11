#ifndef DataAccess_cxx
#define DataAccess_cxx

#include "Selectors/DataAccess.h"

DataAccess::DataAccess() {
	data_source_ = kCollisionData;
	event_ = 0;
}

DataAccess::~DataAccess() {}


#endif