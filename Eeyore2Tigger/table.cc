#include "table.h"
#include "node.h"

using namespace std;
map<string, idType> globalTable = {};
idType check_table(string& name, bool isArray){
    if(globalTable.find(name)!=globalTable.end()){
        return globalTable[name];
    }
    else{
        string newName = "v" + to_string(globalTable.size());
        globalTable[name] = idType(newName, 0, true, isArray);
        return globalTable[name];
    }
}
