#ifndef ElectronCutFunctions_cxx
#define ElectronCutFunctions_cxx

#include "MyTools/AnalysisTools/interface/ElectronCutFunctions.h"

namespace ElectronCutFunctions {
	bool MinPt(const edm::Handle<std::vector<pat::Electron> >& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n) {
		return p_data->at(n).pt() > p_object_selector->GetCutParameters("MinPt")[0];
	}

}

#endif