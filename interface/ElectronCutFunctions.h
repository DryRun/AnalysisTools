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
#include "DataFormats/​PatCandidates/​interface/​Electron.h"

namespace ElectronCutFunctions {
	bool MinPt(const edm::Handle<std::vector<pat::Electron> > p_data, ObjectSelector* p_object_selector, int n);
}

#endif