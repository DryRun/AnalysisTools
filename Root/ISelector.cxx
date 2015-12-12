#ifndef Selector_cxx
#define Selector_cxx

#include "Selectors/ISelector.h"
#include <iostream>
#include <iomanip>
#include <cmath>

ISelector::ISelector() {
	configured_ = false;
	data_ = 0;
	debug_counter_ = 0;
	h_cutflow_counter_ = 0;
	h_cut_counter_ = 0;
}

ISelector::~ISelector() {
	if (h_cutflow_counter_) delete h_cutflow_counter_;
	if (h_cut_counter_) delete h_cut_counter_;
}

void ISelector::GetConfigurationMetadata(TDOMParser *p_xml) {
	TXMLDocument* xmldoc = p_xml->GetXMLDocument();
	TXMLNode* sel_node = xmldoc->GetRootNode();
	TXMLNode* sel_elem = sel_node->GetChildren();
	while (sel_elem != 0) {

		// Metadata
		if (sel_elem->GetNodeName() == TString("author")) {
			author_ = sel_elem->GetText();
		} else if (sel_elem->GetNodeName() == TString("name")) {
			name_ = sel_elem->GetText();
		} else if (sel_elem->GetNodeName() == TString("type")) {
			type_ = sel_elem->GetText();
		} else if (sel_elem->GetNodeName() == TString("collection")) {
			collection_name_ = sel_elem->GetText();
		}
		// Next top-level node
		sel_elem = sel_elem->GetNextNode();
	}
}

void ISelector::GetConfigurationCuts(TDOMParser *p_xml) {
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
			std::cout << "[Selector] DEBUG : Loading an include file from " << subconfig_path << std::endl;
			subxmlparser->ParseFile(subconfig_path);
			GetConfigurationCuts(subxmlparser);
		} // Next top-level node
		sel_elem = sel_elem->GetNextNode();
	}
}

bool ISelector::LoadConfiguration(TString config_path, bool verbose) {
	std::cout << "[Selector] INFO : Reading selection configuration from " << config_path << std::endl;
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
	configured_ = success;
	if (success && verbose) {
		std::cout << "[Selector] INFO : Read in selection: " << std::endl;
		if (author_) std::cout << "[Selector] INFO : \tAuthor = " << author_ << std::endl;
		if (name_) std::cout << "[Selector] INFO : \tName = " << name_ << std::endl;
		std::cout << "[Selector] INFO : Cuts:" << std::endl;
		for (std::vector<TString>::iterator it = cut_list_.begin(); it != cut_list_.end(); ++it) {
			std::cout << "[Selector] \tParameters:" << *it << std::endl;
			for (std::vector<Double_t>::iterator par = cut_parameters_[*it].begin(); par != cut_parameters_[*it].end(); ++par) {
				std::cout << "[Selector] \t\t" << *par << std::endl;
			}
			std::cout << "[Selector] \t\tDescriptors:" << *it << std::endl;
			for (std::vector<TString>::iterator desc= cut_descriptors_[*it].begin(); desc!= cut_descriptors_[*it].end(); ++desc) {
				std::cout << "[Selector] \t\t" << *desc<< std::endl;
			}
		}
	}
	// Initialize cut counters
	pass_calls_ = 0;
	//m_cut_counter["pass"] = 0;
	//m_cut_counter["fail"] = 0;
	pass_ = 0;
	fail_ = 0;


	for (std::vector<TString>::iterator it = cut_list_.begin(); it != cut_list_.end(); ++it) {
		cut_counter_[(*it)] = 0;
		cutflow_counter_[(*it)] = 0;
	}

	delete xmlparser;

	return success;
}

void ISelector::PrintSummary() {

	std::cout << "[Selector] INFO : ****************************************************************" << std::endl;
	std::cout << "[Selector] INFO : Summary for selection " << name_ << ":" << std::endl;
	std::cout << "[Selector] INFO : Pass function called " << pass_calls_ << " times." << std::endl;
	std::cout << "[Selector] INFO : Total pass = " << pass_ << std::endl;
	std::cout << "[Selector] INFO : Total fail = " << fail_ << std::endl;

	std::cout << "[Selector] INFO : Cut Flow:" << std::endl;
	for (std::vector<TString>::iterator it = cut_list_.begin(); it != cut_list_.end(); ++it) {
		std::cout << "[Selector] INFO : \t" << *it << " = " << cutflow_counter_[*it] << std::endl;
	}

	std::cout << "[Selector] INFO : Cut Counters:" << std::endl;
	for (std::vector<TString>::iterator it = cut_list_.begin(); it != cut_list_.end(); ++it) {
		std::cout << "[Selector] INFO : \t" << *it << " = " << cut_counter_[*it] << std::endl;
	}

	std::cout << "[Selector] INFO : ****************************************************************" << std::endl;

}

void ISelector::AddCut(TXMLNode *cut_node) {

	// Get cut name
	TString cut_name = GetNodeAttribute(cut_node, "name");
	if (cut_name == "") {
		std::cerr << "[Selector] ERROR : Cut specified without a name attribute. Exiting." << std::endl;
		exit(1);
	}
	cut_list_.push_back(cut_name);
	cut_counter_[cut_name] = 0;
	cutflow_counter_[cut_name] = 0;

	// Parse cut parameters and descriptor
	TXMLNode *cutparameter_elem = cut_node->GetChildren();
	while (cutparameter_elem != 0) {
		if (cutparameter_elem->GetNodeName() == TString("parameter")) {
			Double_t c_parameter;
			std::stringstream ss;
			if (cutparameter_elem->GetText() != 0) {
				ss.str(cutparameter_elem->GetText());
			} else {
				std::cerr << "[Selector] ERROR : Cut " << cut_name << " has a null parameter. Please fix the configuration file." << std::endl;
				exit(1);
			}
			try {
				ss >> c_parameter;
			} catch (const char *) {
				std::cerr << "[Selector] ERROR : Couldn't parse cut " << cut_name << " / cut parameter " << ss << std::endl;
				exit(1);
			}
			cut_parameters_[cut_name].push_back(c_parameter);
		} else if (cutparameter_elem->GetNodeName() == TString("descriptor")) {
			cut_descriptors_[cut_name].push_back(TString(cutparameter_elem->GetText()));
		}
		cutparameter_elem = cutparameter_elem->GetNextNode();
	}

}

void ISelector::SaveHistograms(EL::Worker *wk) {

	Int_t n_cuts = cut_list_.size();
	h_cutflow_counter_ = new TH1D("CutFlowCounter_" + name_, "Cutflow for selection " + name_, n_cuts + 2, -0.5, n_cuts + 2.5);
	h_cutflow_counter_->GetXaxis()->SetTitle("Cut Name");
	h_cutflow_counter_->GetYaxis()->SetTitle("Electrons Remaining");
	h_cut_counter_ = new TH1D("CutCounter_" + name_, "Cut Counter for selection " + name_, n_cuts + 2, -0.5, n_cuts + 2.5);
	h_cut_counter_->GetXaxis()->SetTitle("Cut Name");
	h_cut_counter_->GetYaxis()->SetTitle("Electrons Failed");

	wk->addOutput(h_cutflow_counter_);
	wk->addOutput(h_cut_counter_);

	// Does this work?
	Int_t objects_remaining = pass_calls_;
	int bin = 1;
	for (std::vector<TString>::iterator it = cut_list_.begin(); it != cut_list_.end(); ++it) {

		objects_remaining = objects_remaining - cutflow_counter_[*it];

		h_cutflow_counter_->SetBinContent(bin, objects_remaining);
		h_cut_counter_->SetBinContent(bin, cut_counter_[*it]);

		h_cutflow_counter_->GetXaxis()->SetBinLabel(bin, *it);
		h_cut_counter_->GetXaxis()->SetBinLabel(bin, *it);

		bin++;
	}
}

bool ISelector::CutIsConfigured(TString p_name) {
	bool cut_is_configured = false;
	for (std::vector<TString>::iterator it = cut_list_.begin(); it != cut_list_.end(); ++it) {
		if ((*it) == p_name) {
			cut_is_configured = true;
			break;
		}
	}
	return cut_is_configured;
}

std::vector<Double_t>* ISelector::GetCutParameters(TString p_name) {
	if (CutIsConfigured(p_name)) {
		return &cut_parameters_[p_name];
	} else {
		return 0x0;
	}
}

std::vector<TString>* ISelector::GetCutDescriptors(TString p_name) {
	if (CutIsConfigured(p_name)) {
		return &cut_descriptors_[p_name];
	} else {
		return 0x0;
	}

}

void ISelector::PrintCurrentCutResults() {
	std::cout << "[Selector] INFO : Printing current cut results" << std::endl;
	for (std::map<TString, Bool_t>::iterator it = this_event_cut_results_.begin(); it != this_event_cut_results_.end(); ++it) {
		std::cout << "[Selector] INFO : \t" << (*it).first << " = " << ((*it).second ? "true" : "false") << std::endl;
	}
}


#endif

