#ifndef REGMAP_H
#define REGMAP_H

#include <set>
#include <map>
#include <string>

using namespace std;
const int regNum = 27;
const int paraRegStart = 0;
const int paraRegEnd = 7;
const int zeroReg =  26;
const int tmpReg = 13;
const int calleeSaveStart = 14;
const int calleeSaveEnd = 26;
extern map<int, string> regMap;

#endif