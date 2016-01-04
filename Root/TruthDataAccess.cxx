#ifndef TruthDataAccess_cxx
#define TruthDataAccess_cxx

#include "Selectors/TruthDataAccess.h"

TruthDataAccess::TruthDataAccess() {
	truth_particles_ = 0;
	truth_vertices_ = 0;
	truth_events_ = 0;
	truth_pileup_events_ = 0;
}

TruthDataAccess::~TruthDataAccess() {}

bool TruthDataAccess::RetrieveTracks() {
	bool success = true;
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