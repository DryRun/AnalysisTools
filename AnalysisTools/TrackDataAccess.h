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

	inline const xAOD::TruthParticleContainer* GetTruthParticleContainer() {
		return truth_particles_;
	}

	inline const xAOD::TruthParticleContainer* GetTruthParticleContainer() const {
		return truth_particles_;
	}	

	inline const xAOD::TruthVertexContainer* GetTruthVertexContainer() {
		return truth_vertices_;
	}

	inline const xAOD::TruthVertexContainer* GetTruthVertexContainer() const {
		return truth_vertices_;
	}	

	inline const xAOD::TruthEventContainer* GetTruthEventContainer() {
		return truth_events_;
	}

	inline const xAOD::TruthEventContainer* GetTruthEventContainer() const {
		return truth_events_;
	}	

	inline const xAOD::TruthPileupEventContainer* GetTruthPileupEventContainer() {
		return truth_pileup_events_;
	}

	inline const xAOD::TruthPileupEventContainer* GetTruthPileupEventContainer() const {
		return truth_pileup_events_;
	}	


protected:
	/**
	 * Load a new event
	 */
	bool RetrieveTracks();


	/*** Members ***/
protected:
	const xAOD::TrackParticleContainer * tracks_; //!
	const xAOD::TruthParticleContainer * truth_particles_; //!
	const xAOD::TruthVertexContainer * truth_vertices_; //!
	const xAOD::TruthEventContainer * truth_events_; //!
	const xAOD::TruthPileupEventContainer * truth_pileup_events_; //!

};


#endif