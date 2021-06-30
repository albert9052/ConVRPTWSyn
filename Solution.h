#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

class Solution {

public:

    Solution() {

        input();
    }

    int nNodes; // Number of nodes
    int n_normals; // Number of normal nodes
    int n_fictives; // Number of fictive nodes
    int nDays; // Number of days
    int nRoutes; // Number of routes
    std::vector<std::vector<bool>> required; // Required day (false for not required, true for required.)
    std::vector<int> synchronizedServiceMatrix; // If j is i's fictive node, then synchronizedServiceMatrix[i] and synchronizedServiceMatrix[j] will be i and j. 
    std::vector<std::vector<float>> serviceTime, earliestTime, lastTime; 
    std::vector<std::vector<float>> timeMat; // Commuting time between each nodes
    std::vector<int> solutionList; // Indexes of nodes, ex:1~6, 0 for boundary of day, -1 for boundary of route

    void input();

    void output();

    void solveAlgorithm1();
    void solveAlgorithm2(); // SA version

private: 

    // Variables and functions below are for SA

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

	// --------------------------------------------------------------------
	
	// Variables and functions below are for LNS
	
	// --------------------------------------------------------------------
};
