#ifndef DataAccess_cxx
#define DataAccess_cxx

#include "AnalysisTools/DataAccess.h"

ClassImp(DataAccess)

DataAccess::DataAccess() {
	data_source_ = kCollisionData;
	event_ = 0;
}

DataAccess::~DataAccess() {}


#endif