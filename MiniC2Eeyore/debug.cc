#include "util.h"
#include <iostream>
using namespace std;

int debug = 1;
void debugPrint(string s){
    if(debug)
        cerr << s;
}