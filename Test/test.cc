#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    string s = "a";
    fstream f;
    f.open("tmp.txt",fstream::out);
    if(!f.is_open()){
        cerr << "fail openinig" << endl;
    }
    f << s << endl;
    f.close();
}