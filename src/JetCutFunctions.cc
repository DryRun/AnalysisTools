#ifndef JetCutFunctions_cxx
#define JetCutFunctions_cxx

#include "MyTools/AnalysisTools/interface/JetCutFunctions.h"

namespace JetCutFunctions {
	bool MinPt(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return p_data->at(n).pt() >= p_object_selector->GetCutParameters("MinPt")[0];
	}
	bool MaxPt(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return p_data->at(n).pt() <= p_object_selector->GetCutParameters("MaxPt")[0];
	}
	bool MinAbsEta(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return TMath::Abs(p_data->at(n).eta()) >= p_object_selector->GetCutParameters("MinAbsEta")[0];
	}
	bool MaxAbsEta(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n) {
		return TMath::Abs(p_data->at(n).eta()) <= p_object_selector->GetCutParameters("MaxAbsEta")[0];
	}

	void Configure(ObjectSelector<pat::Jet>* p_selector) {
		p_selector->AddCutFunction("MinPt", &MinPt);
		p_selector->AddCutFunction("MaxPt", &MaxPt);
		p_selector->AddCutFunction("MinAbsEta", &MinAbsEta);
		p_selector->AddCutFunction("MaxAbsEta", &MaxAbsEta);

		p_selector->SetObjectName("Jet");
		p_selector->SetObject(ObjectIdentifiers::Jet);
	}

}

#endif