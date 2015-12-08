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

IObjectSelector::~IObjectSelector() {


}

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
