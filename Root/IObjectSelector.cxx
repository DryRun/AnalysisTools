#include "AnalysisTools/IObjectSelector.h"
//#define DEBUG_IObjectSelector
#define MAX_DEBUG 100

IObjectSelector::IObjectSelector() {

	// Set some special counters
	cutflow_counter_["preselection"] = 0;
	cut_counter_["preselection"] = 0;

	// Set pointers to null
	object_preselection_ = 0;

	fresh_event_ = false;

	use_preselection_ = true;

	#ifdef DEBUG_IObjectSelector
	debug_counter = 0;
	#endif
}

IObjectSelector::~IObjectSelector() {}

void IObjectSelector::SetNewEvent() {
	Clear();
	fresh_event_ = true;
}

void IObjectSelector::Clear() {

	obj_pass_.clear();
	obj_good_.clear();
	n_good_objects_ = 0;
	object_preselection_ = 0;
	truth_match_indices_.clear();
	
}

bool IObjectSelector::Pass(int i) {
	bool c_pass = true;

	pass_calls_++;
	for (std::vector<TString>::iterator cut = cut_list_.begin(); cut != cut_list_.end(); ++cut) {
		#ifdef DEBUG_IObjectSelector
		if (debug_counter++ < MAX_DEBUG) {
			std::cout << "[IObjectSelector] DEBUG : Applying cut " << *cut << std::endl;
		}
		#endif
		if (!cut_functions_[*cut](data_, this, i)) {
			if (c_pass) {
				c_pass = false;
				cutflow_counter_[*cut]++;
			}
			cut_counter_[*cut]++;
		}
	}
	
	if (c_pass) {
		pass_++;
	} else {
		fail_++;
	}

	return c_pass;
}

bool IObjectSelector::PassCut(int i, TString p_cut_name) {

	if (!CutIsConfigured(p_cut_name)) {
		std::cerr << "[IObjectSelector] ERROR : Requested cut " << p_cut_name << " was not configured. Exiting..." << std::endl;
		exit(1);
	}
	bool c_pass = cut_functions_[p_cut_name](data_, this, i);
	return c_pass;
}


int IObjectSelector::IsGood(int p_index) {
	int return_code = 0;
	if (obj_pass_.find(p_index) == obj_pass_.end()) {
		return_code = -1;
	} else if (obj_pass_[p_index]) {
		return_code = 1;
	} else {
		return_code = 0;
	}
	return return_code;
}

