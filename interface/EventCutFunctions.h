#ifndef EventCutFunctions_h
#define EventCutFunctions_h

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "TROOT.h"
#include "TMath.h"
#include "TPython.h"

#include "MyTools/AnalysisTools/interface/EventSelector.h"

template class EventSelector<edm::Event>;

namespace EventCutFunctions {

}

#endif