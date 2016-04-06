#include "MyTools/AnalysisTools/interface/ObjectSelector.h"
#include "MyTools/AnalysisTools/interface/JetCutFunctions.h"
#include "MyTools/AnalysisTools/interface/ElectronCutFunctions.h"

template<class T>
ObjectSelector<T>::ObjectSelector() {
	object_ = ObjectIdentifiers::kNoObjectName;
}

template<class T>
ObjectSelector<T>::~ObjectSelector() {}

template <> bool ObjectSelector<pat::Jet>::Configure() {
	cut_functions_["MinPt"] = &JetCutFunctions::MinPt;
	cut_functions_["MaxAbsEta"] = &JetCutFunctions::MaxAbsEta;

	object_ = ObjectIdentifiers::kJet;
	SetName("DefaultJetSelection");
	SetObjectName("Jet");
	return true;
}

template <> bool ObjectSelector<pat::Electron>::Configure() {
	cut_functions_["MinPt"] = &ElectronCutFunctions::MinPt;
	object_ = ObjectIdentifiers::kElectron;
	SetName("DefaultElectronSelection");
	SetObjectName("Electron");
	return true;
}

template<class T>
void ObjectSelector<T>::RegisterCut(TString p_cut_name, std::vector<TString> p_cut_descriptors, std::vector<double> p_cut_parameters) {
	if (cut_functions_.find(p_cut_name) == cut_functions_.end()) {
		std::cerr << "[ObjectSelector] ERROR : Unknown cut " << p_cut_name << ". Please add it to the index in the appropriate ObjectSelector<T>::Configure() function." << std::endl;
		exit(1);
	}
	Cutflow::RegisterCut(p_cut_name, p_cut_descriptors, p_cut_parameters);
}


template<class T>
void ObjectSelector<T>::ClassifyObjects(const edm::Handle<std::vector<T> > p_data) {
	Reset();
	data_ = p_data;
	for (unsigned int i = 0; i < p_data->size(); ++i) {
		obj_pass_[i] = Pass(i);
		if (obj_pass_[i]) {
			obj_good_.push_back(i);
		}
	}
}

template<class T>
bool ObjectSelector<T>::Pass(int i) {
	++pass_calls_;
	bool this_pass = true;
	for (auto & it_cut : cut_list_) {
		if (!cut_functions_[it_cut](data_, this, i)) {
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

//template class ObjectSelector<pat::Electron>;
//template class ObjectSelector<pat::Jet>;