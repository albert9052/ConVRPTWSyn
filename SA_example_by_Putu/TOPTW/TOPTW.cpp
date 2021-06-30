// TOPTW.cpp : main project file.

#include "stdafx.h"
#include "TOPTW.h"
#include <iostream>
#include <time.h>
#include <math.h> 
#include <fstream>
#include <time.h>

using namespace std;
using std::cout;

/* Return a random number between 0 and 1 */
#define getSRand()	((double)rand() / (double)RAND_MAX)

int main()
{
	isDebug = false;
	t0 = 0.1;
	a = 0.99;
	iIter = 101*2000;
	tMax = 0.099;

	// Random number generator
	// Seed number = time(NULL)
	srand(time(NULL));

	clock_t begin = clock();

	readData("input.txt");
	calculateDistanceMatrix();
	
	startSA();

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "TIME:" << elapsed_secs << endl;

	delete xBest;
	delete x; // solution representation;
	delete y;
	delete selected;
	delete visitTime;
	delete distanceMatrix;
	delete instance;
    return 0;
}

void startSA() {
	int objY;
	int objX;

	//generate initial solution
	createRandomInitialSolution();

	//set parameter
	t = t0;
	i = 0;
	objX = calculateObjectiveFunction(X, false);
	fBest = objX;
	//if (isDebug) 
	cout << "Random fbest: " << fBest << endl;
	copySolution(X,XBEST);
	int count = 0;
	bool working = true;
	while (working)
	{
		float p = getSRand();
		if (p < 0.33) {
			//swap 0-0,33
			swap();
		}
		else if (p > 0.66) {
			//reversion 0.66-1
			reversion();
		}
		else {
			//insertion 0.33-0.66
			insertion();
		}

		i += 1;

		objY = calculateObjectiveFunction(Y, false);
		//objX = calculateObjectiveFunction(X);
		int delta = objY - objX ;

		if ( delta >= 0 ) {
			copySolution(Y, X);
			objX = objY;
		}
		else {
			float r = getSRand();
			if (r < exp(delta / t)) {
				copySolution(Y, X);
				objX = objY;
			}
		}

		if (objX > fBest) {
			copySolution(X, XBEST);
			fBest = objX;

		}

		if (i == iIter) {
			t *= a;

			i = 0;

			//perform local search TODO
			localSearch();
			count++;
		}

		//cout << "x: " << objX << endl;
		//print(X);

		//check termination
		if (t<tMax) {
			working = false;
		}
	}
	
	cout << "fBest: " << fBest<< endl;
	copySolution(XBEST, X);
	calculateObjectiveFunction(X, false);
	print(XBEST);
	print(USED);

	cout << count;
}

void localSearch() {
	for (int i = 0; i < nNodes-1; i++)
	{
		for (int j = i+1; j < nNodes; j++)
		{
			copySolution(XBEST,Y);
			int temp = y[i];
			y[i] = y[j];
			y[j] = temp;
			int objY = calculateObjectiveFunction(Y, false);
			
			if (objY > fBest) {
				cout << "LOCAL SEARCH GET BEST" << fBest << " " << objY << endl;
				copySolution(Y, XBEST);
				fBest = objY;
				
			}
		}
	}
}

void swap() {
	copySolution(X, Y);
	int r1 ;
	int r2 ; 

	while (r1 == r2) {
		r1 = rand() % (nNodes - 1);
		r2 = rand() % (nNodes - 1);

		while (r1 == dummyZeroIndex) {
			r1 = rand() % (nNodes - 1);
		}
		while (r2 == dummyZeroIndex) {
			r2 = rand() % (nNodes - 1);
		}
	}

	//cout << "r1: " << r1 << " r2: " << r2;

	int temp = y[r1];
	y[r1] = y[r2];
	y[r2] = temp;
}

void insertion() {
	copySolution(X, Y);
	int r1 ;
	int r2 ;

	//int count = 0;
	while (r1 == r2) {
		//if(count>0)cout << "same";
		r1 = rand() % (nNodes - 1);
		r2 = rand() % (nNodes - 1);

		while (r1 == dummyZeroIndex) {
			r1 = rand() % (nNodes - 1);
		}
		while (r2 == dummyZeroIndex) {
			r2 = rand() % (nNodes - 1);
		}
		//count++;
	}
	//system("PAUSE");
	if (r1 > r2) {
		int temp = y[r1];
		for (int i = r1; i > r2; i--)
		{	
			if (y[i] == 0) continue;
			if (y[i - 1] == 0) y[i] = y[i - 2];
			else y[i] = y[i - 1];			
		}
		y[r2] = temp;
	}
	else {
		int temp = y[r1];
		for (int i = r1; i < r2; i++)
		{
			if (y[i] == 0) continue;
			if (y[i + 1] == 0) y[i] = y[i + 2];
			else y[i] = y[i + 1];
		}
		if (y[r2 - 1] == 0) y[r2 - 2] = temp;
		else y[r2-1] = temp;
	}	
}

void reversion() {
	copySolution(X, Y);
	int r1;
	int r2;

	while (r1 == r2) {
		r1 = rand() % (nNodes - 1);
		r2 = rand() % (nNodes - 1);

		while (r1 == dummyZeroIndex) {
			r1 = rand() % (nNodes - 1);
		}
		while (r2 == dummyZeroIndex) {
			r2 = rand() % (nNodes - 1);
		}
	}

	if (r2 < r1) {
		int temp = r1;
		r1 = r2;
		r2 = temp;
	}

	//cout << "r1:" << r1 << " r2:" << r2 << endl;
	//int temp;
	//print(Y);

	int* temp= new int[nNodes];
	for (int i = r1; i <= r2; i++)
	{
		temp[i] = y[i];
	}

	int j = r1;
	for (int i = r2; i >= r1; i--)
	{
		if (y[j] == 0) {
			j++;
			continue;
		}
		if (temp[i] == 0) {
			j++;
			continue;
		}
		y[j] = temp[i];
		j++;
	}

	delete temp;
	//print(Y);

	/*
	print(Y);
	for (int i = r1; i <= ((r2-r1 +1)/2); i++){
		//cout << "i:" << i << " j:" << j << endl;
		temp = y[i]; 
		y[i] = y[((r2 - r1 + 1) -1 ) - i];
		y[((r2 - r1 ) + r1 ) - (i - r1)] = temp;
	}
	print(Y);
	system("PAUSE");
	*/
	//system("PAUSE");
}

int calculateObjectiveFunction(int solType, bool print) {
	float timeKeeper = 0.0;
	int from, to, lastTo;
	int obj = 0;
	int * arr;

	if (solType == X) arr = x;
	else arr = y;

	if(print) cout << "soltype: " << solType << endl;

	from = 0;
	for (int i = 0; i < nNodes; i++){
		to = arr[i];
		//if(to<0 && to >nNodes-1)		cout << "@========================" << to ; 

		float eT = instance[to][5]; //early Time
		float lT = instance[to][6]; // late time
		float traveltime = distanceMatrix[from][to];
		int score = instance[to][4];
		float sT = instance[to][3]; // service time
		
		if (print ) {
			cout << "et:" << eT << " lT:" << lT << endl;
		}

		if (to == 0){ //check if we back to depot
			if ((timeKeeper + distanceMatrix[from][to]) > instance[0][6]) { //remove last node if we back to depot late
				selected[i] = 0;
				obj -= instance[from][4];
			}
			timeKeeper = 0;
			from = 0;
			selected[i] = 2;
			if (print) cout << to << "zero ";
		}
		else if ((timeKeeper + distanceMatrix[from][to]) < eT ) {//check if we arive too early
			//we get to early
			selected[i] = 1;
			visitTime[i] = timeKeeper + traveltime;

			//add traveling time, wait time and service time
			timeKeeper += traveltime; //add traveling time
			float wait = eT - timeKeeper;
			timeKeeper += wait + sT;//add wait and service time
			if (print) cout << to << "early:" << visitTime[i] << " " << timeKeeper << " ";
			obj += score;
			from = to;
			
		}
		else if ((timeKeeper + distanceMatrix[from][to]) > lT ) { //check if we arive too late
			//we are to late 
			//ignore this node
			selected[i] = 0;
			visitTime[i] = 0;
			//dont add time here
		}
		else {
			//we are within timewindows
			selected[i] = 1;
			visitTime[i] = timeKeeper + traveltime;

			//add traveling time and service time
			timeKeeper += traveltime + sT;//add traveling and service time
			if (print) cout << to << "within:" << visitTime[i] << " "<<timeKeeper<<" ";
			obj += score;
			from = to;
			
		}

		if (i == nNodes - 1) { //check if this is the last node
			if ((timeKeeper + distanceMatrix[from][0]) > instance[0][6]) { //remove last node if we back to depot late
				selected[i] = 0;
				obj -= instance[from][4];
			}
		}
		if (print)cout << endl;
	}

	if (print) cout << endl;

	arr = NULL;
	return obj;
}

void copySolution(int from, int to) {
	int *arrFrom;
	int *arrTo;

	if (from == Y && to == X) {
		arrFrom = y;
		arrTo = x;
	}
	else if (from == X && to == XBEST) {
		arrFrom = x;
		arrTo = xBest;
	}
	else if (from == XBEST && to == X) {
		arrFrom = xBest;
		arrTo = x;
	}
	else if (from == XBEST && to == Y) {
		arrFrom = xBest;
		arrTo = y;
	}
	else if (from == Y && to == XBEST) {
		arrFrom = y;
		arrTo = xBest;
	}
	else if (from == X && to == Y) {
		arrFrom = x;
		arrTo = y;
	}
	else {
		cout << "================= COPY NOT HANDLED YET ===============" << from << " " << to << endl;
		return;
	}

	for (int  i = 0; i < nNodes; i++)
	{
		arrTo[i] = arrFrom[i];
	}

	arrFrom = NULL;
	arrTo = NULL;

}

void createRandomInitialSolution() {
	dummyZeroIndex = nNodes / 2; //for 2 route
	x = new int[nNodes];
	y = new int[nNodes];
	selected = new int[nNodes];
	visitTime = new float[nNodes];
	xBest = new int[nNodes];

	int currentDataCount = nNodes;

	if (isDebug) cout << "sorted node:" << endl;
	//create sorted node
	for (int i = 0; i < nNodes-1; i++)
	{
		y[i] = i+1;
		if (isDebug) cout << y[i] << " ";
	}
	if (isDebug) cout << endl;
	  
	if (isDebug) cout << "randomized node:" << endl;
	//generate x randomly
	int r = 0;
	for (int i = 0; i < nNodes; i++)
	{
		if (i!=dummyZeroIndex) {
			
			r=0;
			if (i < nNodes - 3) {
				r = rand() % currentDataCount;
				if (r <= 0) r = 1;
				r -= 1;
			}

			//cout << "to " << currentDataCount - 1 << " get: " << r << endl;
			
			x[i] = y[r];
			removeArrayIndex(r, --currentDataCount);
		}
		else {
			x[i] = 0;
		}
		//if (isDebug) cout << x[i] << " ";
	}

	for (int i = 0; i < nNodes; i++)
	{
		if (isDebug) cout << x[i] << " ";
	}
	if (isDebug) cout << endl;

	//check sama
	for (int i = 0; i < nNodes - 1; i++)
	{
		for (int j = i + 1; j < nNodes; j++)
		{
			if (x[i] == x[j]) {
				cout << "DUPLICATE ON CREATE++++++++++ i:" << i << " j:" << j; break;
			}
		}
	}
}

void print(int type) {
	int* arr;
	if (type == X) arr = x;
	else if (type == Y) arr = y;
	else if (type == USED) arr = selected;
	else arr = xBest;

	for (int i = 0; i < nNodes; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	arr = NULL;

	//check sama
	for (int i = 0;  i < nNodes-1;  i++)
	{
		for (int j = i+1; j < nNodes; j++)
		{
			if (xBest[i] == xBest[j]) {
				cout << "DUPLICATE++++++++++ i:" << i << " j:" << j; break;
			}
		}
	}
}



void removeArrayIndex(int index, int count) {
	
	for (int i = index; i < count-1; ++i)
		y[i] = y[i + 1]; // copy next element left

	
}

void calculateDistanceMatrix() {

	ofstream data("distance.txt");


	if (isDebug) cout << "Distance matrix: " << endl;
	distanceMatrix = new float*[nNodes];
	for (int i = 0; i < nNodes; i++) {
		distanceMatrix[i] = new float[nNodes];
		for (int j = 0; j < nNodes; j++)
		{
			distanceMatrix[i][j] = sqrt(pow(instance[i][1] - instance[j][1], 2) + pow(instance[i][2] - instance[j][2], 2));
			//if (isDebug) cout << distanceMatrix[i][j] << " ";
		}
		//if (isDebug) cout << endl;
	}

	//storeData("output.txt");
}

void storeData(string output) {
	ofstream myfile(output);
	if (myfile.is_open())
	{

		for (int i = 0; i < nNodes; i++) {
			distanceMatrix[i] = new float[nNodes];
			for (int j = 0; j < nNodes; j++)
			{
				distanceMatrix[i][j] = (sqrt(pow(instance[i][1] - instance[j][1], 2) + pow(instance[i][2] - instance[j][2], 2)));
				myfile << distanceMatrix[i][j] << " ";
			}
			myfile << "\n";
		}
		
		myfile.close();
	}
	else cout << "Unable to open file";
}

void readData(string input) {
	FILE* infile;
	// open input file
	fopen_s(&infile, input.c_str(), "r");
	if (infile == NULL)
	{
		cout << "Can't find this file" << endl;
		exit(0);
	}

	// read first row
	fscanf_s(infile, "%d", &nNodes);
	if (isDebug) cout << "Node:" << nNodes << endl;
	
	if (isDebug) cout << "Instance:" << endl;
	instance = new float*[nNodes];
	for (int i = 0; i < nNodes; i++){
		instance[i] = new float[7];
		for (int j = 0; j < 7; j++) {
			fscanf_s(infile, "%fd", &instance[i][j]);
			if (isDebug) cout << instance[i][j] << " ";
		}
		if (isDebug) cout << endl;
	}
}