#include "semantic.h"
#include <iostream>
#include <typeinfo>
#include <exception>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cassert>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using patch::to_string;
using std::exception;
using std::runtime_error;
using std::cout;
using std::endl;
using std::find_if;
using std::atoi;
void error(string s){
    cout << "Static Semantic Analysis Failed: " << s << endl;
}

void Semantic::printTable(const symbolTable &t){
    cout << "ID\t\t\tAlias\t\t\toffset\t\t\tisfunc\n";
    for(auto e : t.entrys){
        cout << e.id << "\t\t\t" << e.alias << "\t\t\t" << e.offset << endl;
    }
}

void Semantic::print(){
    cout << "\n\nWe are leaving scope "<< tablestack[tablestack.size() - 1].scopeid << ". Printing symbol table now:\n";
    for(int i = 0;i < tablestack.size();i++){
        cout << "---------------Symbol Table " << i << ": " << tablestack[i].scopeid << "--------------------\n";
        printTable(tablestack[i]);
    }
}

bool Semantic::findintable(string id,symbolTableEntry &ret){
    for(int i = tablestack.size() - 1;i >= 0;i--){
        vector<symbolTableEntry>::iterator it = find_if(
            tablestack[i].entrys.begin(),
            tablestack[i].entrys.end(),
            [id](symbolTableEntry a){
                return a.id == id;
        });
        if(it != tablestack[i].entrys.end()) {
            ret = *it;
            return true;
        }
        else return false;
    }
}

int Semantic::analysis(){
    try{
        analysisHelper(root,0);
    }
    catch(runtime_error e){
        error(string(e.what()));
        return 1;
    }
    return 0;
}

parm_type Semantic::analysisHelper(ast_node *root,int level){
    if(root == NULL) return parm_type();
    if(typeid(*root) == typeid(ast_node_prog)){
        // We are now entering global scope
        // So create a new symbol table
        symbolTable global;
        global.scopeid = "global";
        global.level = 0;
        global.isloop = false;
        tablestack.push_back(global);
        for(auto node : dynamic_cast<ast_node_prog *>(root)->lst){
            analysisHelper(node,1);
        }
		if (printSymbolTable) print();
        tablestack.pop_back();
        assert(tablestack.empty());
    }
    if(typeid(*root) == typeid(ast_node_control)){
        //Perform Check: is control sequence in a loop?
        //Check all open scopes
        int i;
        for(i = tablestack.size() - 1;i >= 0;i--){
            if(tablestack[i].isloop == true) break;
        }
        if(i == -1)
            throw runtime_error("Control statement is not in a loop.");
    }
    if(typeid(*root) == typeid(ast_node_bigbrac)){
        // We are now entering a new scope
        // So create a new symbol table
        symbolTable newscope;
        newscope.scopeid = "Compound Statement";
        newscope.level = level + 1;
        newscope.isloop = false;
        tablestack.push_back(newscope);
        for(auto node : dynamic_cast<ast_node_bigbrac *>(root)->body){
            analysisHelper(node,level + 1);
        }
        if(printSymbolTable) print();
        tablestack.pop_back();
    }
    if(typeid(*root) == typeid(ast_node_lvalue)){
        // Encounter an lvalue
        // search it in open scope
        ast_node_lvalue *lv = dynamic_cast<ast_node_lvalue *>(root);
        for(int i = tablestack.size() - 1;i >= 0;i--){
            symbolTableEntry e;
            if(findintable(lv->id,e)){
                //check if type are coherent
                if(e.isfunc){
                    throw runtime_error("Function name " + lv->id + "used as left value.");
                }
                //check if array dimensions are coherent
                if(e.type.arraydim != lv->arrayind.size()){
                    throw runtime_error("Variable " + lv->id + "'s Array dimensions does not match.");
                }
                return e.type;
            }
        }
    }
    if(typeid(*root) == typeid(ast_node_if)){
        ast_node_if * st = dynamic_cast<ast_node_if *>(root);
        analysisHelper(st->cond,level + 1);
        analysisHelper(st->body,level + 1);
        analysisHelper(st->el,level + 1);
    }
    if(typeid(*root) == typeid(ast_node_while)){
        ast_node_while *wi = dynamic_cast<ast_node_while *>(root);
        analysisHelper(wi->cond,level + 1);
        // We will now make an auxiliary symbol table
        // that incidates we have entered a loop
        symbolTable newscope;
        newscope.scopeid = "While Statement";
        newscope.level = level + 1;
        newscope.isloop = true;
        tablestack.push_back(newscope);
        analysisHelper(wi->body,level + 1);
        tablestack.pop_back();
    }
    if(typeid(*root) == typeid(ast_node_for)){
        ast_node_for *fo = dynamic_cast<ast_node_for *>(root);
        analysisHelper(fo->init,level + 1);
        analysisHelper(fo->cond,level + 1);
        analysisHelper(fo->iter,level + 1);
        // We will now make an auxiliary symbol table
        // that incidates we have entered a loop
        symbolTable newscope;
        newscope.scopeid = "For Statement";
        newscope.level = level + 1;
        newscope.isloop = true;
        tablestack.push_back(newscope);
        analysisHelper(fo->body,level + 1);
        tablestack.pop_back();
    }
    if(typeid(*root) == typeid(ast_node_ret)){
        ast_node_ret *fo = dynamic_cast<ast_node_ret *>(root);
        analysisHelper(fo->stmt,level + 1);
        //Perform Check: is return in a function?
        //Check all open scopes
        int i;
        for(i = tablestack.size() - 1;i >= 0;i--){
            if(tablestack[i].isfunc == true) break;
        }
        if(i == -1)
            throw runtime_error("Return statement is not in a function.");
        else if((tablestack[i].isvoid && fo->stmt != NULL) ||
                (!tablestack[i].isvoid && fo->stmt == NULL))
            throw runtime_error("Return statement does not match function return value.");
    }
    if(typeid(*root) == typeid(ast_node_callfunc)){
        //find function def in symbol table
        ast_node_callfunc *cf = dynamic_cast<ast_node_callfunc *>(root);
        symbolTableEntry e;
        if(findintable(cf->id,e)){
            //check if type are coherent
            if(e.isfunc){
                throw runtime_error("Variable name " + cf->id + "used as fucntion name.");
            }
            //check if parameters are coherent
            if(e.types.size() != cf->params.size()){
                throw runtime_error("Function call " + cf->id + "'s parameter number not match.");
            }
            for(int i = 0;i < e.types.size();i++){
                parm_type parm = e.types[i];
                if(typeid(*(cf->params[i])) == typeid(ast_node_lvalue)){
                    parm_type t = analysisHelper(cf->params[i],level+1);
                    if(t.arraydim != parm.arraydim)
                        throw runtime_error("Function call " + cf->id + " Parameter " + to_string(i) + "Array dimension not match.");
                    if(t.arraydim == parm.arraydim && t.arraydim != 0 && t.type != parm.type)
                        throw runtime_error("Function call " + cf->id + " Parameter " + to_string(i) + "Array type not match.");
                }
                else{
                    analysisHelper(cf->params[i],level+1);
                }
            }
        }else{
            throw runtime_error("Function " + cf->id + "is not declared.");
        }
    }
    if(typeid(*root) == typeid(ast_node_funcdec)){
        // We encounter a function prototype
        // First search this symbol
        ast_node_funcdec *proto = dynamic_cast<ast_node_funcdec *>(root);
        symbolTableEntry e;
        // If it exists, emit a semantic error
        if(findintable(proto->id,e)) throw runtime_error("Redefinition of symbol " + proto->id);
        // Add it in current symbol table
        e.id = proto->id;
        e.isfunc = true;
        e.type.type = proto->type;
        e.types = proto->parms;
        e.alias = "f_" + e.id + "_" + to_string(e.type.type);
        for(auto i : e.types){
            e.alias = e.alias + "_" + to_string(i.type);
        }
        tablestack[tablestack.size() - 1].entrys.push_back(e);
    }

    if(typeid(*root) == typeid(ast_node_vardec)){
        // We encounter a(probable multiple)variable prototype
        ast_node_vardec *var = dynamic_cast<ast_node_vardec *>(root);
        symbolTableEntry e;
        for(auto v :var->vars){
            if(findintable(v.ident,e)) throw runtime_error("Redefinition of symbol " + v.ident);
            e.id = v.ident;
            e.type = v;
            e.type.type = var->type;
            e.isfunc = false;
            e.alias = "v_" + v.ident;
            tablestack[tablestack.size() - 1].entrys.push_back(e);
        }
    }
    return parm_type();
}   

