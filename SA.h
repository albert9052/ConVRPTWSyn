#include "Solution.h"

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
    int Ld;
    double Alpha;
	int scaleOfViolationScore;

    static bool isFirstTime;

    std::vector<std::vector<bool>> modifiedRequiredMatrix;
	std::vector<std::vector<double>> arrivalTimes;
	std::vector<std::vector<double>> departureTimes;

    int calculateObjective(std::vector<std::vector<int>>& solutionListOfEachDay);
	int calculateViolationScore(std::vector<std::vector<int>>& solutionListOfEachDay, int scaleOfViolationScore);

    double getRandomDecimal(); // Which is [0, 1]
    int getRandomInteger(int x); // Which is [0, x - 1]
    void tweakSolutionByInsertion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionBySwap(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionByReversion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionRandomly(std::vector<std::vector<int>>& solutionListOfEachDay);
    void adjustDepartureTime(std::vector<std::vector<int>>& solutionListOfEachDay);
	void improveTimeConsistency(std::vector<std::vector<int>>& solutionListOfEachDay);
	bool isFeasible(std::vector<std::vector<int>>& solutionListOfEachDay);

public:

    SA();
    void solve();
};


