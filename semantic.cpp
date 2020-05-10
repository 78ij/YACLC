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
    cout << "ID\t\t\tAlias\t\t\tisfunc\t\t\tarray dimension\t\t\tarray sizes\n";
    for(auto e : t.entrys){
		cout << e.id << "\t\t\t" << e.alias << "\t\t\t" << e.isfunc << "\t\t\t" << e.type.arraydim << "\t\t\t";
		for (int i = 0; i < e.type.arraydim; i++) {
			cout << "[" << e.type.arraysize[i] << "]";
		}
		cout <<  endl;
    }
}

void Semantic::print(){
    cout << "\n\nWe are leaving scope "<< tablestack[tablestack.size() - 1].scopeid << ". Printing symbol table now:\n";
    for(int i = 0;i < tablestack.size();i++){
        cout << "---------------Symbol Table " << i << ": " << tablestack[i].scopeid << "--------------------\n";
        printTable(tablestack[i]);
    }
}

bool findintable(string id,symbolTableEntry &ret, vector<symbolTable> tablestack){
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
    }
    return false;
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
            cout << "Semantic Error: " <<("Control statement is not in a loop.");
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
            if(findintable(lv->id,e,tablestack)){
                //check if type are coherent
                if(e.isfunc){
                    cout << "Semantic Error: " <<("Function name " + lv->id + "used as left value.");
                }
				if( e.type.arraydim != lv->arrayind.size()) 
					cout << "Semantic Error: " <<("array dimension of " + lv->id + "doesn't match.");
                return e.type;
			}
			else {
				cout << "Semantic Error: " <<("Variable name " + lv->id + "not defined.");
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
		if (printSymbolTable) print();
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
		if (printSymbolTable) print();
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
            cout << "Semantic Error: " <<("Return statement is not in a function.");
        else if((tablestack[i].isvoid && fo->stmt != NULL) ||
                (!tablestack[i].isvoid && fo->stmt == NULL))
            cout << "Semantic Error: " <<("Return statement does not match function return value.");
        tablestack[i].hasret = true;
    }
    if(typeid(*root) == typeid(ast_node_callfunc)){
        //find function def in symbol table
        ast_node_callfunc *cf = dynamic_cast<ast_node_callfunc *>(root);
        symbolTableEntry e;
        if(findintable(cf->id,e,tablestack)){
            //check if type are coherent
            if(!e.isfunc){
                cout << "Semantic Error: " <<("Variable name " + cf->id + "used as fucntion name.");
            }
            //check if parameters are coherent
            if(e.types.size() != cf->params.size()){
                cout << "Semantic Error: " <<("Function call " + cf->id + "'s parameter number not match.");
            }
            for(int i = 0;i < e.types.size();i++){
                parm_type parm = e.types[i];
                if(typeid(*(cf->params[i])) == typeid(ast_node_lvalue)){
                    parm_type t = analysisHelper(cf->params[i],level+1);
                    if(t.arraydim != parm.arraydim)
                        cout << "Semantic Error: " <<("Function call " + cf->id + " Parameter " + to_string(i) + "Array dimension not match.");
                    if(t.arraydim == parm.arraydim && t.arraydim != 0 && t.type != parm.type)
                        cout << "Semantic Error: " <<("Function call " + cf->id + " Parameter " + to_string(i) + "Array type not match.");
                }
                else{
                    analysisHelper(cf->params[i],level+1);
                }
            }
        }else{
            cout << "Semantic Error: " <<("Function " + cf->id + "is not declared.");
        }
    }
    if(typeid(*root) == typeid(ast_node_funcdec)){
        // We encounter a function prototype
        // First search this symbol
        ast_node_funcdec *proto = dynamic_cast<ast_node_funcdec *>(root);
        symbolTableEntry e;
        // If it exists, emit a semantic error
        if(findintable(proto->id,e, tablestack)) cout << "Semantic Error: " <<("Redefinition of symbol " + proto->id);
        // Add it in current symbol table
        e.id = proto->id;
        e.isfunc = true;
        e.isproto = true;
        e.type.type = proto->type;
        e.types = proto->parms;
        e.alias = "f_" + e.id + "_" + to_string(e.type.type);
        for(auto i : e.types){
            e.alias = e.alias + "_" + to_string(i.type);
        }
        tablestack[tablestack.size() - 1].entrys.push_back(e);
    }
    if(typeid(*root) == typeid(ast_node_funcdef)){
        // We encounter a function define
        // First search this symbol
        ast_node_funcdef *def = dynamic_cast<ast_node_funcdef *>(root);
        symbolTableEntry e;
        // If it exists, check if it is a proto
        if(findintable(def->id,e, tablestack)){
            if(!e.isfunc || !e.isproto){
                cout << "Semantic Error: " <<("Redefinition of function " + def->id);
            }
            // check signature
            if(def->parms.size() != e.types.size()){
                cout << "Semantic Error: " <<("Function def " + def->id + "'s parameter number not match its prototype.");
            }
            for(int i = 0;i < def->parms.size();i++){
                //check every parameter's type and array dimensions
                if(def->parms[i].type != e.types[i].type)
                    cout << "Semantic Error: " <<("Function def " + def->id + "'s parameter type not match its prototype.");
                if(def->parms[i].arraydim != e.types[i].arraydim)
                    cout << "Semantic Error: " <<("Function def " + def->id + "'s parameter array dimension not match its prototype.");
            }
        }else{
            symbolTableEntry e;
            e.id = def->id;
            e.isfunc = true;
            e.type.type = def->ret;
            e.types = def->parms;
            e.isproto = false;
            e.alias = "f_" + e.id + "_" + to_string(e.type.type);
            for(auto i : e.types){
                e.alias = e.alias + "_" + to_string(i.type);
            }
            tablestack[tablestack.size() - 1].entrys.push_back(e);
        }

        // We are now entering a new scope
        // So create a new symbol table
        symbolTable newscope;
        newscope.scopeid = "Function Define:" + def->id;
        newscope.level = level + 1;
        newscope.isloop = false;
        newscope.isfunc = true;
        newscope.isvoid = def->ret == T_VOID? true : false;
        tablestack.push_back(newscope);
		// push back all the parameters into the symbol table
		for (int i = 0; i < def->parms.size();i++) {
			e.id = def->parms[i].ident;
			e.type = def->parms[i];
			e.isfunc = false;
			e.isproto = false;
			e.alias = "v_" + e.id;
			tablestack[tablestack.size() - 1].entrys.push_back(e);
		}
        for(auto node : def->body){
            analysisHelper(node,level + 1);
        }
        if(tablestack[tablestack.size() - 1].hasret == false && def->ret != T_VOID){
            cout << "Semantic Error: " <<("Function def " + def->id + " doesn't return void, but doesn't have a return statement.");
        }
        if(printSymbolTable) print();
        tablestack.pop_back();
    
    }

    if(typeid(*root) == typeid(ast_node_vardec)){
        // We encounter a variable declaration
        ast_node_vardec *var = dynamic_cast<ast_node_vardec *>(root);
        symbolTableEntry e;
        for(auto v :var->vars){
            if(findintable(v.ident,e, tablestack)) cout << "Semantic Error: " <<("Redefinition of symbol " + v.ident);
            e.id = v.ident;
            e.type = v;
            e.type.type = var->type;
            e.isfunc = false;
            e.isproto = false;
            e.alias = "v_" + v.ident;
            tablestack[tablestack.size() - 1].entrys.push_back(e);
        }
    }

    if(typeid(*root) == typeid(ast_node_unary)){
        // We encounter an unary operation
        ast_node_unary *u = dynamic_cast<ast_node_unary *>(root);
        parm_type t = analysisHelper(u->body,level+1);
		if(t.type != T_INT)
			cout << "Semantic Error: " <<("Array index is not int value.");
		if(typeid(u->body) != typeid(ast_node_lvalue) && (u->op == O_UNOT || u->op ==O_UMINUS))
			cout << "Semantic Error: " <<("Right value used as left value.");
        parm_type t2;
        t2.type = T_INT;
        if(u->op == O_UNOT) return t2;
        else return t;
    }
    if(typeid(*root) == typeid(ast_node_bin)){
        // We encounter a binary operation
        ast_node_bin *bin = dynamic_cast<ast_node_bin *>(root);
        parm_type t2;
        t2.type = T_INT;
        if(bin->op == O_EQ || bin->op==O_GE || bin->op==O_GT ||
            bin->op == O_LE || bin->op == O_LT ||bin->op == O_NEQ){
                return t2;
        }
        else{
            parm_type l = analysisHelper(bin->left,level+1);
            parm_type r = analysisHelper(bin->right,level+1);
            types t = std::max(l.type,r.type);
            l.type = t;
			l.arraydim = 0;
            return l;
        }

    }

    if(typeid(*root) == typeid(ast_node_assg)){
        // We encounter an assignment statement
        ast_node_assg *assg = dynamic_cast<ast_node_assg *>(root);
        if(typeid(*(assg->left)) != typeid(ast_node_lvalue))
            cout << "Semantic Error: " <<("The left part of assignment is not a left value");
        parm_type t = analysisHelper(assg->left,level+1);
		if (t.arraydim != 0)
			cout << "Semantic Error: " <<("Array" + t.ident + "Used as left value.");
        analysisHelper(assg->right,level+1);
        return t;
    }

    if(typeid(*root) == typeid(ast_node_const)){
        // We encounter an assignment statement
        ast_node_const *c = dynamic_cast<ast_node_const *>(root);
        parm_type t;
        t.type = c->type;
		t.arraydim = 0;
        return t;
    }
    return parm_type();
}   

