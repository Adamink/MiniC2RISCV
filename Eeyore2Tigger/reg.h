#ifndef REG_H
#define REG_H

#include <map>
#include <string>
#include <set>
#include <cstring>

using namespace std;

extern map<int, string> regMap;
extern map<string, int> backMap;
extern void init_reg();
extern int regNum;
extern int reg0;
extern int reg1;
extern int reg2;
extern int regMem;
extern int zero;
extern set<int> special;
class reg
{
	public:
        int regList[27];
		bool calleeSave[27];
        int acquire();
        void release(int);
        reg(int paraNum);
        bool full();
        bool callee_save(int);
        bool caller_save(int);
};
#endif