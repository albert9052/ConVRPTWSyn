#include "SA.h"

bool SA::isFirstTime = true;

SA::SA(/* args */) {

	Ts = 10;
	Te = 10;
	numberOfIterations = 10;
	Alpha = 0.0001;
}

void SA::solve() {

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
    int bestScore;
	int currentScore;

    // Since we are doing SA, our algorithm will be running several times because nodes on different day can't swtich with each other. 

    // Generate initial datas, like initial SA. 

	int numberOfCorrespondingNode = nNormals + 1;
    for (int day = 0; day < nDays; day++) {

        SAListOfEachDay.push_back(std::vector<int>());
        for (int j = 1; j <= nNormals; j++) {

            if (required[j][day] == 1) {

                SAListOfEachDay[day].push_back(j);
				if (correspondingList[j] != 0) {

					SAListOfEachDay[day].push_back(numberOfCorrespondingNode);
				}
            }
        }
        std::vector<int> tempVectorForBoundary(nRoutes - 1, -1);
        SAListOfEachDay[day].insert(SAListOfEachDay[day].end(), tempVectorForBoundary.begin(), tempVectorForBoundary.end());
    }

	for (int day = 0; day < nDays; day++) {

		std::cout << "Day " << day << ": ";
		for (int i = 0; i < SAListOfEachDay[day].size(); i++) {

			std::cout << SAListOfEachDay[day][i] << " ";
		}
		std::cout << std::endl;
	}

    // 
    
    for (int t = Ts; t <= Te; t = t * Alpha) {

        for (int iterationNum = 0; iterationNum < numberOfIterations; iterationNum) {

            // Tweak the SA
            for (int day = 0; day < nDays; day++) {

                tweakSolutionRandomly(SAListOfEachDay);
            }

			// Adjust the arrival time and departure time to get the minimum violation. 
            calculateObjective(SAListOfEachDay);

			//// Adjust the arrival time and departure time to get the minimum score. (Approximately) 
			//adjustDepartureTime(SAListOfEachDay);

			//// Calculate and subtract the violation score
			//int violationScore = calculateViolationScore(SAListOfEachDay, scaleOfViolationScore);

			// Do Step 4 to minimize maximum arrival time differences. 

			// If it's feasible, do Step 5 to find the best local score using 2-opt algorithm. 
			// This one may cost too much time. In one of the references, there's a way to reduce the time it might take. 

			//int newScore;// = getScore();
            //
            //// Store it if it's the best one so far. 
            //if (newScore >= bestScore) {

            //    bestSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
			//	bestScore = newScore;
            //}

            //// Judge if it can replace the current one. 
            //if (newScore >= currentScore) {

			//	currentSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
			//}
			//else {

			//	if (getRandomDecimal() < exp(-(newScore - currentScore) / t)) {

			//		currentSA.assign(SAListOfEachDay.begin(), SAListOfEachDay.end());
			//		currentScore = newScore;
			//	}
			//}
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

int SA::calculateViolationScore(std::vector<std::vector<int>>& solutionListOfEachDay, int scaleOfViolationScore) {

	// Pure calculation. 
}

double SA::getMaxPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double accumulatedPostponedDuration, bool firstLoop) {

	static std::vector<int> routesHavingBeenCalculated;
	if (firstLoop) {

		routesHavingBeenCalculated.clear();
		routesHavingBeenCalculated.push_back(day);
	}
	double maxPF = std::numeric_limits<double>::max();
	while (solutionListOfEachDay[day][positionOfNode] != -1 && positionOfNode < solutionListOfEachDay[day].size()) {

		int currentNode = solutionListOfEachDay[day][positionOfNode];
		int nextNode = 0;
		if (positionOfNode != solutionListOfEachDay[day].size() - 1) {

			nextNode = solutionListOfEachDay[day][positionOfNode + 1];
			if (nextNode == -1) {

				nextNode = 0;
			}
		}

		std::vector<int> daysOfMinArrivalTime = daysOfMinArrivalTimeOfEachCustomer[currentNode];
		std::vector<int> daysOfMaxArrivalTime = daysOfMaxArrivalTimeOfEachCustomer[currentNode];

		// Check how far it can move according to whether it will increase the objective score. 
		if (std::find(daysOfMaxArrivalTime.begin(), daysOfMaxArrivalTime.end(), currentNode) != daysOfMaxArrivalTime.end()) {

			maxPF = std::min(maxPF, accumulatedPostponedDuration);
		}
		else {

			double duration = arrivalTimes[daysOfMaxArrivalTime[0]][day] - arrivalTimes[currentNode][day] + accumulatedPostponedDuration;
			maxPF = std::min(maxPF, duration);
		}

		// Check how far it can move according to whether it will exceeds its own time window. 
		double duration = lastTime[currentNode][day] - arrivalTimes[currentNode][day];
		maxPF = std::min(maxPF, duration);

		// Deal with the synchronized one. 
		if (correspondingList[currentNode] != 0) {

			int correspondingNode = correspondingList[currentNode];
			int positionOfCorrespondingNode = 0;
			int routeOfCorrespondingNode = 0;
			for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

				if (solutionListOfEachDay[day][i] == -1) {

					routeOfCorrespondingNode++;
					continue;
				}
				if (solutionListOfEachDay[day][i] == correspondingNode) {

					positionOfCorrespondingNode = i;
					break;
				}
			}
			
			// Check if this route we have taken into consideration. 
			if (std::find(routesHavingBeenCalculated.begin(), routesHavingBeenCalculated.end(), routeOfCorrespondingNode) == routesHavingBeenCalculated.end()) {

				routesHavingBeenCalculated.push_back(routeOfCorrespondingNode);
				double accumulatedPostponedDurationForAnotherRoute = accumulatedPostponedDuration + postponedDuration[day][correspondingNode][solutionListOfEachDay[day][positionOfCorrespondingNode + 1]];
				maxPF = std::min(maxPF, getMaxPF(solutionListOfEachDay, positionOfCorrespondingNode + 1, day, accumulatedPostponedDurationForAnotherRoute, false));
			}
		}

		accumulatedPostponedDuration += postponedDuration[day][currentNode][nextNode];
		positionOfNode++;
	}

	return maxPF;
}

// Assume all the synchronized service has no violation. 
// This function needs to be adjusted to use daysOfMinArrivalTimeDifferenceOfEachCustomer and daysOfMaxArrivalTimeDifferenceOfEachCustomer. 
CustomerAndArrivalTimeDifference SA::getTheCustomerWithLargestArrivalTimeDifference() {

	int theChosenOne = 1;
	double valueOfTheChosenOne = 0;
	int dayOfMinArrivalTime = 0;
	int dayOfMaxArrivalTime = 0;
	for (int i = 1; i <= nNormals; i++) {

		double difference = arrivalTimes[i][daysOfMaxArrivalTimeOfEachCustomer[i][0]] - arrivalTimes[i][daysOfMinArrivalTimeOfEachCustomer[i][0]];
		if (difference > valueOfTheChosenOne) {

			theChosenOne = i;
			valueOfTheChosenOne = difference;
			dayOfMinArrivalTime = daysOfMinArrivalTimeOfEachCustomer[i][0];
			dayOfMaxArrivalTime = daysOfMaxArrivalTimeOfEachCustomer[i][0];
		}
	}
	struct CustomerAndArrivalTimeDifference customerAndDifference;
	customerAndDifference.customer = theChosenOne;
	customerAndDifference.difference = valueOfTheChosenOne;
	customerAndDifference.dayOfMinArrivalTime = dayOfMinArrivalTime;
	customerAndDifference.dayOfMaxArrivalTime = dayOfMaxArrivalTime;
	return customerAndDifference;
}

std::vector<int>* SA::applyPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double PF, bool firstLoop) {

	static std::vector<int> routesHavingBeenApplied;
	if (firstLoop) {

		routesHavingBeenApplied.clear();
		routesHavingBeenApplied.push_back(day);
	}

	std::vector<int>* nodesBeingMovedPtr = new std::vector<int>();
	int previousNode = 0;
	if (positionOfNode > 0) {

		previousNode = solutionListOfEachDay[day][positionOfNode - 1];
		if (previousNode == -1) {

			previousNode = 0;
		}
	}
	// The part about getting currentNode and nextNode can be more optimized, but it will lose its readability, so I keep it this way. 
	for (int i = positionOfNode; i < solutionListOfEachDay[day].size(); i++) {

		// Get currentNode. 
		int currentNode = solutionListOfEachDay[day][i];
		if (currentNode == -1) {

			break;
		}
		// Transform it into its normal node if it is a fictive node. (Just its number)
		if (currentNode > nNormals) {

			currentNode = correspondingList[currentNode];
		}

		// Get nextNode. 
		int nextNode = 0;
		if (i < solutionListOfEachDay[day].size() - 1) {

			nextNode = solutionListOfEachDay[day][i + 1];
			if (nextNode == -1) {

				nextNode = 0;
			}
		}

		// Apply it. 
		postponedDuration[day][previousNode][currentNode] += PF;
		arrivalTimes[currentNode][day] += PF;
		departureTimes[currentNode][day] += PF;

		// Deal with the synchronized node. 
		int correspondingNode = correspondingList[currentNode];
		if (correspondingNode != 0) {

			int positionOfCorrespondingNode = 0;
			int routeOfCorrespondingNode = 0;
			for (int j = 0; j < nNormals; j++) {

				if (solutionListOfEachDay[day][j] == -1) {

					routeOfCorrespondingNode++;
					continue;
				}
				if (solutionListOfEachDay[day][j] == correspondingNode) {

					positionOfCorrespondingNode = j;
					break;
				}
			}

			// Avoid ReApplying. 
			if (std::find(routesHavingBeenApplied.begin(), routesHavingBeenApplied.end(), routeOfCorrespondingNode) == routesHavingBeenApplied.end()) {

				routesHavingBeenApplied.push_back(routeOfCorrespondingNode);

				int previousNodeForCorrespondingNode = 0;
				if (positionOfCorrespondingNode > 0) {

					previousNodeForCorrespondingNode = solutionListOfEachDay[day][positionOfCorrespondingNode -1];
					if (previousNodeForCorrespondingNode == -1) {

						previousNodeForCorrespondingNode = 0;
					}
				}
				
				int nextNodeForCorrespondingNode = 0;
				if (i < solutionListOfEachDay[day].size() - 1) {

					nextNodeForCorrespondingNode = solutionListOfEachDay[day][i + 1];
					if (nextNodeForCorrespondingNode == -1) {

						nextNodeForCorrespondingNode = 0;
					}
				}

				// Apply it. 
				postponedDuration[day][previousNodeForCorrespondingNode][correspondingNode] += PF;
				arrivalTimes[correspondingNode][day] += PF;
				departureTimes[correspondingNode][day] += PF;

				// Adjust PF for corresponding node. 
				double tempPostponedDuration = postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode];
				double tempPF = PF;
				if (tempPF < tempPostponedDuration) {

					postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode] -= tempPF;
				}
				else {

					postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode] = 0; // This is equal to postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode] -= tempPostponedDuration;
					tempPF -= tempPostponedDuration;
				}

				std::vector<int>* otherNodesBeingMovedPtr = applyPF(solutionListOfEachDay, positionOfCorrespondingNode, day, tempPF, false);
				nodesBeingMovedPtr->reserve(nodesBeingMovedPtr->size() + otherNodesBeingMovedPtr->size());
				nodesBeingMovedPtr->insert(nodesBeingMovedPtr->end(), otherNodesBeingMovedPtr->begin(), otherNodesBeingMovedPtr->end());
				delete otherNodesBeingMovedPtr;
			}
		}

		// Adjust PF. 
		double tempPostponedDuration = postponedDuration[day][currentNode][nextNode];
		if (PF < tempPostponedDuration) {

			postponedDuration[day][currentNode][nextNode] -= PF;
			break;
		}
		else {

			postponedDuration[day][currentNode][nextNode] = 0; // This is equal to postponedDuration[day][currentNode][nextNode] -= tempPostponedDuration;
			PF -= tempPostponedDuration;
		}

		// Add it into nodesBeingMoved
		nodesBeingMovedPtr->push_back(currentNode);
		
		// Get previousNode for next iteration. 
		previousNode = currentNode;
	}
	
	return nodesBeingMovedPtr;
}

// This version can only deal with solution with no violation. 
void SA::adjustDepartureTime(std::vector<std::vector<int>>& solutionListOfEachDay) {

	// Calculate daysOfMinArrivalTimeOfEachCustomer, and daysOfMaxArrivalTimeOfEachCustomer
	daysOfMinArrivalTimeOfEachCustomer.clear();
	daysOfMaxArrivalTimeOfEachCustomer.clear();
	for (int i = 1; i <= nNormals; i++) {

		double minArrivalTime = INT_MAX;
		double maxArrivalTime = 0;
		std::vector<int> daysOfMinArrivalTime;
		std::vector<int> daysOfMaxArrivalTime;
		for (int day = 0; day < nDays; day++) {

			double tempArrivalTime = arrivalTimes[i][day];
			if (tempArrivalTime < minArrivalTime) {

				daysOfMinArrivalTime.clear();
				daysOfMinArrivalTime.push_back(day);
				minArrivalTime = tempArrivalTime;
			}
			else if (tempArrivalTime == minArrivalTime) {

				daysOfMinArrivalTime.push_back(day);
			}
			if (tempArrivalTime > maxArrivalTime) {

				daysOfMaxArrivalTime.clear();
				daysOfMaxArrivalTime.push_back(day);
				maxArrivalTime = tempArrivalTime;
			}
			else if (tempArrivalTime == maxArrivalTime) {

				daysOfMaxArrivalTime.push_back(day);
			}
		}
		daysOfMinArrivalTimeOfEachCustomer[i] = std::vector<int>(daysOfMinArrivalTime);
		daysOfMaxArrivalTimeOfEachCustomer[i] = std::vector<int>(daysOfMaxArrivalTime);
	}
	
	// Start finding. 
	double maxMovingDuration = INT_MAX;
	while(1) {

		// Find the customer with the largest arrival time difference. 
		CustomerAndArrivalTimeDifference customerWithLargestArrivalTimeDifferenceAndItsDifference = getTheCustomerWithLargestArrivalTimeDifference();

		// Get the maximum moving duration and the days that are the most extense. Since we are going to push forward, we only need the day of minimum arrival time. 
		maxMovingDuration = customerWithLargestArrivalTimeDifferenceAndItsDifference.difference;
		int dayOfMinArrivalTime = customerWithLargestArrivalTimeDifferenceAndItsDifference.dayOfMinArrivalTime;
		int dayOfMaxArrivalTime = customerWithLargestArrivalTimeDifferenceAndItsDifference.dayOfMaxArrivalTime;

		// Try to push forward. 
		// Get the customer with largest arrival time difference
		int customerWithLargestArrivalTimeDifference = customerWithLargestArrivalTimeDifferenceAndItsDifference.customer;

		// If it is a fictive node, change to its corresponding normal node. 
		if (correspondingList[customerWithLargestArrivalTimeDifference] > nNormals) {

			customerWithLargestArrivalTimeDifference = correspondingList[customerWithLargestArrivalTimeDifference];
		}

		// Get the position of customer with largest arrival time difference. 
		int positionOfCustomerWithLargestArrivalTimeDifference = 0;
		for (int i = 0; i < solutionListOfEachDay[dayOfMinArrivalTime].size(); i++) {

			if (solutionListOfEachDay[dayOfMinArrivalTime][i] == customerWithLargestArrivalTimeDifference) {

				positionOfCustomerWithLargestArrivalTimeDifference = i;
				break;
			}
		}

		// Get those blocking customer. Calculate their maxPF. 
		maxMovingDuration = std::min(maxMovingDuration, getMaxPF(solutionListOfEachDay, positionOfCustomerWithLargestArrivalTimeDifference, dayOfMinArrivalTime, 0, true));
		std::vector<int>* nodesBeingMovedPtr;
		if (maxMovingDuration > 0) {

			nodesBeingMovedPtr = applyPF(solutionListOfEachDay, positionOfCustomerWithLargestArrivalTimeDifference, dayOfMinArrivalTime, maxMovingDuration, true);
		}
		else {

			break;
		}

		// We have to know which node have been pushed and recalculate their minimum arrival time difference, and maximum arrival time difference. 
		// The nodes in nodesBeingMoved are all normal nodes, not fictive nodes. 
		std::vector<bool> nodesHavingBeenRecalculated(nNodes, false);
		for (int i = 0; i < nodesBeingMovedPtr->size(); i++) {

			int nodeAreGoingToRecalculate = nodesBeingMovedPtr->at(i);
			if (nodesHavingBeenRecalculated[nodeAreGoingToRecalculate]) {

				continue;
			}
			nodesHavingBeenRecalculated[nodeAreGoingToRecalculate] = true;

			double minArrivalTime = INT_MAX;
			std::vector<int> daysOfMinArrivalTime;
			for (int day = 0; day < nDays; day++) {

				double tempArrivalTime = arrivalTimes[nodeAreGoingToRecalculate][day];
				if (tempArrivalTime < minArrivalTime) {

					daysOfMinArrivalTime.clear();
					daysOfMinArrivalTime.push_back(day);
					minArrivalTime = tempArrivalTime;
				}
				else if (tempArrivalTime == minArrivalTime) {

					daysOfMinArrivalTime.push_back(day);
				}
			}
			daysOfMinArrivalTimeOfEachCustomer[nodeAreGoingToRecalculate] = std::vector<int>(daysOfMinArrivalTime);
		}

		// Delete nodesBeingMovedPtr. 
		delete nodesBeingMovedPtr;
	}
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
