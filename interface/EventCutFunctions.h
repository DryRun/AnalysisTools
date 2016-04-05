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

class EventSelector;

namespace EventCutFunctions {
	bool VertexMinTracks(EventSelector* p_event_selector);
	bool VertexMinNdof(EventSelector* p_event_selector);
	bool VertexMaxAbsZ(EventSelector* p_event_selector);
	bool VertexMaxRho(EventSelector* p_event_selector);
	bool ExactNJets(EventSelector* p_event_selector);
	bool MinNJets(EventSelector* p_event_selector);
	bool MaxNJets(EventSelector* p_event_selector);

}

#endif