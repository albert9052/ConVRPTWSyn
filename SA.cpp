#include "SA.h"

bool SA::isFirstTime = true;

SA::SA(/* args */) {}

void SA::solve() {

    if (isFirstTime == true) {

        isFirstTime = false;
        srand(time(NULL));
    }

    // We have Ts, Te, Ld, Alpha
    // Ts: The starting temperature
    // Te: The ending temperature
    // Ld: The number of iteration in one temperature
    // Alpha: The decreasing rate
    
    // Initialize some datas

    std::vector<std::vector<int>> SAListOfEachDay; // It contains all the normal and fictive nodes, and (nRoutes - 1) -1 for boundaries of routes. 
    std::vector<std::vector<int>> bestSA;
	std::vector<std::vector<int>> currentSA;
    int bestScore;
	int currentScore;

    // Since we are doing SA, our algorithm will be running several times because nodes on different day can't swtich with each other. 

    // Generate initial datas, like initial SA. 

    for (int i = 0; i < nDays; i++) {

        SAListOfEachDay.push_back(std::vector<int>());
        for (int j = 0; j < nNodes; j++) {

            if (required[i][j] == true) {

                SAListOfEachDay[i].push_back(j);
            }
        }
        std::vector<int> tempVectorForBoundary(nRoutes - 1, -1);
        SAListOfEachDay[i].insert(SAListOfEachDay[i].end(), tempVectorForBoundary.begin(), tempVectorForBoundary.end());
    }

    // 
    
    for (int t = Ts; t <= Te; t = t * Alpha) {

        for (int iterationNum = 0; iterationNum < Ld; iterationNum) {

            // Tweak the SA
            for (int day = 0; day < nDays; day++) {

                tweakSolutionRandomly(SAListOfEachDay);
            }

			// Adjust the SA to its best
			adjustDepartureTime(SAListOfEachDay);

            // Get its minimized violation score by giving each node arrival and departure times. 
            calculateObjective(SAListOfEachDay);

			// Calculate and subtract the violation score
			int violationScore = calculateViolationScore(SAListOfEachDay, scaleOfViolationScore);

			// Do Step 4 to minimize maximum arrival time differences. 

			// If it's feasible, do Step 5 to find the best local score using 2-opt algorithm. 
			// This one may cost too much time. In one of the references, there's a way to reduce the time it might take. 

			int newScore;// = getScore();
            
            // Store it if it's the best one so far. 
            if (newScore >= bestScore) {

                bestSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
				bestScore = newScore;
            }

            // Judge if it can replace the current one. 
            if (newScore >= currentScore) {

				currentSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
			}
			else {

				if (getRandomDecimal() < exp(-(newScore - currentScore) / t)) {

					currentSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
					currentScore = newScore;
				}
			}
        }
    }
}

double SA::getRandomDecimal() {

    return (rand() / RAND_MAX);
}

int SA::getRandomInteger(int x) {

	int randomInteger = floor(rand() / (RAND_MAX) * x);
    return randomInteger == x ? x - 1 : randomInteger; // The reason why RAND_MAX has to add one is to eliminate the possibility the function return x. 
}

void SA::tweakSolutionByInsertion(std::vector<std::vector<int>>& SAListOfEachDay) {

    for (int day = 0; day < nDays; day++) {

        int positionToChoose = getRandomInteger(SAListOfEachDay[day].size());
        int positionToInsert = getRandomInteger(SAListOfEachDay[day].size() - 1);

        int tempValueForInsertion = SAListOfEachDay[day][positionToChoose];
        SAListOfEachDay[day].erase(SAListOfEachDay[day].begin() + positionToChoose);
        SAListOfEachDay[day].insert(SAListOfEachDay[day].begin() + positionToInsert, tempValueForInsertion);
    }
}

void SA::tweakSolutionBySwap(std::vector<std::vector<int>>& SAListOfEachDay) {

    for (int day = 0; day < nDays; day++) {

        int position1 = getRandomInteger(SAListOfEachDay[day].size());
        int position2 = getRandomInteger(SAListOfEachDay[day].size());

        std::swap(SAListOfEachDay[day][position1], SAListOfEachDay[day][position2]);
    }
}

void SA::tweakSolutionByReversion(std::vector<std::vector<int>>& SAListOfEachDay) {

    for (int day = 0; day < nDays; day++) {

        int position1 = getRandomInteger(SAListOfEachDay[day].size());
        int position2 = getRandomInteger(SAListOfEachDay[day].size());

        int middlePosition = (position1 + position2) / 2;
        int totalOfTwoPositions = position1 + position2;
        for (int i = std::min(position1, position2); i <= middlePosition; i++) {

            std::swap(SAListOfEachDay[day][i], SAListOfEachDay[day][totalOfTwoPositions - i]);
        }
    }
}

void SA::tweakSolutionRandomly(std::vector<std::vector<int>>& SAListOfEachDay) {

    int randomChoice = getRandomInteger(3);

    if (randomChoice == 0) {

        tweakSolutionByInsertion(SAListOfEachDay);
    }
    else if (randomChoice == 1) {

        tweakSolutionBySwap(SAListOfEachDay);
    }
    else if (randomChoice == 2) {

        tweakSolutionByReversion(SAListOfEachDay);
    }
    else {

        std::cout << "Error: tweakSARandomly get value out of {0, 1, 2}" << std::endl;
        exit(1);
    }
}


int SA::calculateViolationScore(std::vector<std::vector<int>>& SAListOfEachDay, int scaleOfViolationScore) {

	// Pure calculation. 
}

void SA::adjustDepartureTime(std::vector<std::vector<int>>& SAListOfEachDay) {

	// First adjust the arrival times of those non-synchronized one. 
	
	// Then adjust the arrival times of those synchronized one. 
}

void SA::improveTimeConsistency(std::vector<std::vector<int>>& solutionListOfEachDay) {
	
	return;
}

bool SA::isFeasible(std::vector<std::vector<int>>& solutionListOfEachDay) {

	return true;
}

int Smallest::getTheSmallest() {

	return index[0];
}

void Smallest::increaseAValue(int _index, int _value) {

	bool found = false;
	for (int i = 0; i < quantity; i++) {

		if (found == true) {

			if (value[i] < value[i - 1]) {

				std::swap(value[i], value[i - 1]);
			}
			else {

				break;
			}
		}

		if (_index == index[i]) {

			found = true;
			value[i] = _value;
		}
	}
}

void Smallest::resetAll(int _value) {

	for (int i = 0; i < quantity; i++) {

		value[i] = _value;
	}
}
