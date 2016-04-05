#ifndef Cutflow_cc
#define Cutflow_cc

#include "MyTools/AnalysisTools/interface/Cutflow.h"

Cutflow::Cutflow() {
	pass_calls_ = 0;
}

Cutflow::~Cutflow() {}

void Cutflow::RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters) {
	cut_list_.push_back(p_cut_name);
	cut_descriptors_[p_cut_name] = p_cut_descriptors;
	cut_parameters_[p_cut_name] = p_cut_parameters;
}

void Cutflow::MakeCutflowHistograms(TFileService *p_fs) {
	Int_t n_cuts = cut_list_.size();
	TH1D* h_cutflow_counter = p_fs->make<TH1D>("CutFlowCounter_" + name_, "CutFlowCounter_" + name_, n_cuts + 2, -0.5, n_cuts + 2.5);
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

	TH1D* h_cut_counter = p_fs->make<TH1D>("CutCounter_" + name_, "CutCounter_" + name_, n_cuts + 2, -0.5, n_cuts + 2.5);
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

	int bin = 1;
	h_cutflow_counter->SetBinContent(bin, pass_calls_);
	h_cutflow_counter->GetXaxis()->SetBinLabel(bin, "Inclusive");
	h_cut_counter->SetBinContent(bin, pass_calls_);
	h_cut_counter->GetXaxis()->SetBinLabel(bin, "Total");
	++bin;
	for (std::vector<TString>::iterator it_cut = cut_list_.begin(); it_cut != cut_list_.end(); ++it_cut) {
		h_cutflow_counter->SetBinContent(bin, pass_counter_[*it_cut]);
		h_cutflow_counter->GetXaxis()->SetBinLabel(bin, *it_cut);

		h_cut_counter->SetBinContent(bin, cut_counter_[*it_cut]);
		h_cut_counter->GetXaxis()->SetBinLabel(bin, *it_cut);

		++bin;
	}

}

#endif