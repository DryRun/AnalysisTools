#ifndef Cutflow_h
#define Cutflow_h

#include <map>
#include <vector>
#include <iostream>

#include "TString.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH1F.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

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

	inline std::vector<double>& GetCutParameters(TString p_cut_name) {
		return cut_parameters_[p_cut_name];
	}

	inline std::vector<TString>& GetCutDescriptors(TString p_cut_name) {
		return cut_descriptors_[p_cut_name];
	}

	/**
	 * Make cutflow histograms and save to TFileService
	 * @param p_fs [description]
	 */
	void MakeCutflowHistograms(TFileService *p_fs);

private:

public:

protected:
	TString name_;
	TString object_name_;

	// Cut information
	std::vector<TString> cut_list_;
	std::map<TString, std::vector<Double_t> > cut_parameters_;
	std::map<TString, std::vector<TString> > cut_descriptors_;

	// Cutflow counter
	unsigned int pass_calls_;
	std::map<TString, unsigned int> cut_counter_; // Lists number of times a given cut is failed. Map is <cut> : <total #fails>. Inclusive.
	std::map<TString, unsigned int> cutflow_counter_; // Cutflow counter. Map is <cut> : <#fails>. Exclusive.
	std::map<TString, unsigned int> pass_counter_; // Counts number of events that pass a given cut. Exclusive.

private:
};

#endif