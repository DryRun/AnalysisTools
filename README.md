# AnalysisTools
Tools for performing event and object selections in an xAOD analysis. 

DATA ACCESS:
To use the object selector classes, the analysis code (e.g. the EL::Algorithm) is required to inherit from various DataAccess classes, which load the xAOD event data. Each class must have a RetrieveX function, which is called at the start of EL::Algorithm::execute() to load the data. The CutFunctions then cast the DataAccess object to the appropriate subclass, e.g. ElectronDataAccess, to read the current event data. 


OBJECT SELECTORS:
Classes deriving from IObjectSelector loop over a given type of object in an event, e.g. tracks, electrons, pixel clusters, etc. A set of cuts are applied to each object, and the resulting pass/fail decision is saved. The subclasses must define ClassifyObjects(), which contains the loop over the objects in the event, e.g. for (int i = 0; i < tracks_->size(); i++) {...} (this could possibly be moved to IObjectSelector, using DataHandles...?). 


CUT FUNCTIONS:
The cuts are performed by:
typedef bool (*CutFunction)(const DataAccess* p_data, IObjectSelector* p_track_selector, int n);
See TrackCutFunctions.h, for example.


OTHER:
Details on the cutflow are automaticallly recorded, and can be written out by using ISelector::SaveHistograms(EL::Worker *wk). 

ISelector is separate from IObjectSelector to anticipate implementing an EventSelector, which performs event-by-event selection, rather than object-by-object. Unfortunately, I'm moving to CMS, so this will likely never happen :_( .