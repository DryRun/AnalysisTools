#ifndef ElectronCutFunctions_cxx
#define ElectronCutFunctions_cxx

#include "MyTools/AnalysisTools/interface/ElectronCutFunctions.h"

namespace ElectronCutFunctions {
	bool MinPt(const std::vector<pat::Electron>& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n) {
		return p_data[n].pt() > p_object_selector->GetCutParameters("MinPt")[0];
	}

	bool MaxPt(const edm::Handle<std::vector<pat::Electron> >& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n) {
		return p_data[n].pt() < p_object_selector->GetCutParameters("MinPt")[0];
	}
	bool MinAbsEta(const edm::Handle<std::vector<pat::Electron> >& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n) {
		return TMath::Abs(p_data[n].eta()) > p_object_selector->GetCutParameters("MinPt")[0];
	}
	bool MaxAbsEta(const edm::Handle<std::vector<pat::Electron> >& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n) {
		return TMath::Abs(p_data[n].eta()) < p_object_selector->GetCutParameters("MinPt")[0];
	}

	void Configure(ObjectSelector<pat::Electron>* p_selector) {
		p_selector->AddCutFunction("MinPt", &MinPt);
		p_selector->AddCutFunction("MaxPt", &MaxPt);
		p_selector->AddCutFunction("MinAbsEta", &MinAbsEta);
		p_selector->AddCutFunction("MaxAbsEta", &MaxAbsEta);

		p_selector->SetObjectName("Electron");
		p_selector->SetObject(ObjectIdentifiers::kElectron);
	}

}

#endif