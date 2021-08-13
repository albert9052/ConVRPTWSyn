#include <cstdlib>
#include <ctime>
#include "SA.h"
#include "LNS.h"
using namespace std;

int main(){
    srand(time(NULL));

	//LNS lns(100000, 200, 0.99, 12, 4, 7);
	//lns.input();
	//lns.solve();
	
	
	//cout << "bold red text" << std::endl;
	//cout << "\033[1;31mbold red text\033[0m\n";
	//int test[10];
	//test[0] = 12;
	//std::cout << test[-10] << std::endl;
	//std::cout << test[1] << std::endl;
	//Ts = 100000000000;
	//Te = 0.0000000000001;
	//numberOfIterations = 100000;
	//Alpha = 0.1;
	
	//int numberOfCases = 5;
	//double bestScore = std::numeric_limits<int>::max();
	
	// Ts=100
	// Te=0.00000001
	// numberOfIterations=51200
	// Alpha=0.3
	//SA sa(100, 0.00000001, 51200, 0.3);
	//sa.readData("Dataset/case_1_20_4_2_1.dat");
	//sa.printInput();
	//for (double Alpha = 0.5; Alpha >= 0.1; Alpha -= 0.1) {

	//	double result = 0;
	//	for (int i = 0; i < numberOfCases; i++) {

	//		sa.Alpha = Alpha;
	//		sa.solve();
	//		result += sa.getTheBestScore() / numberOfCases;
	//	}
	//	std::cout << "Alpha: " << Alpha << ": " << result << std::endl;
	//}
	
	SA sa(100, 0.00000001, 51200, 0.3);
	sa.readData("Dataset/case_1_20_4_2_1.dat");
	sa.printInput();
	sa.solve();
	double score = sa.getTheBestScore();
	std::cout << score << std::endl;
}


//for (double Te = 0.000001; Te >= 0.00000000001; Te /= 10) {
//
//for (int numberOfIterations = 5000; numberOfIterations <= 100000; numberOfIterations + 5000) {
//
//for (double Alpha = 0.5; Alpha >= 0.01; Alpha /= 2) {
