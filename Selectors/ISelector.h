#ifndef ISelector_h
#define ISelector_h

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

class ISelector : public ISelector, public TObject {

	ClassDef(ISelector, 1);

public:
	enum DataSource {
		kCollisionData,
		kSimulation
	};

	/*** Public Methods ***/
public:
	// Basic
	ISelector();
	~ISelector();

	// Load configuration stuff
	/**
	 * Load the ISelector configuration from an XML file. DTD can be found at http://www-atlas.lbl.gov/~dryu/Multilepton/selections.dtd.
	 * @param  config_path Path to XML file
	 * @param  verbose     Print out list of cuts
	 */
	virtual bool LoadConfiguration(TString config_path, bool verbose = false);

	/**
	 * Was this cut configured?
	 * @param  p_name Name of cut
	 * @return        True if cut was configured in LoadConfiguration()
	 */
	bool CutIsConfigured(TString p_name);

	/**
	 * Set pointer to a D3PDReader::Event, and specify what kind of D3PD
	 * @param p_event     Pointer to D3PDReader::Event
	 * @param p_d3pd_type D3PDReader::SUSY or D3PDReader::SMWZ
	 */
	inline void SetxAODEvent(xAOD::TEvent *p_event) {
		event_ = p_event;
	}

	/**
	 * Set the data source to 
	 * @param p_source kCollisionData or kSimulation
	 */
	inline void SetDataSource(DataSource p_source) {
		data_source_ = p_source;
	}

	/**
	 * Print list of cuts and cut parameters/descriptors
	 */
	void PrintSummary();

	/**
	 * Save cutflow histograms to the EventLoop Worker output.
	 * @param wk Pointer to EL::Worker, which takes care of the output stream.
	 */
	virtual void SaveHistograms(EL::Worker *wk);

	// Accessors
	inline TString GetName() {
		return name_;
	}
	inline TString GetType() {
		return type_;
	}
	inline TString GetAuthor() {
		return author_;
	}

	inline std::vector<Double_t> *GetCutParameters(TString p_name) {
		return &cut_parameters_;
	}

	inline std::vector<TString> *GetCutDescriptors(TString p_name) {
		return &cut_descriptors_;
	}

	/**
	 * Print current cut results
	 */
	void PrintCurrentCutResults();

	/*** Private Methods ***/
private:
	/**
	 * Get configuration metadata out of an XML file
	 * @param p_xml TDOMParser object with configuration file loaded.
	 */
	void GetConfigurationMetadata(TDOMParser *p_xml);

	/**
	 * Get configuration cuts out of an XML file
	 * @param p_xml TDOMParser object with configuration file loaded.
	 */
	void GetConfigurationCuts(TDOMParser *p_xml);

	virtual void AddCut(TXMLNode *cut_node);
	//void AddCut(TString c_name, Double_t c_value, TString c_cutgroup_name);


	/*** Public Members ***/
public:
	// -- List of configured cuts, and parameters
	TString author_;
	TString name_;
	TString type_; // numerator or denominator
	std::vector<TString> cut_list_;
	std::map<TString, std::vector<Double_t> > cut_parameters_;
	std::map<TString, std::vector<TString> > cut_descriptors_;
 	std::map<TString, bool> configured_cuts_;
 	bool save_histograms_; 

	// -- Data comes from the D3PDReader event.
	xAOD::TEvent *event_;

	// -- Awareness of data or MC. Some cut functions may want to know.
	DataSource data_source_;

	// -- Bookkeeping
	std::map<TString, Int_t> cut_counter_; // Lists number of times a given cut is failed. Map is <cut> : <#fails>. Inclusive.
	std::map<TString, Int_t> cutflow_counter_; // Cutflow counter. Map is <cut> : <#fails>. Exclusive.
	std::map<TString, Int_t> pass_counter_; // Counts number of events that pass a given cut. Exclusive.
	std::map<TString, Bool_t> this_event_cut_results_; // Stores cut results of current event
	int pass_calls_;
	int pass_;
	int fail_;
	bool configured;
	TH1D *h_cutflow_counter_;
	TH1D *h_cut_counter_;
	Int_t debug_counter_;

};

//----------------------------------------------------------------------------------------
#endif
