#ifndef TrackDataAccess_cxx
#define TrackDataAccess_cxx

#include "Selectors/TrackDataAccess.h"

TrackDataAccess::TrackDataAccess() {
	track_truth_ = false;
}

TrackDataAccess::~TrackDataAccess() {}

TrackDataAccess::NewEvent() {
	if (!event_->retrieve(tracks_,"InDetTrackParticles").isSuccess()) {
		Error("execute()", "Failed to retrieve InDetTrackParticles from xAOD.");
		return EL::StatusCode::FAILURE;
	}

	if (data_source_ == kSimulation) {
		if (!event_->retrieve(truth_particles_, "TruthParticles").isSuccess()) {
			Error("execute()", "Failed to retrieve TruthParticles from xAOD.");
			return EL::StatusCode::FAILURE;
		}
		if (!event_->retrieve(truth_vertices_, "TruthVertices").isSuccess()) {
			Error("execute()", "Failed to retrieve TruthVertices from xAOD.");
			return EL::StatusCode::FAILURE;
		}
		if (!event_->retrieve(truth_events_, "TruthEvents").isSuccess()) {
			Error("execute()", "Failed to retrieve TruthEvents from xAOD.");
			return EL::StatusCode::FAILURE;
		}
		if (!event_->retrieve(truth_pileup_events_, "TruthPileupEvents").isSuccess()) {
			Error("execute()", "Failed to retrieve TruthPileupEvents from xAOD.");
			return EL::StatusCode::FAILURE;
		}

	}

}

#endif