#ifndef ObjectTypeEnums_h
#define ObjectTypeEnums_h

namespace ObjectIdentifiers {
	enum ObjectType {
		kNoObjectName,
		kElectron,
		kMuon,
		kTau,
		kJet,
		kW,
		kZ,
		kHiggs,
		kElectronNeutrino,
		kMuonNeutrino,
		kTauNeutrino,
		kAnyNeutrino,
		kTrack
	};

	enum ObjectFakeType {
		kNumerator,
		kDenominator,
		kUnspecified
	};
}

#endif