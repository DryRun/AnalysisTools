#include "Selectors/IObjectSelector.h"
#define MAX_DEBUG 100

ClassImp(IObjectSelector);

IObjectSelector::IObjectSelector() {

	// Set some special counters
	cutflow_counter_["preselection"] = 0;
	cut_counter_["preselection"] = 0;

	// Set pointers to null
	object_preselection_ = 0;

	fresh_event_ = false;

	use_preselection_ = true;
}

IObjectSelector::~IObjectSelector() {}

void IObjectSelector::UsePreselection(bool p_use_preselection) {
	use_preselection_ = p_use_preselection;
}

void IObjectSelector::SetNewEvent(std::map<Int_t, Bool_t> *p_object_preselection) {
	Clear();

	if (use_preselection_) {
		object_preselection_ = p_object_preselection;
	}
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

	m_pass_calls++;
	for (std::vector<TString>::iterator cut = cut_list.begin(); cut != cut_list.end(); ++cut) {
		#ifdef DEBUG_IObjectSelector
		if (debug_counter++ < MAX_DEBUG) {
			std::cout << "[IObjectSelector] DEBUG : Applying cut " << *cut << std::endl;
		}
		#endif
		if (!cut_functions[*cut](event_, this, i) {
			if (c_pass) {
				c_pass = false;
				m_cutflow_counter[*cut]++;
			}
			m_cut_counter[*cut]++;
		}
	}
	
	if (c_pass) {
		m_pass++;
	} else {
		m_fail++;
	}

	return c_pass;
}

bool IObjectSelector::PassCut(int i, TString p_cut_name) {

	if (!configured[p_cut_name]) {
		std::cerr << "[IObjectSelector] ERROR : Requested cut " << p_cut_name << " was not configured. Exiting..." << std::endl;
		exit(1);
	}
	bool c_pass = cut_functions[p_cut_name](event_, this, i);
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

