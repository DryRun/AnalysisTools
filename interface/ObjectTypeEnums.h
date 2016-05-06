#ifndef ObjectTypeEnums_h
#define ObjectTypeEnums_h

namespace ObjectIdentifiers {
	enum ObjectType {
		kNoObjectName,
		kElectron,
		kMuon,
		kTau,
		kJet,
		kPFJet,
		kCaloJet,
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

	enum JetAlgorithm {
		kAK5,
		kAK7
	};

	enum JetType {
		kCalo,
		kPF,
		kGen
	};

	enum DataSource {
		kCollisionData,
		kSimulation
	};
}

#endif