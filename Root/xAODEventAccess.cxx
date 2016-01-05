#ifndef xAODEventAccess_cxx
#define xAODEventAccess_cxx

#include "AnalysisTools/xAODEventAccess.h"
#include <iostream>
#include <iomanip>
#include <cmath>

ClassImp(xAODEventAccess);

xAODEventAccess::xAODEventAccess() {
	configured = false;
	m_event = 0;
	m_is_mc = false;
	m_debug_counter = 0;
	h_cutflow_counter = 0;
	h_cut_counter = 0;
}

xAODEventAccess::~xAODEventAccess() {
	if (h_cutflow_counter) delete h_cutflow_counter;
	if (h_cut_counter) delete h_cut_counter;
}

void xAODEventAccess::GetConfigurationMetadata(TDOMParser *p_xml) {
	TXMLDocument* xmldoc = p_xml->GetXMLDocument();
	TXMLNode* sel_node = xmldoc->GetRootNode();
	TXMLNode* sel_elem = sel_node->GetChildren();
	while (sel_elem != 0) {

		// Metadata
		if (sel_elem->GetNodeName() == TString("author")) {
			m_author = sel_elem->GetText();
		} else if (sel_elem->GetNodeName() == TString("name")) {
			m_name = sel_elem->GetText();
		} else if (sel_elem->GetNodeName() == TString("type")) {
			m_type = sel_elem->GetText();
		} else if (sel_elem->GetNodeName() == TString("collection")) {
			m_collection_name = sel_elem->GetText();
		}
		// Next top-level node
		sel_elem = sel_elem->GetNextNode();
	}
}

void xAODEventAccess::GetConfigurationCuts(TDOMParser *p_xml) {
	TXMLDocument* xmldoc = p_xml->GetXMLDocument();
	TXMLNode* sel_node = xmldoc->GetRootNode();
	TXMLNode* sel_elem = sel_node->GetChildren();
	while (sel_elem != 0) {
		if (TString(sel_elem->GetNodeName()).EqualTo("cut")) {
				AddCut(sel_elem);
		} else if (TString(sel_elem->GetNodeName()).EqualTo("include")) {
			// Load another configuration file
			TDOMParser *subxmlparser = new TDOMParser();
			TString subconfig_path = sel_elem->GetText();
			gSystem->ExpandPathName(subconfig_path);
			std::cout << "[xAODEventAccess] DEBUG : Loading an include file from " << subconfig_path << std::endl;
			subxmlparser->ParseFile(subconfig_path);
			GetConfigurationCuts(subxmlparser);
		} // Next top-level node
		sel_elem = sel_elem->GetNextNode();
	}
}

bool xAODEventAccess::LoadConfiguration(TString config_path, bool verbose) {
	std::cout << "[xAODEventAccess] INFO : Reading selection configuration from " << config_path << std::endl;
	bool success;

	// Expand path variables
	gSystem->ExpandPathName(config_path);

	// Load configuration from XML file. See Config/testSelection.xml for an example. 
	TDOMParser *xmlparser = new TDOMParser();
	Int_t parseCode(1);

	// Where does this function come from? For now, ignore it. 
	// xmlparser->SetValidate(kFALSE);

	parseCode = xmlparser->ParseFile(config_path);
	if (parseCode != 0) {
		success = false;
	} else {
		success = true;
		GetConfigurationMetadata(xmlparser);
		GetConfigurationCuts(xmlparser);
	}

	// Result
	configured = success;
	if (success && verbose) {
		std::cout << "[xAODEventAccess] INFO : Read in selection: " << std::endl;
		if (m_author) std::cout << "[xAODEventAccess] INFO : \tAuthor = " << m_author << std::endl;
		if (m_name) std::cout << "[xAODEventAccess] INFO : \tName = " << m_name << std::endl;
		std::cout << "[xAODEventAccess] INFO : Cuts:" << std::endl;
		for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {
			std::cout << "[xAODEventAccess] \tParameters:" << *it << std::endl;
			for (std::vector<Double_t>::iterator par = cut_parameters[*it].begin(); par != cut_parameters[*it].end(); ++par) {
				std::cout << "[xAODEventAccess] \t\t" << *par << std::endl;
			}
			std::cout << "[xAODEventAccess] \t\tDescriptors:" << *it << std::endl;
			for (std::vector<TString>::iterator desc= cut_descriptors[*it].begin(); desc!= cut_descriptors[*it].end(); ++desc) {
				std::cout << "[xAODEventAccess] \t\t" << *desc<< std::endl;
			}
		}
	}
	// Initialize cut counters
	m_pass_calls = 0;
	//m_cut_counter["pass"] = 0;
	//m_cut_counter["fail"] = 0;
	m_pass = 0;
	m_fail = 0;


	for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {
		m_cut_counter[(*it)] = 0;
		m_cutflow_counter[(*it)] = 0;
	}

	delete xmlparser;

	return success;
}

void xAODEventAccess::SetD3PDEvent(D3PDReader::Event *p_event, D3PDReader::D3PDType p_d3pd_type) {
	m_event = p_event;
	m_d3pd_type = p_d3pd_type;
}

void xAODEventAccess::PrintSummary() {

	std::cout << "[xAODEventAccess] INFO : ****************************************************************" << std::endl;
	std::cout << "[xAODEventAccess] INFO : Summary for selection " << m_name << ":" << std::endl;
	std::cout << "[xAODEventAccess] INFO : Pass function called " << m_pass_calls << " times." << std::endl;
	std::cout << "[xAODEventAccess] INFO : Total pass = " << m_pass << std::endl;
	std::cout << "[xAODEventAccess] INFO : Total fail = " << m_fail << std::endl;

	std::cout << "[xAODEventAccess] INFO : Cut Flow:" << std::endl;
	for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {
		std::cout << "[xAODEventAccess] INFO : \t" << *it << " = " << m_cutflow_counter[*it] << std::endl;
	}

	std::cout << "[xAODEventAccess] INFO : Cut Counters:" << std::endl;
	for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {
		std::cout << "[xAODEventAccess] INFO : \t" << *it << " = " << m_cut_counter[*it] << std::endl;
	}

	std::cout << "[xAODEventAccess] INFO : ****************************************************************" << std::endl;

}

void xAODEventAccess::AddCut(TXMLNode *cut_node) {

	// Get cut name
	TString cut_name = GetNodeAttribute(cut_node, "name");
	if (cut_name == "") {
		std::cerr << "[xAODEventAccess] ERROR : Cut specified without a name attribute. Exiting." << std::endl;
		exit(1);
	}
	cut_list.push_back(cut_name);
	m_cut_counter[cut_name] = 0;
	m_cutflow_counter[cut_name] = 0;

	// Parse cut parameters and descriptor
	TXMLNode *cutparameter_elem = cut_node->GetChildren();
	while (cutparameter_elem != 0) {
		if (cutparameter_elem->GetNodeName() == TString("parameter")) {
			Double_t c_parameter;
			std::stringstream ss;
			if (cutparameter_elem->GetText() != 0) {
				ss.str(cutparameter_elem->GetText());
			} else {
				std::cerr << "[xAODEventAccess] ERROR : Cut " << cut_name << " has a null parameter. Please fix the configuration file." << std::endl;
				exit(1);
			}
			try {
				ss >> c_parameter;
			} catch (const char *) {
				std::cerr << "[xAODEventAccess] ERROR : Couldn't parse cut " << cut_name << " / cut parameter " << ss << std::endl;
				exit(1);
			}
			cut_parameters[cut_name].push_back(c_parameter);
		} else if (cutparameter_elem->GetNodeName() == TString("descriptor")) {
			cut_descriptors[cut_name].push_back(TString(cutparameter_elem->GetText()));
		}
		cutparameter_elem = cutparameter_elem->GetNextNode();
	}

}

void xAODEventAccess::SaveHistograms(EL::Worker *wk) {

	Int_t n_cuts = cut_list.size();
	h_cutflow_counter = new TH1D("CutFlowCounter_" + m_name, "Cutflow for selection " + m_name, n_cuts + 2, -0.5, n_cuts + 2.5);
	h_cutflow_counter->GetXaxis()->SetTitle("Cut Name");
	h_cutflow_counter->GetYaxis()->SetTitle("Electrons Remaining");
	h_cut_counter = new TH1D("CutCounter_" + m_name, "Cut Counter for selection " + m_name, n_cuts + 2, -0.5, n_cuts + 2.5);
	h_cut_counter->GetXaxis()->SetTitle("Cut Name");
	h_cut_counter->GetYaxis()->SetTitle("Electrons Failed");

	wk->addOutput(h_cutflow_counter);
	wk->addOutput(h_cut_counter);

	// Does this work?
	Int_t electrons_remaining = m_pass_calls;
	int bin = 1;
	for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {

		electrons_remaining = electrons_remaining - m_cutflow_counter[*it];

		h_cutflow_counter->SetBinContent(bin, electrons_remaining);
		h_cut_counter->SetBinContent(bin, m_cut_counter[*it]);

		h_cutflow_counter->GetXaxis()->SetBinLabel(bin, *it);
		h_cut_counter->GetXaxis()->SetBinLabel(bin, *it);

		bin++;
	}
}

bool xAODEventAccess::CutIsConfigured(TString p_name) {
	configured = false;
	for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {
		if ((*it) == p_name) {
			configured = true;
			break;
		}
	}
	return configured;
}

std::vector<Double_t>* xAODEventAccess::GetCutParameters(TString p_name) {
	if (CutIsConfigured(p_name)) {
		return &cut_parameters[p_name];
	} else {
		return 0x0;
	}
}

std::vector<TString>* xAODEventAccess::GetCutDescriptors(TString p_name) {
	if (CutIsConfigured(p_name)) {
		return &cut_descriptors[p_name];
	} else {
		return 0x0;
	}

}

TString xAODEventAccess::GetName() {
	return m_name;
}

TString xAODEventAccess::GetType() {
	return m_type;
}

TString xAODEventAccess::GetAuthor() {
	return m_author;
}

void xAODEventAccess::SetDataOrigin(Bool_t p_is_mc) {
	m_is_mc = p_is_mc;
}

D3PDReader::D3PDType xAODEventAccess::GetD3PDType() {
	return m_d3pd_type;
}

void xAODEventAccess::PrintCurrentCutResults() {
	std::cout << "[xAODEventAccess] INFO : Printing current cut results" << std::endl;
	for (std::map<TString, Bool_t>::iterator it = m_this_event_cut_results.begin(); it != m_this_event_cut_results.end(); ++it) {
		std::cout << "[xAODEventAccess] INFO : \t" << (*it).first << " = " << ((*it).second ? "true" : "false") << std::endl;
	}
}


#endif

