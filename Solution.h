#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

class Task {

public:

    int index;
    double arrivalTime;
    double departureTime;
}

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
    std::vector<int> synchronizedServiceMatrix; // If j is i's fictive node, then synchronizedServiceMatrrix[i] and synchronizedServiceMatrix[j] will be i and j. 
    std::vector<std::vector<float>> serviceTime, earliestTime, lastTime; 
    std::vector<std::vector<float>> timeMat; // Commuting time between each nodes
    std::vector<int> solutionList; // Indexes of nodes, ex:1~6, 0 for boundary of day, -1 for boundary of route

    void input();

    void output();

    void solveAlgoeithm1();
    void solveAlgoeithm2(); // SA version

private: 

    // Variables and functions below are for SA

    double Ts;
    double Te;
    int Ld;
    double Alpha;

    static isFirstTime;

    std::vector<std::vector<bool>> modifiedRequiredMatrix;
    std::vector<std::vector<bool>> synchronizedServiceMatrix;

    int calculateObjective(std::vector<std::vector<int>>& solutionListOfEachDay);
	int Solution::calculateViolationScore(std::vector<std::vector<int>> solutionListOfEachDay, int scaleOfViolationScore);

    double getRandomDecimal(); // Which is [0, 1]
    int getRandomInteger(x); // Which is [0, x - 1]
    void tweakSolutionByInsertion(std::vector<std::vector<Task>> solutionListOfEachDay);
    void tweakSolutionBySwap(std::vector<std::vector<Task>> solutionListOfEachDay);
    void tweakSolutionByReversion(std::vector<std::vector<Task>> solutionListOfEachDay);
    void tweakSolutionRandomly(std::vector<std::vector<Task>> solutionListOfEachDay);
    void adjustDepartureTime(std::vector<std::vector<Task>> solutionListOfEachDay);

	// --------------------------------------------------------------------
	
	// Variables and functions below are for LNS
	
	// --------------------------------------------------------------------
};
