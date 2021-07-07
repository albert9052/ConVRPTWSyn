#include "Solution.h"
using namespace std;

class LNS :  public Solution
{
private:
    int Iter;
    float T0, Alpha, Lambdam, Nu, Xi;

    vector<vector<vector<int>>> S;
    vector<int> rmdNodes; //tmp rmd nodes, 1~nNodes

    vector<int> genInitSolution();

    void removal();
    void randomRemoval(int u);
    void relatedRemoval(int u);
    void clusterRemoval(int u);
    void worstRemoval_timeConsistency(int u);
    void synchronized_servicesCustomerRemoval(int u);
    int rmFromEachday(int node);

    void repair();
    void greedyRepair();
    void regretRepair();
    vector<int> getMinCost(int day, vector<int> rmd, double& minCost);

    void adjustDepartureTime();
public:
    LNS();
    LNS(int Iter, float T0, float Alpha, float Lambdam, float Nu, float Xi);
    void solve();
};

