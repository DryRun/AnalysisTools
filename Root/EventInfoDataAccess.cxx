#ifndef EventInfoDataAccess_cxx
#define EventInfoDataAccess_cxx

#include "AnalysisTools/EventInfoDataAccess.h"

ClassImp(EventInfoDataAccess)

EventInfoDataAccess::EventInfoDataAccess() {
	event_info_ = 0;
	ignore_branch_["EventInfo"] = false;
}

EventInfoDataAccess::~EventInfoDataAccess() {}

bool EventInfoDataAccess::RetrieveEventInfo() {
	bool success = true;
	if (!ignore_branch_["EventInfo"]) {
		if (!event_->retrieve(event_info_,"EventInfo").isSuccess()) {
			Error("EventInfoDataAccess::RetrieveEventInfo()", "Failed to retrieve EventInfo from xAOD.");
			success = false;
		}
	}
	return success;
}

#endif