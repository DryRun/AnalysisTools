#ifndef EventSelector_h
#define EventSelector_h

#include <iostream>
#include <map>
#include <vector>

#include "TString.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "MyTools/AnalysisTools/interface/ObjectTypeEnums.h"
#include "MyTools/AnalysisTools/interface/ObjectSelector.h"
#include "MyTools/AnalysisTools/interface/EventCutFunctions.h"

class EventSelector : public Cutflow {
public:
	// Index of cut functions
	#ifndef __CINT__
	typedef bool (*CutFunction)(EventSelector* p_event_selector);
 	std::map<TString, CutFunction> cut_functions_;
 	#endif

public:
	EventSelector();

	~EventSelector();

	/**
	 * Setup map from cuts to cut functions
	 */
	void Configure();

	/**
	 * Make sure the cut exists in the cut index, then register it with Cutflow::RegisterCut.
	 * @param p_cut_name        Name
	 * @param p_cut_descriptors String cuts
	 * @param p_cut_parameters  Number cuts
	 */
	void RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters);

	/**
	 * Add/Get methods for object selectors.
	 */
	inline void AddJetSelector(ObjectSelector<pat::Jet>* p_jet_selector) {
		jet_selector_ = p_jet_selector;
	}

	inline ObjectSelector<pat::Jet>* GetJetSelector() {
		return jet_selector_;
	}

	inline void AddElectronSelector(ObjectSelector<pat::Electron>* p_electron_selector) {
		electron_selector_ = p_electron_selector;
	}

	inline ObjectSelector<pat::Electron>* GetElectronSelector() {
		return electron_selector_;
	}

	inline const edm::Event* GetEvent() {
		return event_;
	}

	inline edm::Handle<std::vector<reco::Vertex> >* GetVertices() {
		return vertices_;
	}

	void ProcessEvent(const edm::Event* p_event, edm::Handle<std::vector<reco::Vertex> >* p_vertices);

	inline bool GetEventPass() {
		return event_good_;
	}

private:
	/**
	 * Clear any data saved from the previous event
	 */
	void Reset();

public:

private:
	const edm::Event* event_;
	edm::Handle<std::vector<reco::Vertex> >* vertices_;
	//std::map<ObjectIdentifiers::ObjectType, ObjectSelector*> object_selectors_;
	ObjectSelector<pat::Electron>* electron_selector_;
	ObjectSelector<pat::Jet>* jet_selector_;
	bool event_good_;
};

#endif