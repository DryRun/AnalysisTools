#ifndef ElectronDataAccess_cxx
#define ElectronDataAccess_cxx

#include "AnalysisTools/ElectronDataAccess.h"

ClassImp(ElectronDataAccess)

ElectronDataAccess::ElectronDataAccess() {
	electrons_ = 0;
	forward_electrons_ = 0;
	egamma_truth_particles_ = 0;
	egamma_clusters_ = 0;
	forward_egamma_clusters_ = 0;
	ignore_branch_["Electrons"] = false;
	ignore_branch_["ForwardElectrons"] = false;
	ignore_branch_["egammaClusters"] = false;
	ignore_branch_["ForwardElectronClusters"] = false;
	ignore_branch_["egammaTruthParticles"] = false;
}

ElectronDataAccess::~ElectronDataAccess() {}

bool ElectronDataAccess::RetrieveElectrons() {
	bool success = true;
	if (!ignore_branch_["Electrons"]) {
		if (!event_->retrieve(electrons_,"Electrons").isSuccess()) {
			Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve Electrons from xAOD.");
			success = false;
		}
	}
	if (!ignore_branch_["ForwardElectrons"]) {
		if (!event_->retrieve(forward_electrons_,"ForwardElectrons").isSuccess()) {
			Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve ForwardElectrons from xAOD.");
			success = false;
		}
	}
	if (!ignore_branch_["egammaClusters"]) {
		if (!event_->retrieve(egamma_clusters_,"egammaClusters").isSuccess()) {
			Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve egammaClusters from xAOD.");
			success = false;
		}
	}
	if (!ignore_branch_["ForwardElectronClusters"]) {
		if (!event_->retrieve(forward_egamma_clusters_,"ForwardElectronClusters").isSuccess()) {
			Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve ForwardElectronClusters from xAOD.");
			success = false;
		}
	}
	if (data_source_ == kSimulation) {
		if (! ignore_branch_["egammaTruthParticles"]) {
			if (!event_->retrieve(egamma_truth_particles_, "egammaTruthParticles").isSuccess()) {
				Error("ElectronTruthDataAccess::RetrieveElectrons()", "Failed to retrieve egammaTruthParticles from xAOD.");
				success = false;
			}
		}
	}
	return success;
}

#endif
