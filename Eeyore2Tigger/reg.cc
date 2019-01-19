#include "reg.h"
#include <cassert>
#include <memory.h>
#include <iostream>

using namespace std;
int regNum = 27;
int reg0 = 7;
int reg1 = 8;
int reg2 = 9;
int regMem = 10;
int zero = 26;
set<int> special = {7,8,9,10,26};
map<int, string> regMap{
{0, "a0"},
{1, "a1"},
{2, "a2"},
{3, "a3"},
{4, "a4"},
{5, "a5"},
{6, "a6"},
{7, "t0"},
{8, "t1"},
{9, "t2"},
{10, "t3"},
{11, "t4"},
{12, "t5"},
{13, "t6"},
{14, "s0"},
{15, "s1"},
{16, "s2"},
{17, "s3"},
{18, "s4"},
{19, "s5"},
{20, "s6"},
{21, "s7"},
{22, "s8"},
{23, "s9"},
{24, "s10"},
{25, "s11"},
{26, "x0"}
};
map<string, int> backMap = {};
void init_reg(){

    for(auto& it:regMap){
        backMap[it.second] = it.first;
    }
};
reg::reg(int paraNum){
    // memset(regList, 0, sizeof(regList));
    //regList = int[regNum];
    //calleeSave = [regNum];
    for(int i = 0;i<paraNum;i++){
        regList[i] = 1;
    }
    for(int i = paraNum; i<regNum;i++){
        regList[i] = 0;
    }
    regList[0] = 1;
    for(int i = 0;i<=13;i++){
        calleeSave[i] = false;
    }
    calleeSave[26] = false;
    for(int i = 14;i<=25;i++){
        calleeSave[i] = true;
    }
}
bool reg::callee_save(int i){
    if(calleeSave[i]==true){
        calleeSave[i]=false;
        return true;
    }
    else return false;
}
bool reg::caller_save(int i){
    if(i>=0&&i<=13||i==26) return true;
    else return false;
}
int reg::acquire(){
    for(int i = 0;i<regNum;i++){
        if(regList[i]==0&&special.count(i)==0){
            regList[i] = 1;
            return i;
        }
    }
    assert(false);
    return -1;
}
void reg::release(int i){
    assert(i>=0&&i<regNum&&special.count(i)==0);
    regList[i] = 0;
}
bool reg::full(){
    for(int i = 0;i<regNum;i++){
        // 有多余寄存器且不是特殊寄存器
        if(regList[i]==0&&special.count(i)==0) return false;
    }
    return true;
}