#ifndef TrackDataAccess_cxx
#define TrackDataAccess_cxx

#include "Selectors/TrackDataAccess.h"

TrackDataAccess::TrackDataAccess() {
	tracks_ = 0;
	truth_particles_ = 0;
	truth_vertices_ = 0;
	truth_events_ = 0;
	truth_pileup_events_ = 0;
}

TrackDataAccess::~TrackDataAccess() {}

bool TrackDataAccess::RetrieveTracks() {
	bool success = true;
	if (!event_->retrieve(tracks_,"InDetTrackParticles").isSuccess()) {
		Error("TrackDataAccess::RetrieveTracks()", "Failed to retrieve InDetTrackParticles from xAOD.");
		success = false;
	}
	if (data_source_ == kSimulation) {
		if (!event_->retrieve(truth_particles_, "TruthParticles").isSuccess()) {
			Error("TrackTruthDataAccess::RetrieveTracks()", "Failed to retrieve TruthParticles from xAOD.");
			success = false;
		}
		if (!event_->retrieve(truth_vertices_, "TruthVertices").isSuccess()) {
			Error("TrackTruthDataAccess::RetrieveTracks()", "Failed to retrieve TruthVertices from xAOD.");
			success = false;
		}
		if (!event_->retrieve(truth_events_, "TruthEvents").isSuccess()) {
			Error("TrackTruthDataAccess::RetrieveTracks()", "Failed to retrieve TruthEvents from xAOD.");
			success = false;
		}
		if (!event_->retrieve(truth_pileup_events_, "TruthPileupEvents").isSuccess()) {
			Error("TrackTruthDataAccess::RetrieveTracks()", "Failed to retrieve TruthPileupEvents from xAOD.");
			success = false;
		}
	}
	return success;
}

#endif