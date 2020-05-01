#include <stack>
#include <list>
#include "decl.h"
#include "llvm/IR/Instructions.h"
#include <string>
#include <vector>
using std::stack;
using std::list;
using std::string;
using std::vector;
struct symbolTableEntry{
    string id;
    string alias;
    int offset;
    bool isfunc;
	AllocaInst *mem;
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

