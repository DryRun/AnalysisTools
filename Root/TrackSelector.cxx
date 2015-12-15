#include "Selectors/TrackSelector.h"

TrackSelector::TrackSelector() : IObjectSelector() {
	object_name_ = IObjectSelector::kTrack;

	// Make index of cut functions
	//cut_functions["tight++_flag"]                   = &ElectronCutFunctions::ApplyTightPlusPlusFlag;
	//cut_functions["medium++_flag"]                  = &ElectronCutFunctions::ApplyMediumPlusPlusFlag;
	//cut_functions["loose++_flag"]                   = &ElectronCutFunctions::ApplyLoosePlusPlusFlag;
	cut_functions_["MinNPixHits"] = &TrackCutFunctions::MinNPixHits;
	cut_functions_["MinNSCTHits"] = &TrackCutFunctions::MinNSCTHits;
	cut_functions_["MinNSiHits"] = &TrackCutFunctions::MinNSiHits;
	cut_functions_["MinNPixLayerHits"] = &TrackCutFunctions::MinNPixLayerHits;
	cut_functions_["MinNInnerPixLayerHits"] = &TrackCutFunctions::MinNInnerPixLayerHits;
	cut_functions_["MinNOuterPixLayerHits"] = &TrackCutFunctions::MinNOuterPixLayerHits;
	cut_functions_["MinNSCTLayerHits"] = &TrackCutFunctions::MinNSCTLayerHits;
	cut_functions_["MinNSiLayerHits"] = &TrackCutFunctions::MinNSiLayerHits;
	cut_functions_["MaxNPixHoles"] = &TrackCutFunctions::MaxNPixHoles;
	cut_functions_["MaxNSCTHoles"] = &TrackCutFunctions::MaxNSCTHoles;
	cut_functions_["MaxNSiHoles"] = &TrackCutFunctions::MaxNSiHoles;
	cut_functions_["MaxD0SignificanceNoBeamspot"] = &TrackCutFunctions::MaxD0SignificanceNoBeamspot;
	cut_functions_["MaxD0Significance"] = &TrackCutFunctions::MaxD0Significance;
	// Set configured flags to false
	for (std::map<TString, CutFunction>::iterator it = cut_functions_.begin(); it != cut_functions_.end(); ++it) {
		configured_cuts_[(*it).first] = false;
	}
}

TrackSelector::~TrackSelector() {}

void TrackSelector::ClassifyObjects() {
	if (!fresh_event_) {
		std::cerr << "[TrackSelector] ERROR : ClassifyObjects() called without calling SetNewEvent() on this event." << std::endl;
		exit(1);
	}
	// Run selection on every electron, skipping the overlapped electrons.
	for (int i = 0; i < tracks_->size(); i++) {
		obj_pass_[i] = Pass(i);
		if (obj_pass_[i]) {
			obj_good_.push_back(i);
			n_good_objects_++;
		}
	}

	fresh_event_ = false;
}


void TrackSelector::SetNewEvent() {
	IObjectSelector::SetNewEvent();
	tracks_ = dynamic_cast<TrackDataAccess*>(data_)->GetTrackParticleContainer();
}


bool TrackSelector::LoadConfiguration(TString config_path, bool verbose) {
	bool success = ISelector::LoadConfiguration(config_path, verbose);
	// Check list of cuts
	for (std::vector<TString>::iterator it = cut_list_.begin(); it != cut_list_.end(); ++it) {
		if (cut_functions_.find(*it) == cut_functions_.end()) {
			std::cerr << "[TrackSelector] ERROR : Cut " << *it << " does not match any cut function in the index. Please fix before proceeding." << std::endl;
			exit(1);
		}
	}

	return success;
}


