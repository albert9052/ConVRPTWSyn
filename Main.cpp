#include <cstdlib>
#include <ctime>
#include "SA.h"
#include "LNS.h"
using namespace std;

int main(){
    srand(time(NULL));
    SA sa;
    LNS lns;
    lns.input();
    lns.solve();
    lns.output();
}
