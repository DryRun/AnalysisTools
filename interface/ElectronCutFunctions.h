#ifndef ElectronCutFunctions_h
#define ElectronCutFunctions_h

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "TROOT.h"
#include "TMath.h"
#include "TPython.h"

#include "MyTools/RootUtils/interface/Constants.h"
#include "MyTools/AnalysisTools/interface/ObjectSelector.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

template class ObjectSelector<pat::Electron>;

namespace ElectronCutFunctions {
	bool MinPt(const std::vector<pat::Electron>& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n);
	bool MaxPt(const std::vector<pat::Electron>& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n);
	bool MinAbsEta(const std::vector<pat::Electron>& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n);
	bool MaxAbsEta(const std::vector<pat::Electron>& p_data, ObjectSelector<pat::Electron>* p_object_selector, const int n);
	void Configure(ObjectSelector<pat::Electron>* p_selector);
}

#endif