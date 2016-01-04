#ifndef ElectronDataAccess_h
#define ElectronDataAccess_h

#include <iostream>

#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/ElectronContainerFwd.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODCaloEvent/CaloClusterContainer.h"

#include "Selectors/DataAccess.h"

class ElectronDataAccess : public virtual DataAccess {
	/*** Methods ***/
public:
	ElectronDataAccess();

	virtual ~ElectronDataAccess();

	inline const xAOD::ElectronContainer* GetForwardElectronContainer() {
		return forward_electrons_;
	}

	inline const xAOD::ElectronContainer* GetForwardElectronContainer() const {
		return forward_electrons_;
	}

	inline const xAOD::ElectronContainer* GetElectronContainer() {
		return electrons_;
	}

	inline const xAOD::ElectronContainer* GetElectronContainer() const {
		return electrons_;
	}

	inline const xAOD::TruthParticleContainer* GetEgammaTruthParticleContainer() {
		return egamma_truth_particles_;
	}

	inline const xAOD::TruthParticleContainer* GetEgammaTruthParticleContainer() const {
		return egamma_truth_particles_;
	}

	inline const xAOD::CaloClusterContainer* GetEgammaClusterContainer() {
		return egamma_clusters_;
	}

	inline const xAOD::CaloClusterContainer* GetEgammaClusterContainer() const {
		return egamma_clusters_;
	}

	inline const xAOD::CaloClusterContainer* GetForwardElectronClusterContainer() {
		return forward_egamma_clusters_;
	}

	inline const xAOD::CaloClusterContainer* GetForwardElectronClusterContainer() const {
		return forward_egamma_clusters_;
	}

protected:
	/**
	 * Load a new event
	 */
	bool RetrieveElectrons();


	/*** Members ***/
protected:
	const xAOD::ElectronContainer * electrons_; //!
	const xAOD::ElectronContainer * forward_electrons_; //!
	const xAOD::TruthParticleContainer * egamma_truth_particles_; //!
	const xAOD::CaloClusterContainer * egamma_clusters_; //!
	const xAOD::CaloClusterContainer * forward_egamma_clusters_; //!
};


#endif