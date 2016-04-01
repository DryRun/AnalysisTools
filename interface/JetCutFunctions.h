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

#include "MyTools/RootUtils/Constants.h"
#include "MyTools/AnalysisTools/include/ObjectSelector.h"
#include "DataFormats/​PatCandidates/​interface/​Jet.h"

namespace JetCutFunctions {
	bool MinPt(const edm::Handle<std::vector<pat::Jet> > p_data, ObjectSelector* p_object_selector, int n);
}

#endif