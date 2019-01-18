#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> a = vector<int>();
    a.push_back(0);
    a.push_back(1);
    for(auto it:a){
        cout << it << endl;
    }
}