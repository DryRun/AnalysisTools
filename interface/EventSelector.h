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

	inline ObjectSelectorResults* GetObjectSelector(ObjectIdentifiers::ObjectType p_object_type) {
		if (object_selectors_.find(p_object_type) == object_selectors_.end()) {
			std::cerr << "[EventSelector::GetObjectSelector] ERROR : Unknown object type" << std::endl;
			exit(1);
		}
		return object_selectors_[p_object_type];
	}

	/**
	 * Accessor to underlying ObjectSelector::GetObjectPass. 
	 * @param  p_object_type ObjectIdentifier for the ObjectSelector
	 * @param  n             Index of object
	 * @return               True if object[n] passes the ObjectSelector selection. Return false if the index n is outside the range.
	 */
	bool GetObjectPass(ObjectIdentifiers::ObjectType p_object_type, unsigned int n);

	/**
	 * Accessot to underlying ObjectSelector::GetNumberOfGoodObjects
	 * @param  p_object_type ObjectIdentifier for the ObjectSelector
	 * @return               ObjectSelector::GetNumberOfGoodObjects()
	 */
	unsigned int GetNumberOfGoodObjects(ObjectIdentifiers::ObjectType p_object_type);

	inline const T* GetEvent() {
		return event_;
	}

	void ProcessEvent(const T* p_event);

	inline bool Pass() {
		return event_good_;
	}

	inline bool PassCut(TString cut_name) const {
		bool pass = false;
		auto cut_result = cut_results_.find(cut_name);
		if (cut_result == cut_results_.end()) {
			std::cerr << "[EventSelector::PassCut] WARNING : PassCut requested for unknown cut " << cut_name << ". Returning false." << std::endl;
		} else {
			pass = (*cut_result).second;
		}
		return pass;
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
	std::map<TString, bool> cut_results_;

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
		cut_results_[it_cut] = cut_functions_[it_cut](*event_, this);
		if (!cut_results_[it_cut]) {
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

	// N-1 histograms
	for (auto& it_cut : cut_list_) {
		if (histograms_nminusone_.find(it_cut) != histograms_nminusone_.end()) {
			if (return_data_.find(it_cut) != return_data_.end()) {
				// Calculate N - 1
				bool pass_nminusone = true;
				for (auto& it_cut2 : cut_list_) {
					if (it_cut == it_cut2) {
						continue;
					}
					pass_nminusone = pass_nminusone && cut_results_[it_cut2];
				}
				if (pass_nminusone) {
					histograms_nminusone_[it_cut]->Fill(return_data_[it_cut]);
					if (histograms_nminusone_2D_.find(it_cut) != histograms_nminusone_2D_.end()) {
						for (auto& it_second_var_hist : histograms_nminusone_2D_[it_cut]) {
							if (return_data_.find(it_second_var_hist.first) != return_data_.end()) {
								(it_second_var_hist.second)->Fill(return_data_[it_cut], return_data_[it_second_var_hist.first]);
							} else {
								std::cerr << "[EventSelector::ProcessEvent] WARNING : 2D N-1 histogram requested for " << it_cut << " vs " << it_second_var_hist.first << ", but return data was not set for the second variable." << std::endl;
							}
						}
					}
				}
			}
		}
	}
}

template<class T>
void EventSelector<T>::Reset() {
	event_ = 0;
	return_data_.clear();
	cut_results_.clear();
}

template<class T>
bool EventSelector<T>::GetObjectPass(ObjectIdentifiers::ObjectType p_object_type, unsigned int n) {
	if (object_selectors_.find(p_object_type) == object_selectors_.end()) {
		std::cerr << "[EventSelector::GetObjectPass] ERROR : Unknown object type." << std::endl;
		exit(1);
	}
	bool pass = true;
	if (n >= object_selectors_[p_object_type]->GetTotalNumberOfObjects()) {
		pass = false;
	} else {
		pass = object_selectors_[p_object_type]->GetObjectPass(n);
	}
	return pass;
}

template<class T>
unsigned int EventSelector<T>::GetNumberOfGoodObjects(ObjectIdentifiers::ObjectType p_object_type) {
	if (object_selectors_.find(p_object_type) == object_selectors_.end()) {
		std::cerr << "[EventSelector::GetObjectPass] ERROR : Unknown object type." << std::endl;
		exit(1);
	}
	return object_selectors_[p_object_type]->GetNumberOfGoodObjects();
}


#endif