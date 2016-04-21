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

template <class T>
class ObjectSelector : public Cutflow {
public:
	// Index of cut functions
	#ifndef __CINT__
	typedef bool (*CutFunction)(const T& p_data, ObjectSelector* p_object_selector, const int n);
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
	
	 void AddCutFunction(TString p_cut_name, CutFunction p_cut_function) {
	 	cut_functions_[p_cut_name] = p_cut_function
	 }

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
	void ClassifyObjects(const T p_data);

	/**
	 * Get number of objects passing selection
	 * @return Number of objects passing selection
	 */
	inline int GetNumberOfGoodObjects() {
		return obj_good_.size();
	}

	/**
	 * Get map of whether each object passes selection
	 */
	inline std::map<int, bool>& GetGoodObjectMap() {
		return obj_pass_;
	}

	inline std::vector<int>& GetGoodObjectIndices() {
		return obj_good_;
	}

	inline bool GetObjectPass(int p_index) {
		return obj_pass_[p_index];
	}

	inline const ObjectIdentifiers::ObjectType GetObjectType() {
		return object_;
	}

	inline const T GetData() {
		return data_;
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
	T data_;
	std::map<int, bool> obj_pass_;
	std::vector<int> obj_good_;

};
//template <> bool ObjectSelector<edm::Handle<std::vector<pat::Jet> > >::Configure();
//template <> bool ObjectSelector<edm::Handle<std::vector<pat::Electron> > >::Configure();


#endif