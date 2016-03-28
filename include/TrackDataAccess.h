#ifndef TrackDataAccess_h
#define TrackDataAccess_h

#include <iostream>

#include "xAODTracking/TrackMeasurementValidationContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/TrackParticlexAODHelpers.h"

#include "AnalysisTools/DataAccess.h"

class TrackDataAccess : public virtual DataAccess {
	/*** Methods ***/
public:
	TrackDataAccess();

	virtual ~TrackDataAccess();

	inline const xAOD::TrackParticleContainer* GetTrackParticleContainer() {
		return tracks_;
	}

	inline const xAOD::TrackParticleContainer* GetTrackParticleContainer() const {
		return tracks_;
	}	


protected:
	/**
	 * Load a new event
	 */
	bool RetrieveTracks();


	/*** Members ***/
protected:
	const xAOD::TrackParticleContainer * tracks_; //!

	ClassDef(TrackDataAccess, 1);
};


#endif