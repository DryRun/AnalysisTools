#ifndef ElectronCutFunctions_h
#define ElectronCutFunctions_h

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "TMath.h"
#include "TPython.h"

#include "MyTools/RootUtils/Constants.h"
#include "MyTools/AnalysisTools/include/ObjectSelector.h"

namespace TrackCutFunctions {
	bool MinNPixHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MinNSCTHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MinNSiHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MinNPixLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MinNInnerPixLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MinNOuterPixLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MinNSCTLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MinNSiLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MaxNPixHoles(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MaxNSCTHoles(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MaxNSiHoles(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MaxD0SignificanceNoBeamspot(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
	bool MaxD0Significance(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
}

#endif