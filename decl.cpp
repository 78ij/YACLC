#include "decl.h"
const char* typenames[] = {
    "int","float","char","array of int","array of float","array of char"
};
const char *opnames[] = {
	"+","-","*","/","==","!=","<=",">=",">","<","&&","||","-","!","++","--"
};
const char *ctrlnames[] = {"Break","Continue"};

inline string mytolower(string s){
    string ret;
    for (auto c : s)
        ret.push_back(tolower(c));
    return ret;
}

inline void pl(int l) {
    for (int i = 0; i < l * 4; i++)
        cout << ' ';
}

inline void pl(int l,ostream &out) {
    for (int i = 0; i < l * 4; i++)
        out << ' ';
}

void ast_node_prog::print(int l){
    pl(l);
    cout << "ASTNode Type: Prog\n";
    pl(l);
    cout << "Childs:\n";
    for (int i = 0; i < lst.size(); i++) {
        lst[i]->print(l + 1);
    }
    cout << "\n";
}   


void ast_node_control::print(int l){
    pl(l);
	cout << "ASTNode Type: Control, Type:" << ctrlnames[ctrltype] << "\n";

}

void ast_node_bigbrac::print(int l){
    pl(l);
    cout << "ASTNode Type: Big Bracket Childs:\n";
    for (int i = 0; i < body.size(); i++) {
        body[i]->print(l + 1);
    }
}

void ast_node_lvalue::print(int l){
    pl(l);
    if(arrayind.size() != 0){
        cout << "ASTNode Type: Left Value ID: " << id << "Array dimensions: " << arrayind.size() << " Child Expressions: \n";
        for(auto nodes : arrayind){
        nodes->print(l+1);
        }
    }
    else cout << "ASTNode Type: Left Value ID: " << id << endl;
}	

void ast_node_if::print(int l) {
    pl(l);
    cout << "ASTNode Type: If\n";
    pl(l);
    cout << "Condition:\n";
    cond->print(l + 1);
    pl(l);
    cout << "Body:\n";
    body->print(l + 1);
}

void ast_node_while::print(int l){
    pl(l);
    cout << "ASTNode Type: While\n";
    pl(l);
    cout << "Condition:\n";
    cond->print(l  + 1);
    pl(l);
    cout << "body:\n";
    body->print(l + 1);
}

void ast_node_for::print(int l) {
    pl(l);
    cout << "ASTNode Type: For\n";
    if (init != nullptr) {
        pl(l);
        cout << "Init:\n";
        init->print(l + 1);
    }
    if (cond != nullptr) {
        pl(l);
        cout << "Cond:\n";
        cond->print(l + 1);
    }
    if (iter != nullptr) {
        pl(l);
        cout << "Iter\n";
        iter->print(l + 1);
    }
    pl(l);
    cout << "Body:\n";

    body->print(l + 1);
}

void ast_node_ret::print(int l){
    pl(l);
    cout << "ASTNode Type: Return\n";
    pl(l);
    cout << "Statement:\n";
    if(stmt != nullptr)
        stmt->print(l + 1);
}

void ast_node_callfunc::print(int l){
    pl(l);
    cout << "ASTNode Type: Function Call\n";
    for (int i = 0; i < params.size(); i++) {
        pl(l);
        cout << "Parameter " << i << " :\n";
        params[i]->print(l + 1);
    }
}

void ast_node_funcdec::print(int l){
    pl(l);
    cout << "ASTNode Type: Function Declare, id: " << id << "Returns: " << typenames[type] << " Types: ";
    for (int i = 0; i < parms.size() - 1; i++)
        cout << typenames[parms[i].type] << ", ";
    cout << typenames[parms[parms.size() - 1].type] << "\n";
}

void ast_node_funcdef::print(int l){
    pl(l);
    cout << "ASTNode Type: Function Define, id: " << id << " Returns: " << typenames[ret] << " Types:";
    if (parms.size() > 0) {
        for (int i = 0; i < (parms.size() - 1); i++)
            cout << typenames[parms[i].type] << ", ";
        cout << typenames[parms[parms.size() - 1].type] << "  ";
        cout << endl;
    }
    else cout << "None\n";
    if(!body.empty()){
        pl(l);
        cout << "Body:\n";
        if (body.size() > 0) {
            for (int i = 0; i < body.size(); i++)
                body[i]->print(l + 1);
        }
    }

}

void ast_node_vardec::print(int l){
    pl(l);
    cout << "ASTNode Type: Variable Declare, type: " << typenames[type]  << " id: ";
        for (int i = 0; i < vars.size() - 1; i++){
            if(vars[i].isarray) cout << vars[i].ident << " [array], ";
            else cout << vars[i].ident << ", ";
        }
            
    cout << vars[vars.size() - 1].ident << "\n";
}

void ast_node_unary::print(int l){
    pl(l);
    cout << "ASTNode Type: Unary Operation, type:" << opnames[op] << "\n";
    pl(l);
    cout << "body:\n";
    body->print(l + 1);
}

void ast_node_bin::print(int l){
    pl(l);
    cout << "ASTNode Type: Binary Operation, type:" << opnames[op] << "\n";
    pl(l);
    cout <<	"left:\n";
    left->print(l + 1);
    pl(l);
    cout << "right:\n";
    right->print(l + 1);
}

void ast_node_const::print(int l){
    pl(l);
    cout << "ASTNode Type: Constant Literal, Type: " << typenames[type] << " Value :" ;
    switch(type){
        case T_INT: cout << data.i << endl;break;
        case T_FLOAT: cout << data.f << endl;break;
        case T_CHAR: cout << data.c << endl;break;
    }
}

void ast_node_assg::print(int l){
    pl(l);
    if(op == O_EQ){
    cout << "ASTNode Type: Assignment\n";
    }
    else{
        cout << "ASTNode Type: Compound Assignment, " << "Type: " << opnames[op] << endl;
    }
    pl(l);
    cout << "left: \n" ;
    left->print(l+1);
    pl(l);
    cout << "right: \n";
    right->print(l + 1);
}