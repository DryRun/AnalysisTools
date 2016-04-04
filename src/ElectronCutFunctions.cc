#ifndef ElectronCutFunctions_cxx
#define ElectronCutFunctions_cxx

#include "MyTools/AnalysisTools/include/ElectronCutFunctions.h"

namespace ElectronCutFunctions {
	bool MinPt(const edm::Handle<std::vector<pat::Electron> > p_data, ObjectSelector* p_object_selector, int n) {
		return p_data->at(n)->pt() > p_object_selector->GetCutParameters("MinPt")->at(0);
	}

}

#endif