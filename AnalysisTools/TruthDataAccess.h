#ifndef TruthDataAccess_h
#define TruthDataAccess_h

#include <iostream>

#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertex.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthPileupEventContainer.h"

#include "AnalysisTools/DataAccess.h"

class TruthDataAccess : public virtual DataAccess {
	/*** Methods ***/
public:
	TruthDataAccess();

	virtual ~TruthDataAccess();

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
	bool RetrieveTruths();


	/*** Members ***/
protected:
	const xAOD::TruthParticleContainer * truth_particles_; //!
	const xAOD::TruthVertexContainer * truth_vertices_; //!
	const xAOD::TruthEventContainer * truth_events_; //!
	const xAOD::TruthPileupEventContainer * truth_pileup_events_; //!

};


#endif