#ifndef ElectronDataAccess_cxx
#define ElectronDataAccess_cxx

#include "AnalysisTools/ElectronDataAccess.h"

ElectronDataAccess::ElectronDataAccess() {
	electrons_ = 0;
	forward_electrons_ = 0;
	egamma_truth_particles_ = 0;
	egamma_clusters_ = 0;
	forward_egamma_clusters_ = 0;
}

ElectronDataAccess::~ElectronDataAccess() {}

bool ElectronDataAccess::RetrieveElectrons() {
	bool success = true;
	if (!event_->retrieve(electrons_,"Electrons").isSuccess()) {
		Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve Electrons from xAOD.");
		success = false;
	}
	if (!event_->retrieve(forward_electrons_,"ForwardElectrons").isSuccess()) {
		Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve ForwardElectrons from xAOD.");
		success = false;
	}
	if (!event_->retrieve(egamma_clusters_,"egammaClusters").isSuccess()) {
		Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve egammaClusters from xAOD.");
		success = false;
	}
	if (!event_->retrieve(forward_egamma_clusters_,"ForwardElectronClusters").isSuccess()) {
		Error("ElectronDataAccess::RetrieveElectrons()", "Failed to retrieve ForwardElectronClusters from xAOD.");
		success = false;
	}
	if (data_source_ == kSimulation) {
		if (!event_->retrieve(egamma_truth_particles_, "egammaTruthParticles").isSuccess()) {
			Error("ElectronTruthDataAccess::RetrieveElectrons()", "Failed to retrieve egammaTruthParticles from xAOD.");
			success = false;
		}
	}
	return success;
}

#endif
