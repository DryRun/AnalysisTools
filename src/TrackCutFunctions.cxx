#ifndef TrackCutFunctions_cxx
#define TrackCutFunctions_cxx

#define DEBUG_MAX 100
#include "MyTools/AnalysisTools/include/TrackCutFunctions.h"

namespace TrackCutFunctions {
	bool MinNPixHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_npixhits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfPixelHits");
		return this_npixhits >= (unsigned char)(p_track_selector->GetCutParameters("MinNPixHits")->at(0));
	}
	bool MinNSCTHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_nscthits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfSCTHits");
		return this_nscthits >= (unsigned char)(p_track_selector->GetCutParameters("MinNSCTHits")->at(0));
	}

	bool MinNSiHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_nsihits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfPixelHits") + dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfSCTHits");
		return this_nsihits >= (unsigned char)(p_track_selector->GetCutParameters("MinNSiHits")->at(0));
	}

	bool MinNPixLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_npixlayerhits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfContribPixelLayers");
		return this_npixlayerhits >= (unsigned char)(p_track_selector->GetCutParameters("MinNPixLayerHits")->at(0));
	}

	bool MinNInnerPixLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_ninnerpixlayerhits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfInnermostPixelLayerHits") + dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfNextToInnermostPixelLayerHits");
		return this_ninnerpixlayerhits >= (unsigned char)(p_track_selector->GetCutParameters("MinNInnerPixLayerHits")->at(0));
	}

	bool MinNOuterPixLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_ninnerpixlayerhits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfInnermostPixelLayerHits") + dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfNextToInnermostPixelLayerHits");
		unsigned char this_npixlayerhits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfContribPixelLayers");
		unsigned char this_nouterpixlayerhits = this_npixlayerhits - this_ninnerpixlayerhits;
		return this_nouterpixlayerhits >= (unsigned char)(p_track_selector->GetCutParameters("MinNOuterPixLayerHits")->at(0));
	}

	bool MinNSCTLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_nsctlayerhits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfContribSCTLayers");
		return this_nsctlayerhits >= (unsigned char)(p_track_selector->GetCutParameters("MinNSCTLayerHits")->at(0));
	}

	bool MinNSiLayerHits(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_nsilayerhits = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfContribPixelLayers") + dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfContribSCTLayers");
		return this_nsilayerhits >= (unsigned char)(p_track_selector->GetCutParameters("MinNSiLayerHits")->at(0));
	}

	bool MaxNPixHoles(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_npixholes = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfPixelHoles");
		return this_npixholes <= (unsigned char)(p_track_selector->GetCutParameters("MaxNPixHoles")->at(0));
	}

	bool MaxNSCTHoles(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_nsctholes = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfSCTHoles");
		return this_nsctholes <= (unsigned char)(p_track_selector->GetCutParameters("MaxNSCTHoles")->at(0));	}

	bool MaxNSiHoles(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		unsigned char this_nsiholes = dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfPixelHoles") + dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n)->auxdata< unsigned char >("numberOfSCTHoles");
		return this_nsiholes <= (unsigned char)(p_track_selector->GetCutParameters("MaxNSiHoles")->at(0));
	}

	bool MaxD0SignificanceNoBeamspot(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		double this_d0sig_nobs = xAOD::TrackingHelpers::d0significance(dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n));
		return this_d0sig_nobs < (p_track_selector->GetCutParameters("MaxD0SignificanceNoBeamspot")->at(0));
	}

	bool MaxD0Significance(const DataAccess* p_data, IObjectSelector* p_track_selector, int n) {
		// Get beamspot
		double bs_sx = dynamic_cast<const EventInfoDataAccess*>(p_data)->GetEventInfo()->beamPosSigmaX();
		double bs_sy = dynamic_cast<const EventInfoDataAccess*>(p_data)->GetEventInfo()->beamPosSigmaX();
		double bs_sxy = dynamic_cast<const EventInfoDataAccess*>(p_data)->GetEventInfo()->beamPosSigmaXY();
		double this_d0sig = xAOD::TrackingHelpers::d0significance(dynamic_cast<const TrackDataAccess*>(p_data)->GetTrackParticleContainer()->at(n), bs_sx, bs_sy, bs_sxy);
		return this_d0sig < (p_track_selector->GetCutParameters("MaxD0Significance")->at(0));
	}

}

#endif