#ifndef PixelClusterDataAccess_cxx
#define PixelClusterDataAccess_cxx

#include "Selectors/PixelClusterDataAccess.h"

PixelClusterDataAccess::PixelClusterDataAccess() {
	pixel_clusters_ = 0;
}

PixelClusterDataAccess::~PixelClusterDataAccess() {}

bool PixelClusterDataAccess::RetrievePixelClusters() {
	bool success = true;
    if (!event_->retrieve(pixel_clusters_,"PixelClusters").isSuccess()) {
		Error("PixelClusterDataAccess::RetrievePixelClusters()", "Failed to retrieve PixelClusters from xAOD.");
		success = false;
    }
	return success;
}

#endif