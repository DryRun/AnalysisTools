#ifndef ObjectSelectorResults_h
#define ObjectSelectorResults_h

#include <map>
#include <vector>

class ObjectSelectorResults {

public:
	/**
	 * Get number of objects passing selection
	 * @return Number of objects passing selection
	 */
	inline int GetNumberOfGoodObjects() {
		return obj_good_.size();
	}

	/**
	 * Get map of whether each object passes selection
	 */
	inline std::map<int, bool>& GetGoodObjectMap() {
		return obj_pass_;
	}

	inline std::vector<int>& GetGoodObjectIndices() {
		return obj_good_;
	}

	inline bool GetObjectPass(int p_index) {
		return obj_pass_[p_index];
	}

protected:
	std::map<int, bool> obj_pass_;
	std::vector<int> obj_good_;

};

#endif
