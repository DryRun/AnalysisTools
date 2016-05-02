#ifndef EventSelector_cc
#define EventSelector_cc

#include "MyTools/AnalysisTools/interface/EventSelector.h"

EventSelector::EventSelector() {}

EventSelector::~EventSelector() {}

void EventSelector::Configure() {
	cut_functions_["VertexMinTracks"] = &EventCutFunctions::VertexMinTracks;
	cut_functions_["VertexMinNdof"]   = &EventCutFunctions::VertexMinNdof;
	cut_functions_["VertexMaxAbsZ"]   = &EventCutFunctions::VertexMaxAbsZ;
	cut_functions_["VertexMaxRho"]    = &EventCutFunctions::VertexMaxRho;
	cut_functions_["ExactNJets"]      = &EventCutFunctions::ExactNJets;
	cut_functions_["MinNJets"]        = &EventCutFunctions::MinNJets;
	cut_functions_["MaxNJets"]        = &EventCutFunctions::MaxNJets;

	SetName("DefaultEventSelection");
	SetObjectName("Event");
}

void EventSelector::RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters) {
	if (cut_functions_.find(p_cut_name) == cut_functions_.end()) {
		std::cerr << "[EventSelector] ERROR : Unknown cut " << p_cut_name << ". Please add it to the index in EventSelector::Configure()." << std::endl;
		exit(1);
	}
	Cutflow::RegisterCut(p_cut_name, p_cut_descriptors, p_cut_parameters);
}

void EventSelector::ProcessEvent(const edm::Event* p_event, edm::Handle<std::vector<reco::Vertex> >* p_vertices) {
	Reset();
	event_ = p_event;
	vertices_ = p_vertices;
	++pass_calls_;
	bool this_pass = true;
	for (auto & it_cut : cut_list_) {
		if (!cut_functions_[it_cut](event_, this)) {
			if (this_pass) {
				this_pass = false;
				cutflow_counter_[it_cut]++;
			}
			cut_counter_[it_cut]++;
		}
		if (this_pass) {
			pass_counter_[it_cut]++;
		}
	}
	event_good_ = this_pass;
}

void EventSelector::Reset() {
	event_ = 0;
	vertices_ = 0;
	cut_return_data_.clear();
}

#endif