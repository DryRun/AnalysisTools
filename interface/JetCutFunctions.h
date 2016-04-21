#ifndef JetCutFunctions_h
#define JetCutFunctions_h

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "TROOT.h"
#include "TMath.h"
#include "TPython.h"

#include "MyTools/RootUtils/interface/Constants.h"
//#include "MyTools/AnalysisTools/interface/EventSelector.h"
#include "MyTools/AnalysisTools/interface/ObjectSelector.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

template class ObjectSelector<pat::Jet>;

namespace JetCutFunctions {
	bool MinPt(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n);
	bool MaxPt(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n);
	bool MinAbsEta(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n);
	bool MaxAbsEta(const std::vector<pat::Jet>& p_data, ObjectSelector<pat::Jet>* p_object_selector, const int n);

	void Configure(ObjectSelector<pat::Jet>* p_selector);
}

#endif