#ifndef EventInfoDataAccess_cxx
#define EventInfoDataAccess_cxx

#include "Selectors/EventInfoDataAccess.h"

EventInfoDataAccess::EventInfoDataAccess() {
	event_info_ = 0;
}

EventInfoDataAccess::~EventInfoDataAccess() {}

bool EventInfoDataAccess::RetrieveEventInfo() {
	bool success = true;
	if (!event_->retrieve(event_info_,"EventInfo").isSuccess()) {
		Error("EventInfoDataAccess::RetrieveEventInfo()", "Failed to retrieve EventInfo from xAOD.");
		success = false;
	}
	return success;
}

#endif