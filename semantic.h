#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include <stack>
#include <list>
#include "decl.h"
#include <string>
#include <vector>
using std::stack;
using std::list;
using std::string;
using std::vector;
using namespace llvm;

struct symbolTableEntry{
    string id;
    string alias;
    int offset;
    bool isfunc;
	AllocaInst *mem;
	Function *func;
    bool isproto;
    parm_type type;
    vector<parm_type> types; // Only for functions
};
struct symbolTable{
    string scopeid;
    int level;
    bool isloop;
    bool isfunc;
    bool hasret;
    bool isvoid;
	BasicBlock *next;
    vector<symbolTableEntry> entrys;
};

void error(string s);
bool findintable(string id, symbolTableEntry &ret, vector<symbolTable> tablestack);
class Semantic{
public:
    Semantic(ast_node *_root,bool print):
        root(_root),printSymbolTable(print) {    };
    int analysis();
private:
    bool printSymbolTable;
    ast_node *root;
    vector<symbolTable> tablestack;
    parm_type analysisHelper(ast_node *root,int level);
    void printTable(const symbolTable &t);
    void print();
    
};

#endif