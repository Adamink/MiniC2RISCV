#ifndef TABLE_H
#define TABLE_H

#include <map>
#include <string>
#include <cstring>
#include "node.h"
using namespace std;
extern map<string, idType> globalTable;
// 查找string,返回对应idType，如果没有则新建条目
// bool 指示是否为数组
extern idType check_table(string&, bool isArray = false);
#endif