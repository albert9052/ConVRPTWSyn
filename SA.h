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

struct CustomerAndArrivalTimeDifference {

	int customer;
	double difference;
	int dayOfMinArrivalTime;
	int dayOfMaxArrivalTime;
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

	int calculateViolationScore(std::vector<std::vector<int>>& solutionListOfEachDay, int scaleOfViolationScore);

    double getRandomDecimal(); // Which is [0, 1]
    int getRandomInteger(int x); // Which is [0, x - 1]
    void tweakSolutionByInsertion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionBySwap(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionByReversion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionRandomly(std::vector<std::vector<int>>& solutionListOfEachDay);
	// Assume all the synchronized service has no violation. 
	CustomerAndArrivalTimeDifference getTheCustomerWithLargestArrivalTimeDifference();
	// This version can only deal with solutions with no violation. 
	double getMaxPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double accumulatedPostponedDuration, bool firstLoop);
	// This version can only deal with solutions with no violation. 
	void applyPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double PF);
	// This version can only deal with solutions with no violation. 
	// Haven't consider about 0's lastTime. 
    void adjustDepartureTime(std::vector<std::vector<int>>& solutionListOfEachDay);
	// Variables for adjustDepartureTime
	std::vector<std::vector<int>> nodesHavinglastArrivalTime;
	std::vector<std::vector<int>> nodesHavingEarliestArrivalTime;
	std::vector<std::vector<int>> daysOfMinArrivalTimeOfEachCustomer;
	std::vector<std::vector<int>> daysOfMaxArrivalTimeOfEachCustomer;
	// -------------------------------------

	void improveTimeConsistency(std::vector<std::vector<int>>& solutionListOfEachDay);
	bool isFeasible(std::vector<std::vector<int>>& solutionListOfEachDay);

public:

    SA();
    void solve();
};


