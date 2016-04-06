#ifndef JetCutFunctions_cxx
#define JetCutFunctions_cxx

#include "MyTools/AnalysisTools/interface/JetCutFunctions.h"

namespace JetCutFunctions {
	bool MinPt(const edm::Handle<std::vector<pat::Jet> >& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return p_data->at(n).pt() >= p_object_selector->GetCutParameters("MinPt")[0];
	}
	bool MaxPt(const edm::Handle<std::vector<pat::Jet> >& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return p_data->at(n).pt() <= p_object_selector->GetCutParameters("MaxPt")[0];
	}
	bool MinAbsEta(const edm::Handle<std::vector<pat::Jet> >& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return TMath::Abs(p_data->at(n).eta()) >= p_object_selector->GetCutParameters("MinAbsEta")[0];
	}
	bool MaxAbsEta(const edm::Handle<std::vector<pat::Jet> >& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return TMath::Abs(p_data->at(n).eta()) <= p_object_selector->GetCutParameters("MaxAbsEta")[0];
	}

}

#endif