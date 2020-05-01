#include "codegen.h"

void CodeGen::genIR() {
	codegenHelper(root);
	TheModule->print(errs(), nullptr);
}

Value *CodeGen::codegenHelper(ast_node *root) {
	if (root == NULL) return nullptr;
	if (typeid(*root) == typeid(ast_node_prog)) {
		// We are now entering global scope
		// So create a new symbol table
		symbolTable global;
		global.scopeid = "global";
		//global.level = 0;
		global.isloop = false;
		tablestack.push_back(global);
		for (auto node : dynamic_cast<ast_node_prog *>(root)->lst) {
			codegenHelper(root);
		}
		tablestack.pop_back();
		assert(tablestack.empty());
	}
	//if (typeid(*root) == typeid(ast_node_control)) {
	//	//Perform Check: is control sequence in a loop?
	//	//Check all open scopes
	//	int i;
	//	for (i = tablestack.size() - 1; i >= 0; i--) {
	//		if (tablestack[i].isloop == true) break;
	//	}
	//	if (i == -1)
	//		throw runtime_error("Control statement is not in a loop.");
	//}
	if (typeid(*root) == typeid(ast_node_bigbrac)) {
		// We are now entering a new scope
		// So create a new symbol table
		symbolTable newscope;
		newscope.scopeid = "Compound Statement";
		//newscope.level = level + 1;
		newscope.isloop = false;
		tablestack.push_back(newscope);
		for (auto node : dynamic_cast<ast_node_bigbrac *>(root)->body) {
			codegenHelper(root);
		}
		tablestack.pop_back();
	}
	if (typeid(*root) == typeid(ast_node_lvalue)) {
		// Encounter an lvalue
		// search it in open scope
		ast_node_lvalue *lv = dynamic_cast<ast_node_lvalue *>(root);
		symbolTableEntry e;
		if (findintable(lv->id, e, tablestack)) {
			return Builder->CreateLoad(e.mem, e.id);
		}
	}
	if (typeid(*root) == typeid(ast_node_if)) {
		ast_node_if * st = dynamic_cast<ast_node_if *>(root);
		Value *CondV = codegenHelper(st->cond);
		if (CondV->getType() == Type::getFloatTy(*TheContext)) {
			CondV = Builder->CreateFPToSI(CondV, Type::getInt32Ty(*TheContext));
		}
		else if (CondV->getType == Type::getInt8Ty(*TheContext)) {
			CondV = Builder->CreateSExt(CondV, Type::getInt32Ty(*TheContext));
		}

		CondV = Builder->CreateICmpNE(CondV, ConstantInt::get(*TheContext, APInt(32, 0, true)), "ifcond");

		Function *TheFunction = Builder->GetInsertBlock()->getParent();

		BasicBlock *ThenBB = BasicBlock::Create(*TheContext, "then", TheFunction);
		BasicBlock *ElseBB = BasicBlock::Create(*TheContext, "else");
		BasicBlock *MergeBB = BasicBlock::Create(*TheContext, "ifcont");

		Builder->CreateCondBr(CondV, ThenBB, ElseBB);

		Builder->SetInsertPoint(ThenBB);

		codegenHelper(st->body);

		Builder->CreateBr(MergeBB);
		ThenBB = Builder->GetInsertBlock();
		if (st->el) {
			TheFunction->getBasicBlockList().push_back(ElseBB);
			Builder->SetInsertPoint(ElseBB);
			codegenHelper(st->el);
			Builder->CreateBr(MergeBB);
			ElseBB = Builder->GetInsertBlock();
		}
		TheFunction->getBasicBlockList().push_back(MergeBB);
		Builder->SetInsertPoint(MergeBB);
		return nullptr;
	}
	if (typeid(*root) == typeid(ast_node_while)) {
		symbolTable newscope;
		newscope.scopeid = "While Statement";
		newscope.isloop = true;
		tablestack.push_back(newscope);

		ast_node_while *wi = dynamic_cast<ast_node_while *>(root);
		Function *TheFunction = Builder->GetInsertBlock()->getParent();
		BasicBlock *CondBB = BasicBlock::Create(*TheContext, "while cond", TheFunction);
		BasicBlock *LoopBB = BasicBlock::Create(*TheContext, "while loop", TheFunction);
		BasicBlock *AfterBB = BasicBlock::Create(*TheContext, "after while loop", TheFunction);
		Builder->CreateBr(CondBB);
		Builder->SetInsertPoint(CondBB);
		Value *CondV = codegenHelper(wi->cond);
		if (CondV->getType() == Type::getFloatTy(*TheContext)) {
			CondV = Builder->CreateFPToSI(CondV, Type::getInt32Ty(*TheContext));
		}
		else if (CondV->getType == Type::getInt8Ty(*TheContext)) {
			CondV = Builder->CreateSExt(CondV, Type::getInt32Ty(*TheContext));
		}

		CondV = Builder->CreateICmpNE(CondV, ConstantInt::get(*TheContext, APInt(32, 0, true)), "while cond");
		Builder->CreateCondBr(CondV, LoopBB, AfterBB);
		Builder->SetInsertPoint(LoopBB);
		codegenHelper(wi->body);
		Builder->CreateBr(CondBB);
		Builder->SetInsertPoint(AfterBB);
		
		tablestack.pop_back();
	}
	if (typeid(*root) == typeid(ast_node_for)) {
		ast_node_for *fo = dynamic_cast<ast_node_for *>(root);
		symbolTable newscope;
		newscope.scopeid = "For Statement";
		newscope.isloop = true;
		tablestack.push_back(newscope);

		Function *TheFunction = Builder->GetInsertBlock()->getParent();
		codegenHelper(fo->init);

		BasicBlock *CondBB = BasicBlock::Create(*TheContext, "for cond", TheFunction);
		BasicBlock *BodyBB = BasicBlock::Create(*TheContext, "for body", TheFunction);
		BasicBlock *IterBB = BasicBlock::Create(*TheContext, "for iter", TheFunction);
		BasicBlock *AfterBB = BasicBlock::Create(*TheContext, "for iter", TheFunction);
		Builder->CreateBr(CondBB);
		Builder->SetInsertPoint(CondBB);
		Value *CondV = codegenHelper(fo->cond);
		if (CondV->getType() == Type::getFloatTy(*TheContext)) {
			CondV = Builder->CreateFPToSI(CondV, Type::getInt32Ty(*TheContext));
		}
		else if (CondV->getType == Type::getInt8Ty(*TheContext)) {
			CondV = Builder->CreateSExt(CondV, Type::getInt32Ty(*TheContext));
		}

		CondV = Builder->CreateICmpNE(CondV, ConstantInt::get(*TheContext, APInt(32, 0, true)), "for cond");
		Builder->CreateCondBr(CondV, BodyBB, AfterBB);
		Builder->SetInsertPoint(BodyBB);
		codegenHelper(fo->body);
		Builder->CreateBr(IterBB);
		Builder->SetInsertPoint(IterBB);
		codegenHelper(fo->iter);
		Builder->CreateBr(CondBB);
		Builder->SetInsertPoint(AfterBB);
		tablestack.pop_back();
	}
	if (typeid(*root) == typeid(ast_node_ret)) {
		ast_node_ret *fo = dynamic_cast<ast_node_ret *>(root);
		Function *TheFunction = Builder->GetInsertBlock()->getParent();
		if (!fo->stmt) Builder->CreateRet(nullptr);
		Value *retval = codegenHelper(fo->stmt);
		Type * tr = TheFunction->getReturnType();
		
	}
	if (typeid(*root) == typeid(ast_node_callfunc)) {
		//find function def in symbol table
		ast_node_callfunc *cf = dynamic_cast<ast_node_callfunc *>(root);
		symbolTableEntry e;
		if (findintable(cf->id, e, tablestack)) {
			//check if type are coherent
			if (!e.isfunc) {
				throw runtime_error("Variable name " + cf->id + "used as fucntion name.");
			}
			//check if parameters are coherent
			if (e.types.size() != cf->params.size()) {
				throw runtime_error("Function call " + cf->id + "'s parameter number not match.");
			}
			for (int i = 0; i < e.types.size(); i++) {
				parm_type parm = e.types[i];
				if (typeid(*(cf->params[i])) == typeid(ast_node_lvalue)) {
					parm_type t = analysisHelper(cf->params[i], level + 1);
					if (t.arraydim != parm.arraydim)
						throw runtime_error("Function call " + cf->id + " Parameter " + to_string(i) + "Array dimension not match.");
					if (t.arraydim == parm.arraydim && t.arraydim != 0 && t.type != parm.type)
						throw runtime_error("Function call " + cf->id + " Parameter " + to_string(i) + "Array type not match.");
				}
				else {
					analysisHelper(cf->params[i], level + 1);
				}
			}
		}
		else {
			throw runtime_error("Function " + cf->id + "is not declared.");
		}
	}
	if (typeid(*root) == typeid(ast_node_funcdec)) {
		// We encounter a function prototype
		// First search this symbol
		ast_node_funcdec *proto = dynamic_cast<ast_node_funcdec *>(root);
		symbolTableEntry e;
		// If it exists, emit a semantic error
		if (findintable(proto->id, e, tablestack)) throw runtime_error("Redefinition of symbol " + proto->id);
		// Add it in current symbol table
		e.id = proto->id;
		e.isfunc = true;
		e.isproto = true;
		e.type.type = proto->type;
		e.types = proto->parms;
		e.alias = "f_" + e.id + "_" + to_string(e.type.type);
		for (auto i : e.types) {
			e.alias = e.alias + "_" + to_string(i.type);
		}
		tablestack[tablestack.size() - 1].entrys.push_back(e);
	}
	if (typeid(*root) == typeid(ast_node_funcdef)) {
		// We encounter a function define
		// First search this symbol
		ast_node_funcdef *def = dynamic_cast<ast_node_funcdef *>(root);
		symbolTableEntry e;
		// If it exists, check if it is a proto
		if (findintable(def->id, e, tablestack)) {
			if (!e.isfunc || !e.isproto) {
				throw runtime_error("Redefinition of function " + def->id);
			}
			// check signature
			if (def->parms.size() != e.types.size()) {
				throw runtime_error("Function def " + def->id + "'s parameter number not match its prototype.");
			}
			for (int i = 0; i < def->parms.size(); i++) {
				//check every parameter's type and array dimensions
				if (def->parms[i].type != e.types[i].type)
					throw runtime_error("Function def " + def->id + "'s parameter type not match its prototype.");
				if (def->parms[i].arraydim != e.types[i].arraydim)
					throw runtime_error("Function def " + def->id + "'s parameter array dimension not match its prototype.");
			}
		}
		else {
			symbolTableEntry e;
			e.id = def->id;
			e.isfunc = true;
			e.type.type = def->ret;
			e.types = def->parms;
			e.isproto = false;
			e.alias = "f_" + e.id + "_" + to_string(e.type.type);
			for (auto i : e.types) {
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
		newscope.isvoid = def->ret == T_VOID ? true : false;
		tablestack.push_back(newscope);
		// push back all the parameters into the symbol table
		for (int i = 0; i < def->parms.size(); i++) {
			e.id = def->parms[i].ident;
			e.type = def->parms[i];
			e.isfunc = false;
			e.isproto = false;
			e.alias = "v_" + e.id;
			tablestack[tablestack.size() - 1].entrys.push_back(e);
		}
		for (auto node : def->body) {
			analysisHelper(node, level + 1);
		}
		if (tablestack[tablestack.size() - 1].hasret == false && def->ret != T_VOID) {
			throw runtime_error("Function def " + def->id + " doesn't return void, but doesn't have a return statement.");
		}
		if (printSymbolTable) print();
		tablestack.pop_back();

	}

	if (typeid(*root) == typeid(ast_node_vardec)) {
		// We encounter a variable declaration
		ast_node_vardec *var = dynamic_cast<ast_node_vardec *>(root);
		symbolTableEntry e;
		for (auto v : var->vars) {
			if (findintable(v.ident, e, tablestack)) throw runtime_error("Redefinition of symbol " + v.ident);
			e.id = v.ident;
			e.type = v;
			e.type.type = var->type;
			e.isfunc = false;
			e.isproto = true;
			e.alias = "v_" + v.ident;
			tablestack[tablestack.size() - 1].entrys.push_back(e);
		}
	}

	if (typeid(*root) == typeid(ast_node_unary)) {
		// We encounter an unary operation
		ast_node_unary *u = dynamic_cast<ast_node_unary *>(root);
		parm_type t = analysisHelper(u->body, level + 1);
		if (t.arraydim != 0)
			throw runtime_error("Array" + t.ident + "Used as left value.");
		parm_type t2;
		t2.type = T_INT;
		if (u->op == O_UNOT) return t2;
		else return t;
	}
	if (typeid(*root) == typeid(ast_node_bin)) {
		// We encounter a binary operation
		ast_node_bin *bin = dynamic_cast<ast_node_bin *>(root);
		parm_type t2;
		t2.type = T_INT;
		if (bin->op == O_EQ || bin->op == O_GE || bin->op == O_GT ||
			bin->op == O_LE || bin->op == O_LT || bin->op == O_NEQ) {
			return t2;
		}
		else {
			parm_type l = analysisHelper(bin->left, level + 1);
			if (l.arraydim != 0)
				throw runtime_error("Array" + l.ident + "Used as left value.");
			parm_type r = analysisHelper(bin->right, level + 1);
			if (r.arraydim != 0)
				throw runtime_error("Array" + r.ident + "Used as left value.");
			types t = std::max(l.type, r.type);
			l.type = t;
			l.arraydim = 0;
			return l;
		}

	}

	if (typeid(*root) == typeid(ast_node_assg)) {
		// We encounter an assignment statement
		ast_node_assg *assg = dynamic_cast<ast_node_assg *>(root);
		if (typeid(*(assg->left)) != typeid(ast_node_lvalue))
			throw runtime_error("The left part of assignment is not a left value");
		parm_type t = analysisHelper(assg->left, level + 1);
		if (t.arraydim != 0)
			throw runtime_error("Array" + t.ident + "Used as left value.");
		analysisHelper(assg->right, level + 1);
		return t;
	}

	if (typeid(*root) == typeid(ast_node_const)) {
		// We encounter an assignment statement
		ast_node_const *c = dynamic_cast<ast_node_const *>(root);
		parm_type t;
		t.type = c->type;
		t.arraydim = 0;
		return t;
	}
	return nullptr;
}