#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <set>
#include <vector>

#include "regmap.h"

using namespace std;
enum AddrDescriptorType{RegType, StackType, GlobalType};

class AddrDescriptor{
    private:
        int value;
    protected:
        AddrDescriptorType descriptorType;
    public:
        AddrDescriptor();
        AddrDescriptor(AddrDescriptorType type_, int value = -1);
        AddrDescriptorType getType() const;
        // 寄存器返回编号，栈返回位置，全局变量返回-1
        int getValue() const;
        friend bool operator<(const AddrDescriptor& here, const AddrDescriptor& another);
        // bool operator==(const AddrDescriptor& other);
};

using AddrSet = set<AddrDescriptor>;
class IdNode;
class ExprNode;
class Manager{
    public:
        Manager();

        int getStackSize();

        IdNode* findId(IdNode* );
        IdNode* addId(IdNode* );

        // 将params添加到idTable，并load到对应reg
        // 设置regToSearch
        void setParams(vector<IdNode*> params);

        string genCode(ExprNode* expr);


    private:
        int stackSize;
        int paraNum;
        vector<IdNode*> params;
        // 当前在处理的expr
        ExprNode* expr; 
        // 排除了函数参数和tmpReg,zeroReg以及在同一语句中分配的reg搜索集
        set<int> regToSearch;
        // 描述当前IdNode*活跃的地址描述符
        map<IdNode*, AddrSet> idTable;
        // 描述当前reg中存放的IdNode*
        set<IdNode*>regTable[regNum];
        // 描述IdNode*和已分配栈描述符的对应关系
        map<IdNode*, AddrDescriptor> stackInfo;

        bool calleeSave[regNum];
        // 得到要搜索的reg集合，去掉tmpReg,zeroReg和paraReg
        void calcRegToSearch(int paraNum);

        // 清除reg中别的id，更新别的id的AddrSet
        // 将id load到目标reg，更新id的AddrSet
        // 返回处理代码
        string loadIdToReg(IdNode* id, int reg);

        // 清除reg中的id并清除idTable中活跃于reg的id的地址描述符
        void cleanReg(int reg);

        // 将id添加到reg,增加reg到id的addrSet,增加id到reg的idset
        void addIdToReg(IdNode* id, int reg);

        // 返回将id load到reg时对应的代码
        string genLoadCode(IdNode* id, int reg);

        string getRegName(int reg);

        // 判断id是否被分配了栈描述符
        bool hasAllocatedStack(IdNode* id);

        // 使id的AddrSet包含内存位置
        // 全局变量存回名字
        // 局部变量如果不在栈中则分配栈空间并用stackInfo记录
        // 整数变量不作处理
        // 返回处理代码
        string storeIdToMem(IdNode* id);

        // 返回当前存储id的寄存器编号
        // 如果有多个返回第一个
        // 如果没有返回-1
        int findInWhichReg(IdNode* id);

        // 修改id地址描述符使包含内存位置
        void addMemToId(IdNode* id);

        // 给id分配栈空间
        void allocateStack(IdNode* id);

        // 返回将fromReg处的id存到内存位置时候的代码
        string genStoreCode(IdNode* id, int fromReg);

        // 使reg只包含id
        // 使id只包含reg
        // 更新其它活跃于reg的id的AddrSet
        void makeIdMonopolizeReg(IdNode* id, int reg);

        // 清除id中的所有活跃reg并清除所有regTable中的id
        void cleanId(IdNode* id);

        // 检查reg下标是否越界, 否则报错
        void inRegRange(int);

        // 将id加入reg
        // 使得id只包含reg
        void makeIdShareReg(IdNode* id, int reg);

        // 保存reg中的id,如果id活跃或id是全局非数组变量/函数参数/非临时非数组变量
        // 返回代码
        string saveIdInReg(int reg);


        string saveIdInRegOtherThan(IdNode* id, int reg);
        
        string saveAllGlobalVar();
        string saveAllGlobalVarAndNonTemp();
        string saveAndCleanAllCallerSave();
        string assignValueForIdInReg(IdNode* id, int reg);
        string restorePara();
        void cleanRegExceptParaReg();
        void cleanCallerSaveReg();
        bool inMem(IdNode* id);
        // 找到一个可用的寄存器
        int pickReg();

        void banRegToSearch(int reg1, int reg2 = -1);

        void restoreRegToSearch(int reg1, int reg2 = -1);
};

#endif