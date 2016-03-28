#ifndef PixelClusterDataAccess_h
#define PixelClusterDataAccess_h

#include <iostream>

#include "xAODTracking/TrackMeasurementValidationContainer.h"

#include "MyTools/AnalysisTools/include/DataAccess.h"

class PixelClusterDataAccess : public virtual DataAccess {
	/*** Methods ***/
public:
	PixelClusterDataAccess();

	virtual ~PixelClusterDataAccess();

	inline const xAOD::TrackMeasurementValidationContainer* GetPixelClusterContainer() {
		return pixel_clusters_;
	}

	inline const xAOD::TrackMeasurementValidationContainer* GetPixelClusterContainer() const {
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

	ClassDef(PixelClusterDataAccess, 1);
};


#endif