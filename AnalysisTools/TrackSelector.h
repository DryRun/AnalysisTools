#ifndef TrackSelector_h
#define TrackSelector_h

#include <TSystem.h>
#include <TPython.h>

#include "xAODTracking/TrackMeasurementValidationContainer.h"
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/TrackParticlexAODHelpers.h"

#include "AnalysisTools/IObjectSelector.h"
#include "AnalysisTools/TrackCutFunctions.h"
#include "AnalysisTools/TrackDataAccess.h"

class TrackSelector : public IObjectSelector {

	/*** Public Methods ***/
public:
	TrackSelector();
	~TrackSelector();

	/**
	 * Call whenever a new event is set. This clears the last event's results.
	 */
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
	inline const xAOD::TrackParticleContainer* GetTrackCollection() {
		return tracks_;
	}
	inline const xAOD::TrackParticleContainer* GetTrackCollection() const {
		return tracks_;
	}

	void ClassifyObjects();

	/*** Public Members ***/
public:
	const xAOD::TrackParticleContainer * tracks_; //!

};




#endif