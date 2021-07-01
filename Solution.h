#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>



class Solution {
public:

    int nNodes; // Number of nodes
    int n_normals; // Number of normal nodes
    int n_fictives; // Number of fictive nodes
    int nDays; // Number of days
    int nRoutes; // Number of routes

    std::vector<std::vector<bool>> required; // Required day (false for not required, true for required.)
    std::vector<int> synchronizedServiceMatrix; // If j is i's fictive node, then synchronizedServiceMatrix[i] and synchronizedServiceMatrix[j] will be i and j. 
    std::vector<std::vector<float>> serviceTime, earliestTime, lastTime; 
    std::vector<std::vector<float>> timeMat; // Commuting time between each nodes
    std::vector<int> solutionList; // Indexes of nodes, ex:1~6, 0 for the boundary of day, -1 for the boundary of route

    Solution() {

        input();
    }
    void input();
    void output();
    virtual void solve() = 0;
    int calculateObjective();

};

#endif
