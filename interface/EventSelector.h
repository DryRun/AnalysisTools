#ifndef EventSelector_h
#define EventSelector_h

#include <iostream>
#include <map>
#include <vector>

#include "TString.h"

//#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
//#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "MyTools/AnalysisTools/interface/ObjectTypeEnums.h"
#include "MyTools/AnalysisTools/interface/ObjectSelector.h"

template <class T> 
class EventSelector : public Cutflow {
public:
	// Index of cut functions
	#ifndef __CINT__
	typedef bool (*CutFunction)(const T& p_event, EventSelector* p_event_selector);
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
	 * Add a CutFunction to the index
	 * @param p_cut_name     Name of cut
	 * @param p_cut_function &FunctionName
	 */
	void AddCutFunction(TString p_cut_name, CutFunction p_cut_function);

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
	inline void AddObjectSelector(ObjectIdentifiers::ObjectType p_object_type, ObjectSelectorResults* p_object_selector) {
		object_selectors_[p_object_type] = p_object_selector;
	}

	inline const T* GetEvent() {
		return event_;
	}

	void ProcessEvent(const T* p_event);

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
	const T* event_;
	std::map<ObjectIdentifiers::ObjectType, ObjectSelectorResults*> object_selectors_;
	bool event_good_;
};

template<class T>
EventSelector<T>::EventSelector() {}

template<class T>
EventSelector<T>::~EventSelector() {}

//void EventSelector::Configure() {
//	cut_functions_["VertexMinTracks"] = &EventCutFunctions::VertexMinTracks;
//	cut_functions_["VertexMinNdof"]   = &EventCutFunctions::VertexMinNdof;
//	cut_functions_["VertexMaxAbsZ"]   = &EventCutFunctions::VertexMaxAbsZ;
//	cut_functions_["VertexMaxRho"]    = &EventCutFunctions::VertexMaxRho;
//	cut_functions_["ExactNJets"]      = &EventCutFunctions::ExactNJets;
//	cut_functions_["MinNJets"]        = &EventCutFunctions::MinNJets;
//	cut_functions_["MaxNJets"]        = &EventCutFunctions::MaxNJets;
//
//	SetName("DefaultEventSelection");
//	SetObjectName("Event");
//}

template<class T>
void EventSelector<T>::AddCutFunction(TString p_cut_name, CutFunction p_cut_function) {
	cut_functions_[p_cut_name] = p_cut_function;
}


template<class T>
void EventSelector<T>::RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters) {
	if (cut_functions_.find(p_cut_name) == cut_functions_.end()) {
		std::cerr << "[EventSelector] ERROR : Unknown cut " << p_cut_name << ". Please add it to the index in EventSelector::Configure()." << std::endl;
		exit(1);
	}
	Cutflow::RegisterCut(p_cut_name, p_cut_descriptors, p_cut_parameters);
}

template<class T>
void EventSelector<T>::ProcessEvent(const T* p_event) {
	Reset();
	event_ = p_event;
	++pass_calls_;
	bool this_pass = true;
	for (auto & it_cut : cut_list_) {
		if (!cut_functions_[it_cut](*event_, this)) {
			if (this_pass) {
				this_pass = false;
				cutflow_counter_[it_cut]++;
			}
			cut_counter_[it_cut]++;
		}
		if (this_pass) {
			pass_counter_[it_cut]++;
		}
	}
	event_good_ = this_pass;
}

template<class T>
void EventSelector<T>::Reset() {
	event_ = 0;
}

#endif