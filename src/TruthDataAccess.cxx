#ifndef TruthDataAccess_cxx
#define TruthDataAccess_cxx

#include "AnalysisTools/TruthDataAccess.h"

ClassImp(TruthDataAccess)

TruthDataAccess::TruthDataAccess() {
	truth_particles_ = 0;
	truth_vertices_ = 0;
	truth_events_ = 0;
	truth_pileup_events_ = 0;
	ignore_branch_["TruthParticles"] = false;
	ignore_branch_["TruthVertices"] = false;
	ignore_branch_["TruthEvents"] = false;
	ignore_branch_["TruthPileupEvents"] = false;
}

TruthDataAccess::~TruthDataAccess() {}

bool TruthDataAccess::RetrieveTruth() {
	bool success = true;
	if (data_source_ == kSimulation) {
		if (!ignore_branch_["TruthParticles"]) {
			if (!event_->retrieve(truth_particles_, "TruthParticles").isSuccess()) {
				Error("TrackTruthDataAccess::RetrieveTruth()", "Failed to retrieve TruthParticles from xAOD.");
				success = false;
			}
		}
		if (!ignore_branch_["TruthVertices"]) {
			if (!event_->retrieve(truth_vertices_, "TruthVertices").isSuccess()) {
				Error("TrackTruthDataAccess::RetrieveTruth()", "Failed to retrieve TruthVertices from xAOD.");
				success = false;
			}
		}
		if (!ignore_branch_["TruthEvents"]) {
			if (!event_->retrieve(truth_events_, "TruthEvents").isSuccess()) {
				Error("TrackTruthDataAccess::RetrieveTruth()", "Failed to retrieve TruthEvents from xAOD.");
				success = false;
			}
		}
		if (!ignore_branch_["TruthPileupEvents"]) {
			if (!event_->retrieve(truth_pileup_events_, "TruthPileupEvents").isSuccess()) {
				Error("TrackTruthDataAccess::RetrieveTruth()", "Failed to retrieve TruthPileupEvents from xAOD.");
				success = false;
			}
		}
	}
	return success;
}

#endif