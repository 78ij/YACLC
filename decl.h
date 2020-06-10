#ifndef SIMP_PAR_H
#define SIMP_PAR_H
#include<cstdlib>
#include<cctype>
#include<string>
#include<iostream>
#include<vector>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;
enum types{
		T_CHAR,
        T_INT,
		T_FLOAT,
		T_CHARARRAY,
		T_INTARRAY,
		T_FLOATARRAY,
		T_VOID
};
enum operations{
		O_PLUS,
		O_MINUS,
		O_MULTIPLY,
		O_DIVIDE,
		O_EQ,
		O_NEQ,
		O_LE,
		O_GE,
		O_GT,
		O_LT,
		O_AND,
		O_OR,
		O_UMINUS,
		O_UNOT,
		O_SELFPLUS,
		O_SELFMINUS
};
enum ctrl{C_BREAK,C_CONTINUE} ;

struct parm_type {
	bool isarray;
	int arraydim;
	int arraysize[10];
	string ident;
	types type;
};
void printtokenpair(int tokentype);
inline void pl(int l);
inline void pl(int l,ostream &out);

class ast_node {
public:
	bool isinfunc = false; // Compound Statement
	virtual void print(int l) {}
};

class ast_node_prog :public ast_node{
public:
	vector<ast_node*> lst;
	void print(int l) override;
};

//break, continue
class ast_node_control : public ast_node {
public:
	ctrl ctrltype;
	void print(int l) override;
};

class ast_node_bigbrac : public ast_node {
public:
	vector<ast_node *> body;
	void print(int l) override;
};


class ast_node_lvalue :public ast_node{
public:
	string id;
	bool iscallfunc;
	vector<ast_node *> arrayind;
	void print(int l) override ;
};

class ast_node_if : public ast_node {
public:
	ast_node *cond;
	ast_node *body;
	ast_node *el;
	void print(int l) override;

};

class ast_node_while : public ast_node{
public:
	ast_node *cond;
	ast_node *body;
	void print(int l) override ;
};

class ast_node_for : public ast_node {
public:
	ast_node *init;
	ast_node *cond;
	ast_node *iter;
	ast_node *body;
	void print(int l) override;

};

class ast_node_ret : public ast_node {
public:
	ast_node *stmt;
	void print(int l) override ;

};

//class ast_node_parstmt : public ast_node {
//	ast_node *stmt;
//	void print(int l) override {
//		pl(l);
//		cout << "ASTNode Type: Parentheses Statement :\n";
//		stmt->print(l + 1);
//	}
//   };

class ast_node_callfunc : public ast_node {
public:
	string id;
	bool isstmt = false;
	vector<ast_node *> params;
	void print(int l) override ;

};

class ast_node_funcdec : public ast_node {
public:
	types type;
	string id;
	vector<parm_type> parms;
	void print(int l) override ;
};

class ast_node_funcdef :public ast_node {
public:
	types ret;
	string id;
	vector<parm_type> parms;
	vector<ast_node*> body;
	void print(int l) override ;
};

class ast_node_vardec : public ast_node {
public:
	types type;
	vector<parm_type> vars;
	void print(int l) override ;
};
class ast_node_unary :public ast_node{
public:
	ast_node *body;
	operations op;
	bool isright;
	void print(int l) override;
};
class ast_node_bin : public ast_node {
public:
	operations op;
	ast_node *left;
	ast_node *right;
	void print(int l) override ;
};

class ast_node_const :public ast_node{
public:
	union datau{
		float f;
		int i;
		char c;
	} ;
	datau data;
	types type;
	void print(int l) override;
} ;
class ast_node_assg : public ast_node {
public:
	bool isstmt = false;
	bool isarray = false;
	ast_node *left;
	ast_node *right;
	operations op;
	void print(int l) override ;
};

#endif //SIMP_PAR_H