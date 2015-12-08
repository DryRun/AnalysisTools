#ifndef TrackSelector_h
#define TrackSelector_h

#include <TSystem.h>
#include <TPython.h>

#include "Selectors/IObjectSelector.h"
#include "Selectors/TrackCutFunctions.h"
#include "D3PDReader/TrackD3PDObject.h"

class TrackSelector : public IObjectSelector {

	/*** Public Methods ***/
public:
	TrackSelector();
	~TrackSelector();


	void SetTrackSelectorTool(Root::TTrackSelector *p_Track_selector_tool);

	void SetNewEvent();

	void SetNewEvent(std::map<Int_t, Bool_t> *p_good_jet_list);

	void SetNewEvent(std::map<Int_t, Bool_t> *p_object_preselection, std::map<Int_t, Bool_t> *p_good_jet_list);

	/**
	 * Sets the D3PDReader object, then calls Selector::LoadConfiguration.
	 * @param  config_path Path to selector configuration XML file
	 * @param  verbose     Print out configuration once loaded
	 * @return             Successfully parsed input configuration
	 */
	bool LoadConfiguration(TString config_path, bool verbose = false);


	/**
	 * Get the TrackD3PDObject associated with this selector.
	 * @return D3PDReader::TrackD3PDObject*
	 */
	D3PDReader::TrackD3PDObject* GetTrackCollection();

	/*** Public Members ***/
public:
	Root::TTrackSelector *m_Track_selector_tool;

 	std::map<Int_t, Bool_t> *m_good_jet_list; // List of "looser" jets that pass overlap removal and cleaning.

 	TrackCollection m_collection;

	ClassDef(TrackSelector, 1);

private:
	int debug_counter;

};




#endif