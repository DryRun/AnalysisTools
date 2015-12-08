#include "Selectors/TrackSelector.h"
#define MAX_DEBUG 100

ClassImp(TrackSelector);

TrackSelector::TrackSelector() : ObjectSelector() {
	m_object_name = ObjectSelector::kElectron;

	// Make index of cut functions
	cut_functions["tight++_flag"]                   = &ElectronCutFunctions::ApplyTightPlusPlusFlag;
	cut_functions["medium++_flag"]                  = &ElectronCutFunctions::ApplyMediumPlusPlusFlag;
	cut_functions["loose++_flag"]                   = &ElectronCutFunctions::ApplyLoosePlusPlusFlag;
	cut_functions["tight++"]                        = &ElectronCutFunctions::ApplyTightPlusPlus;
	cut_functions["medium++"]                       = &ElectronCutFunctions::ApplyMediumPlusPlus;
	cut_functions["loose++"]                        = &ElectronCutFunctions::ApplyLoosePlusPlus;
	#ifdef USE_SMWZD3PD
	cut_functions["multilepton++"]                  = &ElectronCutFunctions::ApplyMultileptonPlusPlus;
	#endif
	cut_functions["failtight++_flag"]               = &ElectronCutFunctions::ApplyFailTightPlusPlusFlag;
	cut_functions["failmedium++_flag"]              = &ElectronCutFunctions::ApplyFailMediumPlusPlusFlag;
	cut_functions["failloose++_flag"]               = &ElectronCutFunctions::ApplyFailLoosePlusPlusFlag;
	cut_functions["failtight++"]                    = &ElectronCutFunctions::ApplyFailTightPlusPlus;
	cut_functions["failmedium++"]                   = &ElectronCutFunctions::ApplyFailMediumPlusPlus;
	cut_functions["failloose++"]                    = &ElectronCutFunctions::ApplyFailLoosePlusPlus;
	#ifdef USE_SMWZD3PD
	cut_functions["failmultilepton++"]              = &ElectronCutFunctions::ApplyFailMultileptonPlusPlus;
	#endif
	cut_functions["max_eta"]                        = &ElectronCutFunctions::ApplyMaxEta;
	cut_functions["max_cl_eta"]                     = &ElectronCutFunctions::ApplyMaxClusterEta;
	cut_functions["max_d0sig"]                      = &ElectronCutFunctions::ApplyMaxD0Significance;
	cut_functions["max_z0sig"]                      = &ElectronCutFunctions::ApplyMaxZ0Significance;
	cut_functions["min_d0sig"]                      = &ElectronCutFunctions::ApplyMinD0Significance;
	cut_functions["min_z0sig"]                      = &ElectronCutFunctions::ApplyMinZ0Significance;
	cut_functions["min_pt"]                         = &ElectronCutFunctions::ApplyMinPt;
	cut_functions["min_et"]                         = &ElectronCutFunctions::ApplyMinEt;
	cut_functions["exclude_crack"]                  = &ElectronCutFunctions::ApplyExcludeCrack;
	cut_functions["z0sintheta"]                     = &ElectronCutFunctions::ApplyZ0SinTheta;
	cut_functions["TopoETCone30Fraction"]           = &ElectronCutFunctions::ApplyTopoEtcone30Fraction;
	cut_functions["Etcone30fraction"]               = &ElectronCutFunctions::ApplyEtcone30Fraction;
	cut_functions["ptcone20fraction"]               = &ElectronCutFunctions::ApplyPtcone20Fraction;
	cut_functions["ptcone30fraction"]               = &ElectronCutFunctions::ApplyPtcone30Fraction;
	cut_functions["failEtcone30fraction"]           = &ElectronCutFunctions::ApplyFailEtcone30Fraction;
	cut_functions["failTopoEtcone30fraction"]       = &ElectronCutFunctions::ApplyFailTopoEtcone30Fraction;
	cut_functions["failptcone30fraction"]           = &ElectronCutFunctions::ApplyFailPtcone30Fraction;
	cut_functions["SlidingIsolation"]               = &ElectronCutFunctions::SlidingIsolation;
	cut_functions["SlidingEtcone20"]                = &ElectronCutFunctions::ApplySlidingEtcone20;
	cut_functions["SlidingTopoEtcone20"]            = &ElectronCutFunctions::ApplySlidingTopoEtcone20;
	cut_functions["SlidingEtcone30"]                = &ElectronCutFunctions::ApplySlidingEtcone30;
	cut_functions["SlidingTopoEtcone30"]            = &ElectronCutFunctions::ApplySlidingTopoEtcone30;
	cut_functions["author"]                         = &ElectronCutFunctions::ApplyAuthor;
	cut_functions["GoodObjectQuality"]              = &ElectronCutFunctions::RequireGoodObjectQuality;
	cut_functions["JetSeparation"]                  = &ElectronCutFunctions::ApplyJetSeparation;
	cut_functions["min_si_hits"]                    = &ElectronCutFunctions::ApplyMinSiHits;
	cut_functions["min_pix_hits"]                   = &ElectronCutFunctions::ApplyMinPixHits;
	cut_functions["bl_hit"]                         = &ElectronCutFunctions::ApplyBLHit;
	cut_functions["MaxDeltaEta"]                    = &ElectronCutFunctions::MaxDeltaEta;
	cut_functions["DeltaPhi2Window"]                = &ElectronCutFunctions::DeltaPhi2Window;
	cut_functions["PassDeltaEtaTight"]              = &ElectronCutFunctions::PassDeltaEtaTight;
	cut_functions["PassDeltaPhiTight"]              = &ElectronCutFunctions::PassDeltaPhiTight;
	cut_functions["PassTriggerDeltaEtaTight"]       = &ElectronCutFunctions::PassTriggerDeltaEtaTight;
	cut_functions["PassTriggerDeltaPhiTight"]       = &ElectronCutFunctions::PassTriggerDeltaPhiTight;
	cut_functions["PromptTruth"]                    = &ElectronCutFunctions::ApplyPromptTruthRequirement;
	cut_functions["HeavyFlavorTruth"]               = &ElectronCutFunctions::ApplyHeavyFlavorTruthRequirement;
	cut_functions["LightFlavorTruth"]               = &ElectronCutFunctions::ApplyLightFlavorTruthRequirement;
	cut_functions["BottomTruth"]                    = &ElectronCutFunctions::ApplyBottomTruthRequirement;
	cut_functions["CharmTruth"]                     = &ElectronCutFunctions::ApplyCharmTruthRequirement;
	cut_functions["StrangeTruth"]                   = &ElectronCutFunctions::ApplyStrangeTruthRequirement;
	cut_functions["LightTruth"]                     = &ElectronCutFunctions::ApplyUpDownTruthRequirement;
	cut_functions["ConversionTruth"]                = &ElectronCutFunctions::ApplyConversionTruthRequirement;
	cut_functions["EMProcessTruth"]                 = &ElectronCutFunctions::ApplyEMProcessRequirement;
	cut_functions["OtherHadronTruth"]               = &ElectronCutFunctions::ApplyOtherHadronRequirement;
	#ifdef REMOVED_013113
	cut_functions["TriggerMatch"]                   = &ElectronCutFunctions::TriggerMatch;
	cut_functions["TriggerMatchThreshold"]          = &ElectronCutFunctions::TriggerMatchThreshold;
	cut_functions["TriggerMatchThresholdRelaxed"]   = &ElectronCutFunctions::TriggerMatchThresholdRelaxed;
	cut_functions["TriggerMatch_EF_e24vhi_medium1"] = &ElectronCutFunctions::TriggerMatch_EF_e24vhi_medium1;
	#endif
	cut_functions["InvertTightORIsolation"]         = &ElectronCutFunctions::InvertTightORIsolation;
	cut_functions["InvertMediumFlagXORd0sig"]       = &ElectronCutFunctions::InvertMediumFlagXORd0sig;
	cut_functions["InvertMediumXORd0sig"]           = &ElectronCutFunctions::InvertMediumXORd0sig;
	cut_functions["RequireEventTrigger"]            = &ElectronCutFunctions::ApplyEventTrigger;
	cut_functions["RequireMatchedTrigger"]          = &ElectronCutFunctions::ApplyMatchedTrigger;
	cut_functions["Match2012MediumTrigger"]         = &ElectronCutFunctions::Match2012MediumTrigger;
	cut_functions["Match2012LooseTrigger"]          = &ElectronCutFunctions::Match2012LooseTrigger;
	cut_functions["Match2012LooseTriggerAlternate"] = &ElectronCutFunctions::Match2012LooseTriggerAlternate;
	cut_functions["Match2012MCMediumTrigger"]       = &ElectronCutFunctions::Match2012MCMediumTrigger;
	cut_functions["Match2012MCLooseTrigger"]        = &ElectronCutFunctions::Match2012MCLooseTrigger;
	cut_functions["DebugMediumTriggers"]            = &ElectronCutFunctions::DebugMediumTriggers;
	cut_functions["MaxMT"]                          = &ElectronCutFunctions::MaxMT;
	cut_functions["MaxMET"]                         = &ElectronCutFunctions::MaxMET;
	cut_functions["VetoZDecays"]                    = &ElectronCutFunctions::VetoZDecays;
	cut_functions["RequireTruthMatch"]              = &ElectronCutFunctions::RequireTruthMatch;
	cut_functions["RequirePhotonTruthMatch"]        = &ElectronCutFunctions::RequirePhotonTruthMatch;
	cut_functions["Fail"]                           = &ElectronCutFunctions::Fail;
	// Set configured flags to false
	for (std::map<TString, ElectronCutFunction>::iterator it = cut_functions.begin(); it != cut_functions.end(); ++it) {
		configured_cuts[(*it).first] = false;
	}

	m_debug_medium_triggers = false;
	m_good_jet_list = 0;

	#ifdef DEBUG_TrackSelector
	debug_counter = 0;
	#endif

}

TrackSelector::~TrackSelector() {


}

void TrackSelector::SetDataOrigin(Bool_t p_is_mc, TString p_mc_type) {
	Selector::SetDataOrigin(p_is_mc);

	// If running over MC, set up the SF tools.
	if (p_is_mc) {
		std::vector<TString> m_el_SF_categories;
		m_el_SF_categories.push_back("reco");
		m_el_SF_categories.push_back("ID_tightpp");
		m_el_SF_categories.push_back("ID_mediumpp");
		m_el_SF_categories.push_back("ID_loosepp");
		m_el_SF_categories.push_back("trig_e24e60med_loosepp");
		m_el_SF_categories.push_back("trig_e24e60med_mediumpp");
		m_el_SF_categories.push_back("trig_e24e60med_tightpp");

		std::map<TString, TString> m_el_SF_files;
		m_el_SF_files["reco"] = "$ROOTCOREDIR/data/ElectronEfficiencyCorrection/efficiencySF.offline.RecoTrk.2012.8TeV.rel17p2.v02.root";
		m_el_SF_files["ID_tightpp"] = "$ROOTCOREDIR/data/ElectronEfficiencyCorrection/efficiencySF.offline.Tight.2012.8TeV.rel17p2.v02.root";
		m_el_SF_files["ID_mediumpp"] = "$ROOTCOREDIR/data/ElectronEfficiencyCorrection/efficiencySF.offline.Medium.2012.8TeV.rel17p2.v02.root";
		m_el_SF_files["ID_loosepp"] = "$ROOTCOREDIR/data/ElectronEfficiencyCorrection/efficiencySF.offline.Loose.2012.8TeV.rel17p2.v02.root";
		m_el_SF_files["trig_e24e60med_loosepp"] = "$ROOTCOREDIR/data/ElectronEfficiencyCorrection/efficiencySF.e24vhi_medium1_e60_medium1.Tight.2012.8TeV.rel17p2.v02.root";
		m_el_SF_files["trig_e24e60med_mediumpp"] = "$ROOTCOREDIR/data/ElectronEfficiencyCorrection/efficiencySF.e24vhi_medium1_e60_medium1.Medium.2012.8TeV.rel17p2.v02.root";
		m_el_SF_files["trig_e24e60med_tightpp"] = "$ROOTCOREDIR/data/ElectronEfficiencyCorrection/efficiencySF.e24vhi_medium1_e60_medium1.Loose.2012.8TeV.rel17p2.v02.root";

		for (std::vector<TString>::iterator it = m_el_SF_categories.begin(); it != m_el_SF_categories.end(); ++it) {
			m_el_SF_tool[(*it)] = new Root::TElectronEfficiencyCorrectionTool();
			gSystem->ExpandPathName(m_el_SF_files[(*it)]);
			m_el_SF_tool[(*it)]->addFileName(m_el_SF_files[(*it)].Data());
			m_el_SF_tool[(*it)]->initialize();
		}

		m_pileup_reweighting_tool = new Root::TPileupReweighting();
		TString pileup_reweighting_config_file = "$ROOTCOREDIR/data/PileupReweighting/mc12a_defaults.prw.root";
		gSystem->ExpandPathName(pileup_reweighting_config_file);
		m_pileup_reweighting_tool->AddConfigFile(pileup_reweighting_config_file.Data());
		TString ilumicalc_file = "$ROOTCOREDIR/data/PileupReweighting/ilumicalc_histograms_None_200842-215643.root";
		gSystem->ExpandPathName(ilumicalc_file);
		m_pileup_reweighting_tool->AddLumiCalcFile(ilumicalc_file.Data());
		m_pileup_reweighting_tool->Initialize();

		if (p_mc_type.EqualTo("FullSim")) {
			m_ParticleDataType = PATCore::ParticleDataType::Full;
		} else if (p_mc_type.EqualTo("Fast") || p_mc_type.EqualTo("FastSim")) {
			m_ParticleDataType = PATCore::ParticleDataType::Fast;
		} else {
			std::cerr << "[TrackSelector] ERROR : In call to TrackSelector::SetDataOrigin, argument 2 must be \"FullSim\" or \"Fast\"" << std::endl;
			exit(1);
		}
	}
}


#ifdef OLD_OVERLAP
void TrackSelector::ClassifyObjects() {
	ObjectSelector::Clear();

	// Run selection on every electron
	for (int i = 0; i < m_event->el.n(); i++) {
		m_el_pass[i] = Pass(i);
		if (m_obj_pass[i]) {
			m_obj_good.push_back(i);
			m_n_good_objects++;
		}
	}
}
#endif

void TrackSelector::ClassifyObjects() {
	if (!m_fresh_event) {
		std::cerr << "[TrackSelector] ERROR : ClassifyObjects() called without calling SetNewEvent() on this event." << std::endl;
		exit(1);
	}
	// Run selection on every electron, skipping the overlapped electrons.
	for (int i = 0; i < m_event->el.n(); i++) {
		// Skip pre-removed electrons
		if (m_use_preselection) {
			if (!(*m_object_preselection)[i]) continue;
		}
		m_obj_pass[i] = Pass(i);
		if (m_obj_pass[i]) {
			m_obj_good.push_back(i);
			m_n_good_objects++;
		}
	}

	m_fresh_event = false;
}


bool TrackSelector::Pass(int i) {
	bool c_pass = true;

	m_pass_calls++;
	for (std::vector<TString>::iterator cut = cut_list.begin(); cut != cut_list.end(); ++cut) {
		#ifdef DEBUG_TrackSelector
		if (debug_counter++ < MAX_DEBUG) {
			std::cout << "[TrackSelector] DEBUG : Applying cut " << *cut << std::endl;
		}
		#endif
		if (!cut_functions[*cut](m_event, this, i, &(cut_parameters[*cut]), &(cut_descriptors[*cut]))) {
			if (c_pass) {
				c_pass = false;
				m_cutflow_counter[*cut]++;
			}
			m_cut_counter[*cut]++;
		}
	}
	
	if (c_pass) {
		m_pass++;
	} else {
		m_fail++;
	}

	if (m_debug_medium_triggers && c_pass) {
		if (m_debug_counter < 100) {
			m_debug_counter++;
			std::cout << std::endl << "[TrackSelector] *** Found electron for medium trigger debugging. ***" << std::endl;
			std::cout << "[TrackSelector] Event Info:" << std::endl;
			std::cout << "[TrackSelector] \tEventNumber = " << m_event->eventinfo.EventNumber() << std::endl;
			std::cout << "[TrackSelector] \tRunNumber = " << m_event->eventinfo.RunNumber() << std::endl;
			std::cout << "[TrackSelector] \tactualIntPerXing = " << m_event->eventinfo.actualIntPerXing() << std::endl;
			std::cout << "[TrackSelector] \taverageIntPerXing = " << m_event->eventinfo.averageIntPerXing() << std::endl;
			std::cout << "[TrackSelector] \tbcid = " << m_event->eventinfo.bcid() << std::endl;
			std::cout << "[TrackSelector] \tcoreError = " << m_event->eventinfo.coreError() << std::endl;
			std::cout << "[TrackSelector] \tcoreFlags = " << m_event->eventinfo.coreFlags() << std::endl;
			std::cout << "[TrackSelector] \tdetmask0 = " << m_event->eventinfo.detmask0() << std::endl;
			std::cout << "[TrackSelector] \tdetmask1 = " << m_event->eventinfo.detmask1() << std::endl;
			std::cout << "[TrackSelector] \tfwdError = " << m_event->eventinfo.fwdError() << std::endl;
			std::cout << "[TrackSelector] \tfwdFlags = " << m_event->eventinfo.fwdFlags() << std::endl;
			std::cout << "[TrackSelector] \tisCalibration = " << m_event->eventinfo.isCalibration() << std::endl;
			std::cout << "[TrackSelector] \tisSimulation = " << m_event->eventinfo.isSimulation() << std::endl;
			std::cout << "[TrackSelector] \tisTestBeam = " << m_event->eventinfo.isTestBeam() << std::endl;
			std::cout << "[TrackSelector] \tlarError = " << m_event->eventinfo.larError() << std::endl;
			std::cout << "[TrackSelector] \tlarFlags = " << m_event->eventinfo.larFlags() << std::endl;
			std::cout << "[TrackSelector] \tlbn = " << m_event->eventinfo.lbn() << std::endl;
			std::cout << "[TrackSelector] \tmuonError = " << m_event->eventinfo.muonError() << std::endl;
			std::cout << "[TrackSelector] \tmuonFlags = " << m_event->eventinfo.muonFlags() << std::endl;
			std::cout << "[TrackSelector] \tpixelError = " << m_event->eventinfo.pixelError() << std::endl;
			std::cout << "[TrackSelector] \tpixelFlags = " << m_event->eventinfo.pixelFlags() << std::endl;
			std::cout << "[TrackSelector] \tsctError = " << m_event->eventinfo.sctError() << std::endl;
			std::cout << "[TrackSelector] \tsctFlags = " << m_event->eventinfo.sctFlags() << std::endl;
			std::cout << "[TrackSelector] \tstreamDecision_Egamma = " << m_event->eventinfo.streamDecision_Egamma() << std::endl;
			std::cout << "[TrackSelector] \tstreamDecision_JetTauEtmiss = " << m_event->eventinfo.streamDecision_JetTauEtmiss() << std::endl;
			std::cout << "[TrackSelector] \tstreamDecision_Muons = " << m_event->eventinfo.streamDecision_Muons() << std::endl;
			std::cout << "[TrackSelector] \ttileError = " << m_event->eventinfo.tileError() << std::endl;
			std::cout << "[TrackSelector] \ttileFlags = " << m_event->eventinfo.tileFlags() << std::endl;
			std::cout << "[TrackSelector] \ttimestamp = " << m_event->eventinfo.timestamp() << std::endl;
			std::cout << "[TrackSelector] \ttimestamp_ns = " << m_event->eventinfo.timestamp_ns() << std::endl;
			std::cout << "[TrackSelector] \ttrtError = " << m_event->eventinfo.trtError() << std::endl;
			std::cout << "[TrackSelector] \ttrtFlags = " << m_event->eventinfo.trtFlags		() << std::endl;
		
			std::cout << "[TrackSelector] Electron Info:" << std::endl;
			std::cout << "[TrackSelector] \tIndex = " << i << std::endl;
			std::cout << "[TrackSelector] \tcl_E = " << m_event->el[i].cl_E() << std::endl;
			std::cout << "[TrackSelector] \tnSiHits = " << m_event->el[i].nSiHits() << std::endl;
			std::cout << "[TrackSelector] \ttracketa = " << m_event->el[i].tracketa() << std::endl;
			std::cout << "[TrackSelector] \tcl_eta = " << m_event->el[i].cl_eta() << std::endl;
			Double_t eta = (m_event->el[i].nSiHits() > 3 ? m_event->el[i].tracketa() : m_event->el[i].cl_eta());
			Double_t pt = (m_event->el[i].cl_E() / cosh(eta));
			std::cout << "[TrackSelector] \tpt = " << pt << std::endl;
			std::cout << "[TrackSelector] \teta = " << eta << std::endl;
			std::cout << "[TrackSelector] \ttopoEtcone20 = " << m_event->el[i].topoEtcone20() / pt << std::endl;
			std::cout << "[TrackSelector] \ttopoEtcone30 = " << m_event->el[i].topoEtcone30() / pt << std::endl;
			std::cout << "[TrackSelector] \ttopoEtcone40 = " << m_event->el[i].topoEtcone40() / pt << std::endl;
			std::cout << "[TrackSelector] \tptcone20 = " << m_event->el[i].ptcone20() / pt<< std::endl;
			std::cout << "[TrackSelector] \tptcone30 = " << m_event->el[i].ptcone30() / pt << std::endl;
			std::cout << "[TrackSelector] \tisEM = " << m_event->el[i].isEM() << std::endl;
			std::cout << "[TrackSelector] \tisEMLoose = " << m_event->el[i].isEMLoose() << std::endl;
			std::cout << "[TrackSelector] \tisEMMedium = " << m_event->el[i].isEMMedium() << std::endl;
			std::cout << "[TrackSelector] \tisEMTight = " << m_event->el[i].isEMTight() << std::endl;
		}
	}

	return c_pass;
}

bool TrackSelector::Pass(int i, TString p_cut_name) {

	if (!configured[p_cut_name]) {
		std::cerr << "[TrackSelector] ERROR : Requested cut " << p_cut_name << " was not configured. Exiting..." << std::endl;
		exit(1);
	}
	bool c_pass = cut_functions[p_cut_name](m_event, this, i, &(cut_parameters[p_cut_name]), &(cut_descriptors[p_cut_name]));
	return c_pass;
}

void TrackSelector::SetNewEvent() {
	ObjectSelector::SetNewEvent(0);
	m_is_conversion_.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_is_conversion_[i] = false;
	}
}

void TrackSelector::SetNewEvent(std::map<Int_t, Bool_t> *p_good_jet_list) {
	m_good_jet_list = p_good_jet_list;
	ObjectSelector::SetNewEvent(0);
	m_is_conversion_.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_is_conversion_[i] = false;
	}
}

void TrackSelector::SetNewEvent(std::map<Int_t, Bool_t> *p_object_preselection, std::map<Int_t, Bool_t> *p_good_jet_list) {
	ObjectSelector::SetNewEvent(p_object_preselection);

	m_trigger_match_results.clear();

	for (int i = 0; i < m_event->el.n(); ++i) {
		m_trigger_match_results[i] = "None";
	}

	m_electron_pid.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_electron_pid[i] = ElectronID_IsEM;
	}

	m_is_conversion_.clear();
	for (int i = 0; i < m_event->el.n(); ++i) {
		m_is_conversion_[i] = false;
	}

	m_good_jet_list = p_good_jet_list;
}

void TrackSelector::SetMatchedTrigger(Int_t p_index, TString p_trigger, Int_t p_ef_index) {
	m_trigger_match_results[p_index] = p_trigger;
	m_trigger_match_index[p_index] = p_ef_index;
}

TString TrackSelector::GetMatchedTrigger(Int_t p_index) {
	if (m_trigger_match_results.find(p_index) == m_trigger_match_results.end()) {
		std::cerr << "[TrackSelector] ERROR : m_trigger_match_results does not contain an entry for index " << p_index << ". Debugging is required :(" << std::endl;
		std::cerr << "[TrackSelector] ERROR : Selector name = " << this->GetName() << std::endl;
		std::cerr << "[TrackSelector] ERROR : Printing m_trigger_match_results:" << std::endl;
		for (std::map<Int_t, TString>::iterator it = m_trigger_match_results.begin(); it != m_trigger_match_results.end(); ++it) {
			std::cerr << "[TrackSelector] ERROR : \tm_trigger_match_results[" << (*it).first << "] = " << (*it).second << std::endl;
		}
		exit(1);
	} else {
		return m_trigger_match_results[p_index];
	}
}

Int_t TrackSelector::GetMatchedTriggerIndex(Int_t p_index) {
	if (m_trigger_match_index.find(p_index) == m_trigger_match_index.end()) {
		std::cerr << "[TrackSelector] ERROR : m_trigger_match_index does not contain an entry for index " << p_index << ". Debugging is required :(" << std::endl;
		std::cerr << "[TrackSelector] ERROR : Selector name = " << this->GetName() << std::endl;
		std::cerr << "[TrackSelector] ERROR : Printing trigger match results:" << std::endl;
		for (std::map<Int_t, TString>::iterator it = m_trigger_match_results.begin(); it != m_trigger_match_results.end(); ++it) {
			std::cerr << "[TrackSelector] ERROR : \tElectron " << (*it).first << " matches to " << (*it).second << " (EF index " << m_trigger_match_index[(*it).first] << ")" << std::endl;
		}
		exit(1);
	} else {
		return m_trigger_match_index[p_index];
	}
}

std::pair<Double_t, Double_t> TrackSelector::GetScaleFactor(Int_t p_index) {
	// Get a random run number from the TPileupReweightingTool
	m_pileup_reweighting_tool->SetRandomSeed(314159 + m_event->eventinfo.mc_channel_number() * 2718 + m_event->eventinfo.EventNumber());
	Int_t c_runnumber = m_pileup_reweighting_tool->GetRandomRunNumber(m_event->eventinfo.RunNumber());
	
	// Reco scale factor: applies to all electrons
	Double_t c_eta = (m_event->el[p_index].nSiHits() > 3 ? m_event->el[p_index].tracketa() : m_event->el[p_index].cl_eta());
	Double_t c_pt = m_event->el[p_index].cl_E() / tanh(c_eta);
	const Root::TResult &c_result_reco = m_el_SF_tool["reco"]->calculate(m_ParticleDataType, c_runnumber, m_event->el[p_index].cl_eta(), c_pt);
	Double_t c_SF_reco = c_result_reco.getScaleFactor();
	Double_t c_dSF_reco = c_result_reco.getTotalUncertainty();

	// ID scale factor: applies to electrons that have an ID requirement. This should be, well, every electron!
	Double_t c_SF_id = 1.;
	Double_t c_dSF_id = 0.;
	if (m_electron_pid[p_index] != ElectronID_IsEM) {
		TString tool_identifier;
		if (m_electron_pid[p_index] == ElectronID_TightPP) {
			tool_identifier = "ID_tightpp";
		} else if (m_electron_pid[p_index] == ElectronID_MediumPP) {
			tool_identifier = "ID_mediumpp";
		} else if (m_electron_pid[p_index] == ElectronID_LoosePP) {
			tool_identifier = "ID_loosepp";
		}
		const Root::TResult &c_result_id = m_el_SF_tool[tool_identifier]->calculate(m_ParticleDataType, c_runnumber, m_event->el[p_index].cl_eta(), c_pt);
		c_SF_id = c_result_id.getScaleFactor();
		c_dSF_id = c_result_id.getTotalUncertainty();
	}

	// Trigger scale factor: applies only if we have requested MC trigger matching with **medium** triggers.
	Double_t c_SF_trigger = 1.;
	Double_t c_dSF_trigger = 0.;
	if (cut_functions.find("Match2012MCMediumTrigger") != cut_functions.end()) {
		// Get the name of the trigger
		TString c_trigger = m_trigger_match_results[p_index];
		// e24vhi_medium1 and e60_medium
		if (c_trigger.EqualTo("EF_e24vhi_medium1") || c_trigger.EqualTo("EF_e60_medium1")) {
			TString tool_identifier;
			if (m_electron_pid[p_index] == ElectronID_TightPP) {
				tool_identifier = "trig_e24e60med_tightpp";
			} else if (m_electron_pid[p_index] == ElectronID_MediumPP) {
				tool_identifier = "trig_e24e60med_mediumpp";
			} else if (m_electron_pid[p_index] == ElectronID_LoosePP) {
				tool_identifier = "trig_e24e60med_loosepp";
			}
			const Root::TResult &c_result_trigger = m_el_SF_tool[tool_identifier]->calculate(m_ParticleDataType, c_runnumber, m_event->el[p_index].cl_eta(), c_pt);
			c_SF_trigger = c_result_trigger.getScaleFactor();
			c_dSF_trigger = c_result_trigger.getTotalUncertainty();
		}
	}

	// Add it all up
	Double_t c_SF_total = c_SF_reco * c_SF_id * c_SF_trigger;
	Double_t c_dSF_total = TMath::Sqrt(TMath::Power(c_dSF_reco, 2) + TMath::Power(c_dSF_id, 2) + TMath::Power(c_dSF_trigger, 2));

	return std::make_pair<Double_t, Double_t>(c_SF_total, c_dSF_total);
}

bool TrackSelector::LoadConfiguration(TString config_path, bool verbose) {
	bool success = Selector::LoadConfiguration(config_path, verbose);
	if (m_collection_name.EqualTo("el")) {
		m_collection = TrackSelector::el;
	} else {
		std::cout << "[TrackSelector] WARNING : No electron collection specified. Using el by default." << std::endl;
		m_collection = TrackSelector::el;
	}
	// Check list of cuts
	for (std::vector<TString>::iterator it = cut_list.begin(); it != cut_list.end(); ++it) {
		if (cut_functions.find(*it) == cut_functions.end()) {
			std::cerr << "[TrackSelector] ERROR : Cut " << *it << " does not match any cut function in the index. Please fix before proceeding." << std::endl;
			exit(1);
		}
	}

	return success;
}

D3PDReader::ElectronD3PDObject* TrackSelector::GetElectronCollection() {
	if (m_collection == TrackSelector::el) {
		return &(m_event->el);
	}
}


