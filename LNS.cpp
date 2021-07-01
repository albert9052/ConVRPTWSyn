#include "LNS.h"

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
    for (int i = 0; i < Iter; i++) {
        removal();
        repair();
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
    for(vector<vector<int>>& v : S)
        v.resize(nRoutes);

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
        int norm = fictiveLink[i] - 1;
        for(int d = 0; d < nDays; d++){
            if(required[norm][d]){
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
        

    solutionList = S;
    output();
}
void LNS::removal(){
    int req_sum = 0;
    for (vector<bool> v : required)
        for (bool b : v)
            req_sum += b ? 1 : 0;
    int up_bnd = fmin(ceil(req_sum * 0.4), 30), low_bnd = fmin(round(req_sum * 0.1), 30);
    int u = rand() % (up_bnd - low_bnd) + low_bnd;
    switch (rand() % 5) {
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
void LNS::randomRemoval(int u){
    while(u > 0){
        int rmNode = rand() % nNodes;
    }
}
void LNS::relatedRemoval(int u){
    
}
void LNS::clusterRemoval(int u){
    
}
void LNS::worstRemoval_timeConsistency(int u){
    
}
void LNS::synchronized_servicesCustomerRemoval(int u){
    
}
void LNS::repair(){
    switch (rand() % 2) {
    case 0:
        greedyRepair();
        break;
    case 1:
        regretRepair();
        break;
    }
}
void LNS::greedyRepair(){
    
}
void LNS::regretRepair(){
    
}
void LNS::adjustDepartureTime(){
    
}

    