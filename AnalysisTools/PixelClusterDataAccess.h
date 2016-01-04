#ifndef PixelClusterDataAccess_h
#define PixelClusterDataAccess_h

#include <iostream>

#include "xAODTracking/TrackMeasurementValidationContainer.h"

#include "AnalysisTools/DataAccess.h"

class PixelClusterDataAccess : public virtual DataAccess {
	/*** Methods ***/
public:
	PixelClusterDataAccess();

	virtual ~PixelClusterDataAccess();

	inline const xAOD::TrackParticleContainer* GetPixelClusterContainer() {
		return pixel_clusters_;
	}

	inline const xAOD::TrackParticleContainer* GetPixelClusterContainer() const {
		return pixel_clusters_;
	}	

protected:
	/**
	 * Load a new event
	 */
	bool RetrievePixelClusters();


	/*** Members ***/
protected:
	const xAOD::TrackMeasurementValidationContainer * pixel_clusters_; //!

};


#endif