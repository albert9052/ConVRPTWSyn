#include "Solution.h"

void Solution::input() {
    
	nCustomer = 7;
    nNodes = 8;
    nNormals = 5;
    nFictives = 2;
    nRoutes = 3;
    nDays = 3;
    fictiveLink = {0, 0, 0, 0, 0, 1, 2};
    serviceTime = { {0, 0, 0}, {15, 15, 15}, {18, 18, 18}, {23, 23, 23}, {45, 45, 45}, {30, 30, 30}, {15, 15, 15}, {18, 18, 18} };
    required = { {0, 0, 0}, {1, 1, 1}, {0, 1, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 0}, {1, 1, 1}, {0, 1, 0} };
    earliestTime = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {15, 15, 15}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    lastTime = { {100, 100, 100}, {50, 50, 50}, {30, 30, 30}, {95, 95, 95}, {25, 25, 25}, {80, 80, 80}, {50, 50, 50}, {30, 30, 30} };
    timeMat = { {100000, 12.751, 3.302, 4.6204, 2.6174, 9.0958, 12.751, 3.302},
                {12.751, 100000, 9.8491, 8.2998, 10.341, 5.2756, 100000, 9.8491},
                {3.302, 9.8491, 100000, 2.82, 0.717, 5.809, 9.8491, 100000},
                {4.6204, 8.2998, 2.82, 100000, 2.8158, 5.7838, 8.2998, 2.82},
                {2.6174, 10.341, 0.717, 2.8158, 100000, 6.4784, 10.341, 0.717},
                {9.0958, 5.2756, 5.809, 5.7838, 6.4784, 100000, 5.2756, 5.809},
                {12.751, 100000, 9.8491, 8.2998, 10.341, 5.2756, 100000, 9.8491},
                {3.302, 9.8491, 100000, 2.82, 0.717, 5.809, 9.8491, 100000} };
	
	// case_1_20_4_2_2
	/*nCustomer = 20;
	nNodes = 21;
	nNormals = 18;
	nFictives = 2;
	nRoutes = 4;
	nDays = 3;
	fictiveLink = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3};
	serviceTime = {
		{0, 0, 0}, 
		{139, 139, 139}, 
		{37, 37, 37}, 
		{32, 32, 32}, 
		{102, 102, 102}, 
		{72, 72, 72}, 
		{75, 75, 75}, 
		{49, 49, 49}, 
		{98, 98, 98}, 
		{107, 107, 107}, 
		{37, 37, 37}, 
		{25, 25, 25}, 
		{88, 88, 88}, 
		{47, 47, 47}, 
		{118, 118, 118}, 
		{131, 131, 131}, 
		{63, 63, 63}, 
		{52, 52, 52}, 
		{69, 69, 69}, 
		{139, 139, 139}, 
		{32, 32, 32}, 
	};
	required = {
		{0, 0, 0}, 
		{1, 1, 0}, 
		{0, 1, 0}, 
		{1, 0, 1}, 
		{0, 0, 1}, 
		{0, 0, 1}, 
		{1, 1, 1}, 
		{1, 0, 1}, 
		{1, 1, 1}, 
		{1, 0, 1}, 
		{1, 1, 1}, 
		{1, 1, 0}, 
		{0, 1, 1}, 
		{1, 1, 1}, 
		{1, 0, 1}, 
		{1, 0, 1}, 
		{1, 0, 1}, 
		{0, 1, 1}, 
		{1, 1, 0}, 
		{1, 1, 0}, 
		{1, 0, 1}, 
	};
	earliestTime = {
		{0, 0, 0}, 
		{170, 170, 170}, 
		{284, 284, 284}, 
		{339, 339, 339}, 
		{447, 447, 447}, 
		{536, 536, 536}, 
		{0, 0, 0}, 
		{38, 38, 38}, 
		{413, 413, 413}, 
		{358, 358, 358}, 
		{566, 566, 566}, 
		{0, 0, 0}, 
		{0, 0, 0}, 
		{97, 97, 97}, 
		{165, 165, 165}, 
		{355, 355, 355}, 
		{0, 0, 0}, 
		{4, 4, 4}, 
		{270, 270, 270}, 
		{170, 170, 170}, 
		{339, 339, 339}, 
	};
	lastTime = {
		{695, 695, 695}, 
		{288, 288, 288}, 
		{378, 378, 378}, 
		{497, 497, 497}, 
		{560, 560, 560}, 
		{684, 684, 684}, 
		{29, 29, 29}, 
		{136, 136, 136}, 
		{492, 492, 492}, 
		{549, 549, 549}, 
		{667, 667, 667}, 
		{88, 88, 88}, 
		{107, 107, 107}, 
		{206, 206, 206}, 
		{333, 333, 333}, 
		{419, 419, 419}, 
		{72, 72, 72}, 
		{172, 172, 172}, 
		{400, 400, 400}, 
		{288, 288, 288}, 
		{497, 497, 497}, 
	};
	timeMat = {
		{0, 21, 18, 20, 22, 23, 7, 18, 13, 18, 13, 9, 11, 19, 19, 19, 17, 26, 13, 21, 20}, 
		{21, 10000, 23, 3, 42, 43, 23, 25, 14, 4, 33, 29, 29, 38, 3, 39, 37, 40, 24, 10000, 3}, 
		{18, 23, 10000, 23, 35, 36, 25, 35, 25, 20, 23, 22, 17, 35, 23, 31, 24, 19, 7, 23, 23}, 
		{20, 3, 23, 10000, 40, 41, 22, 23, 12, 4, 32, 28, 28, 36, 2, 38, 36, 40, 24, 3, 10000}, 
		{22, 42, 35, 40, 10000, 2, 20, 27, 31, 39, 13, 14, 18, 7, 39, 4, 14, 29, 28, 42, 40}, 
		{23, 43, 36, 41, 2, 10000, 20, 27, 32, 40, 14, 15, 19, 7, 40, 6, 15, 30, 29, 43, 41}, 
		{7, 23, 25, 22, 20, 20, 10000, 12, 12, 21, 15, 10, 15, 15, 21, 18, 20, 31, 20, 23, 22}, 
		{18, 25, 35, 23, 27, 27, 12, 10000, 13, 24, 26, 22, 27, 21, 23, 27, 31, 43, 31, 25, 23}, 
		{13, 14, 25, 12, 31, 32, 12, 13, 10000, 12, 25, 20, 23, 26, 11, 29, 30, 37, 23, 14, 12}, 
		{18, 4, 20, 4, 39, 40, 21, 24, 12, 10000, 30, 26, 26, 35, 3, 36, 34, 36, 21, 4, 4}, 
		{13, 33, 23, 32, 13, 14, 15, 26, 25, 30, 10000, 5, 6, 14, 31, 9, 6, 19, 16, 33, 32}, 
		{9, 29, 22, 28, 14, 15, 10, 22, 20, 26, 5, 10000, 7, 13, 27, 11, 10, 22, 15, 29, 28}, 
		{11, 29, 17, 28, 18, 19, 15, 27, 23, 26, 6, 7, 10000, 19, 27, 14, 8, 16, 10, 29, 28}, 
		{19, 38, 35, 36, 7, 7, 15, 21, 26, 35, 14, 13, 19, 10000, 35, 8, 17, 32, 28, 38, 36}, 
		{19, 3, 23, 2, 39, 40, 21, 23, 11, 3, 31, 27, 27, 35, 10000, 37, 35, 39, 23, 3, 2}, 
		{19, 39, 31, 38, 4, 6, 18, 27, 29, 36, 9, 11, 14, 8, 37, 10000, 10, 25, 24, 39, 38}, 
		{17, 37, 24, 36, 14, 15, 20, 31, 30, 34, 6, 10, 8, 17, 35, 10, 10000, 16, 17, 37, 36}, 
		{26, 40, 19, 40, 29, 30, 31, 43, 37, 36, 19, 22, 16, 32, 39, 25, 16, 10000, 16, 40, 40}, 
		{13, 24, 7, 24, 28, 29, 20, 31, 23, 21, 16, 15, 10, 28, 23, 24, 17, 16, 10000, 24, 24}, 
		{21, 10000, 23, 3, 42, 43, 23, 25, 14, 4, 33, 29, 29, 38, 3, 39, 37, 40, 24, 10000, 3}, 
		{20, 3, 23, 10000, 40, 41, 22, 23, 12, 4, 32, 28, 28, 36, 2, 38, 36, 40, 24, 3, 10000}, 
	};*/

    // below are data processing
	requiredList.resize(nDays);
	for (int n = 0; n < nCustomer; n++)
		for (int d = 0; d < nDays; d++)
			if (required[n][d])
				requiredList[d].push_back(n);

	correspondingList.resize(nNodes);
	correspondingList[0] = 0;
	for (int i = 1; i <= fictiveLink.size(); i++) {

		correspondingList[i] = fictiveLink[i - 1];
		if (fictiveLink[i - 1] != 0) {

			correspondingList[fictiveLink[i - 1]] = i;
		}
	}

	arrivalTimes = std::vector<std::vector<double>>(nNodes, (std::vector<double>(nDays, -1)));

	departureTimes = std::vector<std::vector<double>>(nNodes, (std::vector<double>(nDays, -1)));
	
	postponedDuration = std::vector<std::vector<std::vector<double>>>(nDays, std::vector<std::vector<double>>(nNodes, std::vector<double>(nNodes, 0)));

	daysOfEarliestArrivalTimeOfEachCustomer = std::vector<std::vector<int>>(nNormals + 1, std::vector<int>());
	daysOfLatestArrivalTimeOfEachCustomer = std::vector<std::vector<int>>(nNormals + 1, std::vector<int>());
}

void Solution::readData(std::string input) {

	int RC = 80;
	int VN = 500;
	FILE* infile;
	char dispose[1000];
	// open input file
	infile = fopen(input.c_str(), "r");
	if (infile == NULL)
	{
		std::cout << "Can't find this file" << std::endl;
		exit(0);
	}
	int counts1 = 0, counts2 = 0, counts3 = 0;
	for (int i = 0; i < 8; i++)  // dispose first three rows
	{
		fscanf(infile, "%s", dispose);
	}
	int Single_service[1000];
	for (int i = 0; i < VN; i++)  // Read Single service nodes
	{
		fscanf(infile, "%d", &Single_service[i]);
		if (Single_service[i] == 0)
		{
			Single_service[i] = -1;
			break;
		}
		counts1++;
	}
	//std::cout << "Single service : ";
	//for (int i = 0; i < counts1; i++)
	//{
	//	std::cout << Single_service[i] << "\t";
	//}
	//std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	int* Synchronized_services = (int*)malloc(sizeof(int) * VN);
	for (int i = 0; i < VN; i++)  // Read Synchronized services nodes
	{
		fscanf(infile, "%d", &Synchronized_services[i]);
		if (Synchronized_services[i] == 0)
		{
			Synchronized_services[i] = -1;
			break;
		}
		counts2++;
	}
	nNormals = counts1 + counts2 / 2;
	//std::cout << "nNormals: " << nNormals << std::endl;
	nFictives = counts2 / 2;
	//td::cout << "nFictives: " << nFictives << std::endl;
	nCustomer = nNormals + nFictives;
	//std::cout << "nCustomer: " << nCustomer << std::endl;
	nNodes = nCustomer + 1;
	//std::cout << "nNodes: " << nNodes << std::endl;
	//std::cout << "Synchronized services : ";
	//for (int i = 0; i < counts2; i++)
	//{
	//	std::cout << Synchronized_services[i] << "\t";
	//}
	//std::cout << std::endl;
	for (int i = 0; i < 3; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	char Real_node[1000];
	for (int i = 0; i < VN; i++)  // Read Shared1
	{
		fscanf(infile, "%d", &Real_node[i]);
		if (Real_node[i] == 0)
		{
			Real_node[i] = -1;
			break;
		}
		counts3++;
	}
	for (int i = 0; i < 3; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	for (int i = 0; i < nCustomer; i++) {
		fictiveLink.push_back(0);
	}
	for (int i = 0; i < counts3; i++)  // Read Shared2
	{
		int disposeInt;
		fscanf(infile, "%d", &disposeInt);
		fictiveLink[disposeInt - 1] = Real_node[i];
	}
	int node_number = nCustomer;  // Get Node numbers
	//std::cout << "Synchronized Node : ";
	//for (int i = 0; i < counts3; i++)
	//	std::cout << Real_node[i] << "__" << Fictive_node[i] << "\t";
	//std::cout << "hi" << std::endl;
	//std::cout << std::endl;
	for (int i = 0; i < 6; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	int vehicle_number;
	fscanf(infile, "%d", &vehicle_number);  // Read Vehicle numbers
	nRoutes = vehicle_number;
	for (int i = 0; i < 3; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	fscanf(infile, "%d", &nDays);
	//cout << "Vehicle : " << vehicle_number << endl;
	for (int i = 0; i < 3; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	int T;
	fscanf(infile, "%d", &T);  // Read Total time
	//std::cout << "T: " << T << std::endl;
	//cout << "Total time : " << T << endl;
	for (int i = 0; i < 4 + nDays; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	for (int i = 0; i < node_number + 1; i++)  // Read Service time
	{
		//std::cout << serviceTime.size() << ": ";
		fscanf(infile, "%s", dispose);
		serviceTime.push_back(std::vector<float>());
		for (int j = 0; j < nDays; j++)
		{
			serviceTime[i].push_back(0);
			fscanf(infile, "%f", &serviceTime[i][j]);
			if (i == 0 && serviceTime[i][j] != 0) {

				exit(1);
			}
			//std::cout << serviceTime[i].size() << ", ";
		}
		//std::cout << std::endl;
	}
	/*cout << "Service Time ~~~~~~~~~~~~~~~~" << endl;
	for (int i = 0; i < node_number + 1; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < nDays; j++)
		{
			cout << service_time[i][j] << "\t";
		}
		cout << endl;
	}*/
	for (int i = 0; i < 4 + node_number + 1; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	//cout << dispose;
	for (int i = 0; i < node_number + 1; i++)  // Read Travelling time
	{
		fscanf(infile, "%s", dispose);
		timeMat.push_back(std::vector<float>());
		for (int j = 0; j < node_number + 1; j++)
		{
			timeMat[i].push_back(0);
			fscanf(infile, "%f", &timeMat[i][j]);
		}
	}
	/*cout << "Distance Matrix ~~~~~~~~~~~~~~~~" << endl;
	cout << "\t";
	for (int i = 0; i < node_number + 1; i++)
		cout << i << "\t";
	cout << endl;
	for (int i = 0; i < node_number + 1; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < node_number + 1; j++)
		{
			cout << DistanceMatrix_Time[i][j] << "\t";
		}
		cout << endl;
	}*/
	for (int i = 0; i < 4 + nDays; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	int w[1000][100];
	required.push_back(std::vector<bool>());
	for (int i = 0; i < nDays; i++) {
		required[0].push_back(false);
	}
	for (int i = 1; i < node_number + 1; i++)  // Read w
	{
		fscanf(infile, "%s", dispose);
		required.push_back(std::vector<bool>());
		for (int j = 0; j < nDays; j++)
		{
			fscanf(infile, "%d", &w[i][j]);
			if (w[i][j] == 0) 
			{
				required[i].push_back(false);
			}
			else 
			{
				required[i].push_back(true);
			}
		}
	}
	/*cout << endl;
	cout << "w ~~~~~~~~~~~~~~~~" << endl;
	for (int i = 1; i < node_number + 1; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < nDays; j++)
		{
			if (w[i][j] == 0)
				service_time[i][j] = 0;
			cout << w[i][j] << "\t";
		}
		cout << endl;
	}*/
	for (int i = 0; i < 4 + nDays; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	for (int i = 0; i < node_number + 1; i++)  // Read Earliest time
	{
		//std::cout << earliestTime.size() << ": " << std::endl;
		fscanf(infile, "%s", dispose);
		earliestTime.push_back(std::vector<float>());
		for (int j = 0; j < nDays; j++)
		{
			earliestTime[i].push_back(0);
			//std::cout << earliestTime[i].size() << std::endl;
			fscanf(infile, "%f", &earliestTime[i][j]);
		}
	}
	/*cout << "Earliest Time ~~~~~~~~~~~~~~~~" << endl;
	for (int i = 0; i < node_number + 1; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < nDays; j++)
		{
			cout << ready_time[i][j] << "\t";
		}
		cout << endl;
	}*/
	for (int i = 0; i < 4 + nDays; i++)
	{
		fscanf(infile, "%s", dispose);
	}
	for (int i = 0; i < node_number + 1; i++)  // Read Latest time
	{
		fscanf(infile, "%s", dispose);
		lastTime.push_back(std::vector<float>());
		for (int j = 0; j < nDays; j++)
		{
			lastTime[i].push_back(0);
			fscanf(infile, "%f", &lastTime[i][j]);
		}
	}
	/*cout << "Latest Time ~~~~~~~~~~~~~~~~" << endl;
	for (int i = 0; i < node_number + 1; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < nDays; j++)
		{
			cout << due_time[i][j] << "\t";
		}
		cout << endl;
	}*/

	std::cout << "Finish Read Data--------------------------------------------------------------------" << std::endl;

	fclose(infile);

    // below are data processing
	requiredList.resize(nDays);
	for (int n = 0; n < nCustomer; n++)
		for (int d = 0; d < nDays; d++)
			if (required[n][d])
				requiredList[d].push_back(n);

	correspondingList.resize(nNodes);
	correspondingList[0] = 0;
	for (int i = 1; i <= fictiveLink.size(); i++) {

		correspondingList[i] = fictiveLink[i - 1];
		if (fictiveLink[i - 1] != 0) {

			correspondingList[fictiveLink[i - 1]] = i;
		}
	}

	arrivalTimes = std::vector<std::vector<double>>(nNodes, (std::vector<double>(nDays, -1)));

	departureTimes = std::vector<std::vector<double>>(nNodes, (std::vector<double>(nDays, -1)));
	
	postponedDuration = std::vector<std::vector<std::vector<double>>>(nDays, std::vector<std::vector<double>>(nNodes, std::vector<double>(nNodes, 0)));

	daysOfEarliestArrivalTimeOfEachCustomer = std::vector<std::vector<int>>(nNormals + 1, std::vector<int>());
	daysOfLatestArrivalTimeOfEachCustomer = std::vector<std::vector<int>>(nNormals + 1, std::vector<int>());
}

void Solution::printInput() {

	std::cout << "nCustomer: " << nCustomer << std::endl;
	std::cout << "nNodes: " << nNodes << std::endl;
	std::cout << "nNormals: " << nNormals << std::endl;
	std::cout << "nFictives: " << nFictives << std::endl;
	std::cout << "nRoutes: " << nRoutes << std::endl;
	std::cout << "nDays: " << nDays << std::endl;
	std::cout << "fictiveLink: {" << fictiveLink[0];
	for (int i = 1; i < fictiveLink.size(); i++) {

		std::cout << ", " << fictiveLink[i];
	}
	std::cout << "}" << std::endl;
	std::cout << "serviceTime: {" << std::endl;
	for (int i = 0; i < serviceTime.size(); i++) {

		std::cout << "\t{" << serviceTime[i][0];
		for (int j = 1; j < serviceTime[i].size(); j++) {

			std::cout << ", " << serviceTime[i][j];
		}
		std::cout << "}" << std::endl;
	}
	std::cout << "required: {" << std::endl;
	for (int i = 0; i < required.size(); i++) {

		std::cout << "\t{" << required[i][0];
		for (int j = 1; j < required[i].size(); j++) {

			std::cout << ", " << required[i][j];
		}
		std::cout << "}" << std::endl;
	}
	std::cout << "earliestTime: {" << std::endl;
	for (int i = 0; i < earliestTime.size(); i++) {

		std::cout << "\t{" << earliestTime[i][0];
		for (int j = 1; j < earliestTime[i].size(); j++) {

			std::cout << ", " << earliestTime[i][j];
		}
		std::cout << "}" << std::endl;
	}
	std::cout << "lastTime: {" << std::endl;
	for (int i = 0; i < lastTime.size(); i++) {

		std::cout << "\t{" << lastTime[i][0];
		for (int j = 1; j < lastTime[i].size(); j++) {

			std::cout << ", " << lastTime[i][j];
		}
		std::cout << "}" << std::endl;
	}
	std::cout << "timeMat: {" << std::endl;
	for (int i = 0; i < timeMat.size(); i++) {

		std::cout << "\t{" << timeMat[i][0];
		for (int j = 1; j < timeMat[i].size(); j++) {

			std::cout << ", " << timeMat[i][j];
		}
		std::cout << "}" << std::endl;
	}
}

void Solution::output(){ 
	for(int i = 0; i < nDays; i++){ 
		std::cout << "Day " << i + 1 << std::endl; 
		for(int j = 0; j < nRoutes; j++){
            std::cout << "   Route " << j + 1 << ":";
            for(int& k : solutionList[i][j]){
                std::cout << " => " << k;
            }
            std::cout << std::endl;
        }
    }
    /*int nRoute = 1;
    int nDay = 1;
    std::cout << std::endl << std::endl << " Day 1";
    std::cout << std::endl << "   Route 1 :";
    for (int i = 0; i < solutionList.size(); i++) {
        if (solutionList[i] == 0) 
            continue;
        if (solutionList[i] == -1) {            
            nRoute++;
            if (nRoute > nRoutes) {
                if (nDay == nDays)
                    break;
                nDay++;
                nRoute = 1;
                std::cout << std::endl << std::endl << " Day " << nDay ;
            }
            std::cout << std::endl << "   Route " << nRoute << " : ";
        }
        else {
            std::cout << "=> " << solutionList[i] << " ";
        }
    }
    std::cout << std::endl << std::endl;*/
}

void Solution::calculateObjective(std::vector<std::vector<int>>& solutionListOfEachDay) {

	// Directly arrange the arrival time (only consider commuting time and service time). 
	for (int day = 0; day < nDays; day++) {

		double currentTime = earliestTime[0][day];
		int previousNode = 0;
		for (int j = 0; j < solutionListOfEachDay[day].size(); j++) {

			int currentNode = solutionListOfEachDay[day][j];
			if (currentNode == -1) {

				// Next routes
				currentTime = earliestTime[0][day];
				previousNode = 0;
				continue;
			}
			double commutingTime = timeMat[previousNode][currentNode];
			arrivalTimes[currentNode][day] = currentTime + commutingTime;
			currentTime = arrivalTimes[currentNode][day] + serviceTime[currentNode][day];
			departureTimes[currentNode][day] = currentTime;
			previousNode = currentNode;
		}
	}
	for (int day = 0; day < nDays; day++) {

		for (int i = 0; i < nNodes; i++) {

			for (int j = 0; j < nNodes; j++) {

				postponedDuration[day][i][j] = 0;
			}
		}
	}
	//std::cout << "Diretly arranging the arrival time successes. " << std::endl;
	//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	
	//CheckConstraintsResult checkConstraintsResult = checkConstraints(solutionListOfEachDay);
	////std::cout << "checkConstraints done. " << std::endl;
	//if (checkConstraintsResult.result == false) {

	//	printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	//	std::cout << "After directly arranging the arrival time" << std::endl;
	//	std::cout << "Violation detected ----------------------------------" << std::endl;
	//	for (std::string message : checkConstraintsResult.messages) {

	//		std::cout << message << std::endl;
	//	}
	//	std::cout << "-----------------------------------------------------" << std::endl;
	//}

	// Rearrange the arrival time to minimize the violation of time windows. 
	// Needs to consider 0's last time. (IMPORTANT)
	for (int day = 0; day < nDays; day++) {

		int numberOfGoodNodes = 0;
		int numberOfBadNodes = 0;
		std::vector<TypeAndDuration> typesAndDurations;
		for (int i = solutionListOfEachDay[day].size() - 1; i >= 0; i--) {

			int currentNode = solutionListOfEachDay[day][i];
			if (currentNode == -1) {

				typesAndDurations.clear();
				continue;
			}

			int previousNode = 0;
			if (i != 0) {

				previousNode = solutionListOfEachDay[day][i - 1];
				if (previousNode == -1) {

					previousNode = 0;
				}
			}

			int nextNode = 0;
			if (i != solutionListOfEachDay[day].size() - 1) {

				nextNode = solutionListOfEachDay[day][i + 1];
				if (nextNode == -1) {

					nextNode = 0;
				}
			}
			
			if (arrivalTimes[currentNode][day] < earliestTime[currentNode][day]) {

				//std::cout << "////////////" << std::endl;
				//std::cout << "Postpone This One" << std::endl;
				//std::cout << "Day: " << day << ", node: " << currentNode << std::endl;
				//std::cout << "////////////" << std::endl;

				numberOfGoodNodes++;

				// Start moving. 
				// Find the movingDuration. 
				double targetDuration = earliestTime[currentNode][day] - arrivalTimes[currentNode][day];
				double movingDuration = targetDuration;
				//std::cout << "CurrentNode: " << currentNode << std::endl;
				while (numberOfGoodNodes > numberOfBadNodes && typesAndDurations.size() > 0) {

					movingDuration = (typesAndDurations.end() - 1) -> duration;
					//std::cout << "(" << numberOfGoodNodes << ", " << numberOfBadNodes << ") Processing " << (typesAndDurations.end() - 1) -> type << " / " << (typesAndDurations.end() - 1) -> duration << std::endl;
					if (movingDuration < targetDuration) {

						int movingType = (typesAndDurations.end() - 1) -> type;
						typesAndDurations.pop_back();

						switch(movingType) {

						case 0:
							std::cout << "Error: There should be no 0 in movingType. (In function calculateObjective)" << std::endl;
							exit(1);
							break;
						case 1:
							numberOfBadNodes++;
							break;
						case 2:
							numberOfGoodNodes++;
							break;
						case 3:
							numberOfGoodNodes--;
							numberOfBadNodes++;
							break;
						case 4:
							numberOfGoodNodes--;
							break;
						}
					}
					else {

						movingDuration = targetDuration;
						// Because this node has been pushed to its best. 
						numberOfGoodNodes--;
						break;
					}
				}
				
				// Move the current node and the nodes that will be pushed. 
				//std::cout << "Size: " << typesAndDurations.size() << ", moving duration: " << movingDuration << std::endl;
				arrivalTimes[currentNode][day] += movingDuration;
				departureTimes[currentNode][day] += movingDuration;
				postponedDuration[day][previousNode][currentNode] += movingDuration;
				int previousNodeForPushing = currentNode;
				for (int j = i + 1; j < solutionListOfEachDay[day].size(); j++) {

					int currentNodeForPushing = solutionListOfEachDay[day][j];
					if (currentNodeForPushing == -1) {

						break;
					}
					if (movingDuration <= postponedDuration[day][previousNodeForPushing][currentNodeForPushing]) {

						postponedDuration[day][previousNodeForPushing][currentNodeForPushing] -= movingDuration;
						break;
					}
					movingDuration -= postponedDuration[day][previousNodeForPushing][currentNodeForPushing];
					postponedDuration[day][previousNodeForPushing][currentNodeForPushing] = 0;
					arrivalTimes[currentNodeForPushing][day] += movingDuration;
					departureTimes[currentNodeForPushing][day] += movingDuration;
					previousNodeForPushing = currentNodeForPushing;
				}
			}

			// No need for this section, because you don't need to adjust typesAndDurations everytime. you can use some objects or drawings to help yourself understand this. 
			// Readjust typesAndDurations
			//for (int j = 0; j < typesAndDurations.size(); j++) {

			//	//typesAndDurations[j].duration += (timeMat[currentNode][nextNode] + serviceTime[currentNode][day]);
			//	typesAndDurations[j].duration += postponedDuration[day][previousNode][currentNode];
			//}

			// Add new timestamps, whose data type is TypeAndDuration. 
			double tempDuration = earliestTime[currentNode][day] - arrivalTimes[currentNode][day];
			if (tempDuration > 0) {

				typesAndDurations.push_back(TypeAndDuration(2, postponedDuration[day][previousNode][currentNode]));
				typesAndDurations.push_back(TypeAndDuration(4, tempDuration + postponedDuration[day][previousNode][currentNode]));
			}
			
			tempDuration = lastTime[currentNode][day] - arrivalTimes[currentNode][day];
			if (tempDuration > 0) {

				typesAndDurations.push_back(TypeAndDuration(1, tempDuration + postponedDuration[day][previousNode][currentNode]));
			}
			else {

				typesAndDurations.push_back(TypeAndDuration(1, postponedDuration[day][previousNode][currentNode]));
			}

			// If nextNode == 0, add a new timestamp, because of the vehicle needs to arrive at 0 before 0's latest time. (lastTime)
			if (nextNode == 0) {

				tempDuration = lastTime[0][day] - departureTimes[currentNode][day] - timeMat[currentNode][0];
				if (tempDuration > 0) {

					typesAndDurations.push_back(TypeAndDuration(1, tempDuration + postponedDuration[day][previousNode][currentNode]));
				}
				else {

					typesAndDurations.push_back(TypeAndDuration(1, postponedDuration[day][previousNode][currentNode]));
				}
			}

			// No need for this section, because we have done this above. If the while loop is broken by the else in it, then numberOfGoodNodes--. On the other hand, it won't subtract 1 from numberOfGoodNodes. 
			//if (arrivalTimes[currentNode][day] < earliestTime[currentNode][day]) {

			//	numberOfGoodNodes++;
			//}
			//else if (arrivalTimes[currentNode][day] >= lastTime[currentNode][day]) {

			//	numberOfBadNodes++;
			//}

			// Reorder typesAndDurations (Decreasing)
			// This can be optimized, since most of them were sorted before. 
			std::sort(typesAndDurations.begin(), typesAndDurations.end(), std::greater<TypeAndDuration>());
		}
	}
	//std::cout << "Rearranging the arrival time to minimize the violation of time window successes. " << std::endl;
	//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	
	//checkConstraintsResult = checkConstraints(solutionListOfEachDay);
	////std::cout << "checkConstraints done. " << std::endl;
	//if (checkConstraintsResult.result == false) {

	//	printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	//	std::cout << "After rearranging the arrival time to minimize the violation of time window" << std::endl;
	//	std::cout << "Violation detected ----------------------------------" << std::endl;
	//	for (std::string message : checkConstraintsResult.messages) {

	//		std::cout << message << std::endl;
	//	}
	//	std::cout << "-----------------------------------------------------" << std::endl;
	//}
	
	// Rearrange the arrival time of each synchronized service. 
	// Haven't consider about 0's last time (latest time). This needs to be implemented. 
	// Needs to check the part about duration. (TypeAndDuration)
	for (int day = 0; day < nDays; day++) {
		
		//std::cout << "Day " << day << " started. " << std::endl;

		std::vector<int> wholeList = solutionListOfEachDay[day];

		// Sort all synchronized nodes
		std::vector<std::vector<int>> nonSortedLists = std::vector<std::vector<int>>(nRoutes);;
		int temp = 0; 
		for (int i = 0; i < wholeList.size(); i++) {

			if (wholeList[i] == -1) {

				temp++;
				continue;
			}
			nonSortedLists[temp].push_back(wholeList[i]);
		}

		//std::cout << "nonSortedLists: " << std::endl;
		//for (int i = 0; i < nRoutes; i++) {

		//	for (int j = 0; j < nonSortedLists[i].size(); j++) {

		//		std::cout << nonSortedLists[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}

		int* currentIndexes = new int[nRoutes];
		for (int i = 0; i < nRoutes; i++) {

			currentIndexes[i] = 0;
		}
		std::vector<int> sortedList;
		while(1) {

			int smallest = std::numeric_limits<int>::max();
			bool finished = true;
			int chosenRoute = 0;
			for (int i = 0; i < nRoutes; i++) {

				if (currentIndexes[i] >= nonSortedLists[i].size()) {

					continue;
				}
				int currentNode = nonSortedLists[i][currentIndexes[i]];
				//std::cout << "Examine " << currentNode << std::endl;
				if (correspondingList[currentNode] == 0) {

					currentIndexes[i]++;
					i--;
					continue;
				}
				//std::cout << "Start compare " << currentNode << std::endl;
				if (arrivalTimes[currentNode][day] < smallest) {

					chosenRoute = i;
					finished = false;
					smallest = arrivalTimes[currentNode][day];
				}
			}
			if (finished == true) {

				break;
			}
			//std::cout << "chosenRoute: " << chosenRoute << ", nonSortedLists[chosenRoute][currentIndexes[chosenRoute]]: " << nonSortedLists[chosenRoute][currentIndexes[chosenRoute]] << std::endl;
			sortedList.push_back(nonSortedLists[chosenRoute][currentIndexes[chosenRoute]]);
			currentIndexes[chosenRoute]++;
		}
		//std::cout << "Sort result: " << std::endl;
		//for (int result : sortedList) {

		//	std::cout << result << " ";
		//}
		//std::cout << std::endl;
		//std::cout << "Sort completed" << std::endl;

		// If sortedList is empty, it means that there's no synchronized service on this day. 
		if (sortedList.size() != 0) {

			while (1) {

				//std::cout << "while loop started, length of sortedList: " << sortedList.size() << std::endl;
				// Get the earliest. 
				int chosenOne = sortedList[0];
				int correspondingOne = correspondingList[chosenOne];

				// If the normal and fictive node are on the same route, don't try to reduce the violation. 
				bool onTheSameRoute = false;
				for (int i = 0; i < nRoutes; i++) {

					if (std::find(nonSortedLists[i].begin(), nonSortedLists[i].end(), chosenOne) != nonSortedLists[i].end()) {

						if (std::find(nonSortedLists[i].begin(), nonSortedLists[i].end(), correspondingOne) != nonSortedLists[i].end()) {

							onTheSameRoute = true;
							break;
						}
						else {

							break;
						}
					}
				}
				if (onTheSameRoute) {
				
					// Remove the picked one and its corresponding node. 
					sortedList.erase(std::find(sortedList.begin(), sortedList.end(), chosenOne));
					sortedList.erase(std::find(sortedList.begin(), sortedList.end(), correspondingOne));
					
					// Make sure that we still have elements in sortedList, or we will need to break this loop. 
					if (sortedList.size() == 0) {

						break;
					}

					continue;
				}

				// Find all the nodes that will be affected
				int chosenRoute = 0;
				int positionOfChosenOne = 0;
				int* affectedNodes = NULL;
				int lengthOfAffectedNodes = 0;
				for (int j = 0; j < nRoutes; j++) {

					auto position = std::find(nonSortedLists[j].begin(), nonSortedLists[j].end(), chosenOne);
					if (position != nonSortedLists[j].end()) {

						positionOfChosenOne = (int)(position - nonSortedLists[j].begin());
						lengthOfAffectedNodes = nonSortedLists[j].size() - positionOfChosenOne - 1;
						affectedNodes = new int[lengthOfAffectedNodes];
						int tempIndex = 0;
						for (int k = positionOfChosenOne + 1; k < nonSortedLists[j].size(); k++) {

							affectedNodes[tempIndex] = nonSortedLists[j][k];
							tempIndex++;
						}
						chosenRoute = j;
						break;
					}
				}
				//std::cout << "Finding all the nodes that will be affected completed" << std::endl;
				//std::cout << "Affected nodes: " << std::endl;
				//for (int j = 0; j < lengthOfAffectedNodes; j++) {

				//	std::cout << affectedNodes[j] << " ";
				//}
				//std::cout << std::endl;

				// Calculate how long it would take to postpone to match its corresponding node. 
				int maxPostponedDuration = arrivalTimes[correspondingOne][day] - arrivalTimes[chosenOne][day];
				//std::cout << "Day: " << day << std::endl;
				//std::cout << "Node " << chosenOne << " needs to move " << maxPostponedDuration << std::endl;
				//std::cout << "Corresponding node: " << correspondingOne << std::endl;
				//std::cout << arrivalTimes[chosenOne][day] << " / " << arrivalTimes[correspondingOne][day] << std::endl;
				//std::cout << "/////////" << std::endl;
				//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
				//std::cout << "/////////" << std::endl;
				
				// For the next part, get typesAndDurations. 
				int numberOfGoodNodes = 1; // We already got a good node which is the one we are targeting. 
				int numberOfBadNodes = 0;
				std::vector<TypeAndDuration> typesAndDurations;

				// Also need to take its own time window into consideration. 
				if (earliestTime[chosenOne][day] > arrivalTimes[chosenOne][day]) {

					//std::cout << "earliest time: " << earliestTime[chosenOne][day] << ", arrival time: " << arrivalTimes[chosenOne][day] << std::endl;
					numberOfGoodNodes++;
					double duration = earliestTime[chosenOne][day] - arrivalTimes[chosenOne][day];
					typesAndDurations.push_back(TypeAndDuration(4, duration));
				}
				if (lastTime[chosenOne][day] > arrivalTimes[chosenOne][day]) {

					double duration = lastTime[chosenOne][day] - arrivalTimes[chosenOne][day];
					typesAndDurations.push_back(TypeAndDuration(1, duration));
				}
				else {

					numberOfBadNodes++;
				}

				// Get nextNode. 
				int nextNode = 0;
				if (positionOfChosenOne + 1 < solutionListOfEachDay[day].size()) {

					nextNode = solutionListOfEachDay[day][positionOfChosenOne + 1];
					if (nextNode == -1) {

						nextNode = 0;
					}
				}

				// If nextNode == 0, we need to take 0's latest time into consideration. 
				if (nextNode == 0) {

					double arrivalTimeOf0 = departureTimes[chosenOne][day] + timeMat[chosenOne][0];
					if (lastTime[0][day] > arrivalTimeOf0) {

						double duration = lastTime[0][day] - arrivalTimeOf0;
						typesAndDurations.push_back(TypeAndDuration(1, duration));
					}
					else {

						numberOfBadNodes++;
					}
				}

				// If there are affected nodes, you need to calculate how far you gonna push. 
				if (lengthOfAffectedNodes != 0) {
			
					// Calculate all the maximum distance that each node which will be affected if we move the node we picked before can move. 
					// In order to get our maximum moving distance for the picked node. 
					// If the duration is longer than the maxPostponedDuration, there's no reason to record it, since we can only postpone that much time. 
					// This part has problem. Need to be fixed. 
					int previousNode = chosenOne;
					double accumulatedPostponedDuration = 0;
					for (int j = 0; j < lengthOfAffectedNodes; j++) {

						//std::cout << "Start for loop!!!" << std::endl;
						int theOneToCalculate = affectedNodes[j];
						accumulatedPostponedDuration += postponedDuration[day][previousNode][theOneToCalculate];

						// If the accumulated postponed duration is already larger than the amount we want to push, break it. 
						if (accumulatedPostponedDuration >= maxPostponedDuration) {

							break;
						}

						if (arrivalTimes[theOneToCalculate][day] < earliestTime[theOneToCalculate][day]) {

							typesAndDurations.push_back(TypeAndDuration(2, accumulatedPostponedDuration));
							double duration = (earliestTime[theOneToCalculate][day] - arrivalTimes[theOneToCalculate][day] + accumulatedPostponedDuration);
							if (duration < maxPostponedDuration) {

								typesAndDurations.push_back(TypeAndDuration(4, duration));
							}
						}
						else if (arrivalTimes[theOneToCalculate][day] >= lastTime[theOneToCalculate][day]) {

							typesAndDurations.push_back(TypeAndDuration(1, accumulatedPostponedDuration));
						}
						else {

							double duration = (lastTime[theOneToCalculate][day] - arrivalTimes[theOneToCalculate][day] + accumulatedPostponedDuration);
							if (duration < maxPostponedDuration) {

								typesAndDurations.push_back(TypeAndDuration(1, duration));
							}
						}
						
						// If this is the last one, which means the vehicle needs to go back to 0 after this service, we need to take 0's latest time into consideration. 
						// It is not efficient to write this in this for loop. This is for reducing the length of code. 
						if (j == lengthOfAffectedNodes - 1) {

							double arrivalTimeOf0 = departureTimes[theOneToCalculate][day] + timeMat[theOneToCalculate][0];
							if (lastTime[0][day] > arrivalTimeOf0) {

								typesAndDurations.push_back(TypeAndDuration(1, arrivalTimeOf0 + accumulatedPostponedDuration));
							}
							else {

								typesAndDurations.push_back(TypeAndDuration(1, accumulatedPostponedDuration));
							}
						}

						//std::cout << "theOneToCalculate:  " << theOneToCalculate << ", day:  " << day << std::endl;

						// Might not need this section, because those affected synchronized services, can be adjusted later. 
						// If we take this into consideration, it will make the node that we want to push forward stuck (numberOfGoodNodes <= numberOfBadNodes), and we won't be able to get the minimal violation score. 
						// The reason why this can work is because after we push this node forward, other nodes can't affected it at all. 
						// Deal with the synchronized one. 
						//if (correspondingList[theOneToCalculate] != 0) {

						//	if (arrivalTimes[correspondingList[theOneToCalculate]][day] <= arrivalTimes[theOneToCalculate][day]) {

						//		typesAndDurations.push_back(TypeAndDuration(1, accumulatedPostponedDuration));
						//	}
						//	else {

						//		typesAndDurations.push_back(TypeAndDuration(2, accumulatedPostponedDuration));
						//		double duration = (arrivalTimes[correspondingList[theOneToCalculate]][day] - arrivalTimes[theOneToCalculate][day] + accumulatedPostponedDuration);
						//		if (duration < maxPostponedDuration) {

						//			typesAndDurations.push_back(TypeAndDuration(3, duration));
						//		}
						//	}
						//}
						//std::cout << "Initialize typesAndDurations finished" << std::endl;
						previousNode = theOneToCalculate;
					}
				}

				// put our goal in it. 
				typesAndDurations.push_back(TypeAndDuration(0, maxPostponedDuration));

				// Sort the durations and types together. 
				// This part needs to be checked, once we finished other parts. 
				std::sort(typesAndDurations.begin(), typesAndDurations.end());
				
				// By go over the durations and types, we can get our best moving distance. 
				double currentPostponedDuration = 0;
				for (int j = 0; j < typesAndDurations.size(); j++) {

					if (numberOfGoodNodes > numberOfBadNodes) {

						currentPostponedDuration = typesAndDurations[j].duration;
						if (typesAndDurations[j].type == 0) {

							break;
						}
						switch(typesAndDurations[j].type) {

						case 1:
							numberOfBadNodes++;
							break;
						case 2: 
							numberOfGoodNodes++;
							break;
						case 3: 
							numberOfGoodNodes++;
							numberOfBadNodes++;
							break;
						case 4:
							numberOfGoodNodes--;
							break;
						default:

							std::cout << "Error occurred when we try to find our best moving distance by going over the durations and types. " << std::endl;
							exit(1);
						}
					}
					else {

						break;
					}
				}

				// Postpone it by currentPostpondDuration. 
				for (int j = 0; j < solutionListOfEachDay[day].size(); j++) {

					if (solutionListOfEachDay[day][j] == chosenOne) {

						//std::cout << "Current postponed duration: " << currentPostponedDuration << std::endl;
						arrivalTimes[chosenOne][day] += currentPostponedDuration;
						departureTimes[chosenOne][day] += currentPostponedDuration;
						int previousOne = 0;
						if (j != 0) {

							previousOne = solutionListOfEachDay[day][j - 1];
							if (previousOne == -1) {

								previousOne = 0;
							}
						}
						postponedDuration[day][previousOne][chosenOne] += currentPostponedDuration;

						int previousNode = solutionListOfEachDay[day][j];
						for (int k = j + 1; k < solutionListOfEachDay[day].size(); k++) {

							if (solutionListOfEachDay[day][k] == -1) {

								break;
							}
							currentPostponedDuration -= postponedDuration[day][previousNode][solutionListOfEachDay[day][k]];
							if (currentPostponedDuration <= 0) {

								postponedDuration[day][previousNode][solutionListOfEachDay[day][k]] -= (currentPostponedDuration + postponedDuration[day][previousNode][solutionListOfEachDay[day][k]]);
								break;
							}
							else {

								postponedDuration[day][previousNode][solutionListOfEachDay[day][k]] = 0;
							}
							arrivalTimes[solutionListOfEachDay[day][k]][day] += currentPostponedDuration;
							departureTimes[solutionListOfEachDay[day][k]][day] += currentPostponedDuration;
							previousNode = solutionListOfEachDay[day][k];
						}
						break;
					}
				}
				
				// Remove the picked one and its corresponding node. 
				sortedList.erase(std::find(sortedList.begin(), sortedList.end(), chosenOne));
				sortedList.erase(std::find(sortedList.begin(), sortedList.end(), correspondingOne));

				// Then, rearrange every node, since the arrival time of some of them has been changed. 
				for (int j = sortedList.size() - 1; j >= 1; j--) { 

					if (arrivalTimes[sortedList[j]][day] < arrivalTimes[sortedList[j - 1]][day]) {

						std::swap(sortedList[j], sortedList[j - 1]);
						for (int k = j; k < sortedList.size() - 1; k++) {

							if (arrivalTimes[sortedList[k]][day] < arrivalTimes[sortedList[k + 1]][day]) {

								std::swap(sortedList[k], sortedList[k + 1]);
							}
							else {

								break;
							}
						}
					}
				}
				
				// Make sure that we still have elements in sortedList, or we will need to break this loop. 
				if (sortedList.size() == 0) {

					break;
				}
			}
		}
		//std::cout << "Day " << day << " finished. " << std::endl;
	}
	//std::cout << "Rearranging the arrival time of each synchronized service successes. " << std::endl;
	//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	
	//checkConstraintsResult = checkConstraints(solutionListOfEachDay);
	////std::cout << "checkConstraints done. " << std::endl;
	//if (checkConstraintsResult.result == false) {

	//	printGraph(solutionListOfEachDay, GRAPH_LIMIT);
	//	std::cout << "After rearranging the arrival time of each synchronized service" << std::endl;
	//	std::cout << "Violation detected ----------------------------------" << std::endl;
	//	for (std::string message : checkConstraintsResult.messages) {

	//		std::cout << message << std::endl;
	//	}
	//	std::cout << "-----------------------------------------------------" << std::endl;
	//}
}

double Solution::getMaxPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double accumulatedPostponedDuration, bool firstLoop) {

	//std::cout << "getMaxPF started" << std::endl;
	static std::vector<int> routesHavingBeenCalculated;
	if (firstLoop) {

		routesHavingBeenCalculated.clear();
		int route = 0;
		for (int i = 0; i < positionOfNode; i++) {

			if (solutionListOfEachDay[day][i] == -1) {

				route++;
			}
		}
		routesHavingBeenCalculated.push_back(route);
	}
	double maxPF = std::numeric_limits<double>::max();
	while (positionOfNode < solutionListOfEachDay[day].size() && solutionListOfEachDay[day][positionOfNode] != -1) {

		int currentNode = solutionListOfEachDay[day][positionOfNode];
		int nextNode = 0;
		if (positionOfNode != solutionListOfEachDay[day].size() - 1) {

			nextNode = solutionListOfEachDay[day][positionOfNode + 1];
			if (nextNode == -1) {

				nextNode = 0;
			}
		}

		//std::cout << "seciont 1" << std::endl;
		//std::cout << "currentNode: " << currentNode << std::endl;

		// If currentNode is a fictive node, then we need to translate it into its original number. 
		//int normalNode = 1;
		//if (currentNode <= nNormals) {

		//	normalNode = currentNode;
		//}
		//else {

		//	normalNode = correspondingList[currentNode];
		//}

		//std::vector<int> daysOfEarliestArrivalTime = daysOfEarliestArrivalTimeOfEachCustomer[normalNode];
		//std::vector<int> daysOfLatestArrivalTime = daysOfLatestArrivalTimeOfEachCustomer[normalNode];

		// Check how far it can move according to whether it will increase the objective score. 
		//if (std::find(daysOfLatestArrivalTime.begin(), daysOfLatestArrivalTime.end(), day) != daysOfLatestArrivalTime.end()) {

		//	if (std::find(daysOfEarliestArrivalTime.begin(), daysOfEarliestArrivalTime.end(), day) != daysOfEarliestArrivalTime.end()) {

		//		
		//	}
		//	if (accumulatedPostponedDuration < maxPF) {

		//		std::cout << "currentNode: " << currentNode << ", accumulatedPostponedDuration: " << accumulatedPostponedDuration << std::endl;
		//	}
		//	maxPF = std::min(maxPF, accumulatedPostponedDuration);
		//}
		//else {

		//	double duration = arrivalTimes[normalNode][daysOfLatestArrivalTime[0]] - arrivalTimes[normalNode][day] + accumulatedPostponedDuration;
		//	if (duration < maxPF) {

		//		std::cout << "currentNode: " << currentNode << ", duration: " << duration << std::endl;
		//	}
		//	maxPF = std::min(maxPF, duration);
		//}

		// Check how far it can move according to whether it will exceeds its own time window. 
		double duration = lastTime[currentNode][day] - arrivalTimes[currentNode][day];
		maxPF = std::min(maxPF, duration + accumulatedPostponedDuration);

		// If nextNode == 0, we need to take 0's latest time into consideration. 
		if (nextNode == 0) {

			double arrivalTimeOf0 = departureTimes[currentNode][day] + timeMat[currentNode][0];
			//std::cout << "currentNode: " << currentNode << std::endl;
			//std::cout << "departureTimes[currentNode][day]: " << departureTimes[currentNode][day] << std::endl;
			//std::cout << "accumulatedPostponedDuration: " << accumulatedPostponedDuration << std::endl;
			//std::cout << "lastTime[0][day] - arrivalTimeOf0 + accumulatedPostponedDuration: " << lastTime[0][day] - arrivalTimeOf0 + accumulatedPostponedDuration << std::endl;
			maxPF = std::min(maxPF, lastTime[0][day] - arrivalTimeOf0 + accumulatedPostponedDuration);
		}

		// If maxPF is already smaller than 0, then the node we want to move is already not movable. 
		if (maxPF <= 0) {

			return maxPF;
		}

		//std::cout << "seciont 2" << std::endl;
		// Deal with the synchronized one. 
		if (correspondingList[currentNode] != 0) {

			int correspondingNode = correspondingList[currentNode];
			int positionOfCorrespondingNode = 0;
			int routeOfCorrespondingNode = 0;
			for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

				if (solutionListOfEachDay[day][i] == -1) {

					routeOfCorrespondingNode++;
					continue;
				}
				if (solutionListOfEachDay[day][i] == correspondingNode) {

					positionOfCorrespondingNode = i;
					break;
				}
			}
			
			// Check if we have taken this route into consideration. 
			if (std::find(routesHavingBeenCalculated.begin(), routesHavingBeenCalculated.end(), routeOfCorrespondingNode) == routesHavingBeenCalculated.end()) {

				routesHavingBeenCalculated.push_back(routeOfCorrespondingNode);
				//double oldMaxPF = maxPF; // For testing

				// Check if there are other node ahead of corresponding node. 
				if (positionOfCorrespondingNode + 1 < solutionListOfEachDay[day].size() && solutionListOfEachDay[day][positionOfCorrespondingNode + 1] != -1) {

					double accumulatedPostponedDurationForAnotherRoute;
					accumulatedPostponedDurationForAnotherRoute = accumulatedPostponedDuration + postponedDuration[day][correspondingNode][solutionListOfEachDay[day][positionOfCorrespondingNode + 1]];
					maxPF = std::min(maxPF, getMaxPF(solutionListOfEachDay, positionOfCorrespondingNode + 1, day, accumulatedPostponedDurationForAnotherRoute, false));
				}
				//if (oldMaxPF != maxPF) {

				//	std::cout << "currentNode: " << currentNode << ", because of correspondingNode, change to : " << maxPF << std::endl;
				//}
			}
		}
		//std::cout << "seciont 3" << std::endl;

		accumulatedPostponedDuration += postponedDuration[day][currentNode][nextNode];
		positionOfNode++;
	}

	return maxPF;
}

// Assume all the synchronized service has no violation. 
// This function needs to be adjusted to use daysOfMinArrivalTimeOfEachCustomer and daysOfLatestArrivalTimeOfEachCustomer. 
CustomerAndArrivalTimeDifference Solution::getTheCustomerWithLargestArrivalTimeDifference() {

	int theChosenOne = 1;
	double valueOfTheChosenOne = 0;
	int dayOfEarliestArrivalTime = 0;
	int dayOfLatestArrivalTime = 0;
	for (int i = 1; i <= nNormals; i++) {

		//std::cout << i << ", " << daysOfLatestArrivalTimeOfEachCustomer[i].size() << ", " << daysOfEarliestArrivalTimeOfEachCustomer[i].size() << std::endl;
		double difference = arrivalTimes[i][daysOfLatestArrivalTimeOfEachCustomer[i][0]] - arrivalTimes[i][daysOfEarliestArrivalTimeOfEachCustomer[i][0]];
		if (difference > valueOfTheChosenOne) {

			theChosenOne = i;
			valueOfTheChosenOne = difference;
			dayOfEarliestArrivalTime = daysOfEarliestArrivalTimeOfEachCustomer[i][0];
			dayOfLatestArrivalTime = daysOfLatestArrivalTimeOfEachCustomer[i][0];
		}
	}
	struct CustomerAndArrivalTimeDifference customerAndDifference;
	customerAndDifference.customer = theChosenOne;
	customerAndDifference.difference = valueOfTheChosenOne;
	customerAndDifference.dayOfEarliestArrivalTime = dayOfEarliestArrivalTime;
	customerAndDifference.dayOfLatestArrivalTime = dayOfLatestArrivalTime;
	return customerAndDifference;
}

std::vector<int>* Solution::applyPF(const std::vector<std::vector<int>>& solutionListOfEachDay, int positionOfNode, int day, double PF, bool firstLoop) {

	static std::vector<int> routesHavingBeenApplied;

	std::vector<int>* nodesBeingMovedPtr = new std::vector<int>();
	int previousNode = 0;
	if (positionOfNode > 0) {

		previousNode = solutionListOfEachDay[day][positionOfNode - 1];
		if (previousNode == -1) {

			previousNode = 0;
		}
	}

	if (firstLoop) {

		routesHavingBeenApplied.clear();
		int routeOfCurrentNode = 0;
		for (int i = 0; i < positionOfNode; i++) {

			if (solutionListOfEachDay[day][i] == -1) {

				routeOfCurrentNode++;
			}
		}
		routesHavingBeenApplied.push_back(routeOfCurrentNode);

		int currentNode = solutionListOfEachDay[day][positionOfNode];
		postponedDuration[day][previousNode][currentNode] += PF;
	}

	// The part about getting currentNode and nextNode can be more optimized, but it will lose its readability, so I keep it this way. 
	for (int i = positionOfNode; i < solutionListOfEachDay[day].size(); i++) {

		// Get currentNode. 
		int currentNode = solutionListOfEachDay[day][i];
		if (currentNode == -1) {

			break;
		}
		// Transform it into its normal node if it is a fictive node. (Just its number)
		if (currentNode > nNormals) {

			currentNode = correspondingList[currentNode];
		}

		// Get nextNode. 
		int nextNode = 0;
		if (i < solutionListOfEachDay[day].size() - 1) {

			nextNode = solutionListOfEachDay[day][i + 1];
			if (nextNode == -1) {

				nextNode = 0;
			}
		}

		//std::cout << "i: " << i << std::endl;
		//std::cout << "currentNode: " << currentNode << std::endl;
		//std::cout << "nextNode: " << nextNode << std::endl;

		// Apply it. 
		arrivalTimes[currentNode][day] += PF;
		departureTimes[currentNode][day] += PF;

		// Deal with the synchronized node. 
		int correspondingNode = correspondingList[currentNode];
		if (correspondingNode != 0) {

			int positionOfCorrespondingNode = 0;
			int routeOfCorrespondingNode = 0;
			for (int j = 0; j < solutionListOfEachDay[day].size(); j++) {

				if (solutionListOfEachDay[day][j] == -1) {

					routeOfCorrespondingNode++;
					continue;
				}
				if (solutionListOfEachDay[day][j] == correspondingNode) {

					positionOfCorrespondingNode = j;
					break;
				}
			}

			// Avoid ReApplying. 
			if (std::find(routesHavingBeenApplied.begin(), routesHavingBeenApplied.end(), routeOfCorrespondingNode) == routesHavingBeenApplied.end()) {

				//std::cout << "deal with synchronized customer in applyPF" << std::endl;
				//std::cout << "currentNode: " << currentNode << ", correspondingNode: " << correspondingNode << std::endl;
				routesHavingBeenApplied.push_back(routeOfCorrespondingNode);

				int previousNodeForCorrespondingNode = 0;
				if (positionOfCorrespondingNode > 0) {

					previousNodeForCorrespondingNode = solutionListOfEachDay[day][positionOfCorrespondingNode - 1];
					if (previousNodeForCorrespondingNode == -1) {

						previousNodeForCorrespondingNode = 0;
					}
				}
				
				int nextNodeForCorrespondingNode = 0;
				if (positionOfCorrespondingNode < solutionListOfEachDay[day].size() - 1) {

					nextNodeForCorrespondingNode = solutionListOfEachDay[day][positionOfCorrespondingNode + 1];
					if (nextNodeForCorrespondingNode == -1) {

						nextNodeForCorrespondingNode = 0;
					}
				}

				// Apply it. 
				postponedDuration[day][previousNodeForCorrespondingNode][correspondingNode] += PF;
				arrivalTimes[correspondingNode][day] += PF;
				departureTimes[correspondingNode][day] += PF;

				// Adjust PF for corresponding node. 
				double tempPostponedDuration = postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode];
				double tempPF = PF;
				if (tempPF <= tempPostponedDuration) {

					postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode] -= tempPF;
				}
				else {

					//std::cout << "tempPF: " << tempPF << std::endl;
					//std::cout << "tempPostponedDuration: " << tempPostponedDuration << std::endl;
					postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode] = 0; // This is equal to postponedDuration[day][correspondingNode][nextNodeForCorrespondingNode] -= tempPostponedDuration;
					tempPF -= tempPostponedDuration;
					//std::cout << "Next applyPF!!!!!!!" << std::endl;
					//std::cout << "positionOfCorrespondingNode" << positionOfCorrespondingNode << std::endl;
					std::vector<int>* otherNodesBeingMovedPtr = applyPF(solutionListOfEachDay, positionOfCorrespondingNode + 1, day, tempPF, false);
					nodesBeingMovedPtr->reserve(nodesBeingMovedPtr->size() + otherNodesBeingMovedPtr->size());
					nodesBeingMovedPtr->insert(nodesBeingMovedPtr->end(), otherNodesBeingMovedPtr->begin(), otherNodesBeingMovedPtr->end());
					delete otherNodesBeingMovedPtr;
				}
			}
		}

		// Adjust PF. 
		double tempPostponedDuration = postponedDuration[day][currentNode][nextNode];
		if (PF <= tempPostponedDuration) {

			postponedDuration[day][currentNode][nextNode] -= PF;
			break;
		}
		else {

			postponedDuration[day][currentNode][nextNode] = 0; // This is equal to postponedDuration[day][currentNode][nextNode] -= tempPostponedDuration;
			PF -= tempPostponedDuration;
		}

		// Add it into nodesBeingMoved
		nodesBeingMovedPtr->push_back(currentNode);
		
		// Get previousNode for next iteration. 
		previousNode = currentNode;
	}
	
	//std::cout << "End of applyPF!!!!!!!" << std::endl;
	return nodesBeingMovedPtr;
}

// This version can only deal with solution with no violation. 
void Solution::adjustDepartureTime(std::vector<std::vector<int>>& solutionListOfEachDay) {

	// Calculate daysOfEarliestArrivalTimeOfEachCustomer, and daysOfLatestArrivalTimeOfEachCustomer
	// To fill 0's position. 
	for (int i = 1; i <= nNormals; i++) {

		daysOfEarliestArrivalTimeOfEachCustomer[i].clear();
		daysOfLatestArrivalTimeOfEachCustomer[i].clear();
		double minArrivalTime = INT_MAX;
		double maxArrivalTime = -1;
		for (int day = 0; day < nDays; day++) {

			if (required[i][day] == false) {

				continue;
			}
			double tempArrivalTime = arrivalTimes[i][day];
			if (tempArrivalTime < minArrivalTime) {

				daysOfEarliestArrivalTimeOfEachCustomer[i].clear();
				daysOfEarliestArrivalTimeOfEachCustomer[i].push_back(day);
				minArrivalTime = tempArrivalTime;
			}
			else if (tempArrivalTime == minArrivalTime) {

				daysOfEarliestArrivalTimeOfEachCustomer[i].push_back(day);
			}
			if (tempArrivalTime > maxArrivalTime) {

				daysOfLatestArrivalTimeOfEachCustomer[i].clear();
				daysOfLatestArrivalTimeOfEachCustomer[i].push_back(day);
				maxArrivalTime = tempArrivalTime;
			}
			else if (tempArrivalTime == maxArrivalTime) {

				daysOfLatestArrivalTimeOfEachCustomer[i].push_back(day);
			}
		}
	}
	//std::cout << "Initializing daysOfEarliestArrivalTimeOfEachCustomer and daysOfLatestArrivalTimeOfEachCustomer finished. " << std::endl;
	//for (int i = 1; i <= nNormals; i++) {

	//	std::cout << "Node " << i << ": (";
	//	std::cout << daysOfEarliestArrivalTimeOfEachCustomer[i][0];
	//	for (int j = 1; j < daysOfEarliestArrivalTimeOfEachCustomer[i].size(); j++) {

	//		std::cout << ", " << daysOfEarliestArrivalTimeOfEachCustomer[i][j];
	//	}
	//	std::cout << " / " << daysOfLatestArrivalTimeOfEachCustomer[i][0];
	//	for (int j = 1; j < daysOfLatestArrivalTimeOfEachCustomer[i].size(); j++) {

	//		std::cout << ", " << daysOfLatestArrivalTimeOfEachCustomer[i][j];
	//	}
	//	std::cout << ")" << std::endl;
	//}
	
	// Start finding. 
	double maxMovingDuration = INT_MAX;
	while(1) {
		
		//CheckConstraintsResult checkConstraintsResult = checkConstraints(solutionListOfEachDay);
		//if (checkConstraintsResult.result == false) {

		//	printGraph(solutionListOfEachDay, GRAPH_LIMIT);
		//	std::cout << "Violation detected ----------------------------------" << std::endl;
		//	for (std::string message : checkConstraintsResult.messages) {

		//		std::cout << message << std::endl;
		//	}
		//	std::cout << "-----------------------------------------------------" << std::endl;
		//	exit(1);
		//}

		//std::cout << "///////////////////////////////////////////////////////////////////////////////////////" << std::endl;
		//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
		//std::cout << "///////////////////////////////////////////////////////////////////////////////////////" << std::endl;
		//for (int i = 1; i <= nNormals; i++) {

		//	std::cout << "Node " << i << ": (";
		//	std::cout << arrivalTimes[i][daysOfEarliestArrivalTimeOfEachCustomer[i][0]] << ", " << arrivalTimes[i][daysOfLatestArrivalTimeOfEachCustomer[i][0]] << ") " << std::endl;
		//}
		//for (int i = 1; i <= nNormals; i++) {

		//	std::cout << "Node " << i << ": (";
		//	std::cout << daysOfEarliestArrivalTimeOfEachCustomer[i][0];
		//	for (int j = 1; j < daysOfEarliestArrivalTimeOfEachCustomer[i].size(); j++) {

		//		std::cout << ", " << daysOfEarliestArrivalTimeOfEachCustomer[i][j];
		//	}
		//	std::cout << " / " << daysOfLatestArrivalTimeOfEachCustomer[i][0];
		//	for (int j = 1; j < daysOfLatestArrivalTimeOfEachCustomer[i].size(); j++) {

		//		std::cout << ", " << daysOfLatestArrivalTimeOfEachCustomer[i][j];
		//	}
		//	std::cout << ")" << std::endl;
		//}

		// Find the customer with the largest arrival time difference. 
		CustomerAndArrivalTimeDifference customerWithLargestArrivalTimeDifferenceAndItsDifference = getTheCustomerWithLargestArrivalTimeDifference();
		//std::cout << "Getting customer with largest arrival time difference finished. " << std::endl;
		//std::cout << "We got " << customerWithLargestArrivalTimeDifferenceAndItsDifference.customer << std::endl;
		//std::cout << "Difference:  " << customerWithLargestArrivalTimeDifferenceAndItsDifference.difference << std::endl;

		// Get the maximum moving duration and the days that are the most extense. Since we are going to push forward, we only need the day of minimum arrival time. 
		maxMovingDuration = customerWithLargestArrivalTimeDifferenceAndItsDifference.difference;
		int dayOfEarliestArrivalTime = customerWithLargestArrivalTimeDifferenceAndItsDifference.dayOfEarliestArrivalTime;
		int dayOfLatestArrivalTime = customerWithLargestArrivalTimeDifferenceAndItsDifference.dayOfLatestArrivalTime;

		// Try to push forward. 
		// Get the customer with largest arrival time difference
		int customerWithLargestArrivalTimeDifference = customerWithLargestArrivalTimeDifferenceAndItsDifference.customer;

		// We don't need this section anymore, because we had already avoid calculating fictive nodes. 
		// If it is a fictive node, change to its corresponding normal node. 
		//if (correspondingList[customerWithLargestArrivalTimeDifference] > nNormals) {

		//	customerWithLargestArrivalTimeDifference = correspondingList[customerWithLargestArrivalTimeDifference];
		//}

		// Get the position of customer with largest arrival time difference. 
		int positionOfCustomerWithLargestArrivalTimeDifference = 0;
		for (int i = 0; i < solutionListOfEachDay[dayOfEarliestArrivalTime].size(); i++) {

			if (solutionListOfEachDay[dayOfEarliestArrivalTime][i] == customerWithLargestArrivalTimeDifference) {

				positionOfCustomerWithLargestArrivalTimeDifference = i;
				break;
			}
		}

		//std::cout << "/////////" << std::endl;
		//std::cout << arrivalTimes[solutionListOfEachDay[dayOfEarliestArrivalTime][positionOfCustomerWithLargestArrivalTimeDifference]][dayOfEarliestArrivalTime] << std::endl;
		//std::cout << "/////////" << std::endl;

		// Get those blocking customer. Calculate their maxPF. 
		maxMovingDuration = std::min(maxMovingDuration, getMaxPF(solutionListOfEachDay, positionOfCustomerWithLargestArrivalTimeDifference, dayOfEarliestArrivalTime, 0, true));
		//std::cout << "Getting maxMovingDuration finished. " << std::endl;
		//std::cout << "maxMovingDuration: " << maxMovingDuration << std::endl;

		// Apply PF. 
		std::vector<int>* nodesBeingMovedPtr;
		if (maxMovingDuration > 0) {

			nodesBeingMovedPtr = applyPF(solutionListOfEachDay, positionOfCustomerWithLargestArrivalTimeDifference, dayOfEarliestArrivalTime, maxMovingDuration, true);
			//std::cout << "nodesBeingMoved: ";
			//for (int t = 0; t < nodesBeingMovedPtr->size(); t++) {

			//	std::cout << nodesBeingMovedPtr->at(t) << ", ";
			//}
			//std::cout << std::endl;
			//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
		}
		else {

			// Break this while loop. 
			break;
		}

		// We have to know which node have been pushed and recalculate their minimum arrival time difference and maximum arrival time difference. 
		// The nodes in nodesBeingMoved are all normal nodes, not fictive nodes. 
		std::vector<bool> nodesHavingBeenRecalculated(nNodes, false);
		for (int i = 0; i < nodesBeingMovedPtr->size(); i++) {

			int nodeBeingGoingToRecalculate = nodesBeingMovedPtr->at(i);
			if (nodesHavingBeenRecalculated[nodeBeingGoingToRecalculate]) {

				continue;
			}
			nodesHavingBeenRecalculated[nodeBeingGoingToRecalculate] = true;

			daysOfEarliestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
			daysOfLatestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
			double minArrivalTime = INT_MAX;
			double maxArrivalTime = -1;
			for (int day = 0; day < nDays; day++) {

				if (required[nodeBeingGoingToRecalculate][day] == false) {

					continue;
				}
				double tempArrivalTime = arrivalTimes[nodeBeingGoingToRecalculate][day];
				if (tempArrivalTime < minArrivalTime) {

					daysOfEarliestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
					daysOfEarliestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
					minArrivalTime = tempArrivalTime;
				}
				else if (tempArrivalTime == minArrivalTime) {

					daysOfEarliestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
				}
				if (tempArrivalTime > maxArrivalTime) {

					daysOfLatestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].clear();
					daysOfLatestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
					maxArrivalTime = tempArrivalTime;
				}
				else if (tempArrivalTime == maxArrivalTime) {

					daysOfLatestArrivalTimeOfEachCustomer[nodeBeingGoingToRecalculate].push_back(day);
				}
			}
		}

		// Delete nodesBeingMovedPtr. 
		delete nodesBeingMovedPtr;
		//std::cout << "While done" << std::endl;
		//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
		//std::cin.get();
	}
}

double Solution::getViolationScore(const std::vector<std::vector<int>>& solutionListOfEachDay, double scaleOfViolationScore) {

	double violation = 0;
	for (int day = 0; day < nDays; day++) {

		for (int currentNode = 1; currentNode <= nNormals; currentNode++) {

			if (required[currentNode][day] == false) {

				continue;
			}
			if (earliestTime[currentNode][day] > arrivalTimes[currentNode][day]) {

				violation += earliestTime[currentNode][day] - arrivalTimes[currentNode][day];
			}
			if (lastTime[currentNode][day] < arrivalTimes[currentNode][day]) {

				violation += arrivalTimes[currentNode][day] - lastTime[currentNode][day];
			}
			if (correspondingList[currentNode] != 0) {

				int correspondingNode = correspondingList[currentNode];
				if (arrivalTimes[currentNode][day] != arrivalTimes[correspondingNode][day]) {

					violation += abs(arrivalTimes[currentNode][day] - arrivalTimes[correspondingNode][day]);
				}
			}
		}

		int previousNode = 0;
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			int currentNode = solutionListOfEachDay[day][i];
			if (currentNode == -1) {

				if (previousNode != 0) {

					if (departureTimes[previousNode][day] + timeMat[previousNode][0] > lastTime[0][day]) {

						violation += departureTimes[previousNode][day] + timeMat[previousNode][0] - lastTime[0][day];
					}
				}
				previousNode = 0;
				continue;
			}
			previousNode = currentNode;
		}
		if (previousNode != 0) {

			if (departureTimes[previousNode][day] + timeMat[previousNode][0] > lastTime[0][day]) {

				violation += departureTimes[previousNode][day] + timeMat[previousNode][0] - lastTime[0][day];
			}
		}
	}
	return violation * scaleOfViolationScore;
}

double Solution::getObjectiveScore(const std::vector<std::vector<int>>& solutionListOfEachDay) {

	double score = 0;
	for (int i = 1; i <= nNormals; i++) {

		double minArrivalTime = std::numeric_limits<double>::max();
		double maxArrivalTime = -1;
		for (int day = 0; day < nDays; day++) {

			if (required[i][day] == false) {

				continue;
			}
			if (arrivalTimes[i][day] < minArrivalTime) {

				minArrivalTime = arrivalTimes[i][day];
				//std::cout << "minArrivalTime: " << minArrivalTime << std::endl;
			}
			if (arrivalTimes[i][day] > maxArrivalTime) {

				maxArrivalTime = arrivalTimes[i][day];
				//std::cout << "maxArrivalTime: " << maxArrivalTime << std::endl;
			}
			if (correspondingList[i] != 0) {

				if (arrivalTimes[correspondingList[i]][day] < minArrivalTime) {

					minArrivalTime = arrivalTimes[correspondingList[i]][day];
					//std::cout << "Corresponding: " << "minArrivalTime: " << minArrivalTime << std::endl;
				}
				if (arrivalTimes[correspondingList[i]][day] > maxArrivalTime) {

					maxArrivalTime = arrivalTimes[correspondingList[i]][day];
					//std::cout << "Corresponding: " << "maxArrivalTime: " << maxArrivalTime << std::endl;
				}
			}
		}
		score += maxArrivalTime - minArrivalTime;
	}

	for (int day = 0; day < nDays; day++) {

		int currentNode = 0;
		int previousNode = 0;
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			if (solutionListOfEachDay[day][i] == -1) {

				currentNode = 0;
			}
			else {

				currentNode = solutionListOfEachDay[day][i];
			}
			if (currentNode == previousNode && currentNode == 0) {

				continue;
			}
			score += timeMat[previousNode][currentNode];
			//std::cout << "(" << previousNode << ", " << currentNode << ", " << timeMat[previousNode][currentNode] << ")" << std::endl;
			previousNode = currentNode;
		}
		score += timeMat[currentNode][0];
		//std::cout << "(" << currentNode << ", 0, " << timeMat[currentNode][0] << ")" << std::endl;
	}
	//std::cout << "getObjectiveScore: " << score << std::endl;
	return score;
}

void Solution::improveTimeConsistency(std::vector<std::vector<int>>& solutionListOfEachDay) {

	//std::cout << "improveTimeConsistency started" << std::endl;
	// Record the original score. 
	double originalScore = getObjectiveScore(solutionListOfEachDay);
	double newScore = originalScore;
	std::vector<std::vector<int>> alternativeSolution = std::vector<std::vector<int>>();
	alternativeSolution.reserve(nDays);
	for (int day = 0; day < nDays; day++) {

		alternativeSolution.push_back(solutionListOfEachDay[day]);
	}

	while (1) {

		bool betterOne = false;

		// Initialize
		for (int day = 0; day < nDays; day++) {

			alternativeSolution[day] = std::vector<int>(solutionListOfEachDay[day]);
		}

		//std::cout << "section 1" << std::endl;

		// Get the customer with the largest arrival time difference. 
		int customerWithLargestArrivalTimeDifference = 0;
		double largestDifference = -1;
		for (int i = 1; i <= nNormals; i++) {

			double difference = arrivalTimes[i][daysOfLatestArrivalTimeOfEachCustomer[i][0]] - arrivalTimes[i][daysOfEarliestArrivalTimeOfEachCustomer[i][0]];
			if (difference > largestDifference) {

				largestDifference = difference;
				customerWithLargestArrivalTimeDifference = i;
			}
		}
		//std::cout << "section 2" << std::endl;

		// Get its average arrival time, earliest arrival time, and latest arrival time. 
		int dayOfEarliestArrivalTime = daysOfEarliestArrivalTimeOfEachCustomer[customerWithLargestArrivalTimeDifference][0];
		int dayOfLatestArrivalTime = daysOfLatestArrivalTimeOfEachCustomer[customerWithLargestArrivalTimeDifference][0];
		double averageArrivalTime = 0;
		double earliestArrivalTime = arrivalTimes[customerWithLargestArrivalTimeDifference][dayOfEarliestArrivalTime];
		double latestArrivalTime = arrivalTimes[customerWithLargestArrivalTimeDifference][dayOfLatestArrivalTime];
		for (int day = 0; day < nDays; day++) {

			double arrivalTime = arrivalTimes[customerWithLargestArrivalTimeDifference][day];
			averageArrivalTime += (arrivalTime / nDays);
		}
		//std::cout << "section 3" << std::endl;

		// Decide which day to reverse
		// Also need to check if it is the special case. 
		// When there are more than two days being the earliest days or the latest days, we break this function. 
		// This is according to the original paper, not the one written by Jeff. 
		int dayToReverse = 0;
		if (averageArrivalTime - earliestArrivalTime < latestArrivalTime - averageArrivalTime) {

			dayToReverse = dayOfEarliestArrivalTime;
			if (daysOfEarliestArrivalTimeOfEachCustomer[customerWithLargestArrivalTimeDifference].size() > 1) {

				break;
			}
		}
		else {

			dayToReverse = dayOfLatestArrivalTime;
			if (daysOfLatestArrivalTimeOfEachCustomer[customerWithLargestArrivalTimeDifference].size() > 1) {

				break;
			}
		}
		//std::cout << "section 4" << std::endl;
		
		std::vector<std::vector<int>> bestSolutionSoFar;
		bestSolutionSoFar.resize(nDays);
		
		// Apply 2-opt to that day. 
		for (int k = 0; k < solutionListOfEachDay[dayToReverse].size(); k++) {

			for (int l = k + 1; l < solutionListOfEachDay[dayToReverse].size(); l++) {

				tweakADayOfSolutionWithTwoOptAlgorithm(alternativeSolution, dayToReverse, k, l);

				// Recalculate everything and get the score
				calculateObjective(alternativeSolution);
				
				newScore = getViolationScore(alternativeSolution, FACTOR_OF_VIOLATION);
				if (newScore == 0) {

					//printGraph(solutionListOfEachDay, GRAPH_LIMIT);
					adjustDepartureTime(alternativeSolution);
					newScore += getObjectiveScore(alternativeSolution);
					CheckConstraintsResult checkConstraintsResult = checkConstraints(alternativeSolution);
					//std::cout << "checkConstraints done. " << std::endl;
					if (checkConstraintsResult.result == false) {

						printGraph(alternativeSolution, GRAPH_LIMIT);
						std::cout << "Violation detected ----------------------------------" << std::endl;
						for (std::string message : checkConstraintsResult.messages) {

							std::cout << message << std::endl;
						}
						std::cout << "-----------------------------------------------------" << std::endl;
						exit(1);
					}
					//std::cout << "Score: " << newScore << std::endl;
				}
				
				if (newScore < originalScore) {
				
					betterOne = true;
					originalScore = newScore;
					for (int day = 0; day < nDays; day++) {

						solutionListOfEachDay[day] = std::vector<int>(alternativeSolution[day]);
					}
					for (int day = 0; day < nDays; day++) {

						bestSolutionSoFar[day] = std::vector<int>(alternativeSolution[day]);
					}
				}
			}
		}

		if (betterOne) {

			for (int day = 0; day < nDays; day++) {

				solutionListOfEachDay[day] = std::vector<int>(bestSolutionSoFar[day]);
			}
			calculateObjective(solutionListOfEachDay);
			adjustDepartureTime(solutionListOfEachDay);
		}
		else {

			break;
		}
	}

	return;
}

void Solution::tweakADayOfSolutionWithTwoOptAlgorithm(std::vector<std::vector<int>>& solutionListOfEachDay, int day, int k, int l) {

	if (k > l) {

		std::swap(k, l);
	}

	std::reverse(solutionListOfEachDay[day].begin() + k, solutionListOfEachDay[day].begin() + l);
	return;
}

double Solution::getRandomDecimal() {

    return ((double)rand() / RAND_MAX);
}

int Solution::getRandomInteger(int x) {

	int randomInteger = floor((double)rand() / (RAND_MAX) * x);
    return randomInteger == x ? x - 1 : randomInteger; // The reason why RAND_MAX has to add one is to eliminate the possibility the function return x. 
}

CheckConstraintsResult Solution::checkConstraints(const std::vector<std::vector<int>>& solutionListOfEachDay) {

	CheckConstraintsResult checkConstraintsResult;
	checkConstraintsResult.result = true;
	// Check service time
	for (int i = 1; i < nNodes; i++) {

		for (int day = 0; day < nDays; day++) {

			if (required[i][day] == false) {

				continue;
			}
			if (departureTimes[i][day] - arrivalTimes[i][day] != serviceTime[i][day]) {

				checkConstraintsResult.result = false;
				checkConstraintsResult.messages.push_back("Customer " + std::to_string(i) + " on Day " + std::to_string(day) + " service time didn't much. Correct value: " + std::to_string(serviceTime[i][day]) + ", wrong value: " + std::to_string(departureTimes[i][day] - arrivalTimes[i][day]));
			}
		}
	}

	// Check time window
	for (int i = 0; i < nNodes; i++) {

		for (int day = 0; day < nDays; day++) {

			if (required[i][day] == false) {

				continue;
			}
			if (arrivalTimes[i][day] < earliestTime[i][day]) {

				checkConstraintsResult.result = false;
				checkConstraintsResult.messages.push_back("Customer " + std::to_string(i) + " on Day " + std::to_string(day) + " serves too early. Earliest time: " + std::to_string(earliestTime[i][day]) + ". Arrival time: " + std::to_string(arrivalTimes[i][day]));
			}
			if (arrivalTimes[i][day] > lastTime[i][day]) {

				checkConstraintsResult.result = false;
				checkConstraintsResult.messages.push_back("Customer " + std::to_string(i) + " on Day " + std::to_string(day) + " serves too late. Latest time: " + std::to_string(lastTime[i][day]) + ". Arrival time: " + std::to_string(arrivalTimes[i][day]));
			}
		}
	}

	// Check synchronized service
	for (int i = 1; i <= nNormals; i++) {

		for (int day = 0; day < nDays; day++) {

			if (required[i][day] == false) {

				continue;
			}
			if (correspondingList[i] != 0) {

				if (arrivalTimes[i][day] != arrivalTimes[correspondingList[i]][day]) {

					checkConstraintsResult.result = false;
					checkConstraintsResult.messages.push_back("Customer " + std::to_string(i) + " on Day " + std::to_string(day) + " didn't synchronize. Node " + std::to_string(i) + ": " + std::to_string(arrivalTimes[i][day]) + ". Node " + std::to_string(correspondingList[i]) + ": " + std::to_string(arrivalTimes[correspondingList[i]][day]));
				}
			}
		}
	}

	// Check commuting time and postponedDuration
	for (int day = 0; day < nDays; day++) {

		int previousNode = 0;
		for (int i = 1; i < solutionListOfEachDay[day].size(); i++) {

			int currentNode = solutionListOfEachDay[day][i];
			if (currentNode == -1 && previousNode == 0) {

				continue;
			}
			if (currentNode == -1) {

				currentNode = 0;
				if (lastTime[currentNode][day] - departureTimes[previousNode][day] < timeMat[previousNode][currentNode]) {

					checkConstraintsResult.result = false;
					checkConstraintsResult.messages.push_back("Node " + std::to_string(previousNode) + " and node " + std::to_string(currentNode) + "\'s commmuting time is too short on day " + std::to_string(day) + ". Minimal commuting time: " + std::to_string(timeMat[previousNode][currentNode]) + ". Commuting time: " + std::to_string(lastTime[currentNode][day] - departureTimes[previousNode][day]));
				}
				previousNode = 0;
				continue;
			}
			if (previousNode == 0) {

				if (arrivalTimes[currentNode][day] - earliestTime[previousNode][day] < timeMat[previousNode][currentNode]) {

					checkConstraintsResult.result = false;
					checkConstraintsResult.messages.push_back("Node " + std::to_string(previousNode) + " and node " + std::to_string(currentNode) + "\'s commmuting time is too short on day " + std::to_string(day) + ". Minimal commuting time: " + std::to_string(timeMat[previousNode][currentNode]) + ". Commuting time: " + std::to_string(arrivalTimes[currentNode][day] - earliestTime[previousNode][day]));
				}
				previousNode = currentNode;
				continue;
			}
			if (arrivalTimes[currentNode][day] - departureTimes[previousNode][day] < timeMat[previousNode][currentNode]) {

				checkConstraintsResult.result = false;
				checkConstraintsResult.messages.push_back("Node " + std::to_string(previousNode) + " and node " + std::to_string(currentNode) + "\'s commmuting time is too short on day " + std::to_string(day) + ". Minimal commuting time: " + std::to_string(timeMat[previousNode][currentNode]) + ". Commuting time: " + std::to_string(arrivalTimes[currentNode][day] - departureTimes[previousNode][day]));
			}
			if (postponedDuration[day][previousNode][currentNode] != arrivalTimes[currentNode][day] - departureTimes[previousNode][day] - timeMat[previousNode][currentNode]) {

				checkConstraintsResult.result = false;
				checkConstraintsResult.messages.push_back("Node " + std::to_string(previousNode) + " and node " + std::to_string(currentNode) + "\'s postponed duration has problem. Correct: " + std::to_string(arrivalTimes[currentNode][day] - departureTimes[previousNode][day] - timeMat[previousNode][currentNode]) + ". Wrong: " + std::to_string(postponedDuration[day][previousNode][currentNode]));
			}
			
			previousNode = currentNode;
		}
		int currentNode = 0;
		if (previousNode != 0) {

			if (lastTime[currentNode][day] - departureTimes[previousNode][day] < timeMat[previousNode][currentNode]) {

				checkConstraintsResult.result = false;
				checkConstraintsResult.messages.push_back("Node " + std::to_string(previousNode) + " and node " + std::to_string(currentNode) + "\'s commmuting time is too short on day " + std::to_string(day) + ". Minimal commuting time: " + std::to_string(timeMat[previousNode][currentNode]) + ". Commuting time: " + std::to_string(lastTime[currentNode][day] - departureTimes[previousNode][day]));
			}
		}
	}

	return checkConstraintsResult;
}

// Width: 159 characters. 
void Solution::printGraph(const std::vector<std::vector<int>>& solutionListOfEachDay, double limit) {

	for (int day = 0; day < nDays; day++) {

		//if (day != 0) continue;
		std::cout << "\033[1;33mDay " << day << ": \033[0m";
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			std::cout << solutionListOfEachDay[day][i] << " ";
		}
		std::cout << std::endl;
		std::cout << "Arrival time: " << std::endl;
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			if (solutionListOfEachDay[day][i] != -1) {

				std::cout << solutionListOfEachDay[day][i] << ": " << arrivalTimes[solutionListOfEachDay[day][i]][day] << std::endl;
			}
		}
		std::cout << std::endl;
		std::cout << "Departure time: " << std::endl;
		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			if (solutionListOfEachDay[day][i] != -1) {

				std::cout << solutionListOfEachDay[day][i] << ": " << departureTimes[solutionListOfEachDay[day][i]][day] << std::endl;
			}
		}
		std::cout << std::endl;

		std::vector<PointAndType> pointsAndTypes;

		int route = 1;
		std::cout << "Route 1: " << std::endl;
		double unit = 10.0 / 159.0 * GRAPH_LIMIT;
		for (int i = 0; i < 4; i++) {

			std::cout << " ";
		}
		for (int i = 1; i <= 15; i++) {

			std::cout << std::setfill(' ') << std::setw(10) << std::left << unit * i;
		}
		std::cout << std::endl;
		printVerticalLines(2);

		for (int i = 0; i < solutionListOfEachDay[day].size(); i++) {

			int currentNode = solutionListOfEachDay[day][i];
			if (currentNode == -1) {

				printTimeLine(pointsAndTypes);

				route++;
				std::cout << "Route " << route << ":  |";
				for (int i = 1; i <= 14; i++) {

					for (int j = 0; j < 9; j++) {

						std::cout << " ";
					}
					std::cout << "|";
				}
				std::cout << std::endl;
				printVerticalLines(1);

				pointsAndTypes.clear();

				continue;
			}

			if (arrivalTimes[currentNode][day] > limit) {

				continue;
			}

			int point = std::floor(arrivalTimes[currentNode][day] / limit * 159);
			pointsAndTypes.push_back(PointAndType(point, 1, currentNode));

			if (departureTimes[currentNode][day] > limit) {

				continue;
			}

			point = std::floor(departureTimes[currentNode][day] / limit * 159);
			pointsAndTypes.push_back(PointAndType(point, 2, currentNode));
		}
		printTimeLine(pointsAndTypes);
		std::cout << std::endl;
	}
}

void Solution::printVerticalLines(int lines) {

	for (int k = 0; k < lines; k++) {

		std::cout << " ";
		for (int i = 1; i <= 15; i++) {

			for (int j = 0; j < 9; j++) {

				std::cout << " ";
			}
			std::cout << "|";
		}
		std::cout << std::endl;
	}
}

void Solution::printTimeLine(const std::vector<PointAndType>& pointsAndTypes) {

	int currentCursor = 0;
	for (int i = 0; i < pointsAndTypes.size(); i++) {

		if (pointsAndTypes[i].point > currentCursor) {

			for (int j = 0; j < pointsAndTypes[i].point - currentCursor; j++) {

				std::cout << "-";
			}
			currentCursor = pointsAndTypes[i].point;
		}
		else if (pointsAndTypes[i].point < currentCursor) {

			continue;
		}

		if (pointsAndTypes[i].type == 1) {

			std::cout << "\033[1;42m" << pointsAndTypes[i].value << "\033[0m";
		}
		else if (pointsAndTypes[i].type == 2) {

			std::cout << "\033[1;41m" << pointsAndTypes[i].value << "\033[0m";
		}

		currentCursor++;
	}
	std::cout << std::endl;
	printVerticalLines(1);
}
