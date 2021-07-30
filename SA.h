#include "Solution.h"
#include <algorithm>
#include <cstring>
#include <climits>

class Smallest {

public: 
	
	double* value;
	int* index;
	int quantity;

	Smallest(int _value, int _quantity) {

		quantity = _quantity;
		value = new double[quantity];
		index = new int[quantity];

		for (int i = 0; i < quantity; i++) {

			value[i] = _value;
			index[i] = i;
		}
	}

	int getTheSmallest();
	void increaseAValue(int _index, int _value);
	void resetAll(int _value);
};

class SA : public Solution{

private:

    double Ts;
    double Te;
    int numberOfIterations;
    double Alpha;
	int scaleOfViolationScore;

    static bool isFirstTime;

    std::vector<std::vector<bool>> modifiedRequiredMatrix;

    void tweakSolutionByInsertion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionBySwap(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionByReversion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionRandomly(std::vector<std::vector<int>>& solutionListOfEachDay);

public:

    SA();
    void solve();
};


