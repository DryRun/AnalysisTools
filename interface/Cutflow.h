#ifndef Cutflow_h
#define Cutflow_h

#include <map>
#include <vector>
#include <iostream>

#include "TString.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

/***
 * Class Cutflow
 * - Base class for EventSelector and ObjectSelector
 * - Stores a list of cuts, cut descriptors (string) and parameters(double), and the cut results.
 * - Note that the actual cuts and the incrementing of cut counters is not implemented here! The logic will be different depending on the objects in question (e.g. event or objects per event).
 */
class Cutflow {
public:
	Cutflow();
	~Cutflow();

	/**
	 * Set name of cutflow. This is prefixed to the name of all the saved histograms.
	 * @param p_name [description]
	 */
	inline void SetName(TString p_name) {
		name_ = p_name;
	}

	/**
	 * Name of objects being counted (e.g. electrons, jets, events, etc). This is used for the cutflow histogram labels.
	 * @param p_object_name [description]
	 */
	inline void SetObjectName(TString p_object_name) {
		object_name_ = p_object_name;
	}

	/**
	 * Add a cut.
	 * @param p_cut_name        Name of cut (must match cut in the index)
	 * @param p_cut_descriptors String-based cut details
	 * @param p_cut_parameters  Number-based cut details
	 */
	virtual void RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters);

	/**
	 * Add a N-1 histogram for a cut (note that the cut should be registered with RegisterCut)
	 * @param p_cut_name     Cut name
	 * @param p_x_axis_title X axis title
	 * @param p_nbins        X axis number of bins
	 * @param p_xmin         X axis min
	 * @param p_xmax         X axis max
	 */
	virtual void AddNMinusOneHistogram(TString p_cut_name, TString p_x_axis_title, int p_nbins, double p_xmin, double p_xmax);

	/**
	 * Add a N-1 histogram for a cut (note that the cut should be registered with RegisterCut) vs. another variable
	 * @param p_cut_name     Cut name
	 * @param p_second_var_name Second variable name
	 * @param p_x_axis_title X axis title
	 * @param p_nbins        X axis number of bins
	 * @param p_xmin         X axis min
	 * @param p_xmax         X axis max
	 */
	virtual void AddNMinusOne2DHistogram(TString p_cut_name, TString p_second_var_name, TString p_x_axis_title, int p_nxbins, double p_xmin, double p_xmax, TString p_y_axis_title, int p_nybins, double p_ymin, double p_ymax);

	inline std::vector<double>& GetCutParameters(TString p_cut_name) {
		if (cut_parameters_.find(p_cut_name) == cut_parameters_.end()) {
			std::cerr << "[Cutflow::GetCutParameters] ERROR : Couldn't find parameters for cut " << p_cut_name << std::endl;
			exit(1);
		}
		return cut_parameters_[p_cut_name];
	}

	inline std::vector<TString>& GetCutDescriptors(TString p_cut_name) {
		if (cut_descriptors_.find(p_cut_name) == cut_descriptors_.end()) {
			std::cerr << "[Cutflow::GetCutParameters] ERROR : Couldn't find descriptors for cut " << p_cut_name << std::endl;
			exit(1);
		}
		return cut_descriptors_[p_cut_name];
	}

	inline void SetReturnData(TString p_cut_name, double p_cut_data) {
		return_data_[p_cut_name] = p_cut_data;
	}

	inline double GetReturnData(TString p_cut_name) {
		if (return_data_.find(p_cut_name) == return_data_.end()) {
			std::cerr << "[Cutflow::GetReturnData] ERROR : Cut name not recognized: " << p_cut_name << std::endl;
			exit(1);
		}
		return return_data_[p_cut_name];
	}

	/**
	 * Make cutflow histograms and save to TFileService
	 * @param p_fs [description]
	 */
	void MakeCutflowHistograms(TFileService *p_fs);

	/**
	 * Make cutflow histograms and save to TFile
	 * @param p_fs [description]
	 */
	void MakeCutflowHistograms(TDirectory *p_directory);

	/**
	 * Save N-1 histograms to a TFileService
	 */
	void SaveNMinusOneHistograms(TFileService *p_fs);

	/**
	 * Save N-1 histograms to a TFileService
	 */
	void SaveNMinusOneHistograms(TDirectory *p_directory);

private:

public:

protected:
	TString name_;
	TString object_name_;

	// Cut information
	std::vector<TString> cut_list_;
	std::map<TString, std::vector<Double_t> > cut_parameters_;
	std::map<TString, std::vector<TString> > cut_descriptors_;

	std::map<TString, double> return_data_;
	std::map<TString, TH1D*> histograms_nminusone_; // Container for storing any N-1 histograms if desired
	std::map<TString, std::map<TString, TH2D*> > histograms_nminusone_2D_; // Container for storing any N-1 histograms if desired

	// Cutflow counter
	unsigned int pass_calls_;
	double pass_calls_weighted_;
	std::map<TString, unsigned int> cut_counter_; // Lists number of times a given cut is failed. Map is <cut> : <total #fails>. Inclusive.
	std::map<TString, unsigned int> cutflow_counter_; // Cutflow counter. Map is <cut> : <#fails>. Exclusive.
	std::map<TString, unsigned int> pass_counter_; // Counts number of events that pass a given cut. Exclusive.
	std::map<TString, double> cut_counter_weighted_; // Lists number of times a given cut is failed. Map is <cut> : <total #fails>. Inclusive.
	std::map<TString, double> cutflow_counter_weighted_; // Cutflow counter. Map is <cut> : <#fails>. Exclusive.
	std::map<TString, double> pass_counter_weighted_; // Counts number of events that pass a given cut. Exclusive.


private:
};

inline Cutflow::Cutflow() {
	pass_calls_ = 0;
}

inline Cutflow::~Cutflow() {
	histograms_nminusone_.clear();
	histograms_nminusone_2D_.clear();
}

inline void Cutflow::RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters) {
	cut_list_.push_back(p_cut_name);
	cut_descriptors_[p_cut_name] = p_cut_descriptors;
	cut_parameters_[p_cut_name] = p_cut_parameters;
	std::cout << "[Cutflow::RegisterCut] INFO : Registered cut " << p_cut_name << std::endl;
	std::cout << "[Cutflow::RegisterCut] INFO : \t Cut descriptors: " << std::endl;
	for (auto& it_cut_descriptor : p_cut_descriptors) {
		std::cout << "[Cutflow::RegisterCut] INFO : \t\t" << it_cut_descriptor << std::endl;
	}
	std::cout << "[Cutflow::RegisterCut] INFO : \t Cut parameters: " << std::endl;
	for (auto& it_cut_parameter : p_cut_parameters) {
		std::cout << "[Cutflow::RegisterCut] INFO : \t\t" << it_cut_parameter << std::endl;
	}

}

inline void Cutflow::AddNMinusOneHistogram(TString p_cut_name, TString p_x_axis_title, int p_nbins, double p_xmin, double p_xmax) {
	histograms_nminusone_[p_cut_name] = new TH1D("h_nminusone_" + p_cut_name, "h_nminusone_" + p_cut_name, p_nbins, p_xmin, p_xmax);
	histograms_nminusone_[p_cut_name]->SetDirectory(0);
	histograms_nminusone_[p_cut_name]->Sumw2();
	histograms_nminusone_[p_cut_name]->GetXaxis()->SetTitle(p_x_axis_title);
}

inline void Cutflow::AddNMinusOne2DHistogram(TString p_cut_name, TString p_second_var_name, TString p_x_axis_title, int p_nxbins, double p_xmin, double p_xmax, TString p_y_axis_title, int p_nybins, double p_ymin, double p_ymax) {
	std::cout << "[Cutflow::AddNMinusOne2DHistogram] DEBUG : Adding N-1 2D histogram for " << p_cut_name << " vs " << p_second_var_name << std::endl;
	histograms_nminusone_2D_[p_cut_name][p_second_var_name] = new TH2D("h_nminusone_" + p_cut_name + "_vs_" + p_second_var_name, "h_nminusone_" + p_cut_name + "_vs_" + p_second_var_name, p_nxbins, p_xmin, p_xmax, p_nybins, p_ymin, p_ymax);
	histograms_nminusone_2D_[p_cut_name][p_second_var_name]->SetDirectory(0);
	histograms_nminusone_2D_[p_cut_name][p_second_var_name]->Sumw2();
	histograms_nminusone_2D_[p_cut_name][p_second_var_name]->GetXaxis()->SetTitle(p_x_axis_title);
	histograms_nminusone_2D_[p_cut_name][p_second_var_name]->GetYaxis()->SetTitle(p_y_axis_title);
}


inline void Cutflow::MakeCutflowHistograms(TFileService *p_fs) {
	MakeCutflowHistograms(p_fs->getBareDirectory());
}

inline void Cutflow::MakeCutflowHistograms(TDirectory *p_directory) {
	p_directory->cd();
	Int_t n_cuts = cut_list_.size();
	TH1D* h_cutflow_counter = new TH1D("CutFlowCounter_" + name_, "CutFlowCounter_" + name_, n_cuts + 2, -0.5, n_cuts + 2.5);
	h_cutflow_counter->GetXaxis()->SetTitle("Cut Name");
	if (object_name_ != "") {
		if (object_name_ == "Vertex") {
			h_cutflow_counter->GetYaxis()->SetTitle("Vertices Remaining");
		} else {
			h_cutflow_counter->GetYaxis()->SetTitle(object_name_ + "s Remaining");
		}
	} else {
		h_cutflow_counter->GetYaxis()->SetTitle("Objects Remaining");
	}
	TH1D* h_cutflow_counter_weighted = (TH1D*)h_cutflow_counter->Clone();
	h_cutflow_counter_weighted->SetName(TString(h_cutflow_counter_weighted->GetName()) + "_weighted");

	TH1D* h_cut_counter = new TH1D("CutCounter_" + name_, "CutCounter_" + name_, n_cuts + 2, -0.5, n_cuts + 2.5);
	h_cut_counter->GetXaxis()->SetTitle("Cut Name");
	if (object_name_ != "") {
		if (object_name_ == "Vertex") {
			h_cut_counter->GetYaxis()->SetTitle("Vertices Failing Cut");
		} else {
			h_cut_counter->GetYaxis()->SetTitle(object_name_ + "s Failing Cut");
		}
	} else {
		h_cut_counter->GetYaxis()->SetTitle("Objects Failing Cut");
	}
	TH1D* h_cut_counter_weighted = (TH1D*)h_cut_counter->Clone();
	h_cut_counter_weighted->SetName(TString(h_cut_counter_weighted->GetName()) + "_weighted");

	int bin = 1;
	h_cutflow_counter->SetBinContent(bin, pass_calls_);
	h_cutflow_counter->GetXaxis()->SetBinLabel(bin, "Inclusive");
	h_cut_counter->SetBinContent(bin, pass_calls_);
	h_cut_counter->GetXaxis()->SetBinLabel(bin, "Total");

	h_cutflow_counter_weighted->SetBinContent(bin, pass_calls_weighted_);
	h_cutflow_counter_weighted->GetXaxis()->SetBinLabel(bin, "Inclusive");
	h_cut_counter_weighted->SetBinContent(bin, pass_calls_weighted_);
	h_cut_counter_weighted->GetXaxis()->SetBinLabel(bin, "Total");
	++bin;
	for (std::vector<TString>::iterator it_cut = cut_list_.begin(); it_cut != cut_list_.end(); ++it_cut) {
		h_cutflow_counter->SetBinContent(bin, pass_counter_[*it_cut]);
		h_cutflow_counter->GetXaxis()->SetBinLabel(bin, *it_cut);

		h_cut_counter->SetBinContent(bin, cut_counter_[*it_cut]);
		h_cut_counter->GetXaxis()->SetBinLabel(bin, *it_cut);
		
		h_cutflow_counter_weighted->SetBinContent(bin, pass_counter_weighted_[*it_cut]);
		h_cutflow_counter_weighted->GetXaxis()->SetBinLabel(bin, *it_cut);

		h_cut_counter_weighted->SetBinContent(bin, cut_counter_weighted_[*it_cut]);
		h_cut_counter_weighted->GetXaxis()->SetBinLabel(bin, *it_cut);

		++bin;
	}
	h_cutflow_counter->Write();
	h_cutflow_counter_weighted->Write();
	h_cut_counter->Write();
	h_cut_counter_weighted->Write();
}

inline void Cutflow::SaveNMinusOneHistograms(TFileService *p_fs) {
	SaveNMinusOneHistograms(p_fs->getBareDirectory());
}

inline void Cutflow::SaveNMinusOneHistograms(TDirectory *p_directory) {
	p_directory->cd();

	for (auto& it_cut : cut_list_) {
		if (histograms_nminusone_.find(it_cut) != histograms_nminusone_.end()) {
			histograms_nminusone_[it_cut]->Write();
		}
		if (histograms_nminusone_2D_.find(it_cut) != histograms_nminusone_2D_.end()) {
			for (auto& it_second : histograms_nminusone_2D_[it_cut]) {
				(it_second.second)->Write();
			}
		}
	}
}


#endif