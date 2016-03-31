#ifndef ObjectSelector_h
#define ObjectSelector_h

#include <iostream>
#include <map>
#include <vector>

#include 

template <class T>
class ObjectSelector {
public:
	enum ObjectName {
		kElectron,
		kMuon,
		kTau,
		kJet,
		kW,
		kZ,
		kHiggs,
		kElectronNeutrino,
		kMuonNeutrino,
		kTauNeutrino,
		kAnyNeutrino,
		kNoObjectName,
		kTrack
	};

	enum ObjectFakeType {
		kNumerator,
		kDenominator,
		kUnspecified
	};

	// Index of cut functions
	#ifndef __CINT__
	typedef bool (*CutFunction)(const edm::Handle<std::vector<T> > p_data, ObjectSelector* p_object_selector, int n);
 	std::map<TString, CutFunction> cut_functions_;
 	#endif

public:
	ObjectSelector();
	~ObjectSelector();

	/**
	 * Configure the object selector
	 * @param  p_cut_descriptors String-based cuts
	 * @param  p_cut_parameters  Double-based cuts
	 * @return                   true if everything succeeded
	 */
	bool Configure(std::map<TString, std::vector<TString> > p_cut_descriptors, std::map<TString, std::vector<double> > p_cut_parameters);

	/**
	 * Run selection on all objects in event.
	 * @param p_data edm::Handle to the data.
	 */
	void ClassifyObjects(edm::Handle<std::vector<T> > p_data);

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

	inline bool GetObjectPass(int p_index) {
		return obj_pass_[p_index];
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

	void RegisterCut(TString p_cut_name, std::map<TString, std::vector<TString> > p_cut_descriptors, std::map<TString, std::vector<double> > p_cut_parameters);
public:

private:
	edm::EDGetTokenT<T> token_;
	std::map<int, bool> obj_pass_;
	std::vector<int> obj_good_;

	// Bookkeeping
	std::vector<TString> cut_list_;
	std::map<TString, std::vector<Double_t> > cut_parameters_;
	std::map<TString, std::vector<TString> > cut_descriptors_;
 	std::map<TString, bool> configured_cuts_;

	std::map<TString, Int_t> cut_counter_; // Lists number of times a given cut is failed. Map is <cut> : <#fails>. Inclusive.
	std::map<TString, Int_t> cutflow_counter_; // Cutflow counter. Map is <cut> : <#fails>. Exclusive.
	std::map<TString, Int_t> pass_counter_; // Counts number of events that pass a given cut. Exclusive.


};

template <> bool ObjectSelector<pat::Jet>::Configure(std::map<TString, std::vector<TString> > p_cut_descriptors, std::map<TString, std::vector<double> > p_cut_parameters);
template <> bool ObjectSelector<pat::Electron>::Configure(std::map<TString, std::vector<TString> > p_cut_descriptors, std::map<TString, std::vector<double> > p_cut_parameters);


#endif