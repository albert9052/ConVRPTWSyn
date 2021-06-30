#pragma once
#include <string>

//variable
const int X = 0;
const int Y = 1;
const int XBEST = 2;
const int USED = 3;

int fBest;
int * xBest;
int * x; // solution representation;
int * y;
int * selected;
float * visitTime;
float ** distanceMatrix;
float ** instance;
float a;
float t;
float tMax;
float t0;
int i;
int iIter;
int nNodes;
int dummyZeroIndex;
bool isDebug;



//method
void readData(std::string input);
void createRandomInitialSolution();
void startSA();
void calculateDistanceMatrix();
void removeArrayIndex(int index, int count);
int calculateObjectiveFunction(int solType, bool print);
void copySolution(int from, int to);
void swap();
void insertion();
void reversion();
void print(int type);
void storeData(std::string out);
void localSearch();