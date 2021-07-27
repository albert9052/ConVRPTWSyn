#include <cstdlib>
#include <ctime>
#include "SA.h"
#include "LNS.h"
using namespace std;

int main(){
    //srand(time(NULL));
    //SA sa;
    //LNS lns(5, 1, 0.9, 1, 1, 1);
    //lns.input();
    //lns.solve();
    //lns.output();
	
	//cout << "bold red text" << std::endl;
	//cout << "\033[1;31mbold red text\033[0m\n";
	SA sa;
	sa.input();
	sa.solve();
}
