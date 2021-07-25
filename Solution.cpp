#include "Solution.h"

void Solution::input() {
    
	nCustomer = 7;
    nNodes = 8;
    nNormals = 5;
    nFictives = 2;
    nRoutes = 3;
    nDays = 3;
    fictiveLink = {0, 0, 0, 0, 0, 1, 2};
    serviceTime = { {0, 0, 0}, {15, 15, 15}, {18, 18, 18}, {23, 23, 23}, {45, 45, 45}, {30, 30, 30}, {15, 15, 15}, {18, 18, 18} };
    required = { {0, 0, 0}, {1, 1, 1}, {0, 1, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 0}, {1, 1, 1}, {0, 1, 0} };
    earliestTime = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {15, 15, 15}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    lastTime = { {100, 100, 100}, {50, 50, 50}, {30, 30, 30}, {95, 95, 95}, {25, 25, 25}, {80, 80, 80}, {50, 50, 50}, {30, 30, 30} };
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
	//std::cout << "Diretly arraning the arrival time successes. " << std::endl;
	//printGraph(solutionListOfEachDay, GRAPH_LIMIT);

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

				//std::cout << "////////////" << std::endl;
				//std::cout << "Postpone This One" << std::endl;
				//std::cout << "Day: " << day << ", node: " << currentNode << std::endl;
				//std::cout << "////////////" << std::endl;

				numberOfGoodNodes++;

				// Start moving. 
				// Find the movingDuration. 
				double targetDuration = earliestTime[currentNode][day] - arrivalTimes[currentNode][day];
				double movingDuration = targetDuration;
				//std::cout << "CurrentNode: " << currentNode << std::endl;
				while (numberOfGoodNodes > numberOfBadNodes && typesAndDurations.size() > 0) {

					movingDuration = (typesAndDurations.end() - 1) -> duration;
					//std::cout << "(" << numberOfGoodNodes << ", " << numberOfBadNodes << ") Processing " << (typesAndDurations.end() - 1) -> type << " / " << (typesAndDurations.end() - 1) -> duration << std::endl;
					if (movingDuration < targetDuration) {

						int movingType = (typesAndDurations.end() - 1) -> type;
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
						// Because this node has been pushed to its best. 
						numberOfGoodNodes--;
						break;
					}
				}
				
				// Move the current node and the nodes that will be pushed. 
				//std::cout << "Size: " << typesAndDurations.size() << ", moving duration: " << movingDuration << std::endl;
				arrivalTimes[currentNode][day] += movingDuration;
				departureTimes[currentNode][day] += movingDuration;
				postponedDuration[day][previousNode][currentNode] += movingDuration;
				int previousNodeForPushing = currentNode;
				for (int j = i + 1; j < solutionListOfEachDay[day].size(); j++) {

					int currentNodeForPushing = solutionListOfEachDay[day][j];
					if (currentNodeForPushing == -1) {

						break;
					}
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

			// No need for this section, because you don't need to adjust typesAndDurations everytime. you can use some objects or drawings to help yourself understand this. 
			// Readjust typesAndDurations
			//for (int j = 0; j < typesAndDurations.size(); j++) {

			//	//typesAndDurations[j].duration += (timeMat[currentNode][nextNode] + serviceTime[currentNode][day]);
			//	typesAndDurations[j].duration += postponedDuration[day][previousNode][currentNode];
			//}

			// Add new timestamp, whose data type is TypeAndDuration. 
			double tempDuration = earliestTime[currentNode][day] - arrivalTimes[currentNode][day];
			if (tempDuration > 0) {

				typesAndDurations.push_back(TypeAndDuration(2, postponedDuration[day][previousNode][currentNode]));
				typesAndDurations.push_back(TypeAndDuration(4, tempDuration + postponedDuration[day][previousNode][currentNode]));
			}
			
			tempDuration = lastTime[currentNode][day] - arrivalTimes[currentNode][day];
			if (tempDuration > 0) {

				typesAndDurations.push_back(TypeAndDuration(1, tempDuration + postponedDuration[day][previousNode][currentNode]));
			}
			else {

				typesAndDurations.push_back(TypeAndDuration(1, postponedDuration[day][previousNode][currentNode]));
			}

			// No need for this section, because we have done this above. If the while loop is broken by the else in it, then numberOfGoodNodes--. On the other hand, it won't subtract 1 from numberOfGoodNodes. 
			//if (arrivalTimes[currentNode][day] < earliestTime[currentNode][day]) {

			//	numberOfGoodNodes++;
			//}
			//else if (arrivalTimes[currentNode][day] >= lastTime[currentNode][day]) {

			//	numberOfBadNodes++;
			//}

			// Reorder typesAndDurations (Decreasing)
			// This can be optimized, since most of them were sorted before. 
			std::sort(typesAndDurations.begin(), typesAndDurations.end(), std::greater<TypeAndDuration>());
		}
	}
	//std::cout << "Rearranging the arrival time to minimize the violation of time window successes. " << std::endl;
	//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	
	// Rearrange the arrival time of each synchronized service. 
	// Haven't consider about 0's last time (latest time). This needs to be implemented. 
	// Needs to check the part about duration. (TypeAndDuration)
	for (int day = 0; day < nDays; day++) {
		
		//std::cout << "Day " << day << " started. " << std::endl;

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

		//std::cout << "nonSortedLists: " << std::endl;
		//for (int i = 0; i < nRoutes; i++) {

		//	for (int j = 0; j < nonSortedLists[i].size(); j++) {

		//		std::cout << nonSortedLists[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}

		int* currentIndexes = new int[nRoutes];
		for (int i = 0; i < nRoutes; i++) {

			currentIndexes[i] = 0;
		}
		std::vector<int> sortedList;
		while(1) {

			int smallest = std::numeric_limits<int>::max();
			bool finished = true;
			int chosenRoute = 0;
			for (int i = 0; i < nRoutes; i++) {

				if (currentIndexes[i] >= nonSortedLists[i].size()) {

					continue;
				}
				int currentNode = nonSortedLists[i][currentIndexes[i]];
				//std::cout << "Examine " << currentNode << std::endl;
				if (correspondingList[currentNode] == 0) {

					currentIndexes[i]++;
					i--;
					continue;
				}
				//std::cout << "Start compare " << currentNode << std::endl;
				if (arrivalTimes[currentNode][day] < smallest) {

					chosenRoute = i;
					finished = false;
					smallest = arrivalTimes[currentNode][day];
				}
			}
			if (finished == true) {

				break;
			}
			//std::cout << "chosenRoute: " << chosenRoute << ", nonSortedLists[chosenRoute][currentIndexes[chosenRoute]]: " << nonSortedLists[chosenRoute][currentIndexes[chosenRoute]] << std::endl;
			sortedList.push_back(nonSortedLists[chosenRoute][currentIndexes[chosenRoute]]);
			currentIndexes[chosenRoute]++;
		}
		//std::cout << "Sort result: " << std::endl;
		//for (int result : sortedList) {

		//	std::cout << result << " ";
		//}
		//std::cout << std::endl;
		//std::cout << "Sort completed" << std::endl;

		// If sortedList is empty, it means that there's no synchronized service on this day. 
		if (sortedList.size() != 0) {

			while (1) {

				//std::cout << "while loop started, length of sortedList: " << sortedList.size() << std::endl;
				// Get the earliest. 
				int chosenOne = sortedList[0];
				int correspondingOne = correspondingList[chosenOne];

				// If the normal and fictive node are on the same route, don't try to reduce the violation. 
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
						lengthOfAffectedNodes = nonSortedLists[j].size() - positionOfChosenNode - 1;
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
				//std::cout << "Finding all the nodes that will be affected completed" << std::endl;
				//std::cout << "Affected nodes: " << std::endl;
				//for (int j = 0; j < lengthOfAffectedNodes; j++) {

				//	std::cout << affectedNodes[j] << " ";
				//}
				//std::cout << std::endl;

				// Calculate how long it would take to postpone to match its corresponding node. 
				int maxPostponedDuration = arrivalTimes[correspondingOne][day] - arrivalTimes[chosenOne][day];
				//std::cout << "Day: " << day << std::endl;
				//std::cout << "Node " << chosenOne << " needs to move " << maxPostponedDuration << std::endl;
				//std::cout << "Corresponding node: " << correspondingOne << std::endl;
				//std::cout << arrivalTimes[chosenOne][day] << " / " << arrivalTimes[correspondingOne][day] << std::endl;
				//std::cout << "/////////" << std::endl;
				//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
				//std::cout << "/////////" << std::endl;
				
				// For the next part, get typesAndDurations. 
				int numberOfGoodNodes = 1; // We already got a good node which is the one we are targeting. 
				int numberOfBadNodes = 0;
				std::vector<TypeAndDuration> typesAndDurations;

				// Also need to take its own time window into consideration. 
				if (earliestTime[chosenOne][day] > arrivalTimes[chosenOne][day]) {

					//std::cout << "earliest time: " << earliestTime[chosenOne][day] << ", arrival time: " << arrivalTimes[chosenOne][day] << std::endl;
					numberOfGoodNodes++;
					double duration = earliestTime[chosenOne][day] - arrivalTimes[chosenOne][day];
					typesAndDurations.push_back(TypeAndDuration(4, duration));
				}
				if (lastTime[chosenOne][day] > arrivalTimes[chosenOne][day]) {

					double duration = lastTime[chosenOne][day] - arrivalTimes[chosenOne][day];
					typesAndDurations.push_back(TypeAndDuration(1, duration));
				}
				else {

					numberOfBadNodes++;
				}

				// If there are affected nodes, you need to calculate how far you gonna push. 
				if (lengthOfAffectedNodes != 0) {
			
					// Calculate all the maximum distance that each node which will be affected if we move the node we picked before can move. 
					// In order to get our maximum moving distance for the picked node. 
					// If the duration is longer than the maxPostponedDuration, there's no reason to record it, since we can only postpone that much time. 
					// This part has problem. Need to be fixed. 
					int previousNode = chosenOne;
					double accumulatedPostponedDuration = postponedDuration[day][previousNode][affectedNodes[0]];
					for (int j = 0; j < lengthOfAffectedNodes; j++) {

						//std::cout << "Start for loop!!!" << std::endl;
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

						//std::cout << "theOneToCalculate:  " << theOneToCalculate << ", day:  " << day << std::endl;

						// Deal with the synchronized one. 
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
						//std::cout << "Initialize typesAndDurations finished" << std::endl;

						accumulatedPostponedDuration += postponedDuration[day][previousNode][theOneToCalculate];
						// If the accumulated postponed duration is already larger than the amount we want to push, break it. 
						if (accumulatedPostponedDuration >= maxPostponedDuration) {

							break;
						}
						previousNode = theOneToCalculate;
					}
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
				int previousNode = 0;
				for (int j = 0; j < solutionListOfEachDay[day].size(); j++) {

					if (solutionListOfEachDay[day][j] == chosenOne) {

						//std::cout << "Current postponed duration: " << currentPostponedDuration << std::endl;
						arrivalTimes[chosenOne][day] += currentPostponedDuration;
						departureTimes[chosenOne][day] += currentPostponedDuration;
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
		//std::cout << "Day " << day << " finished. " << std::endl;
	}
	//std::cout << "Rearranging the arrival time of each synchronized service successes. " << std::endl;
	//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
}

double Solution::getMaxPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double accumulatedPostponedDuration, bool firstLoop) {

	//std::cout << "getMaxPF started" << std::endl;
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

		//std::cout << "seciont 1" << std::endl;
		//std::cout << "currentNode: " << currentNode << std::endl;

		// If currentNode is a fictive node, then we need to translate it into its original number. 
		int normalNode = 1;
		if (currentNode <= nNormals) {

			normalNode = currentNode;
		}
		else {

			normalNode = correspondingList[currentNode];
		}

		std::vector<int> daysOfMinArrivalTime = daysOfMinArrivalTimeOfEachCustomer[normalNode];
		std::vector<int> daysOfMaxArrivalTime = daysOfMaxArrivalTimeOfEachCustomer[normalNode];

		// Check how far it can move according to whether it will increase the objective score. 
		if (std::find(daysOfMaxArrivalTime.begin(), daysOfMaxArrivalTime.end(), normalNode) != daysOfMaxArrivalTime.end()) {

			maxPF = std::min(maxPF, accumulatedPostponedDuration);
		}
		else {

			double duration = arrivalTimes[daysOfMaxArrivalTime[0]][day] - arrivalTimes[normalNode][day] + accumulatedPostponedDuration;
			maxPF = std::min(maxPF, duration);
		}

		// Check how far it can move according to whether it will exceeds its own time window. 
		double duration = lastTime[currentNode][day] - arrivalTimes[currentNode][day];
		maxPF = std::min(maxPF, duration);

		//std::cout << "seciont 2" << std::endl;
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
			
			// Check if we have taken this route into consideration. 
			if (std::find(routesHavingBeenCalculated.begin(), routesHavingBeenCalculated.end(), routeOfCorrespondingNode) == routesHavingBeenCalculated.end()) {

				routesHavingBeenCalculated.push_back(routeOfCorrespondingNode);

				// Check if there are other node ahead of corresponding node. 
				if (positionOfCorrespondingNode + 1 < solutionListOfEachDay[day].size() && solutionListOfEachDay[day][positionOfCorrespondingNode] != -1) {

					double accumulatedPostponedDurationForAnotherRoute;
					accumulatedPostponedDurationForAnotherRoute = accumulatedPostponedDuration + postponedDuration[day][correspondingNode][solutionListOfEachDay[day][positionOfCorrespondingNode + 1]];
					maxPF = std::min(maxPF, getMaxPF(solutionListOfEachDay, positionOfCorrespondingNode + 1, day, accumulatedPostponedDurationForAnotherRoute, false));
				}
			}
		}
		//std::cout << "seciont 3" << std::endl;

		accumulatedPostponedDuration += postponedDuration[day][currentNode][nextNode];
		positionOfNode++;
	}

	return maxPF;
}

// Assume all the synchronized service has no violation. 
// This function needs to be adjusted to use daysOfMinArrivalTimeDifferenceOfEachCustomer and daysOfMaxArrivalTimeDifferenceOfEachCustomer. 
CustomerAndArrivalTimeDifference Solution::getTheCustomerWithLargestArrivalTimeDifference() {

	int theChosenOne = 1;
	double valueOfTheChosenOne = 0;
	int dayOfMinArrivalTime = 0;
	int dayOfMaxArrivalTime = 0;
	for (int i = 1; i <= nNormals; i++) {

		//std::cout << i << ", " << daysOfMaxArrivalTimeOfEachCustomer[i].size() << ", " << daysOfMinArrivalTimeOfEachCustomer[i].size() << std::endl;
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

std::vector<int>* Solution::applyPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double PF, bool firstLoop) {

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
void Solution::adjustDepartureTime(std::vector<std::vector<int>>& solutionListOfEachDay) {

	// Calculate daysOfMinArrivalTimeOfEachCustomer, and daysOfMaxArrivalTimeOfEachCustomer
	// To fill 0's position. 
	for (int i = 1; i <= nNormals; i++) {

		daysOfMinArrivalTimeOfEachCustomer[i].clear();
		daysOfMaxArrivalTimeOfEachCustomer[i].clear();
		double minArrivalTime = INT_MAX;
		double maxArrivalTime = -1;
		for (int day = 0; day < nDays; day++) {

			if (required[i][day] == false) {

				continue;
			}
			double tempArrivalTime = arrivalTimes[i][day];
			if (tempArrivalTime < minArrivalTime) {

				daysOfMinArrivalTimeOfEachCustomer[i].clear();
				daysOfMinArrivalTimeOfEachCustomer[i].push_back(day);
				minArrivalTime = tempArrivalTime;
			}
			else if (tempArrivalTime == minArrivalTime) {

				daysOfMinArrivalTimeOfEachCustomer[i].push_back(day);
			}
			if (tempArrivalTime > maxArrivalTime) {

				daysOfMaxArrivalTimeOfEachCustomer[i].clear();
				daysOfMaxArrivalTimeOfEachCustomer[i].push_back(day);
				maxArrivalTime = tempArrivalTime;
			}
			else if (tempArrivalTime == maxArrivalTime) {

				daysOfMaxArrivalTimeOfEachCustomer[i].push_back(day);
			}
		}
	}
	//std::cout << "Initializing daysOfMinArrivalTimeOfEachCustomer and daysOfMaxArrivalTimeOfEachCustomer finished. " << std::endl;
	//for (int i = 1; i <= nNormals; i++) {

	//	std::cout << "Node " << i << ": (";
	//	std::cout << daysOfMinArrivalTimeOfEachCustomer[i][0];
	//	for (int j = 1; j < daysOfMinArrivalTimeOfEachCustomer[i].size(); j++) {

	//		std::cout << ", " << daysOfMinArrivalTimeOfEachCustomer[i][j];
	//	}
	//	std::cout << " / " << daysOfMaxArrivalTimeOfEachCustomer[i][0];
	//	for (int j = 1; j < daysOfMaxArrivalTimeOfEachCustomer[i].size(); j++) {

	//		std::cout << ", " << daysOfMaxArrivalTimeOfEachCustomer[i][j];
	//	}
	//	std::cout << ")" << std::endl;
	//}
	
	// Start finding. 
	double maxMovingDuration = INT_MAX;
	while(1) {
		
		//std::cout << "///////////////////////////////////////////////////////////////////////////////////////" << std::endl;
		//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
		//std::cout << "///////////////////////////////////////////////////////////////////////////////////////" << std::endl;
		//for (int i = 1; i <= nNormals; i++) {

		//	std::cout << "Node " << i << ": (";
		//	std::cout << arrivalTimes[i][daysOfMinArrivalTimeOfEachCustomer[i][0]] << ", " << arrivalTimes[i][daysOfMaxArrivalTimeOfEachCustomer[i][0]] << ") " << std::endl;
		//}
		//for (int i = 1; i <= nNormals; i++) {

		//	std::cout << "Node " << i << ": (";
		//	std::cout << daysOfMinArrivalTimeOfEachCustomer[i][0];
		//	for (int j = 1; j < daysOfMinArrivalTimeOfEachCustomer[i].size(); j++) {

		//		std::cout << ", " << daysOfMinArrivalTimeOfEachCustomer[i][j];
		//	}
		//	std::cout << " / " << daysOfMaxArrivalTimeOfEachCustomer[i][0];
		//	for (int j = 1; j < daysOfMaxArrivalTimeOfEachCustomer[i].size(); j++) {

		//		std::cout << ", " << daysOfMaxArrivalTimeOfEachCustomer[i][j];
		//	}
		//	std::cout << ")" << std::endl;
		//}

		// Find the customer with the largest arrival time difference. 
		CustomerAndArrivalTimeDifference customerWithLargestArrivalTimeDifferenceAndItsDifference = getTheCustomerWithLargestArrivalTimeDifference();
		//std::cout << "Getting customer with largest arrival time difference finished. " << std::endl;
		//std::cout << "We got " << customerWithLargestArrivalTimeDifferenceAndItsDifference.customer << std::endl;
		//std::cout << "Difference:  " << customerWithLargestArrivalTimeDifferenceAndItsDifference.difference << std::endl;

		// Get the maximum moving duration and the days that are the most extense. Since we are going to push forward, we only need the day of minimum arrival time. 
		maxMovingDuration = customerWithLargestArrivalTimeDifferenceAndItsDifference.difference;
		int dayOfMinArrivalTime = customerWithLargestArrivalTimeDifferenceAndItsDifference.dayOfMinArrivalTime;
		int dayOfMaxArrivalTime = customerWithLargestArrivalTimeDifferenceAndItsDifference.dayOfMaxArrivalTime;

		// Try to push forward. 
		// Get the customer with largest arrival time difference
		int customerWithLargestArrivalTimeDifference = customerWithLargestArrivalTimeDifferenceAndItsDifference.customer;

		// We don't need this section anymore, because we had already avoid calculating fictive nodes. 
		// If it is a fictive node, change to its corresponding normal node. 
		//if (correspondingList[customerWithLargestArrivalTimeDifference] > nNormals) {

		//	customerWithLargestArrivalTimeDifference = correspondingList[customerWithLargestArrivalTimeDifference];
		//}

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
		//std::cout << "Getting maxMovingDuration finished. " << std::endl;
		//std::cout << "maxMovingDuration: " << maxMovingDuration << std::endl;

		// Apply PF. 
		std::vector<int>* nodesBeingMovedPtr;
		if (maxMovingDuration > 0) {

			nodesBeingMovedPtr = applyPF(solutionListOfEachDay, positionOfCustomerWithLargestArrivalTimeDifference, dayOfMinArrivalTime, maxMovingDuration, true);
			//std::cout << "nodesBeingMoved: ";
			//for (int t = 0; t < nodesBeingMovedPtr->size(); t++) {

			//	std::cout << nodesBeingMovedPtr->at(t) << ", ";
			//}
			//std::cout << std::endl;
			//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
		}
		else {

			// Break this while loop. 
			break;
		}

		// We have to know which node have been pushed and recalculate their minimum arrival time difference and maximum arrival time difference. 
		// The nodes in nodesBeingMoved are all normal nodes, not fictive nodes. 
		std::vector<bool> nodesHavingBeenRecalculated(nNodes, false);
		for (int i = 0; i < nodesBeingMovedPtr->size(); i++) {

			int nodeBeingGoingToRecalculate = nodesBeingMovedPtr->at(i);
			if (nodesHavingBeenRecalculated[nodeBeingGoingToRecalculate]) {

				continue;
			}
			nodesHavingBeenRecalculated[nodeBeingGoingToRecalculate] = true;

			daysOfMinArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
			daysOfMaxArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
			double minArrivalTime = INT_MAX;
			double maxArrivalTime = -1;
			for (int day = 0; day < nDays; day++) {

				if (required[nodeBeingGoingToRecalculate][day] == false) {

					continue;
				}
				double tempArrivalTime = arrivalTimes[nodeBeingGoingToRecalculate][day];
				if (tempArrivalTime < minArrivalTime) {

					daysOfMinArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
					daysOfMinArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
					minArrivalTime = tempArrivalTime;
				}
				else if (tempArrivalTime == minArrivalTime) {

					daysOfMinArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
				}
				if (tempArrivalTime > maxArrivalTime) {

					daysOfMaxArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
					daysOfMaxArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
					maxArrivalTime = tempArrivalTime;
				}
				else if (tempArrivalTime == maxArrivalTime) {

					daysOfMaxArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
				}
			}
		}

		// Delete nodesBeingMovedPtr. 
		delete nodesBeingMovedPtr;
		//std::cout << "While done" << std::endl;
		//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
		//std::cin.get();
	}
}

int Solution::getViolationScore(const std::vector<std::vector<int>>& solutionListOfEachDay, int scaleOfViolationScore) {

	int violation = 0;
	for (int day = 0; day < nDays; day++) {

		for (int currentNode = 1; currentNode <= nNormals; currentNode++) {

			if (required[currentNode][day] == false) {

				continue;
			}
			if (earliestTime[currentNode][day] > arrivalTimes[currentNode][day]) {

				violation += earliestTime[currentNode][day] - arrivalTimes[currentNode][day];
			}
			if (lastTime[currentNode][day] < arrivalTimes[currentNode][day]) {

				violation += arrivalTimes[currentNode][day] - lastTime[currentNode][day];
			}
			if (correspondingList[currentNode] != 0) {

				int correspondingNode = correspondingList[currentNode];
				if (arrivalTimes[currentNode][day] != arrivalTimes[correspondingNode][day]) {

					violation += abs(arrivalTimes[currentNode][day] - arrivalTimes[correspondingNode][day]);
				}
			}
		}
	}
	return violation * scaleOfViolationScore;
}

int Solution::getObjectiveScore(const std::vector<std::vector<int>>& solutionListOfEachDay) {

	int score = 0;
	for (int i = 1; i <= nNormals; i++) {

		int minArrivalTime = INT_MAX;
		int maxArrivalTime = -1;
		for (int day = 0; day < nDays; day++) {

			if (required[i][day] == false) {

				continue;
			}
			if (arrivalTimes[i][day] < minArrivalTime) {

				minArrivalTime = arrivalTimes[i][day];
			}
			if (arrivalTimes[i][day] > maxArrivalTime) {

				maxArrivalTime = arrivalTimes[i][day];
			}
			if (correspondingList[i] != 0) {

				if (arrivalTimes[correspondingList[i]][day] < minArrivalTime) {

					minArrivalTime = arrivalTimes[correspondingList[i]][day];
				}
				if (arrivalTimes[correspondingList[i]][day] > maxArrivalTime) {

					maxArrivalTime = arrivalTimes[correspondingList[i]][day];
				}
			}
		}
		score += maxArrivalTime - minArrivalTime;
	}
	return score;
}

// Width: 159 characters. 
void Solution::printGraph(const std::vector<std::vector<int>>& solutionListOfEachDay, double limit) {

	for (int day = 0; day < nDays; day++) {

		//if (day != 0) continue;
		std::cout << "\033[1;33mDay " << day << ": \033[0m";
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			std::cout << solutionListOfEachDay[day][i] << " ";
		}
		std::cout << std::endl;
		std::cout << "Arrival time: " << std::endl;
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			if (solutionListOfEachDay[day][i] != -1) {

				std::cout << solutionListOfEachDay[day][i] << ": " << arrivalTimes[solutionListOfEachDay[day][i]][day] << std::endl;
			}
		}
		std::cout << std::endl;
		std::cout << "Departure time: " << std::endl;
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			if (solutionListOfEachDay[day][i] != -1) {

				std::cout << solutionListOfEachDay[day][i] << ": " << departureTimes[solutionListOfEachDay[day][i]][day] << std::endl;
			}
		}
		std::cout << std::endl;

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

				printTimeLine(pointsAndTypes);

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

				pointsAndTypes.clear();

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
		printTimeLine(pointsAndTypes);
		std::cout << std::endl;
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

void Solution::printTimeLine(const std::vector<PointAndType>& pointsAndTypes) {

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
}
