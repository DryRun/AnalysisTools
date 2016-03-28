#ifndef TrackDataAccess_cxx
#define TrackDataAccess_cxx

#include "MyTools/AnalysisTools/include/TrackDataAccess.h"

ClassImp(TrackDataAccess)

TrackDataAccess::TrackDataAccess() {
	tracks_ = 0;
	ignore_branch_["InDetTrackParticles"] = false;
}

TrackDataAccess::~TrackDataAccess() {}

bool TrackDataAccess::RetrieveTracks() {
	bool success = true;
	if (!ignore_branch_["InDetTrackParticles"]) {
		if (!event_->retrieve(tracks_,"InDetTrackParticles").isSuccess()) {
			Error("TrackDataAccess::RetrieveTracks()", "Failed to retrieve InDetTrackParticles from xAOD.");
			success = false;
		}
	}
	return success;
}

#endif