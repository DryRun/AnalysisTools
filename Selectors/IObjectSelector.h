#ifndef IObjectSelector_h
#define IObjectSelector_h

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "TObject.h"
#include "TDOMParser.h"
#include "TXMLDocument.h"
#include "TXMLNode.h"
#include "TXMLAttr.h"
#include "TH1.h"
#include "TH2.h"
#include "TList.h"
#include "TMath.h"
#include "TFile.h"
#include "TSystem.h"

#include "xAODRootAccess/TEvent.h"
#include "EventLoop/Worker.h"
#include "EventLoop/Algorithm.h"
#include "RootUtils/SimpleConfiguration.h"

class IObjectSelector : public ISelector, public TObject {
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
public:
	#ifndef __CINT__
	typedef bool (*CutFunction)(const xAOD::TEvent* p_event, IObjectSelector* p_track_selector, int n);
 	std::map<TString, CutFunction> cut_functions_;
 	#endif


	/*** Public Methods ***/
public:
	ClassDef(IObjectSelector, 1);

	// Basic
	IObjectSelector();
	~IObjectSelector();

	/*** Methods to perform the object classifications ***/
	// Most of these are pure virtual functions, since they need to know which D3PDObjectBase-derived classes to use in the cut functions.

	/** 
	  * Pass (int i)
	  * - Returns whether object with D3PDReader::Event index i passes the configured cuts.
	  * - Records the cut decisions for later digestion.
	  */
	virtual Bool_t Pass(int i) = 0;
	
	/**
	  * Pass (int i, TString p_cut_name)
	  * - External access to individual cut functions. Doesn't increment counters.
	  */
	virtual Bool_t Pass(int i, TString p_cut_name) = 0;


	/**
	  * SetNewEvent
	  * - Clear maps and counters from last event, setting a flag "m_fresh_event" for the Classify function
	  * - Set overlap removal and other preselection-type maps
	  */
	virtual void SetNewEvent(std::map<Int_t, Bool_t> *p_object_preselection);


	/**
	  * ClassifyObjects (with overlap removal)
	  * - Calls Pass on each object in the event.
	  */
	virtual void ClassifyObjects() = 0;

	/**
	  * Clear
	  * - Reset the maps and vectors for the next event
	  */
	void Clear();

	inline void AddTruthMatchIndex(const int p_reco_index, const int p_mc_index) {
		m_truth_match_indices_[p_reco_index] = p_mc_index;
	}

	const int GetTruthMatchIndex(const int p_reco_index) {
		if (m_truth_match_indices_.find(p_reco_index) != m_truth_match_indices_.end()) {
			return m_truth_match_indices_[p_reco_index];
		} else {
			return -1;
		}
	}

	/*** Methods to get the results of the current event ***/

	/**
	  * GetNGoodObjects
	  * - Get current number of good electrons
	  */
	inline int GetNGoodObjects() {
		return n_good_objects_;
	}

	/**
	  * GetGoodObjectMap
	  * - Returns a std::map<Int_t, Bool_t> describing whether each object in the current event passed the cuts.
	  */
	inline std::map<Int_t, Bool_t>* GetGoodObjectMap() {
		return &obj_pass_;
	}

	/**
	  * GetGoodObjectList
	  * - Returns a list of the indices of good objects in the current event
	  */
	std::vector<Int_t>* GetGoodObjectList() {
		return &obj_good_;
	}

	/**
	  * IsGood
	  * - Returns 1 if good, 0 if bad, -1 if nonexistent
	  */
	int IsGood(int p_index);


	/**
	 * Set whether to use preselection maps. Set to "true" by default.
	 * @param p_use_preselection 'true' to use preselection maps.
	 */
	void UsePreselection(bool p_use_preselection);

	inline void SetObjectFakeType(ObjectSelector::ObjectFakeType p_fake_type) {
		object_fake_type_ = p_fake_type;
	}

	inline ObjectSelector::ObjectFakeType GetObjectFakeType() {
		return object_fake_type_;
	}

	inline ObjectSelector::ObjectName GetObjectName() {
		return object_name_;
	}

	/*** Private Methods ***/
private:

	/*** Public Members ***/
public:
 	// Preselection things
 	bool use_preselection_;
 	std::map<Int_t, Bool_t> *object_preselection_; // Things to do once, e.g. object overlap removal.

 	// Map: object index : pass
 	std::map<Int_t, Bool_t> obj_pass_;

 	// List of indices that pass
 	std::vector<Int_t> obj_good_;

 	// Number of good electrons
 	Int_t n_good_objects_;


 	/*** Protected Members ***/
protected:
	Bool_t fresh_event_;
 
 	ObjectName object_name_;

 	ObjectFakeType object_fake_type_;

 	std::map<int, int> truth_match_indices_;

	ClassDef(ObjectSelector, 1);


};

//----------------------------------------------------------------------------------------
#endif
