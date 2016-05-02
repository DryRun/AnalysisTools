#ifndef ObjectSelector_h
#define ObjectSelector_h

#include <iostream>
#include <map>
#include <vector>

#include "TString.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
//#include "DataFormats/PatCandidates/interface/Electron.h"
//#include "DataFormats/PatCandidates/interface/Jet.h"

#include "MyTools/AnalysisTools/interface/Cutflow.h"
#include "MyTools/AnalysisTools/interface/ObjectTypeEnums.h"
#include "MyTools/AnalysisTools/interface/ObjectSelectorResults.h"


template <class T>
class ObjectSelector : public Cutflow, public ObjectSelectorResults {
public:
	// Index of cut functions
	#ifndef __CINT__
	typedef bool (*CutFunction)(const std::vector<T>& p_data, ObjectSelector* p_object_selector, const int n);
 	std::map<TString, CutFunction> cut_functions_;
 	#endif

public:
	ObjectSelector();
	~ObjectSelector();

	/**
	 * Configure the object selector. Defined explicitly for objects T, to create the correct map of cut functions.
	 * @return	true if everything succeeded
	 */
	//bool Configure();
	
	 void AddCutFunction(TString p_cut_name, CutFunction p_cut_function);

	/**
	 * Make sure the cut exists in the cut index, then register it with Cutflow::RegisterCut.
	 * @param p_cut_name        Name
	 * @param p_cut_descriptors String cuts
	 * @param p_cut_parameters  Number cuts
	 */
	void RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters);

	/**
	 * Run selection on all objects in event.
	 * @param p_data edm::Handle to the data.
	 */
	void ClassifyObjects(const std::vector<T>& p_data);

	inline const ObjectIdentifiers::ObjectType GetObjectType() {
		return object_;
	}

	inline void SetObjectType(ObjectIdentifiers::ObjectType p_object) {
		object_ = p_object;
	}


private:
	/**
	 * Does object i pass all cuts?
	 * @param  i Index of object inside vector
	 * @return   true if object i passes all cuts
	 */
	bool Pass(int i);

	/**
	 * Clear results from last event
	 */
	void Reset();

public:

private:
	ObjectIdentifiers::ObjectType object_;
	const std::vector<T>* data_;

};
//template <> bool ObjectSelector<edm::Handle<std::vector<pat::Jet> > >::Configure();
//template <> bool ObjectSelector<edm::Handle<std::vector<pat::Electron> > >::Configure();

template<class T>
ObjectSelector<T>::ObjectSelector() {
	object_ = ObjectIdentifiers::kNoObjectName;
}

template<class T>
ObjectSelector<T>::~ObjectSelector() {}

//template <> bool ObjectSelector<pat::Jet>::Configure() {
//	cut_functions_["MinPt"] = &JetCutFunctions::MinPt;
//	cut_functions_["MaxAbsEta"] = &JetCutFunctions::MaxAbsEta;
//
//	object_ = ObjectIdentifiers::kJet;
//	SetName("DefaultJetSelection");
//	SetObjectName("Jet");
//	return true;
//}

//template <> bool ObjectSelector<pat::Electron>::Configure() {
//	cut_functions_["MinPt"] = &ElectronCutFunctions::MinPt;
//	object_ = ObjectIdentifiers::kElectron;
//	SetName("DefaultElectronSelection");
//	SetObjectName("Electron");
//	return true;
//}

template<class T>
void ObjectSelector<T>::AddCutFunction(TString p_cut_name, CutFunction p_cut_function) {
	cut_functions_[p_cut_name] = p_cut_function;
}


template<class T>
void ObjectSelector<T>::RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters) {
	if (cut_functions_.find(p_cut_name) == cut_functions_.end()) {
		std::cerr << "[ObjectSelector] ERROR : Unknown cut " << p_cut_name << ". Please add it to the index in the appropriate ObjectSelector<T>::Configure() function." << std::endl;
		exit(1);
	}
	Cutflow::RegisterCut(p_cut_name, p_cut_descriptors, p_cut_parameters);
}


template<class T>
void ObjectSelector<T>::ClassifyObjects(const std::vector<T>& p_data) {
	Reset();
	data_ = &p_data;
	for (unsigned int i = 0; i < p_data.size(); ++i) {
		obj_pass_[i] = Pass(i);
		if (obj_pass_[i]) {
			obj_good_.push_back(i);
		}
	}
	n_obj_ = p_data.size();
}

template<class T>
bool ObjectSelector<T>::Pass(int i) {
	++pass_calls_;
	bool this_pass = true;
	for (auto & it_cut : cut_list_) {
		if (!cut_functions_[it_cut](*data_, this, i)) {
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
	return this_pass;
}

template<class T>
void ObjectSelector<T>::Reset() {
	obj_pass_.clear();
	obj_good_.clear();
}

#endif