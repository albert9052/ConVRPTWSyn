#include "Solution.h"
using namespace std;

struct aSolution {
    vector<vector<vector<int>>> list;
    vector<vector<double>> arrivalTimes;
    double score;
};

class LNS :  public Solution
{
private:
    int Iter;
    float T0, Alpha, Lambda, Nu, Xi;

    aSolution bestS, curS, newS;

    //double bestScore = (double)INT_MAX, curScore = (double)INT_MAX;
    //vector<vector<vector<int>>> bestS, curS, newS;
    
    vector<vector<int>> rmdNodes; //day * tmp rmd nodes, 1~nNodes

    void genInitSolution();

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
    vector<int> findMSTAndCutIntoTwo(vector<int> nodes);

    void insertion();
    void randomInsertion();
    void greedyInsertion();
    void regretInsertion(int);
    void earliestInsertion();
    void latestInsertion();

    vector<vector<vector<int>>> transFormat(const vector<vector<int>>& v);
    vector<vector<int>> transFormat(const vector<vector<vector<int>>>& v);
    //void calculateObjectiveAndadjustDepartureTime(const vector<vector<vector<int>>>& bef);
public:
    LNS();
    LNS(int Iter, float T0, float Alpha, float Lambda, float Nu, float Xi);
    void solve();
};

