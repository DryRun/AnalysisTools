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
	inline unsigned int GetNumberOfGoodObjects() {
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
		if (obj_pass_.find(p_index) == obj_pass_.end()) {
			std::cerr << "[ObjectSelectorResults::GetObjectPass] ERROR : Requested pass for unknown index " << p_index << std::endl;
			exit(1);
		}
		return obj_pass_[p_index];
	}

	inline unsigned int GetTotalNumberOfObjects() {
		return n_obj_;
	}

protected:
	std::map<int, bool> obj_pass_;
	std::vector<int> obj_good_;
	unsigned int n_obj_;

};

#endif
