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
        T_INT,
		T_FLOAT,
		T_CHAR,
		T_INTARRAY,
		T_FLOATARRAY,
		T_CHARARRAY,
		T_VOID
    };
    const char* typenames[] = {
        "int","float","char","array of int","array of float","array of char"
    };
	inline string mytolower(string s) {
		string ret;
		for (auto c : s)
			ret.push_back(tolower(c));
		return ret;
	}

	inline void pl(int l) {
		for (int i = 0; i < l * 2; i++)
			cout << ' ';
	}

	inline void pl(int l,ostream &out) {
		for (int i = 0; i < l * 4; i++)
			out << ' ';
	}

	struct parm_type {
		bool isarray;
        int arraydim;
        int arraysize[10];
		string ident;
		types type;
	};



	class ast_node {
	public:
		bool isinfunc = false; // Compound Statement
		virtual void print(int l) {}
	};

	class ast_node_prog :public ast_node{
	public:
		vector<ast_node*> lst;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Prog  Childs:\n";
			for (int i = 0; i < lst.size(); i++) {
				lst[i]->print(l + 1);
			}
			cout << "\n";
		}
	};

	//id, const,  break, continue
	class ast_node_const : public ast_node {
	public:
        union{
            float f;
            int i;
            char c;
        } data;
		bool isarray = false;
		ast_node *num;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Const  " << "Token Information: ";
		}

	};

	class ast_node_bigbrac : public ast_node {
	public:
		vector<ast_node *> body;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Big Bracket Childs:\n";
			for (int i = 0; i < body.size(); i++) {
				body[i]->print(l + 1);
			}
		}
	};

	class ast_node_if : public ast_node {
	public:
		ast_node *cond;
		ast_node *body;
		vector<ast_node *>elif;
		vector<ast_node *>elifcond;
		ast_node *el;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: If\n";
			pl(l);
			cout << "Condition:\n";
			cond->print(l + 1);
			pl(l);
			cout << "Body:\n";
			body->print(l + 1);
			for (int i = 0; i < elif.size(); i++) {
				pl(l);
				cout << "Else IF, Condition:\n";
				elifcond[i]->print(l + 1);
				pl(l);
				cout << " Body:\n";
				
				elif[i]->print(l + 1);
			}
			if (el != nullptr) {
				pl(l);
				cout << "Else:\n";
				el->print(l + 1);
			}
			
		}

	};

	class ast_node_while : public ast_node{
	public:
		ast_node *cond;
		ast_node *body;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: While\n";
			pl(l);
			cout << "Condition:\n";
			cond->print(l  + 1);
			pl(l);
			cout << "body:\n";
			body->print(l + 1);
		}
	};

	class ast_node_for : public ast_node {
	public:
		ast_node *init;
		ast_node *cond;
		ast_node *iter;
		ast_node *body;
		void print(int l) override {
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

	};

	class ast_node_ret : public ast_node {
	public:
		ast_node *stmt;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Return\n";
			pl(l);
			cout << "Statement:\n";
			if(stmt != nullptr)
				stmt->print(l + 1);
		}

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
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Function Call\n";
			for (int i = 0; i < params.size(); i++) {
				pl(l + 1);
				cout << "Parameter " << i << " :\n";
				params[i]->print(l + 1);
			}
			cout << "\n";
		}

	};

	class ast_node_funcdec : public ast_node {
	public:
		types type;
		string id;
		vector<parm_type> parms;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Function Declare, id: " << id << "Returns: " << typenames[type] << " Types: ";
			for (int i = 0; i < parms.size() - 1; i++)
				cout << typenames[parms[i].type] << ", ";
			cout << typenames[parms[parms.size() - 1].type] << "\n";
		}
	};

	class ast_node_funcdef :public ast_node {
	public:
		types ret;
		string id;
		vector<parm_type> parms;
		vector<ast_node*> body;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Function Define, id: " << id << " Returns: " << typenames[ret] << " Types: ";
			if (parms.size() > 0) {
				for (int i = 0; i < (parms.size() - 1); i++)
					cout << typenames[parms[i].type] << ", ";
				cout << typenames[parms[parms.size() - 1].type] << "  ";
			}
			else cout << "None";
			cout << "body:\n";
			if (body.size() > 0) {
				for (int i = 0; i < body.size(); i++)
					body[i]->print(l + 1);
			}
		}
	};

	class ast_node_vardec : public ast_node {
	public:
		types type;
		vector<parm_type> vars;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Variable Declare, type: " << typenames[type]  << " id: ";
				for (int i = 0; i < vars.size() - 1; i++)
					cout << vars[i].ident << ", ";
			cout << vars[vars.size() - 1].ident << "\n";
		}
	};

	class ast_node_bin : public ast_node {
	public:
		types type;
		ast_node *left;
		ast_node *right;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Binary Operation, type:" << typenames[type] << "\n";
			pl(l);
			cout <<	"left:\n";
			left->print(l + 1);
			pl(l);
			cout << "right:\n";
			right->print(l + 1);
		}

	};
	class ast_node_exprstmt : public ast_node{
	public:
		ast_node *exp;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Expression Statement, expression:\n";
			exp->print(l + 1);
		}

	};

	class ast_node_assg : public ast_node {
	public:
		string id;
		bool isstmt = false;
		bool isarray = false;
		ast_node *num;
		ast_node *right;
		void print(int l) override {
			pl(l);
			cout << "ASTNode Type: Assignment, id: " << id << " right:\n";
			right->print(l + 1);
        }
	};

#endif //SIMP_PAR_H