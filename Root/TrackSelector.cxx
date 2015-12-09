#include "Selectors/TrackSelector.h"
#define MAX_DEBUG 100

ClassImp(TrackSelector);

TrackSelector::TrackSelector() : ObjectSelector() {
	object_name_ = ObjectSelector::kTrack;

	// Make index of cut functions
	cut_functions["tight++_flag"]                   = &ElectronCutFunctions::ApplyTightPlusPlusFlag;
	cut_functions["medium++_flag"]                  = &ElectronCutFunctions::ApplyMediumPlusPlusFlag;
	cut_functions["loose++_flag"]                   = &ElectronCutFunctions::ApplyLoosePlusPlusFlag;

	// Set configured flags to false
	for (std::map<TString, CutFunction>::iterator it = cut_functions.begin(); it != cut_functions.end(); ++it) {
		configured_cuts[(*it).first] = false;
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
	ObjectSelector::SetNewEvent(0);
	m_is_conversion_.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_is_conversion_[i] = false;
	}
}

void TrackSelector::SetNewEvent(std::map<Int_t, Bool_t> *p_good_jet_list) {
	m_good_jet_list = p_good_jet_list;
	ObjectSelector::SetNewEvent(0);
	m_is_conversion_.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_is_conversion_[i] = false;
	}
}

void TrackSelector::SetNewEvent(std::map<Int_t, Bool_t> *p_object_preselection, std::map<Int_t, Bool_t> *p_good_jet_list) {
	ObjectSelector::SetNewEvent(p_object_preselection);

	m_trigger_match_results.clear();

	for (int i = 0; i < m_event->el.n(); ++i) {
		m_trigger_match_results[i] = "None";
	}

	m_electron_pid.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_electron_pid[i] = ElectronID_IsEM;
	}

	m_is_conversion_.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_is_conversion_[i] = false;
	}

	m_good_jet_list = p_good_jet_list;
}

void TrackSelector::SetMatchedTrigger(Int_t p_index, TString p_trigger, Int_t p_ef_index) {
	m_trigger_match_results[p_index] = p_trigger;
	m_trigger_match_index[p_index] = p_ef_index;
}


bool TrackSelector::LoadConfiguration(TString config_path, bool verbose) {
	bool success = ISelector::LoadConfiguration(config_path, verbose);
	if (m_collection_name.EqualTo("el")) {
		m_collection = TrackSelector::el;
	} else {
		std::cout << "[TrackSelector] WARNING : No electron collection specified. Using el by default." << std::endl;
		m_collection = TrackSelector::el;
	}
	// Check list of cuts
	for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {
		if (cut_functions.find(*it) == cut_functions.end()) {
			std::cerr << "[TrackSelector] ERROR : Cut " << *it << " does not match any cut function in the index. Please fix before proceeding." << std::endl;
			exit(1);
		}
	}

	return success;
}


