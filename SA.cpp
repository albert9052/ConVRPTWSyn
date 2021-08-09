#include "SA.h"

bool SA::isFirstTime = true;

SA::SA(/* args */) {

	Ts = 100000000000;
	Te = 0.0000000000001;
	numberOfIterations = 100000;
	Alpha = 0.1;
}

void SA::solve() {

	//for (int i = 0; i < correspondingList.size(); i++) {

	//	std::cout << i << ": " << correspondingList[i] << std::endl;
	//}

    if (isFirstTime == true) {

        isFirstTime = false;
        srand(time(NULL));
    }

    // We have Ts, Te, numberOfIterations, Alpha
    // Ts: The starting temperature
    // Te: The ending temperature
    // numberOfIterations: The number of iteration in one temperature
    // Alpha: The decreasing rate
    
    // Initialize some datas

    std::vector<std::vector<int>> SAListOfEachDay; // It contains all the normal and fictive nodes, and (nRoutes - 1) -1 for boundaries of routes. 
    std::vector<std::vector<int>> bestSA;
	std::vector<std::vector<int>> currentSA;
    double bestScore = INT_MAX;
	double currentScore = INT_MAX;

    // Since we are doing SA, our algorithm will be running several times because nodes on different day can't swtich with each other. 

    // Generate initial datas, like initial SA. 

	int numberOfCorrespondingNode = nNormals + 1;
    for (int day = 0; day < nDays; day++) {

        SAListOfEachDay.push_back(std::vector<int>());
        for (int j = 1; j < nNodes; j++) {

            if (required[j][day] == 1) {

                SAListOfEachDay[day].push_back(j);
            }
        }
        std::vector<int> tempVectorForBoundary(nRoutes - 1, -1);
        SAListOfEachDay[day].insert(SAListOfEachDay[day].end(), tempVectorForBoundary.begin(), tempVectorForBoundary.end());
    }

	//for (int day = 0; day < nDays; day++) {

	//	std::cout << "Day " << day << ": ";
	//	for (int i = 0; i < SAListOfEachDay[day].size(); i++) {

	//		std::cout << SAListOfEachDay[day][i] << " ";
	//	}
	//	std::cout << std::endl;
	//}

    // 
    
    for (double t = Ts; t >= Te; t = t * Alpha) {

        for (int iterationNum = 0; iterationNum < numberOfIterations; iterationNum++) {

            // Tweak the SA
			tweakSolutionRandomly(SAListOfEachDay);

			//for (int day = 0; day < nDays; day++) {

			//	std::cout << "Day " << day << ": ";
			//	for (int i = 0; i < SAListOfEachDay[day].size(); i++) {

			//		std::cout << SAListOfEachDay[day][i] << " ";
			//	}
			//	std::cout << std::endl;
			//}

			//if (iterationNum % 1000 == 0) {

			//	std::cout << iterationNum << " times" << std::endl;
			//}

			//temporary
			//SAListOfEachDay[0] = {6, 7, 1, 20, 8, -1, 14, 19, 3, 9, -1, 11, 16, 13, 15, 10, -1, 18};
			//SAListOfEachDay[1] = {6, 1, 8, -1, 19, -1, 11, 13, 10, -1, 12, 17, 2, 18};
			//SAListOfEachDay[2] = {6, 7, 20, 8, -1, 14, 3, 9, -1, 16, 13, 15, 10, -1, 12, 17, 4, 5};

			// Adjust the arrival time and departure time to get the minimum violation. 
            calculateObjective(SAListOfEachDay);
			//std::cout << "calculateObjective done. " << std::endl;
			//CheckConstraintsResult checkConstraintsResult = checkConstraints(SAListOfEachDay);
			//std::cout << "checkConstraints done. " << std::endl;
			//if (checkConstraintsResult.result == false) {

			//	printGraph(SAListOfEachDay, GRAPH_LIMIT);
			//	std::cout << "Violation detected ----------------------------------" << std::endl;
			//	for (std::string message : checkConstraintsResult.messages) {

			//		std::cout << message << std::endl;
			//	}
			//	std::cout << "-----------------------------------------------------" << std::endl;
			//	exit(1);
			//}

			//// Adjust the arrival time and departure time to get the minimum score. (Approximately) 
			//adjustDepartureTime(SAListOfEachDay);

			//// Calculate and subtract the violation score
			//int violationScore = calculateViolationScore(SAListOfEachDay, scaleOfViolationScore);

			// Do Step 4 to minimize maximum arrival time differences. 

			// If it's feasible, do Step 5 to find the best local score using 2-opt algorithm. 
			// This one may cost too much time. In one of the references, there's a way to reduce the time it might take. 

			double newScore;// = getScore();
			
			// Temporary: 
			newScore = getViolationScore(SAListOfEachDay, FACTOR_OF_VIOLATION);
			//CheckConstraintsResult checkConstraintsResult = checkConstraints(SAListOfEachDay);
			////std::cout << "checkConstraints done. " << std::endl;
			//if (checkConstraintsResult.result == false) {

			//	printGraph(SAListOfEachDay, GRAPH_LIMIT);
			//	std::cout << "After calculateObjective" << std::endl;
			//	std::cout << "Violation detected ----------------------------------" << std::endl;
			//	for (std::string message : checkConstraintsResult.messages) {

			//		std::cout << message << std::endl;
			//	}
			//	std::cout << "-----------------------------------------------------" << std::endl;
			//	exit(1);
			//}
			if (newScore == 0) {

				//printGraph(SAListOfEachDay, GRAPH_LIMIT);
				adjustDepartureTime(SAListOfEachDay);
				//newScore += getObjectiveScore(SAListOfEachDay);
				CheckConstraintsResult checkConstraintsResult = checkConstraints(SAListOfEachDay);
				//std::cout << "checkConstraints done. " << std::endl;
				if (checkConstraintsResult.result == false) {

					printGraph(SAListOfEachDay, GRAPH_LIMIT);
					std::cout << "After adjustDepartureTime" << std::endl;
					std::cout << "Violation detected ----------------------------------" << std::endl;
					for (std::string message : checkConstraintsResult.messages) {

						std::cout << message << std::endl;
					}
					std::cout << "-----------------------------------------------------" << std::endl;
					exit(1);
				}

				improveTimeConsistency(SAListOfEachDay);
				newScore += getObjectiveScore(SAListOfEachDay);
				checkConstraintsResult = checkConstraints(SAListOfEachDay);
				//std::cout << "checkConstraints done. " << std::endl;
				if (checkConstraintsResult.result == false) {

					printGraph(SAListOfEachDay, GRAPH_LIMIT);
					std::cout << "After adjustDepartureTime" << std::endl;
					std::cout << "Violation detected ----------------------------------" << std::endl;
					for (std::string message : checkConstraintsResult.messages) {

						std::cout << message << std::endl;
					}
					std::cout << "-----------------------------------------------------" << std::endl;
					exit(1);
				}
				if (getViolationScore(SAListOfEachDay, FACTOR_OF_VIOLATION)) {

					printGraph(SAListOfEachDay, GRAPH_LIMIT);
					std::cout << "After ImproveTimeConssitenct" << std::endl;
					std::cout << "Violation score is not zero" << std::endl;
					exit(1);
				}
				//bool improved = improveTimeConsistency(SAListOfEachDay);
				//if (improved) {

				//	calculateObjective(SAListOfEachDay);
				//	adjustDepartureTime(SAListOfEachDay);
				//	newScore = getObjectiveScore(SAListOfEachDay);
				//	CheckConstraintsResult checkConstraintsResult = checkConstraints(SAListOfEachDay);
				//	//std::cout << "checkConstraints done. " << std::endl;
				//	if (checkConstraintsResult.result == false) {

				//		printGraph(SAListOfEachDay, GRAPH_LIMIT);
				//		std::cout << "Violation detected ----------------------------------" << std::endl;
				//		for (std::string message : checkConstraintsResult.messages) {

				//			std::cout << message << std::endl;
				//		}
				//		std::cout << "-----------------------------------------------------" << std::endl;
				//		exit(1);
				//	}
				//}
				//else {

				//	calculateObjective(SAListOfEachDay);
				//	adjustDepartureTime(SAListOfEachDay);
				//}
				//std::cout << "Score: " << newScore << std::endl;
			}
			//std::cout << "Score: " << newScore << ", Best Score: " << bestScore << std::endl;
            
            // Store it if it's the best one so far. 
            if (newScore < bestScore) {

                bestSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
				bestScore = newScore;
				std::cout << "Best Score: " << newScore << std::endl;
				//printGraph(SAListOfEachDay, GRAPH_LIMIT);
            }

            // Judge if it can replace the current one. 
            if (newScore < currentScore) {

				currentSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
			}
			else {

				if (getRandomDecimal() < exp(-(currentScore - newScore) / t)) {

					currentSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
					currentScore = newScore;
				}
			}

			//printGraph(bestSA, GRAPH_LIMIT);
			//std::cout << bestScore << std::endl;
			//exit(1);
        }
    }

	calculateObjective(bestSA);
	adjustDepartureTime(bestSA);
	CheckConstraintsResult checkConstraintsResult = checkConstraints(bestSA);
	printGraph(bestSA, GRAPH_LIMIT);
	std::cout << "Best score: " << bestScore << std::endl;
	if (checkConstraintsResult.result == false) {

		std::cout << "Violation detected ----------------------------------" << std::endl;
		for (std::string message : checkConstraintsResult.messages) {

			std::cout << message << std::endl;
		}
		std::cout << "-----------------------------------------------------" << std::endl;
	}
}

void SA::tweakSolutionByInsertion(std::vector<std::vector<int>>& SAListOfEachDay) {

	//int day = getRandomInteger(3);
	for (int day = 0; day < nDays; day++) {

		int positionToChoose = getRandomInteger(SAListOfEachDay[day].size());
		int positionToInsert = getRandomInteger(SAListOfEachDay[day].size() - 1);

		int tempValueForInsertion = SAListOfEachDay[day][positionToChoose];
		SAListOfEachDay[day].erase(SAListOfEachDay[day].begin() + positionToChoose);
		SAListOfEachDay[day].insert(SAListOfEachDay[day].begin() + positionToInsert, tempValueForInsertion);
	}
}

void SA::tweakSolutionBySwap(std::vector<std::vector<int>>& SAListOfEachDay) {

	//int day = getRandomInteger(3);
	for (int day = 0; day < nDays; day++) {

		int position1 = getRandomInteger(SAListOfEachDay[day].size());
		int position2 = getRandomInteger(SAListOfEachDay[day].size());

		std::swap(SAListOfEachDay[day][position1], SAListOfEachDay[day][position2]);
	}
}

void SA::tweakSolutionByReversion(std::vector<std::vector<int>>& SAListOfEachDay) {

	//int day = getRandomInteger(3);
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
