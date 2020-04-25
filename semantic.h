#include <stack>
#include <list>
#include <decl.h>
#include <string>
#include <vector>
using std::stack;
using std::list;
using std::string;
using std::vector;
struct symbleTableEntry{
    string id;
    string alias;
    int level;
    int offset;
    bool isfunc;
    parm_type type;
};