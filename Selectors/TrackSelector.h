#ifndef TrackSelector_h
#define TrackSelector_h

#include <TSystem.h>
#include <TPython.h>

#include "xAODTracking/TrackMeasurementValidationContainer.h"
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/TrackParticlexAODHelpers.h"

#include "Selectors/IObjectSelector.h"
#include "Selectors/TrackCutFunctions.h"

class TrackSelector : public IObjectSelector {

	/*** Public Methods ***/
public:
	TrackSelector();
	~TrackSelector();

	void SetNewEvent();

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
	xAOD::TrackParticleContainer* GetTrackCollection();

	/*** Public Members ***/
public:
	const xAOD::TrackParticleContainer * tracks_; //!
	const xAOD::TruthParticleContainer * truth_particles_; //!
	const xAOD::TruthVertexContainer * truth_vertices_; //!
	const xAOD::TruthEventContainer * truth_events_; //!
	const xAOD::TruthPileupEventContainer * truth_pileup_events_; //!

	ClassDef(TrackSelector, 1);

private:
	int debug_counter;

};




#endif