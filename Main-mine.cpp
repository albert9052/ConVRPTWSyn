#include <cstdlib>
#include <ctime>
#include <filesystem>
#include "SA.h"
#include "LNS.h"
using namespace std;

int main(){
    srand(time(NULL));

	//SA sa(100, 0.00000001, 51200, 0.3);
	//sa.readData("Dataset/case_1_80_16_8_3.dat");
	//sa.printInput();
	//std::cout << "start" << std::endl;
	//sa.solve();
	//std::cout << "end" << std::endl;
	//std::cout << "SA: " << sa.getTheBestScore() << std::endl;
	//exit(1);

	//int counter = 0;
	double bestFactor = 0;
	int numberOfValid = -1;
	for (double i = 10; i <= 100000000; i *= 10) {

		int counter = 0;
		std::cout << "FACTOR_OF_VIOLATION = " << i << ": " << std::endl;
		for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("./Dataset")) {

			string path = dirEntry.path();
			if (path.find("c101.dat") != std::string::npos) {

				continue;
			}
			if (path.find("case_2_80_16_8_3") != std::string::npos) {

				continue;
			}
			if (path.find("case_1_80_16_8_3") != std::string::npos) {

				continue;
			}
			//if (path.find("80") == std::string::npos) {

			//	continue;
			//}
			//counter++;
			//if (counter < 8) {

			//	continue;
			//}
			std::cout << dirEntry.path() << ": " << std::endl;

			SA sa(100, 0.00000001, 51200, 0.3, i);
			sa.readData(path);
			sa.solve();
			std::cout << "SA(" << ((sa.checkIfTheBestSolutionIsValid()) ? std::string("\033[1;32mvalid\033[0m") : std::string("\033[1;31minvalid\033[0m")) << "): " << sa.getTheBestScore() << std::endl;

			if (sa.checkIfTheBestSolutionIsValid()) {

				counter++;
			}

			//LNS lns(200000, 200, 0.99, 12, 4, 7);
			//lns.readData(path);
			////lns.input();
			//std::cout << "LNS: ";
			//lns.solve();
			//std::cout << std::endl;
		}
		std::cout << std::endl;
		if (counter > numberOfValid) {

			numberOfValid = counter;
			bestFactor = i;
		}
	}

	std::cout << "Best factor: " << bestFactor << std::endl;
	
	
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
	
	/*SA sa(100, 0.00000001, 51200, 0.3);
	sa.readData("Dataset/case_1_20_4_2_1.dat");
	sa.printInput();
	sa.solve();
	double score = sa.getTheBestScore();
	std::cout << score << std::endl;*/
}


//for (double Te = 0.000001; Te >= 0.00000000001; Te /= 10) {
//
//for (int numberOfIterations = 5000; numberOfIterations <= 100000; numberOfIterations + 5000) {
//
//for (double Alpha = 0.5; Alpha >= 0.01; Alpha /= 2) {
