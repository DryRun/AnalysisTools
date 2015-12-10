#ifndef TrackDataAccess_h
#define TrackDataAccess_h

#include <iostream>

#include "xAODTracking/TrackMeasurementValidationContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertex.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthPileupEventContainer.h"
#include "xAODTracking/TrackParticlexAODHelpers.h"

#include "Selectors/DataAccess.h"

class TrackDataAccess : public virtual DataAccess {
	/*** Public Methods ***/
public:
	TrackDataAccess();

	~TrackDataAccess();

	inline void LoadTrackTruth() {
		track_truth_ = true;
	}

	/*** Protected Methods ***/
protected:
	/**
	 * Load a new event
	 */
	void NewEvent();

	/*** Private Methods ***/
private:


	/*** Public Members ***/
public:

	/*** Protected Members ***/
protected:
	const xAOD::TrackParticleContainer * tracks_; //!
	const xAOD::TruthParticleContainer * truth_particles_; //!
	const xAOD::TruthVertexContainer * truth_vertices_; //!
	const xAOD::TruthEventContainer * truth_events_; //!
	const xAOD::TruthPileupEventContainer * truth_pileup_events_; //!

	/*** Private Members ***/
private:
	bool track_truth_; //!


};


#endif