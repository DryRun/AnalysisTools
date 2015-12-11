#include "Selectors/TrackSelector.h"
#define MAX_DEBUG 100

ClassImp(TrackSelector);

TrackSelector::TrackSelector() : IObjectSelector() {
	object_name_ = IObjectSelector::kTrack;

	// Make index of cut functions
	//cut_functions["tight++_flag"]                   = &ElectronCutFunctions::ApplyTightPlusPlusFlag;
	//cut_functions["medium++_flag"]                  = &ElectronCutFunctions::ApplyMediumPlusPlusFlag;
	//cut_functions["loose++_flag"]                   = &ElectronCutFunctions::ApplyLoosePlusPlusFlag;

	// Set configured flags to false
	for (std::map<TString, CutFunction>::iterator it = cut_functions_.begin(); it != cut_functions_.end(); ++it) {
		configured_cuts_[(*it).first] = false;
	}


	#ifdef DEBUG_TrackSelector
	debug_counter = 0;
	#endif

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


