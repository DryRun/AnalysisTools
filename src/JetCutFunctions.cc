#ifndef JetCutFunctions_cxx
#define JetCutFunctions_cxx

#include "MyTools/AnalysisTools/interface/JetCutFunctions.h"

namespace JetCutFunctions {
	template <class T>
	bool MinPt(const edm::Handle<std::vector<pat::Jet> > p_data, ObjectSelector<T>* p_object_selector, int n) {
		return p_data->at(n).pt() > p_object_selector->GetCutParameters("MinPt")->at(0);
	}

}

#endif