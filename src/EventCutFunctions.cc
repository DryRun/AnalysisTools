#ifndef EventCutFunctions_cxx
#define EventCutFunctions_cxx

#include "MyTools/AnalysisTools/interface/EventCutFunctions.h"
#include "MyTools/RootUtils/interface/Constants.h"

namespace EventCutFunctions {
	bool VertexMinTracks(EventSelector* p_event_selector) {
		return (*p_event_selector->GetVertices())->at(0).nTracks() >= p_event_selector->GetCutParameters("VertexMinTracks")[0];
	}
	bool VertexMinNdof(EventSelector* p_event_selector) {
		return (*p_event_selector->GetVertices())->at(0).ndof() >= p_event_selector->GetCutParameters("VertexMinNdof")[0];
	}
	bool VertexMaxAbsZ(EventSelector* p_event_selector) {
		return TMath::Abs((*p_event_selector->GetVertices())->at(0).z()) <= p_event_selector->GetCutParameters("VertexMaxAbsZ")[0];
	}
	bool VertexMaxRho(EventSelector* p_event_selector) {
		return (*p_event_selector->GetVertices())->at(0).position().rho() <= p_event_selector->GetCutParameters("VertexMaxRho")[0];
	}
	bool ExactNJets(EventSelector* p_event_selector) {
		return p_event_selector->GetJetSelector()->GetNumberOfGoodObjects() == p_event_selector->GetCutParameters("ExactNJets")[0];
	}
	bool MinNJets(EventSelector* p_event_selector) {
		return p_event_selector->GetJetSelector()->GetNumberOfGoodObjects() >= p_event_selector->GetCutParameters("MinNJets")[0];
	}
	bool MaxNJets(EventSelector* p_event_selector) {
		return p_event_selector->GetJetSelector()->GetNumberOfGoodObjects() <= p_event_selector->GetCutParameters("MaxNJets")[0];
	}
//		// Get 2 highest pT jets
//		std::pair<pat::Jet, pat::Jet> dijet_pair;
//		for (auto it_jets: p_event_selector->GetObjectSelector(ObjectSelector::kJet)->GetGoodObjectIndices()) {
//			double this_pt = (p_event_selector->GetObjectSelector(ObjectSelector::kJet)->GetData())[it_jet].pt();
//			if (this_pt > dijet_pair.first.pt()) {
//
//			}
//		}
//	}
}

#endif