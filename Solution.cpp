#include "Solution.h"

bool Solution::isFirstTime = true;

void Solution::input() {
    
    nNodes = 7;
    n_normals = 5;
    n_fictives = 2;
    nRoutes = 3;
    nDays = 3;
    serviceTime = { {15, 15, 15}, {18, 18, 18}, {23, 23, 23}, {45, 45, 45}, {30, 30, 30}, {15, 15, 15}, {18, 18, 18} };
    required = { {1, 1, 1}, {0, 1, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 0}, {1, 1, 1}, {0, 1, 0} };
    earliestTime = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {15, 15, 15}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    lastTime = { {100, 100, 100}, {50, 50, 50}, {30, 30, 30}, {95, 95, 95}, {25, 25, 25}, {80, 80, 80}, {50, 50, 50}, {30, 30, 30} };
    timeMat = { {100000, 12.751, 3.302, 4.6204, 2.6174, 9.0958, 12.751, 3.302},
                {12.751, 100000, 9.8491, 8.2998, 10.341, 5.2756, 100000, 9.8491},
                {3.302, 9.8491, 100000, 2.82, 0.717, 5.809, 9.8491, 100000},
                {4.6204, 8.2998, 2.82, 100000, 2.8158, 5.7838, 8.2998, 2.82},
                {2.6174, 10.341, 0.717, 2.8158, 100000, 6.4784, 10.341, 0.717},
                {9.0958, 5.2756, 5.809, 5.7838, 6.4784, 100000, 5.2756, 5.809},
                {12.751, 100000, 9.8491, 8.2998, 10.341, 5.2756, 100000, 9.8491},
                {3.302, 9.8491, 100000, 2.82, 0.717, 5.809, 9.8491, 100000} };

    solutionList = {0, 1, 5, 0, 4, 0, 6, 3, 0, 2, 1, 5, 0, 4, 0, 7, 6, 0, 1, 0, 0, 6, 3, 0};
}

void Solution::output(){

    int nRoute = nRoutes - 1;
    int nDay = 0;
    for (int i = 0; i < solutionList.size(); i++) {

        if (solutionList[i] == 0) {
            
            nRoute++;
            if (nRoute == nRoutes) {
                
                if (nDay == nDays) {

                    break;
                }
                nDay++;
                nRoute = 0;
                std::cout << std::endl << std::endl <<" Day "<< nDay ;
            }
            std::cout << std::endl <<" = Route "<< nRoute <<" : ";
        }
        else {

            std::cout << "=> " << solutionList[i] << " ";
        }
    }
}

void Solution::solveAlgorithm2() {

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

    std::vector<std::vector<Task>> solutionListOfEachDay;
    std::vector<std::vector<Task>> bestSolution;
	std::vector<std::vector<Task>> currentSolution;
    int bestScore;
	int currentScore;

    // Since we are doing SA, our algorithm will be running several times because nodes on different day can't swtich with each other. 

    // Generate initial datas, like initial solution. 

    for (int i = 0; i < nDays; i++) {

        solutionListOfEachDay.push_back(std::vector<Task>());
        for (int j = 0; j < nNodes; j++) {

            if (required[i][j] == true) {

                solutionListOfEachDay[i].push_back(Task(j));
            }
        }
        std::vector<Task> tempVectorForBoundary(nDays, -1);
        solutionListOfEachDay[i].insert(solutionListOfEachDay[i].end(), tempVectorForBoundary.begin(), tempVectorForBoundary.end());
    }

    // 
    
    for (int t = Ts; t <= Te; t = t * Alpha) {

        for (int iterationNum = 0; iterationNum < Ld; iterationNum) {

            // Tweak the solution
            for (int day = 0; day < nDays; day++) {

                tweakSolutionRandomly(solutionListOfEachDay);
            }

			// Adjust the solution to its best
			adjustDepartureTime(solutionListOfEachDay);

            // Calculate its score
            int newScore = calculateObjective(solutionListOfEachDay);

			// Calculate and subtract the violation score
			newScore -= calculateViolationScore(solutionListOfEachDay, scaleOfViolationScore);
            
            // Store it if it's the best one so far. 
            if (newScore >= bestScore) {

                bestSolution.assign(solutionListOfEachDay.begin(), solutionListOfEachDay.end());
				bestScore = newScore;
            }

            // Judge if it can replace the current one. 
            if (newScore >= currentScore) {

				currentSolution.assign(solutionListOfEachDay.begin(), solutionListOfEachDay.end());
			}
			else {

				if (getRandomDecimal() < exp((newScore - currentScore) / t)) {

					currentSolution.assign(solutionListOfEachDay.begin(), solutionListOfEachDay.end());
					currentScore = newScore;
				}
			}
        }
    }
}

double Solution::getRandomDecimal() {

    return (rand() / RAND_MAX + 1);
}

int Solution::getRandomInteger(int x) {

    return floor(rand() / (RAND_MAX + 1) * x); // The reason why RAND_MAX has to add one is to eliminate the possibility the function return x. 
}

void Solution::tweakSolutionByInsertion(std::vector<std::vector<Task>>& solutionListOfEachDay) {

    for (int day = 0; day < nDays; day++) {

        int positionToChoose = getRandomInteger(solutionListOfEachDay[day].size());
        int positionToInsert = getRandomInteger(solutionListOfEachDay[day].size() - 1);

        Task tempValueForInsertion = Task(solutionListOfEachDay[day][positionToChoose]);
        solutionListOfEachDay[day].erase(solutionListOfEachDay[day].begin() + positionToChoose);
        solutionListOfEachDay[day].insert(solutionListOfEachDay[day].begin() + positionToInsert, tempValueForInsertion);
    }
}

void Solution::tweakSolutionBySwap(std::vector<std::vector<Task>>& solutionListOfEachDay) {

    for (int day = 0; day < nDays; day++) {

        int position1 = getRandomInteger(solutionListOfEachDay[day].size());
        int position2 = getRandomInteger(solutionListOfEachDay[day].size());

        std::swap(solutionListOfEachDay[day][position1], solutionListOfEachDay[day][position2]);
    }
}

void Solution::tweakSolutionByReversion(std::vector<std::vector<Task>>& solutionListOfEachDay) {

    for (int day = 0; day < nDays; day++) {

        int position1 = getRandomInteger(solutionListOfEachDay[day].size());
        int position2 = getRandomInteger(solutionListOfEachDay[day].size());

        int middlePosition = (position1 + position2) / 2;
        int totalOfTwoPositions = position1 + position2;
        for (int i = std::min(position1, position2); i <= middlePosition; i++) {

            std::swap(solutionListOfEachDay[day][i], solutionListOfEachDay[day][totalOfTwoPositions - i]);
        }
    }
}

void Solution::tweakSolutionRandomly(std::vector<std::vector<Task>>& solutionListOfEachDay) {

    int randomChoice = getRandomInteger(3);

    if (randomChoice == 0) {

        tweakSolutionByInsertion(solutionListOfEachDay);
    }
    else if (randomChoice == 1) {

        tweakSolutionBySwap(solutionListOfEachDay);
    }
    else if (randomChoice == 2) {

        tweakSolutionByReversion(solutionListOfEachDay);
    }
    else {

        std::cout << "Error: tweakSolutionRandomly get value out of {0, 1, 2}" << std::endl;
        exit(1);
    }
}

int Solution::calculateObjective(std::vector<std::vector<Task>>& solutionListOfEachDay) {

	
}

int Solution::calculateViolationScore(std::vector<std::vector<Task>>& solutionListOfEachDay, int scaleOfViolationScore) {

	
}

void Solution::adjustDepartureTime(std::vector<std::vector<Task>>& solutionListOfEachDay) {

	
}

// Questions: 
// 
// P.25 This pseudo code shows that it calculate the objective function before step 4, but seems like it perform the function againa after step4 and step5. 
// My question is what is the use of objective function before those optimized functions? 
