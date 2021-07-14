#include "Solution.h"
using namespace std;

class LNS :  public Solution
{
private:
    int Iter;
    float T0, Alpha, Lambda, Nu, Xi;

    vector<vector<vector<int>>> S;
    vector<int> rmdNodes; //tmp rmd nodes, 1~nNodes

    vector<int> genInitSolution();

    void removal();
    void randomRemoval();
    void relatedRemoval();
    void clusterRemoval();
    void worstRemoval_timeConsistency();
    void synchronized_servicesCustomerRemoval();
    int rmFromEachday(int node);
    int R(int i, int j);
    int r(int i, int j);
    int getu();

    void repair();
    void greedyRepair();
    void regretRepair();
    vector<int> getMinCost(int day, vector<int> rmd, double& minCost);

    void adjustDepartureTime();
public:
    LNS();
    LNS(int Iter, float T0, float Alpha, float Lambda, float Nu, float Xi);
    void solve();
};

