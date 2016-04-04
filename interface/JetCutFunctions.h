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
#include "MyTools/AnalysisTools/interface/ObjectSelector.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

template <class T>
class ObjectSelector;

namespace JetCutFunctions {
	template <class T>
	bool MinPt(const edm::Handle<std::vector<pat::Jet> > p_data, ObjectSelector<T>* p_object_selector, int n);
}

#endif