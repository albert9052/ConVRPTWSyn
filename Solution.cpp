#include "Solution.h"
#define GRAPH_LIMIT 200

void Solution::input() {
    
	nCustomer = 7;
    nNodes = 8;
    nNormals = 5;
    nFictives = 2;
    nRoutes = 3;
    nDays = 3;
    fictiveLink = {0, 0, 0, 0, 0, 1, 2};
    serviceTime = { {15, 15, 15}, {18, 18, 18}, {23, 23, 23}, {45, 45, 45}, {30, 30, 30}, {15, 15, 15}, {18, 18, 18}, {18, 18, 18}, {23, 23, 23} };
    required = { {1, 1, 1}, {0, 1, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 0}, {1, 1, 1}, {0, 1, 0}, {0, 1, 0}, {1, 0, 1} };
    earliestTime = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {15, 15, 15}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    lastTime = { {100, 100, 100}, {50, 50, 50}, {30, 30, 30}, {95, 95, 95}, {25, 25, 25}, {80, 80, 80}, {50, 50, 50}, {30, 30, 30}, {50, 50, 50}, {30, 30, 30} };
    timeMat = { {100000, 12.751, 3.302, 4.6204, 2.6174, 9.0958, 12.751, 3.302},
                {12.751, 100000, 9.8491, 8.2998, 10.341, 5.2756, 100000, 9.8491},
                {3.302, 9.8491, 100000, 2.82, 0.717, 5.809, 9.8491, 100000},
                {4.6204, 8.2998, 2.82, 100000, 2.8158, 5.7838, 8.2998, 2.82},
                {2.6174, 10.341, 0.717, 2.8158, 100000, 6.4784, 10.341, 0.717},
                {9.0958, 5.2756, 5.809, 5.7838, 6.4784, 100000, 5.2756, 5.809},
                {12.751, 100000, 9.8491, 8.2998, 10.341, 5.2756, 100000, 9.8491},
                {3.302, 9.8491, 100000, 2.82, 0.717, 5.809, 9.8491, 100000} };

    // below are data processing
	requiredList.resize(nDays);
	for (int n = 0; n < nCustomer; n++)
		for (int d = 0; d < nDays; d++)
			if (required[n][d])
				requiredList[d].push_back(n);
}

void Solution::output(){
    for(int i = 0; i < nDays; i++){
        std::cout << "Day " << i + 1 << std::endl;
        for(int j = 0; j < nRoutes; j++){
            std::cout << "   Route " << j + 1 << ":";
            for(int& k : solutionList[i][j]){
                std::cout << " => " << k;
            }
            std::cout << std::endl;
        }
    }
    /*int nRoute = 1;
    int nDay = 1;
    std::cout << std::endl << std::endl << " Day 1";
    std::cout << std::endl << "   Route 1 :";
    for (int i = 0; i < solutionList.size(); i++) {
        if (solutionList[i] == 0) 
            continue;
        if (solutionList[i] == -1) {            
            nRoute++;
            if (nRoute > nRoutes) {
                if (nDay == nDays)
                    break;
                nDay++;
                nRoute = 1;
                std::cout << std::endl << std::endl << " Day " << nDay ;
            }
            std::cout << std::endl << "   Route " << nRoute << " : ";
        }
        else {
            std::cout << "=> " << solutionList[i] << " ";
        }
    }
    std::cout << std::endl << std::endl;*/
}

void Solution::calculateObjective(std::vector<std::vector<int>>& solutionListOfEachDay) {

	// Directly arrange the arrival time (only consider commuting time and service time). 
	for (int day = 0; day < nDays; day++) {

		double currentTime = earliestTime[0][day];
		int previousNode = 0;
		for (int j = 0; j < solutionListOfEachDay[day].size(); j++) {

			int currentNode = solutionListOfEachDay[day][j];
			if (currentNode == -1) {

				// Next routes
				currentTime = earliestTime[0][day];
				previousNode = 0;
				continue;
			}
			double commutingTime = timeMat[previousNode][currentNode];
			arrivalTimes[currentNode][day] = currentTime + commutingTime;
			currentTime = arrivalTimes[currentNode][day] + serviceTime[currentNode][day];
			departureTimes[currentNode][day] = currentTime;
			previousNode = currentNode;
		}
	}
	std::cout << "Diretly arraning the arrival time successes. " << std::endl;
	printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	std::cout << "///////////////" << std::endl;
	std::cout << "6's arrival time: " << arrivalTimes[6][1] << std::endl;
	std::cout << "6's departure time: " << departureTimes[6][1] << std::endl;
	std::cout << "///////////////" << std::endl;

	// Rearrange the arrival time to minimize the violation of time windows. 
	// Needs to consider 0's last time. (IMPORTANT)
	for (int day = 0; day < nDays; day++) {

		int numberOfGoodNodes = 0;
		int numberOfBadNodes = 0;
		std::vector<TypeAndDuration> typesAndDurations;
		for (int i = solutionListOfEachDay[day].size() - 1; i >= 0; i--) {

			int currentNode = solutionListOfEachDay[day][i];
			if (currentNode == -1) {

				typesAndDurations.clear();
				continue;
			}

			int previousNode = 0;
			if (i != 0) {

				previousNode = solutionListOfEachDay[day][i - 1];
				if (previousNode == -1) {

					previousNode = 0;
				}
			}

			int nextNode = 0;
			if (i != solutionListOfEachDay[day].size() - 1) {

				nextNode = solutionListOfEachDay[day][i + 1];
				if (nextNode == -1) {

					nextNode = 0;
				}
			}
			
			if (arrivalTimes[currentNode][day] < earliestTime[currentNode][day]) {

				numberOfGoodNodes++;

				// Start moving. 
				// Find the movingDuration. 
				double targetDuration = earliestTime[currentNode][day] - arrivalTimes[currentNode][day];
				double movingDuration = 0;
				while (numberOfGoodNodes > numberOfBadNodes) {

					movingDuration = typesAndDurations.end() -> duration;
					if (movingDuration < targetDuration) {

						int movingType = typesAndDurations.end() -> type;
						typesAndDurations.pop_back();

						switch(movingType) {

						case 0:
							std::cout << "Error: There should be no 0 in movingType. (In function calculateObjective)" << std::endl;
							exit(1);
							break;
						case 1:
							numberOfBadNodes++;
							break;
						case 2:
							numberOfGoodNodes++;
							break;
						case 3:
							numberOfGoodNodes--;
							numberOfBadNodes++;
							break;
						case 4:
							numberOfGoodNodes--;
							break;
						}
					}
					else {

						movingDuration = targetDuration;
						break;
					}
				}
				
				// Move the current node and the nodes that will be pushed. 
				arrivalTimes[currentNode][day] += movingDuration;
				departureTimes[currentNode][day] += movingDuration;
				postponedDuration[day][previousNode][currentNode] += movingDuration;
				int previousNodeForPushing = currentNode;
				for (int j = i + 1; j < solutionListOfEachDay[day].size(); j++) {

					int currentNodeForPushing = solutionListOfEachDay[day][j];
					movingDuration -= postponedDuration[day][previousNodeForPushing][currentNodeForPushing];
					if (movingDuration <= 0) {

						postponedDuration[day][previousNodeForPushing][currentNodeForPushing] -= movingDuration;
						break;
					}
					postponedDuration[day][previousNodeForPushing][currentNodeForPushing] = 0;
					arrivalTimes[currentNodeForPushing][day] += movingDuration;
					departureTimes[currentNodeForPushing][day] += movingDuration;
					previousNodeForPushing = currentNodeForPushing;
				}
			}

			// Readjust typesAndDurations
			for (int j = 0; j < typesAndDurations.size(); j++) {

				typesAndDurations[j].duration += (timeMat[currentNode][nextNode] + serviceTime[currentNode][day]);
			}

			// Add new time stamp, which is TypeAndDuration. 
			double tempDuration = earliestTime[currentNode][day] - arrivalTimes[currentNode][day] + postponedDuration[day][previousNode][currentNode];
			if (tempDuration > 0) {

				typesAndDurations.push_back(TypeAndDuration(4, tempDuration));
			}
			
			tempDuration = lastTime[currentNode][day] - arrivalTimes[currentNode][day] + postponedDuration[day][previousNode][currentNode];
			if (tempDuration > 0) {

				typesAndDurations.push_back(TypeAndDuration(1, tempDuration));
			}

			if (arrivalTimes[currentNode][day] < earliestTime[currentNode][day]) {

				numberOfGoodNodes++;
			}
			else if (arrivalTimes[currentNode][day] >= lastTime[currentNode][day]) {

				numberOfBadNodes++;
			}

			// Reorder typesAndDurations (Decreasing)
			// This can be optimized, since most of them were sorted before. 
			std::sort(typesAndDurations.begin(), typesAndDurations.end(), std::greater<TypeAndDuration>());
		}
	}
	std::cout << "Rearranging the arrival time to minimize the violation of time window successes. " << std::endl;
	printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	
	// Rearrange the arrival time of each synchronized service. 
	// Haven't consider about 0's last time (latest time). This needs to be implemented. 
	// Needs to check the part about duration. (TypeAndDuration)
	while (1) {

		for (int day = 0; day < nDays; day++) {

			std::vector<int> wholeList = solutionListOfEachDay[day];

			// Sort all synchronized nodes
			std::vector<std::vector<int>> nonSortedLists = std::vector<std::vector<int>>(nRoutes);;
			int temp = 0; 
			for (int i = 0; i < wholeList.size(); i++) {

				if (wholeList[i] == -1) {

					temp++;
					continue;
				}
				nonSortedLists[temp].push_back(wholeList[i]);
			}

			int* currentIndexes = new int[nRoutes];
			std::memset(currentIndexes, 0, nRoutes);
			int lengthOfSortedList = 0;
			for (int i = 0; i < nRoutes; i++) {

				lengthOfSortedList += nonSortedLists[i].size();
			}
			std::vector<int> sortedList = std::vector<int>(lengthOfSortedList);
			while(1) {

				int smallest = std::numeric_limits<int>::max();
				bool finished = true;
				int chosenOne = 0;
				for (int i = 0; i < nRoutes; i++) {

					if (currentIndexes[i] >= nonSortedLists[i].size()) {

						continue;
					}
					int currentNode = nonSortedLists[i][currentIndexes[i]];
					if (correspondingList[currentNode - 1] == 0) {

						currentIndexes[i]++;
						i--;
						continue;
					}
					if (arrivalTimes[currentNode][day] < smallest) {

						chosenOne = i;
						finished = false;
					}
				}
				if (finished == true) {

					break;
				}
				currentIndexes[chosenOne]++;
				sortedList.push_back(smallest);
			}

			while (1) {

				// Get the earliest. 
				int chosenOne = sortedList[0];
				int correspondingOne = correspondingList[chosenOne];

				// If the normal and fictive node are on the same route, don't try to reduce the violation. 
				int routeOfTheChosenOne = 0;
				bool onTheSameRoute = false;
				for (int i = 0; i < nRoutes; i++) {

					if (std::find(nonSortedLists[i].begin(), nonSortedLists[i].end(), chosenOne) != nonSortedLists[i].end()) {

						if (std::find(nonSortedLists[i].begin(), nonSortedLists[i].end(), correspondingOne) != nonSortedLists[i].end()) {

							onTheSameRoute = true;
							break;
						}
						else {

							break;
						}
					}
				}
				if (onTheSameRoute) {
				
					// Remove the picked one and its corresponding node. 
					sortedList.erase(std::find(sortedList.begin(), sortedList.end(), chosenOne));
					sortedList.erase(std::find(sortedList.begin(), sortedList.end(), correspondingOne));
					
					// Make sure that we still have elements in sortedList, or we will need to break this loop. 
					if (sortedList.size() == 0) {

						break;
					}

					continue;
				}

				// Find all the nodes that will be affected
				int chosenRoute = 0;
				int positionOfChosenNode = 0;
				int* affectedNodes = NULL;
				int lengthOfAffectedNodes = 0;
				for (int j = 0; j < nRoutes; j++) {

					auto position = std::find(nonSortedLists[j].begin(), nonSortedLists[j].end(), chosenOne);
					if (position != nonSortedLists[j].end()) {

						positionOfChosenNode = (int)(position - nonSortedLists[j].begin());
						lengthOfAffectedNodes = nonSortedLists[j].size() - positionOfChosenNode;
						affectedNodes = new int[lengthOfAffectedNodes];
						int tempIndex = 0;
						for (int k = positionOfChosenNode + 1; k < nonSortedLists[j].size(); k++) {

							affectedNodes[tempIndex] = nonSortedLists[j][k];
							tempIndex++;
						}
						chosenRoute = j;
						break;
					}
				}

				// Calculate how long it would take to postpone to match its corresponding node. 
				int maxPostponedDuration = arrivalTimes[correspondingOne][day] - arrivalTimes[chosenOne][day];
			
				// Calculate all the maximum distance that each node which will be affected if we move the node we picked before can move. 
				// In order to get our maximum moving distance for the picked node. 
				// If the duration is longer than the maxPostponedDuration, there's no reason to record it, since we can only postpone that much time. 
				// This part has problem. Need to be fixed. 
				int numberOfGoodNodes = 1; // We already got a good node which is the one we are targeting. 
				int numberOfBadNodes = 0;
				std::vector<TypeAndDuration> typesAndDurations;

				int previousNode = chosenOne;
				double accumulatedPostponedDuration = postponedDuration[day][previousNode][affectedNodes[0]];
				for (int j = 0; j < lengthOfAffectedNodes; j++) {

					int theOneToCalculate = affectedNodes[j];
					if (arrivalTimes[theOneToCalculate][day] < earliestTime[theOneToCalculate][day]) {

						typesAndDurations.push_back(TypeAndDuration(2, accumulatedPostponedDuration));
						double duration = (earliestTime[theOneToCalculate][day] - arrivalTimes[theOneToCalculate][day] + accumulatedPostponedDuration);
						if (duration < maxPostponedDuration) {

							typesAndDurations.push_back(TypeAndDuration(4, duration));
						}
					}
					else if (arrivalTimes[theOneToCalculate][day] >= lastTime[theOneToCalculate][day]) {

						typesAndDurations.push_back(TypeAndDuration(1, accumulatedPostponedDuration));
					}
					else {

						double duration = (lastTime[theOneToCalculate][day] - arrivalTimes[theOneToCalculate][day] + accumulatedPostponedDuration);
						if (duration < maxPostponedDuration) {

							typesAndDurations.push_back(TypeAndDuration(1, duration));
						}
					}

					if (correspondingList[theOneToCalculate] != 0) {

						if (arrivalTimes[correspondingList[theOneToCalculate]][day] <= arrivalTimes[theOneToCalculate][day]) {

							typesAndDurations.push_back(TypeAndDuration(1, accumulatedPostponedDuration));
						}
						else {

							typesAndDurations.push_back(TypeAndDuration(2, accumulatedPostponedDuration));
							double duration = (arrivalTimes[correspondingList[theOneToCalculate]][day] - arrivalTimes[theOneToCalculate][day] + accumulatedPostponedDuration);
							if (duration < maxPostponedDuration) {

								typesAndDurations.push_back(TypeAndDuration(3, duration));
							}
						}
					}

					accumulatedPostponedDuration += postponedDuration[day][previousNode][theOneToCalculate];
					// If the accumulated postponed duration is already larger than the amount we want to push, break it. 
					if (accumulatedPostponedDuration >= maxPostponedDuration) {

						break;
					}
					previousNode = theOneToCalculate;
				}

				// put our goal in it. 
				typesAndDurations.push_back(TypeAndDuration(0, maxPostponedDuration));

				// Sort the durations and types together. 
				// This part needs to be checked, once we finished other parts. 
				std::sort(typesAndDurations.begin(), typesAndDurations.end());
				
				// By go over the durations and types, we can get our best moving distance. 
				double currentPostponedDuration = 0;
				for (int j = 0; j < typesAndDurations.size(); j++) {

					if (numberOfGoodNodes > numberOfBadNodes) {

						currentPostponedDuration = typesAndDurations[j].duration;
						if (typesAndDurations[j].type == 0) {

							break;
						}
						switch(typesAndDurations[j].type) {

						case 1:
							numberOfBadNodes++;
							break;
						case 2: 
							numberOfGoodNodes++;
							break;
						case 3: 
							numberOfGoodNodes++;
							numberOfBadNodes++;
							break;
						case 4:
							numberOfGoodNodes--;
							break;
						default:

							std::cout << "Error occurred when we try to find our best moving distance by going over the durations and types. " << std::endl;
							exit(1);
						}
					}
					else {

						break;
					}
				}

				// Postpone it by currentPostpondDuration. 
				previousNode = 0; // Have been defined before. May need to come up a way to fix this problem. Or may not?
				for (int j = 0; j < solutionListOfEachDay[day].size(); j++) {

					if (solutionListOfEachDay[day][j] == chosenOne) {

						arrivalTimes[chosenOne][day] += currentPostponedDuration;
						previousNode = solutionListOfEachDay[day][j];
						for (int k = j + 1; k < solutionListOfEachDay[day].size(); k++) {

							if (solutionListOfEachDay[day][k] == -1) {

								break;
							}
							currentPostponedDuration -= postponedDuration[day][previousNode][solutionListOfEachDay[day][k]];
							if (currentPostponedDuration <= 0) {

								break;
							}
							arrivalTimes[solutionListOfEachDay[day][k]][day] += currentPostponedDuration;
							departureTimes[solutionListOfEachDay[day][k]][day] += currentPostponedDuration;
							previousNode = solutionListOfEachDay[day][k];
						}
						break;
					}
					previousNode = solutionListOfEachDay[day][j];
				}
				
				// Remove the picked one and its corresponding node. 
				sortedList.erase(std::find(sortedList.begin(), sortedList.end(), chosenOne));
				sortedList.erase(std::find(sortedList.begin(), sortedList.end(), correspondingOne));

				// Then, rearrange every node, since the arrival time of some of them has been changed. 
				for (int j = sortedList.size() - 1; j >= 1; j--) { 

					if (arrivalTimes[sortedList[j]][day] < arrivalTimes[sortedList[j - 1]][day]) {

						std::swap(sortedList[j], sortedList[j - 1]);
						for (int k = j; k < sortedList.size() - 1; k++) {

							if (arrivalTimes[sortedList[k]][day] < arrivalTimes[sortedList[k + 1]][day]) {

								std::swap(sortedList[k], sortedList[k + 1]);
							}
							else {

								break;
							}
						}
					}
				}
				
				// Make sure that we still have elements in sortedList, or we will need to break this loop. 
				if (sortedList.size() == 0) {

					break;
				}
			}
		}
	}
	std::cout << "Rearranging the arrival time of each synchronized service successes. " << std::endl;
}

// Width: 159 characters. 
void Solution::printGraph(const std::vector<std::vector<int>>& solutionListOfEachDay, double limit) {

	for (int day = 0; day < nDays; day++) {

		std::cout << "Day " << day << ": ";
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			std::cout << solutionListOfEachDay[day][i] << " ";
		}
		std::cout << std::endl << std::endl;
		std::vector<PointAndType> pointsAndTypes;

		int route = 1;
		std::cout << "Route 1: " << std::endl;
		double unit = 10.0 / 159.0 * GRAPH_LIMIT;
		for (int i = 0; i < 4; i++) {

			std::cout << " ";
		}
		for (int i = 1; i <= 15; i++) {

			std::cout << std::setfill(' ') << std::setw(10) << std::left << unit * i;
		}
		std::cout << std::endl;
		printVerticalLines(2);

		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			int currentNode = solutionListOfEachDay[day][i];
			if (currentNode == -1) {

				int currentCursor = 0;
				for (int i = 0; i < pointsAndTypes.size(); i++) {

					if (pointsAndTypes[i].point > currentCursor) {

						for (int j = 0; j < pointsAndTypes[i].point - currentCursor; j++) {

							std::cout << "-";
						}
						currentCursor = pointsAndTypes[i].point;
					}
					else if (pointsAndTypes[i].point < currentCursor) {

						continue;
					}

					if (pointsAndTypes[i].type == 1) {

						std::cout << "\033[1;42m" << pointsAndTypes[i].value << "\033[0m";
					}
					else if (pointsAndTypes[i].type == 2) {

						std::cout << "\033[1;41m" << pointsAndTypes[i].value << "\033[0m";
					}

					currentCursor++;
				}
				std::cout << std::endl;
				printVerticalLines(1);

				pointsAndTypes.clear();

				route++;
				std::cout << "Route " << route << ":  |";
				for (int i = 1; i <= 14; i++) {

					for (int j = 0; j < 9; j++) {

						std::cout << " ";
					}
					std::cout << "|";
				}
				std::cout << std::endl;
				printVerticalLines(1);

				continue;
			}

			if (arrivalTimes[currentNode][day] > limit) {

				continue;
			}

			int point = std::floor(arrivalTimes[currentNode][day] / limit * 159);
			pointsAndTypes.push_back(PointAndType(point, 1, currentNode));

			if (departureTimes[currentNode][day] > limit) {

				continue;
			}

			point = std::floor(departureTimes[currentNode][day] / limit * 159);
			pointsAndTypes.push_back(PointAndType(point, 2, currentNode));
		}
	}
}

void Solution::printVerticalLines(int lines) {

	for (int k = 0; k < lines; k++) {

		std::cout << " ";
		for (int i = 1; i <= 15; i++) {

			for (int j = 0; j < 9; j++) {

				std::cout << " ";
			}
			std::cout << "|";
		}
		std::cout << std::endl;
	}
}
