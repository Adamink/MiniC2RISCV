#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;
int main(int argc, char** argv){
    assert(argc==2||argc==4);
    string args[4];
    for(int i = 0;i<argc;i++){
        args[i] = string(argv[i]);
    }
    string dst;
    if(argc==2){
        int len = args[1].length();
        if(args[1].substr(len-2,len)==".c")
            dst = args[1].substr(0,len-2) + ".s";
        else{
            dst = args[1] + ".s";
        }
    }
    else{
        int locate = -1;
        for(int i = 1;i<3;i++){
            if(args[i]=="-o"){
                locate = i;
                break;
            }
        }
        if(locate==-1) assert(false);
        dst = args[locate+1];
    }
    stringstream cmd = stringstream();
    cmd << "./MiniC2Eeyore/eeyore < " << args[1] << " > c2e.log";
    int status = system((cmd.str()).c_str());
    cmd.str("");
    if(status==0){
        cmd << "./Eeyore2Tigger/tigger < c2e.log > e2t.log ";
        system((cmd.str()).c_str());
        cmd.str("");
        cmd << "./Tigger2RISC-V/riscv64 < e2t.log > " << dst;
        system((cmd.str()).c_str());
        cmd.str("");
    }
    cmd << "rm -f c2e.log e2t.log eeyore.log";
    system((cmd.str()).c_str());
    cmd.str("");
    return 0;
}