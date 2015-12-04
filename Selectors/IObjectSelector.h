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

	ClassDef(IObjectSelector, 1);


	/*** Public Methods ***/
public:
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
	Int_t GetNGoodObjects();

	/**
	  * GetGoodObjectMap
	  * - Returns a std::map<Int_t, Bool_t> describing whether each object in the current event passed the cuts.
	  */
	std::map<Int_t, Bool_t>* GetGoodObjectMap();

	/**
	  * GetGoodObjectList
	  * - Returns a list of the indices of good objects in the current event
	  */
	std::vector<Int_t>* GetGoodObjectList();

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
		m_object_fake_type_ = p_fake_type;
	}

	inline ObjectSelector::ObjectFakeType GetObjectFakeType() {
		return m_object_fake_type_;
	}

	inline ObjectSelector::ObjectName GetObjectName() {
		return m_object_name;
	}

	/*** Private Methods ***/
private:

	/*** Public Members ***/
public:
 	// Preselection things
 	bool m_use_preselection;
 	std::map<Int_t, Bool_t> *m_object_preselection; // Things to do once, e.g. object overlap removal.

 	// Map: object index : pass
 	std::map<Int_t, Bool_t> m_obj_pass;

 	// List of indices that pass
 	std::vector<Int_t> m_obj_good;

 	// Number of good electrons
 	Int_t m_n_good_objects;


 	/*** Protected Members ***/
protected:
	Bool_t m_fresh_event;
 
 	ObjectName m_object_name;

 	ObjectFakeType m_object_fake_type_;

 	std::map<int, int> m_truth_match_indices_;

	ClassDef(ObjectSelector, 1);


};

//----------------------------------------------------------------------------------------
#endif
