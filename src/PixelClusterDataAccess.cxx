#ifndef PixelClusterDataAccess_cxx
#define PixelClusterDataAccess_cxx

#include "AnalysisTools/PixelClusterDataAccess.h"

ClassImp(PixelClusterDataAccess)

PixelClusterDataAccess::PixelClusterDataAccess() {
	pixel_clusters_ = 0;
	ignore_branch_["PixelClusters"] = false;
}

PixelClusterDataAccess::~PixelClusterDataAccess() {}

bool PixelClusterDataAccess::RetrievePixelClusters() {
	bool success = true;
	if (!ignore_branch_["PixelClusters"]) {
		if (!event_->retrieve(pixel_clusters_,"PixelClusters").isSuccess()) {
			Error("PixelClusterDataAccess::RetrievePixelClusters()", "Failed to retrieve PixelClusters from xAOD.");
			success = false;
		}
	}
	return success;
}

#endif