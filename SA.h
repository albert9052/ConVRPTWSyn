#include "Solution.h"

class SA : public Solution{

private:

    double Ts;
    double Te;
    int Ld;
    double Alpha;
	int scaleOfViolationScore;

    static bool isFirstTime;

    std::vector<std::vector<bool>> modifiedRequiredMatrix;
	std::vector<std::vector<int>> arrivalTimes;
	std::vector<std::vector<int>> departureTimes;

    int calculateObjective(std::vector<std::vector<int>>& solutionListOfEachDay);
	int calculateViolationScore(std::vector<std::vector<int>>& solutionListOfEachDay, int scaleOfViolationScore);

    double getRandomDecimal(); // Which is [0, 1]
    int getRandomInteger(int x); // Which is [0, x - 1]
    void tweakSolutionByInsertion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionBySwap(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionByReversion(std::vector<std::vector<int>>& solutionListOfEachDay);
    void tweakSolutionRandomly(std::vector<std::vector<int>>& solutionListOfEachDay);
    void adjustDepartureTime(std::vector<std::vector<int>>& solutionListOfEachDay);

public:

    SA();
    void solve();
};


