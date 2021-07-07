#include "LNS.h"

template <class T> 
T in(T item, vector<T> arr){
    for(T& it : arr)
        if(it == item)
            return true;
    return false;
}

LNS::LNS(){
    
}
LNS::LNS(int _Iter, float _T0, float _Alpha, float _Lambdam, float _Nu, float _Xi): 
Iter(_Iter), T0(_T0), Alpha(_Alpha), Lambdam(_Lambdam), Nu(_Nu), Xi(_Xi){
    // I : number of iterations proceeds from the beginning of the algorithm
    // T0 : represents the initial temperature
    // Alpha : the cooling rate, 0 < Alpha < 1
    // Lambdam, Nu, Xi : used in the related removal operator
}
void LNS::solve() {
    float T = T0;
    vector<int> S = genInitSolution();
    for (int i = 0; i < /*Iter*/10; i++) {
        cout <<endl <<endl<<"   ====  "<<i<<"  ====" <<endl;
        removal();
        cout<<" ==== rmdNodes : ";
        for(int i : rmdNodes) cout<<i<<" "; 
        cout<<endl;
        repair();
        rmdNodes.clear();
        /*float Fbef, Faft = calculateObjective(S);
        adjustDepartureTime();
        if (isFeasible()) ImproveTimeConsistency();
        int r3 = rand() % 2;
        if (r3 <= exp((Fbef - Faft) / T))S = Saft;
        Fbest = fmax(Fbest, Faft);
        T *= Alpha;*/
    }

}
vector<int> LNS::genInitSolution(){
    S.resize(nDays);
    for(vector<vector<int>>& v : S){
        v.resize(nRoutes, {0});
    }
    
    vector<int> notInserted(nNormals);
    for(int i = 0; i < nNormals; i++)
        notInserted[i] = i;
    for(int i = 0; i < nNormals; i++)
        swap(notInserted[i], notInserted[rand() % nNormals]);
    for(int& i : notInserted)
        for(int d = 0; d < nDays; d++)
            if(required[i][d])
                S[d][rand() % nRoutes].push_back(i + 1);

    notInserted.resize(nFictives);
    for(int i = 0; i < nFictives; i++)
        notInserted[i] = nNormals + i;
    for(int i = 0; i < nFictives; i++)
        swap(notInserted[i], notInserted[rand() % nFictives]);
    for(int& i : notInserted){
        int norm = fictiveLink[i];
        for(int d = 0; d < nDays; d++){
            if(required[i][d]){
                int route;
                bool valid = false;
                while(!valid){
                    valid = true;
                    route = rand() % nRoutes;
                    for(int n : S[d][route]) if(n == norm) valid = false;               
                }
                S[d][route].push_back(i + 1);
            }
        }
    }        
    for(int i = 0; i < nDays; i++){
        for(int j = 0; j < nRoutes; j++){
            S[i][j].push_back(0);
        }
    }
    solutionList = S;
    output();
}
void LNS::removal(){
    int req_sum = 0;
    for (vector<bool> v : required)
        for (bool b : v)
            req_sum += b ? 1 : 0;
    int up_bnd = fmin(floor(req_sum * 0.4), 30), low_bnd = fmin(ceil(req_sum * 0.1), 30);
    int u = rand() % (up_bnd - low_bnd) + low_bnd;
    switch (/*rand() % 5*/0) {
    case 0:
        randomRemoval(u);
        break;
    case 1:
        relatedRemoval(u);
        break;
    case 2:
        clusterRemoval(u);
        break;
    case 3:
        worstRemoval_timeConsistency(u);
        break;
    case 4:
        synchronized_servicesCustomerRemoval(u);
        break;
    }
}
int LNS::rmFromEachday(int node){
    int ans = 0;
    for(int i = 0; i < nDays; i++){
        for(int j = 0; j < nRoutes; j++){
            for(int k = 0; k < S[i][j].size(); k++){
                if(S[i][j][k] == node){
                    S[i][j].erase(S[i][j].begin() + k);
                    ans++;
                }
            }
        }
    }
    return ans;
}
void LNS::randomRemoval(int u){
    while(u > 0){
        int rmNode;
        while(1){
            rmNode = rand() % nNodes + 1;
            if(!in(rmNode, rmdNodes))
                break;
        }
        rmdNodes.push_back(rmNode);
        u -= rmFromEachday(rmNode);
    }
    solutionList = S;
    output();
}
void LNS::relatedRemoval(int u){
    int initNode = rand() % nNodes + 1;
    u -= rmFromEachday(initNode);
    rmdNodes.push_back(initNode);
    while(u > 0){
        int refNode = rmdNodes[rand() % rmdNodes.size()];
        
    }
}
void LNS::clusterRemoval(int u){
    
}
void LNS::worstRemoval_timeConsistency(int u){
    
}
void LNS::synchronized_servicesCustomerRemoval(int u){
    
}
void LNS::repair(){
    switch (/*rand() % 2*/1) {
    case 0:
        greedyRepair();
        break;
    case 1:
        regretRepair();
        break;
    }
}
void LNS::greedyRepair(){
    for(int i = 0; i < nDays; i++){        
        vector<int> tmpRmd = rmdNodes;
        while(tmpRmd.size() > 0){
            double minCost = 100000.0;
            int bestIdxInRmd = -1, bestRoute, bestIdxInRut;
            for(int nodeIdx = 0; nodeIdx < tmpRmd.size(); nodeIdx++){
                int node = tmpRmd[nodeIdx];
                if(!required[node-1][i])
                    continue;           
                for(int j = 0; j < nRoutes; j++){
                    for(int k = 1; k < S[i][j].size(); k++){
                        double cost = timeMat[node][S[i][j][k]] + timeMat[node][S[i][j][k - 1]];
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
            S[i][bestRoute].insert(S[i][bestRoute].begin() + bestIdxInRut, tmpRmd[bestIdxInRmd]);
            tmpRmd.erase(tmpRmd.begin()+bestIdxInRmd);
        }
    }
    solutionList = S;
    output();
}
void LNS::regretRepair(){
    for(int i = 0; i < nDays; i++){
        cout<<"repair"<<i<<" : ";  
        vector<int> tmpRmd;
        for(int node : rmdNodes)
            if(required[node-1][i])
                tmpRmd.push_back(node);                     
        while(tmpRmd.size() > 0){
            double maxDiff = 0;
            int bestIdxInRmd = -1, bestRoute, bestIdxInRut;
            for(int nodeIdx = 0; nodeIdx < tmpRmd.size(); nodeIdx++){
                double minCost1 = 100000.0, minCost2 = 100000.0;
                int bestIdxInRmd1 = -1, bestRoute1, bestIdxInRut1;
                int node = tmpRmd[nodeIdx];                      
                for(int j = 0; j < nRoutes; j++){
                    for(int k = 1; k < S[i][j].size(); k++){
                        double cost = timeMat[node][S[i][j][k]] + timeMat[node][S[i][j][k - 1]];
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
            cout<<tmpRmd[bestIdxInRmd]<<" ";
            S[i][bestRoute].insert(S[i][bestRoute].begin() + bestIdxInRut, tmpRmd[bestIdxInRmd]);
            tmpRmd.erase(tmpRmd.begin()+bestIdxInRmd);
        }
        cout<<endl;
    }
    solutionList = S;
    output();
}
void LNS::adjustDepartureTime(){
    
}

    