#include <cstdlib>
#include <ctime>
#include "SA.h"
#include "LNS.h"
using namespace std;

int main(){
    srand(time(NULL));

	LNS lns(100000, 200, 0.99, 12, 4, 7);
	lns.input();
	lns.solve();
	
	
	//cout << "bold red text" << std::endl;
	//cout << "\033[1;31mbold red text\033[0m\n";
	//int test[10];
	//test[0] = 12;
	//std::cout << test[-10] << std::endl;
	//std::cout << test[1] << std::endl;
	//SA sa;
	////sa.input();
	//sa.readData("Dataset/case_1_20_4_2_1.dat");
	//sa.printInput();
	//sa.solve();
}
