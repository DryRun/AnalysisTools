#ifndef EventInfoDataAccess_h
#define EventInfoDataAccess_h

#include "xAODEventInfo/EventInfo.h"
#include "Selectors/DataAccess.h"

class EventInfoDataAccess : public virtual DataAccess {

	/*** Methods ***/
public:
	EventInfoDataAccess();
	virtual ~EventInfoDataAccess();

	inline const xAOD::EventInfo* GetEventInfo() {
		return event_info_;
	}

	inline const xAOD::EventInfo* GetEventInfo() const {
		return event_info_;
	}

protected:
	/**
	 * Load a new event
	 */
	bool RetrieveEventInfo();

	/*** Members ***/
protected:
	const xAOD::EventInfo* event_info_; //!

};


#endif