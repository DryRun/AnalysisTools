#ifndef TrackDataAccess_cxx
#define TrackDataAccess_cxx

#include "Selectors/TrackDataAccess.h"

TrackDataAccess::TrackDataAccess() {
	tracks_ = 0;
}

TrackDataAccess::~TrackDataAccess() {}

bool TrackDataAccess::RetrieveTracks() {
	bool success = true;
	if (!event_->retrieve(tracks_,"InDetTrackParticles").isSuccess()) {
		Error("TrackDataAccess::RetrieveTracks()", "Failed to retrieve InDetTrackParticles from xAOD.");
		success = false;
	}
	return success;
}

#endif