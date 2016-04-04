#include "MyTools/AnalysisTools/interface/ObjectSelector.h"
#include "MyTools/AnalysisTools/interface/JetCutFunctions.h"
#include "MyTools/AnalysisTools/interface/ElectronCutFunctions.h"

template<class T>
ObjectSelector<T>::ObjectSelector() {
	// Declare data consumption
}

template<class T>
ObjectSelector<T>::~ObjectSelector() {}

template <> bool ObjectSelector<pat::Jet>::Configure(std::map<TString, std::vector<TString> > p_cut_descriptors, std::map<TString, std::vector<double> > p_cut_parameters) {
	cut_functions_["MinPt"] = &JetCutFunctions::MinPt;
	return true;
}

template <> bool ObjectSelector<pat::Electron>::Configure(std::map<TString, std::vector<TString> > p_cut_descriptors, std::map<TString, std::vector<double> > p_cut_parameters) {
	cut_functions_["MinPt"] = &ElectronCutFunctions::MinPt;
	return true;
}

template<class T>
void ObjectSelector<T>::ClassifyObjects(edm::Handle<std::vector<T> > p_data) {
	Reset();
	for (unsigned int i = 0; i < p_data->size(); ++i) {
		obj_pass_[i] = Pass(i);
		if (obj_pass_[i]) {
			obj_good_.push_back(i);
		}
	}
}

template<class T>
bool ObjectSelector<T>::Pass(int i) {
	bool this_pass = true;
	for (auto & it_cut : cut_list_) {
		if (!cut_functions_[it_cut](this, i, &(cut_parameters_[it_cut]), &(cut_descriptors_[it_cut]))) {
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
	return this_pass;
}

template<class T>
void ObjectSelector<T>::Reset() {
	obj_pass_.clear();
	obj_good_.clear();
}

template<class T>
void ObjectSelector<T>::RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters) {
	cut_list_.push_back(p_cut_name);
	cut_descriptors_[p_cut_name] = p_cut_descriptors;
	cut_parameters_[p_cut_name] = p_cut_parameters;
}

template class ObjectSelector<pat::Electron>;
template class ObjectSelector<pat::Jet>;