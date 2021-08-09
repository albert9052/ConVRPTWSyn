#include <cstdlib>
#include <ctime>
#include "SA.h"
#include "LNS.h"
using namespace std;

int main(){
    srand(time(NULL));
	
	//LNS lns(5, 1, 0.9, 1, 1, 1);
	//LNS lns(300000, 30, 0.96, 12, 4, 7);

	// for test
	//vector<vector<int>> list = { {6, -1, 5, 7, -1, 4, 2}, { 3, 2, 5, -1, 6, -1, 7}, { 2, -1, 4, 7, -1 } };
	//lns.calculateObjective(list);

	//lns.input();
	//lns.solve();
	//lns.output();
	
	//cout << "bold red text" << std::endl;
	//cout << "\033[1;31mbold red text\033[0m\n";
	//int test[10];
	//test[0] = 12;
	//std::cout << test[-10] << std::endl;
	//std::cout << test[1] << std::endl;
	SA sa;
	//sa.input();
	sa.readData("Dataset/case_1_20_4_2_1.dat");
	sa.printInput();
	sa.solve();
}
