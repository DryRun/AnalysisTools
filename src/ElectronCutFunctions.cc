#ifndef ElectronCutFunctions_cxx
#define ElectronCutFunctions_cxx

#include "MyTools/AnalysisTools/interface/ElectronCutFunctions.h"

namespace ElectronCutFunctions {
	template<class T>
	bool MinPt(const edm::Handle<std::vector<pat::Electron> > p_data, ObjectSelector<T>* p_object_selector, int n) {
		return p_data->at(n).pt() > p_object_selector->GetCutParameters("MinPt")->at(0);
	}

}

#endif