#include "LNS.h"

template <class T> 
T in(T item, vector<T> arr){
    for(T it : arr)
        if(it == item)
            return true;
    return false;
}

template <class T> 
T avr(vector<T> arr){
    T ans = 0;
    for(T it : arr)
        ans += it;
    return ans / arr.size();
}

LNS::LNS(){
    
}
LNS::LNS(int _Iter, float _T0, float _Alpha, float _Lambda, float _Nu, float _Xi): 
Iter(_Iter), T0(_T0), Alpha(_Alpha), Lambda(_Lambda), Nu(_Nu), Xi(_Xi){
    // I : number of iterations proceeds from the beginning of the algorithm
    // T0 : represents the initial temperature
    // Alpha : the cooling rate, 0 < Alpha < 1
    // Lambdam, Nu, Xi : used in the related removal operator
}

//void LNS::calculateObjectiveAndadjustDepartureTime(const vector<vector<vector<int>>>& bef){
//    // for calculate obj
//    
//}

void LNS::solve() {

    float T = T0;
    genInitSolution();
    solutionList = curS;    //output();
    for (int i = 0; i < Iter; i++) {
        newS = curS;
        rmdNodes.resize(nDays, {});
        //cout << endl << endl << "   ====  " << i << "  ====" << endl;
        removal();
        solutionList = newS;        //output();

        /*cout << endl << " Removed Nodes " <<endl;
        for (int d = 0; d < nDays; d++) {
            cout << " Day " << d + 1 << " : ";
            for (int i : rmdNodes[d]) cout << i << " ";
            cout << endl;
        }*/
            

        repair();
        solutionList = newS;        //output();
        rmdNodes.clear();
        
        vector<vector<int>> Saft;
        for (const vector<vector<int>>& vvbef : newS) {
            vector<int> v;
            for (const vector<int>& vbef : vvbef) {
                v.insert(v.end(), vbef.begin() + 1, vbef.end() - 1);
                v.push_back(-1);
            }
            v.pop_back();
            Saft.push_back(v);
        }
        calculateObjective(Saft);
        adjustDepartureTime(Saft);
        //if (isFeasible()) improveTimeConsistency(Saft);

        double newScore = getViolationScore(Saft, 100000);
        int r3 = rand()/RAND_MAX;
        if (r3 <= exp((newScore - curScore) / T)) {
            curS = newS;
            curScore = newScore;
        }
        if (newScore < bestScore) {
            bestS = newS;
            bestScore = newScore;
            //std::cout << "Best Score: " << newScore << std::endl;
        }
        T *= Alpha;
    }

    vector<vector<int>> Saft;
    for (const vector<vector<int>>& vvbef : bestS) {
        vector<int> v;
        for (const vector<int>& vbef : vvbef) {
            v.insert(v.end(), vbef.begin() + 1, vbef.end() - 1);
            v.push_back(-1);
        }
        v.pop_back();
        Saft.push_back(v);
    }
    calculateObjective(Saft);
    adjustDepartureTime(Saft);
    CheckConstraintsResult checkConstraintsResult = checkConstraints(Saft);
    //printGraph(Saft, GRAPH_LIMIT);
    std::cout << "Best score: " << bestScore << std::endl;
    /*if (checkConstraintsResult.result == false) {

        std::cout << "Violation detected ----------------------------------" << std::endl;
        for (std::string message : checkConstraintsResult.messages) {

            std::cout << message << std::endl;
        }
        std::cout << "-----------------------------------------------------" << std::endl;
    }*/
}
void LNS::genInitSolution(){
    curS.resize(nDays);
    for(vector<vector<int>>& v : curS){
        v.resize(nRoutes, {0});
    }
    
    vector<int> notInserted(nNormals);
    for(int i = 0; i < nNormals; i++)
        notInserted[i] = i + 1;
    for(int i = 0; i < nNormals; i++)
        swap(notInserted[i], notInserted[rand() % nNormals]);
    for (int& i : notInserted) {
        for (int d = 0; d < nDays; d++) {
            if (required[i][d]) {
                curS[d][rand() % nRoutes].push_back(i);
            }
        }
    }

    notInserted.resize(nFictives);
    for(int i = 0; i < nFictives; i++)
        notInserted[i] = nNormals + i + 1;
    for(int i = 0; i < nFictives; i++)
        swap(notInserted[i], notInserted[rand() % nFictives]);
    for(int& i : notInserted){
        int norm = fictiveLink[i - 1];
        for(int d = 0; d < nDays; d++){
            if(required[i][d]){
                int route;
                bool valid = false;
                while(!valid){
                    valid = true;
                    route = rand() % nRoutes;
                    for(int n : curS[d][route]) if(n == norm) valid = false;
                }
                curS[d][route].push_back(i);
            }
        }
    }        
    for(int i = 0; i < nDays; i++){
        for(int j = 0; j < nRoutes; j++){
            curS[i][j].push_back(0);
        }
    }
}
int LNS::getu(){
    int req_sum = 0;
    for (vector<bool> v : required)
        for (bool b : v)
            req_sum += b ? 1 : 0;
    int up_bnd = fmin(floor(req_sum * 0.4), 30), low_bnd = fmin(ceil(req_sum * 0.1), 30);
    return rand() % (up_bnd - low_bnd) + low_bnd;
}
void LNS::removal(){
    switch (rand() % 5) {
    case 0:
        //cout << "randomRemoval" << endl;
        randomRemoval();
        break;
    case 1:
        //cout << "relatedRemoval" << endl;
        relatedRemoval();
        break;
    case 2:
        //cout << "clusterRemoval" << endl;
        clusterRemoval();
        break;
    case 3:
        //cout << "worstRemoval_timeConsistency" << endl;
        worstRemoval_timeConsistency();
        break;
    case 4:
        //cout << "synchronized_servicesCustomerRemoval" << endl;
        synchronized_servicesCustomerRemoval();
        break;
    }
}
int LNS::rmFromEachday(int node){    
    int ans = 0;
    for(int d = 0; d < nDays; d++){
        rmdNodes[d].push_back(node);
        for(int r = 0; r < nRoutes; r++){
            for(int n = 0; n < newS[d][r].size(); n++){
                if(newS[d][r][n] == node){
                    newS[d][r].erase(newS[d][r].begin() + n);
                    ans++;
                }
            }
        }
    }
    return ans;
}

void LNS::randomRemoval(){
    int u = getu();
    while(u > 0){
        int rmNode;
        while(1){
            rmNode = rand() % nCustomer + 1;
            if(!in(rmNode, rmdNodes[0]))
                break;
        }
        u -= rmFromEachday(rmNode);
    }
}

int LNS::r(int i, int j){
    int ans = nDays;
    for (int d = 0; d < nDays; d++)
        if (required[i][d] != required[j][d])
            ans--;
    return ans;
}

int LNS::R(int i, int j){
    if (i < 0 || i>7 || j > 7 || j < 0) {
        return 0;
    }
    int v=1;
    return Lambda * timeMat[i][j] + v * (abs(avr(required[i]) - avr(required[j]))) + Xi * r(i, j);
}

void LNS::relatedRemoval(){
    int rmNode = rand() % nCustomer + 1, u = getu();
    u -= rmFromEachday(rmNode);
    while(u > 0){
        int refNode = rmdNodes[0][rand() % rmdNodes[0].size()], minSimilarity = INT_MAX;
        for(int n = 1; n <= nCustomer; n++){
            if(!in(n, rmdNodes[0])){
                int similarity = R(refNode, n);
                if(similarity < minSimilarity){
                    minSimilarity = similarity;
                    rmNode = n;
                }
            }
        }
        u -= rmFromEachday(rmNode);
    }
}

vector<int> LNS::findMSTAndCutIntoTwo(vector<int> nodes){
    // return edge
    vector<vector<int>> groups, edges, mst;
    vector<double> times;
    for(int i=0; i<nodes.size(); i++){
        for(int j=i+1; j<nodes.size(); j++){
            edges.push_back({nodes[i], nodes[j]});
            times.push_back(timeMat[nodes[i]][nodes[j]]);
        }
    }
    for(int i=0; i<times.size(); i++){
        for(int j=i+1; j<times.size(); j++){
            if(times[i] > times[j]){
                swap(times[i], times[j]);
                swap(edges[i], edges[j]);
            }
        }
    }
    int maxEdgeIdx = 0;
    for (int e = 0; e < edges.size(); e++) {
        vector<int> edge = edges[e];
        int groupIdxOfij[2] = {-1, -1}; //i, j
        for(int idx=0; idx<groups.size(); idx++){
            if(in(edge[0], groups[idx]))
                groupIdxOfij[0] = idx;
            if(in(edge[1], groups[idx]))
                groupIdxOfij[1] = idx;
        }
        if (groupIdxOfij[0] >= 0 && groupIdxOfij[1] >= 0 && groupIdxOfij[0] != groupIdxOfij[1]) {
            groups[groupIdxOfij[0]].insert(groups[groupIdxOfij[0]].end(), groups[groupIdxOfij[1]].begin(), groups[groupIdxOfij[1]].end());
            groups.erase(groups.begin() + groupIdxOfij[1]);
            mst.push_back(edge);
        }
        else if (groupIdxOfij[0] >= 0 && groupIdxOfij[1] < 0) {
            groups[groupIdxOfij[0]].push_back(edge[1]);
            mst.push_back(edge);
        }
        else if (groupIdxOfij[0] < 0 && groupIdxOfij[1] >= 0) {
            groups[groupIdxOfij[1]].push_back(edge[0]);
            mst.push_back(edge);
        }
        else if (groupIdxOfij[0] < 0 && groupIdxOfij[1] < 0) {
            groups.push_back({ edge[0], edge[1] });
            mst.push_back(edge);
        }
        else continue;
        maxEdgeIdx = e;
    }
    mst.pop_back();
    vector<int>localRmdNodes = { edges[maxEdgeIdx][rand() % 2] }, curRmdNodes = localRmdNodes;
    while (curRmdNodes.size() > 0) {
        vector<int> newCurRmdNodes;
        int idxMst = 0;
        while(idxMst < mst.size()){
            bool rmd = false;
            for (int rmdNode : curRmdNodes) {
                if (idxMst >= mst.size())
                    break;
                for (int i : {0, 1}) {
                    if (mst[idxMst][i] == rmdNode) {
                        newCurRmdNodes.push_back(mst[idxMst][1 - i]);
                        localRmdNodes.push_back(mst[idxMst][1 - i]);
                        mst.erase(mst.begin() + idxMst);
                        rmd = true;
                        break;
                    }
                }
            }
            if(!rmd) idxMst++;
        }
        curRmdNodes = newCurRmdNodes;
    }
    return localRmdNodes;
}

void LNS::clusterRemoval(){
    for(int day = 0; day < nDays; day++){
        set<int>  routesLessThan3Node;
        for (int route = 0; route < nRoutes; route++)
            if (newS[day][route].size() < 5)
                routesLessThan3Node.insert(route);

        int u = getu();
        while(u > 0 && routesLessThan3Node.size() < nRoutes){
            int route = rand() % nRoutes;
            while (newS[day][route].size() < 5)
                route = rand() % nRoutes;
                
            vector<int> tmpNodes(newS[day][route].begin() + 1, newS[day][route].end() - 1);
            vector<int> newNodes = findMSTAndCutIntoTwo(tmpNodes);

            for (int node : tmpNodes)
                if (!in(node, newNodes))
                    rmdNodes[day].push_back(node);

            u -= newS[day][route].size() - newNodes.size() - 2;
            newS[day][route] = { 0, 0 };
            newS[day][route].insert(newS[day][route].begin() + 1, newNodes.begin(), newNodes.end());
            
            if (newS[day][route].size() < 5)
                routesLessThan3Node.insert(route);
        }
    }
}

void LNS::worstRemoval_timeConsistency(){
    int u = getu();
    vector<int> priorityList, numOfDrivers, arrivalTimeDiff;

    for (int node = 1; node <= nCustomer; node++) {
        priorityList.push_back(node);

        set<int> diffRoutes;
        int arrivalTimeMin = INT_MAX, arrivalTimeMax = 0;
        for (int d = 0; d < nDays; d++) {
            for (int r = 0; r < nRoutes; r++) {
                for (int n : newS[d][r]) {
                    if (n == node) {
                        diffRoutes.insert(r);
                    }
                }
            }
            arrivalTimeMin = fmin(arrivalTimeMin, arrivalTimes[node][d]);
            arrivalTimeMax = fmax(arrivalTimeMax, arrivalTimes[node][d]);
        }
        numOfDrivers.push_back(diffRoutes.size());
        arrivalTimeDiff.push_back(arrivalTimeMax - arrivalTimeMin);
    }

    for (int i = 0; i < u; i++) {
        for (int j = i; j < nCustomer; j++) {
            if (numOfDrivers[i] < numOfDrivers[j] || (numOfDrivers[i] == numOfDrivers[j] && arrivalTimeDiff[i] < arrivalTimeDiff[j])) {
                swap(priorityList[i], priorityList[j]);
                swap(numOfDrivers[i], numOfDrivers[j]);
                swap(arrivalTimeDiff[i], arrivalTimeDiff[j]);
            }
        }
    }

    for (int i = 0; i < u; i++)
        rmFromEachday(priorityList[i]);
}
void LNS::synchronized_servicesCustomerRemoval(){
    for(int i = nNormals + 1; i <= nCustomer; i++)
        rmFromEachday(i);
}
void LNS::repair(){
    switch (rand() % 2) {
    case 0:
        //cout << endl << " greedyRepair" << endl;
        greedyRepair();
        break;
    case 1:
        //cout << endl << " regretRepair" << endl;
        regretRepair();
        break;
    }
}
void LNS::greedyRepair(){
    for(int d = 0; d < nDays; d++){        
        vector<int> tmpRmd = rmdNodes[d];
        while(tmpRmd.size() > 0){
            double minCost = 100000.0;
            int bestIdxInRmd = -1, bestRoute, bestIdxInRut;
            for(int nodeIdx = 0; nodeIdx < tmpRmd.size(); nodeIdx++){
                int node = tmpRmd[nodeIdx];
                if(!required[node][d])
                    continue;           
                for(int j = 0; j < nRoutes; j++){
                    for(int k = 1; k < newS[d][j].size(); k++){
                        double cost = timeMat[node][newS[d][j][k]] + timeMat[node][newS[d][j][k - 1]];
                        if(cost < minCost){
                            minCost = cost;
                            bestRoute = j;
                            bestIdxInRut = k;
                            bestIdxInRmd = nodeIdx;
                        }
                    }
                }
            }
            if(bestIdxInRmd == -1)
                break;
            newS[d][bestRoute].insert(newS[d][bestRoute].begin() + bestIdxInRut, tmpRmd[bestIdxInRmd]);
            tmpRmd.erase(tmpRmd.begin()+bestIdxInRmd);
        }
    }
}
void LNS::regretRepair(){
    for(int d = 0; d < nDays; d++){
        vector<int> tmpRmd;
        for(int node : rmdNodes[d])
            if(required[node][d])
                tmpRmd.push_back(node);                     
        while(tmpRmd.size() > 0){
            double maxDiff = 0;
            int bestIdxInRmd = -1, bestRoute, bestIdxInRut;
            for(int nodeIdx = 0; nodeIdx < tmpRmd.size(); nodeIdx++){
                double minCost1 = 100000.0, minCost2 = 100000.0;
                int bestIdxInRmd1 = -1, bestRoute1, bestIdxInRut1;
                int node = tmpRmd[nodeIdx];                      
                for(int j = 0; j < nRoutes; j++){
                    for(int k = 1; k < newS[d][j].size(); k++){
                        double cost = timeMat[node][newS[d][j][k]] + timeMat[node][newS[d][j][k - 1]];
                        if(cost < minCost1){
                            minCost2 = minCost1;
                            minCost1 = cost;
                            bestRoute1 = j;
                            bestIdxInRut1 = k;
                            bestIdxInRmd1 = nodeIdx;
                        }
                        else if(cost < minCost2){
                            minCost2 = cost;
                        }
                    }
                }
                if(minCost2 - minCost1 >= maxDiff){
                    maxDiff = minCost2 - minCost1;
                    bestIdxInRmd = bestIdxInRmd1;
                    bestRoute = bestRoute1;
                    bestIdxInRut = bestIdxInRut1;
                }
            }
            newS[d][bestRoute].insert(newS[d][bestRoute].begin() + bestIdxInRut, tmpRmd[bestIdxInRmd]);
            tmpRmd.erase(tmpRmd.begin()+bestIdxInRmd);
        }
    }
}

    
