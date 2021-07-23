#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstring>
//<<<<<<< Updated upstream
#include <climits>
#include <set>
//=======
#include <limits>
//>>>>>>> Stashed changes
#include <iomanip>

class PointAndType {

public:

	PointAndType(int _point, int _type, int _value) {
	
		point = _point;
		type = _type;
		value = _value;
	}
	int point;
	int type;
	int value;

	bool operator<(const PointAndType& anotherOne) const{

		if (this->point < anotherOne.point) {

			if (this->type < anotherOne.type) {

				return true;
			}
			else {

				return false;
			}
		}
		return false;
	}

};

class TypeAndDuration {

public: 

	int type; 
	// 0 indicates the final one, which is our goal. 
	// 1 for duration between its arrival time and last time(latest time). after push to this duration, numberOfBadNodes + 1. 
	// 2 indicates that when the duration is pushed, numberOfGoodNodes + 1. 
	// 3 indicates that when the duration is pushed, numberOfGoodNodes - 1, and numberOfBadNodes + 1. 
	// 4 indicates that when the duration is pushed, numberOfGoodNodes - 1. 
	double duration;

	TypeAndDuration(int _type, int _duration) {

		type = _type;
		duration = _duration;
	}

	bool operator<(const TypeAndDuration& anotherOne) const{

		if (this->duration < anotherOne.duration) {

			return true;
		}
		return false;
	}

	bool operator>(const TypeAndDuration& anotherOne) const{

		if (this->duration > anotherOne.duration) {

			return true;
		}
		return false;
	}
};

class Solution {
public:

    int nNodes; // Number of nodes
	int nCustomer;
    int nNormals; // Number of normal nodes
    int nFictives; // Number of fictive nodes
    int nDays; // Number of days
    int nRoutes; // Number of routes
    std::vector<int> fictiveLink; // 0 for normal nodes, n>0 for fictive nodes and it's normal node is n
    std::vector<std::vector<bool>> required; // Required day (false for not required, true for required.)
	std::vector<std::vector<int>> requiredList;
	std::vector<int> synchronizedServiceMatrix; // If j is i's fictive node, then synchronizedServiceMatrix[i] and synchronizedServiceMatrix[j] will be i and j. 
    std::vector<std::vector<float>> serviceTime, earliestTime, lastTime; 
    std::vector<std::vector<float>> timeMat; // Commuting time between each nodes, size: nDays+1, 0 for begin and end
    //std::vector<int> solutionList; // Indexes of nodes, ex:1~6, 0 for boundary of day, -1 for boundary of route
    std::vector<std::vector<std::vector<int>>> solutionList;

    Solution() {

        input();

		arrivalTimes = std::vector<std::vector<double>>(nNodes, (std::vector<double>(nDays, -1)));

		departureTimes = std::vector<std::vector<double>>(nNodes, (std::vector<double>(nDays, -1)));
		
		postponedDuration = std::vector<std::vector<std::vector<double>>>(nDays, std::vector<std::vector<double>>(nNodes, std::vector<double>(nNodes, 0)));

		correspondingList.resize(nNodes);
		correspondingList[0] = 0;
		for (int i = 1; i <= fictiveLink.size(); i++) {

			correspondingList[i] = fictiveLink[i - 1];
			if (fictiveLink[i - 1] != 0) {

				correspondingList[fictiveLink[i - 1]] = i;
			}
		}
    }
    void input();
    void output();
    virtual void solve() = 0;

protected: 

    void calculateObjective(std::vector<std::vector<int>>& solutionListOfEachDay);
	std::vector<std::vector<double>> arrivalTimes;
	std::vector<std::vector<double>> departureTimes;
	std::vector<std::vector<std::vector<double>>> postponedDuration;
	std::vector<int> correspondingList; // 0 means no corresponding nodes
	
	void printGraph(const std::vector<std::vector<int>>& solutionListOfEachDay, double limit);
	void printTimeLine(const std::vector<PointAndType>& pointsAndTypes);
	void printVerticalLines(int lines);
};

#endif
