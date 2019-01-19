#ifndef DEBUG_H
#define DEBUG_H
#include "node.h"
#include "manager.h"
#include "regmap.h"
#include "output.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;
void traverseNode(Node* p);
void printSet(set<int> s);
extern map<int, string> nodeTypeMap;
extern map<int, string> exprTypeMap;
#endif