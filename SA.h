#include "Solution.h"

class Task {

public:

	Task(int _index, double _arrivalTime = -1, double _departureTime = -1) {

		index = _index;
		arrivalTime = _arrivalTime;
		departureTime = _departureTime;
	}

    int index;
    double arrivalTime;
    double departureTime;
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

    int calculateObjective(std::vector<std::vector<Task>>& solutionListOfEachDay);
	int calculateViolationScore(std::vector<std::vector<Task>>& solutionListOfEachDay, int scaleOfViolationScore);

    double getRandomDecimal(); // Which is [0, 1]
    int getRandomInteger(int x); // Which is [0, x - 1]
    void tweakSolutionByInsertion(std::vector<std::vector<Task>>& solutionListOfEachDay);
    void tweakSolutionBySwap(std::vector<std::vector<Task>>& solutionListOfEachDay);
    void tweakSolutionByReversion(std::vector<std::vector<Task>>& solutionListOfEachDay);
    void tweakSolutionRandomly(std::vector<std::vector<Task>>& solutionListOfEachDay);
    void adjustDepartureTime(std::vector<std::vector<Task>>& solutionListOfEachDay);

public:

    SA();
    void solve();
};


