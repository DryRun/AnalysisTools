#ifndef xAODEventAccess_h
#define xAODEventAccess_h

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

#include "EventLoop/Worker.h"
#include "EventLoop/Algorithm.h"
#include "RootUtils/SimpleConfiguration.h"

class xAODEventAccess : public TObject {

	ClassDef(xAODEventAccess, 1);
	/*** Public Members ***/
public:
	// Basic
	xAODEventAccess();
	~xAODEventAccess();

	// -- Load configuration
public:
	/**
	 * Load the xAODEventAccess configuration from an XML file. DTD can be found at http://www-atlas.lbl.gov/~dryu/Multilepton/selections.dtd.
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
	virtual void SetD3PDEvent(D3PDReader::Event *p_event, D3PDReader::D3PDType p_d3pd_type);

	// -- Print summary info
	/**
	 * Print list of cuts and cut parameters/descriptors
	 */
	virtual void PrintSummary();

	/**
	 * Save cutflow histograms to the EventLoop Worker output.
	 * @param wk Pointer to EL::Worker, which takes care of the output stream.
	 */
	virtual void SaveHistograms(EL::Worker *wk);

	std::vector<Double_t> *GetCutParameters(TString p_name);
	std::vector<TString> *GetCutDescriptors(TString p_name);
	virtual void SetDataOrigin(Bool_t p_is_mc);

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
	TString m_author;
	TString m_name;
	TString m_type; // numerator or denominator
	std::vector<TString> cut_list;
	std::map<TString, std::vector<Double_t> > cut_parameters;
	std::map<TString, std::vector<TString> > cut_descriptors;
 	std::map<TString, bool> configured_cuts;

	// -- Data comes from the D3PDReader event.
	D3PDReader::Event *m_event;

	// -- Two types of D3PD are available at the moment: SUSY and SMWZ. Annoyingly, they have different branches for the primary vertex, (SUSY=vx, SMWZ=vxp), so this needs to be handled manually.
	D3PDReader::D3PDType m_d3pd_type;

	// -- String identifying the D3PDReader object to use
	TString m_collection_name;

	// -- Awareness of data or MC. Some cut functions may want to know.
	Bool_t m_is_mc;

	// -- Bookkeeping
	std::map<TString, Int_t> m_cut_counter; // Lists number of times a given cut is failed. Map is <cut> : <#fails>. Inclusive.
	std::map<TString, Int_t> m_cutflow_counter; // Cutflow counter. Map is <cut> : <#fails>. Exclusive.
	std::map<TString, Int_t> m_pass_counter; // Counts number of events that pass a given cut. Exclusive.
	std::map<TString, Bool_t> m_this_event_cut_results; // Stores cut results of current event
	int m_pass_calls;
	int m_pass;
	int m_fail;
	bool configured;
	TH1D *h_cutflow_counter;
	TH1D *h_cut_counter;
	Int_t m_debug_counter;

};

//----------------------------------------------------------------------------------------
#endif
