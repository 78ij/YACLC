#include "codegen.h"

AllocaInst *CodeGen::CreateEntryBlockAlloca(Function *TheFunction,
	StringRef VarName, Type *t) {
	IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
		TheFunction->getEntryBlock().begin());
	return TmpB.CreateAlloca(t, nullptr, VarName);
}


Value *CodeGen::tofloat(Value *a) {
	if (a->getType() == Type::getInt32Ty(*TheContext)) {
		return Builder->CreateSIToFP(a, Type::getFloatTy(*TheContext));
	}
	if (a->getType() == Type::getInt8Ty(*TheContext)) {
		return Builder->CreateSIToFP(a, Type::getFloatTy(*TheContext));
	}
	return nullptr;
}
Value *CodeGen::toint(Value *a) {
	if (a->getType() == Type::getFloatTy(*TheContext)) {
		return Builder->CreateFPToSI(a, Type::getInt32Ty(*TheContext));
	}
	if (a->getType() == Type::getInt8Ty(*TheContext)) {
		return Builder->CreateSExt(a, Type::getInt32Ty(*TheContext));
	}
	return nullptr;
}

bool CodeGen::typecmp(Type *a, Type *b) {
	if (a == Type::getFloatTy(*TheContext)) return true;
	else if (a == Type::getInt32Ty(*TheContext)) {
		if (b == Type::getFloatTy(*TheContext)) return false;
		else return true;
	}
	else if (a == Type::getInt8Ty(*TheContext)) {
		if (b == Type::getInt8Ty(*TheContext)) return true;
		else return false;
	}
}

Value *CodeGen::convert(Value *a, Value *b) {
	if (a == b) return a;
	if (a->getType() == Type::getFloatTy(*TheContext)) {
		if (b->getType() != Type::getFloatTy(*TheContext))
			return tofloat(b);
	}
	else if (a->getType() == Type::getInt32Ty(*TheContext)) {
		if (b->getType() != Type::getInt32Ty(*TheContext))
			return toint(b);
	}
	return nullptr;
}


Type *CodeGen::gettype(parm_type p) {
	if (p.type == T_INT && p.arraydim == 0) return (Type::getInt32Ty(*TheContext));
	if (p.type == T_FLOAT && p.arraydim == 0) return(Type::getFloatTy(*TheContext));
	if (p.type == T_CHAR && p.arraydim == 0) return(Type::getInt8Ty(*TheContext));
	if (p.type == T_INT && p.arraydim != 0) {
		int size = 1;
		for (int i = 0; i < p.arraydim; i++) {
			size *= p.arraysize[i];
		}
		Type *t = Type::getInt32Ty(*TheContext);
		return ArrayType::get(t, size);
	}
	if (p.type == T_FLOAT && p.arraydim != 0) {
		int size = 1;
		for (int i = 0; i < p.arraydim; i++) {
			size *= p.arraysize[i];
		}
		Type *t = Type::getFloatTy(*TheContext);
		return ArrayType::get(t, size);
	}
	if (p.type == T_CHAR && p.arraydim != 0) {
		int size = 1;
		for (int i = 0; i < p.arraydim; i++) {
			size *= p.arraysize[i];
		}
		Type *t = Type::getInt8Ty(*TheContext);
		return ArrayType::get(t, size);
	}
}

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
			codegenHelper(node);
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
			if (e.type.arraydim != 0) {
				Value *index = codegenHelper(lv->arrayind[0]);
				for (int i = 1; i < lv->arrayind.size(); i++) {
					Value *tmp = codegenHelper(lv->arrayind[i]);
					index = Builder->CreateMul(index, tmp);
				}
				auto zero = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
				Type *t = gettype(e.type);
				auto ptr = llvm::GetElementPtrInst::Create(t,e.mem, { zero, index },"", Builder->GetInsertBlock());
				return Builder->CreateLoad(ptr);
			}
			else
			return Builder->CreateLoad(e.mem, e.id);
		}
	}
	if (typeid(*root) == typeid(ast_node_if)) {
		ast_node_if * st = dynamic_cast<ast_node_if *>(root);
		Value *CondV = codegenHelper(st->cond);
		if (CondV->getType() == Type::getFloatTy(*TheContext)) {
			CondV = Builder->CreateFPToSI(CondV, Type::getInt32Ty(*TheContext));
		}
		else if (CondV->getType() == Type::getInt8Ty(*TheContext)) {
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
		else if (CondV->getType() == Type::getInt8Ty(*TheContext)) {
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
		else if (CondV->getType() == Type::getInt8Ty(*TheContext)) {
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
		std::vector<Value *> ArgsV;
		ast_node_callfunc *cf = dynamic_cast<ast_node_callfunc *>(root);
		symbolTableEntry e;
		if (findintable(cf->id, e, tablestack)) {
			for (int i = 0; i < e.types.size(); i++) {
				parm_type parm = e.types[i];
				Value *V = codegenHelper(cf->params[i]);
				Type *t = V->getType();
				if (t == Type::getInt32PtrTy(*TheContext) ||
					t == Type::getFloatPtrTy(*TheContext) ||
					t == Type::getInt8PtrTy(*TheContext)) {
					ArgsV.push_back(V);
				}
				else if (t == Type::getInt32Ty(*TheContext)) {
					if(parm.type == T_INT) ArgsV.push_back(V);
					if (parm.type == T_FLOAT) {
						V = Builder->CreateSIToFP(V, Type::getFloatTy(*TheContext));
						ArgsV.push_back(V);
					}
					if (parm.type == T_CHAR) {
						V = Builder->CreateTrunc(V, Type::getInt8Ty(*TheContext));
						ArgsV.push_back(V);
					}
				}
				else if (t == Type::getFloatTy(*TheContext)) {
					if (parm.type == T_FLOAT) ArgsV.push_back(V);
					if (parm.type == T_INT) {
						V = Builder->CreateFPToSI(V, Type::getInt32Ty(*TheContext));
						ArgsV.push_back(V);
					}
					if (parm.type == T_CHAR) {
						V = Builder->CreateFPToSI(V, Type::getInt8Ty(*TheContext));
						ArgsV.push_back(V);
					}
				}
				else if (t == Type::getInt8Ty(*TheContext)) {
					if (parm.type == T_CHAR) ArgsV.push_back(V);
					if (parm.type == T_FLOAT) {
						V = Builder->CreateSIToFP(V, Type::getFloatTy(*TheContext));
						ArgsV.push_back(V);
					}
					if (parm.type == T_INT) {
						V = Builder->CreateSExt(V, Type::getInt32Ty(*TheContext));
						ArgsV.push_back(V);
					}
				}
			}
			return Builder->CreateCall(e.func, ArgsV, e.id + "func call");
		}
	}
	if (typeid(*root) == typeid(ast_node_funcdec)) {
		// We encounter a function prototype
		// First search this symbol
		ast_node_funcdec *proto = dynamic_cast<ast_node_funcdec *>(root);
		std::vector<Type *> args;
		parm_type tp;
		tp.type = proto->type;
		Type *ret = gettype(tp);
		for (auto p : proto->parms) {
			args.push_back(gettype(p));
		}
		FunctionType *FT = FunctionType::get(ret, args, false);
		Function *F = Function::Create(FT, Function::ExternalLinkage, proto->id, TheModule.get());
		symbolTableEntry e;
		e.id = proto->id;
		e.isfunc = true;
		e.func = F;
		e.isproto = true;
		e.type.type = proto->type;
		e.types = proto->parms;
		tablestack[tablestack.size() - 1].entrys.push_back(e);
	}
	if (typeid(*root) == typeid(ast_node_funcdef)) {
		// We encounter a function define
		// First search this symbol
		ast_node_funcdef *def = dynamic_cast<ast_node_funcdef *>(root);
		symbolTableEntry e;
		Function *F;
		// If it exists, check if it is a proto
		if (findintable(def->id, e, tablestack)) F = e.func;
		else {
			std::vector<Type *> args;
			parm_type tp;
			tp.type = def->ret;
			Type *ret = gettype(tp);
			for (auto p : def->parms) {
				args.push_back(gettype(p));
			}
			FunctionType *FT = FunctionType::get(ret, args, false);
			F = Function::Create(FT, Function::ExternalLinkage, def->id, TheModule.get());
			symbolTableEntry e;
			e.id = def->id;
			e.isfunc = true;
			e.func = F;
			e.type.type = def->ret;
			e.types = def->parms;
			e.isproto = false;
			tablestack[tablestack.size() - 1].entrys.push_back(e);
		}

		// We are now entering a new scope
		// So create a new symbol table
		symbolTable newscope;
		newscope.scopeid = "Function Define:" + def->id;
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
		BasicBlock *BB = BasicBlock::Create(*TheContext, def->id + " entry", F);
		Builder->SetInsertPoint(BB);
		for (auto &Arg : F->args()) {
			AllocaInst *Alloca = CreateEntryBlockAlloca(F, Arg.getName(), Arg.getType());
			Builder->CreateStore(&Arg, Alloca);
		}
		for (auto node : def->body) {
			codegenHelper(node);
		}
		tablestack.pop_back();

	}

	if (typeid(*root) == typeid(ast_node_vardec)) {
		// We encounter a variable declaration
		ast_node_vardec *var = dynamic_cast<ast_node_vardec *>(root);
		symbolTableEntry e;
		for (auto v : var->vars) {
			
			Function *TheFunction = Builder->GetInsertBlock()->getParent();
			parm_type tmp;
			tmp.type = var->type;
			tmp.arraydim = 0;
			Type *t = gettype(tmp);
			if (v.arraydim != 0) {
				int size = 1;
				for (int i = 0; i < v.arraydim; i++) {
					size *= v.arraysize[i];
				}
				Type *t2 = ArrayType::get(t, size);
			}
			AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, v.ident, t);
			e.id = v.ident;
			e.type = v;
			e.type.type = var->type;
			e.isfunc = false;
			e.isproto = false;
			e.mem = Alloca;
			tablestack[tablestack.size() - 1].entrys.push_back(e);

		}
	}

	if (typeid(*root) == typeid(ast_node_unary)) {
		// We encounter an unary operation
		ast_node_unary *u = dynamic_cast<ast_node_unary *>(root);
		Value *V = codegenHelper(u->body);
		switch (u->op) {
		case O_UMINUS:
			if (V->getType() == Type::getFloatTy(*TheContext))
				return Builder->CreateFNeg(V);
			return Builder->CreateNeg(V);
			break;
		case O_UNOT:
			if (V->getType() == Type::getFloatTy(*TheContext)) {
				V = Builder->CreateFPToSI(V, Type::getInt32Ty(*TheContext));
				return Builder->CreateNot(V);
			}
			return Builder->CreateNot(V);
			break;
		case O_SELFMINUS:
			if (V->getType() == Type::getFloatTy(*TheContext)) {
				return Builder->CreateFAdd(V,ConstantFP::get(*TheContext,APFloat(-1.f)));
			}
			else {
				return Builder->CreateAdd(V, ConstantInt::get(*TheContext, APInt(32,-1)));
			}
			break;
		case O_SELFPLUS:
			if (V->getType() == Type::getFloatTy(*TheContext)) {
				return Builder->CreateFAdd(V, ConstantFP::get(*TheContext, APFloat(1.f)));
			}
			else {
				return Builder->CreateAdd(V, ConstantInt::get(*TheContext, APInt(32, 1)));
			}
			break;
		}
	}
	if (typeid(*root) == typeid(ast_node_bin)) {
		// We encounter a binary operation
		ast_node_bin *bin = dynamic_cast<ast_node_bin *>(root);
		Value *LHS = codegenHelper(bin->left);
		Value *RHS = codegenHelper(bin->right);
		if (!typecmp(LHS->getType(), RHS->getType())) std::swap(LHS, RHS);
		Value *tmp = convert(LHS, RHS);
		if (tmp != nullptr) RHS = tmp;
		switch (bin->op) {
		case O_AND:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				LHS = Builder->CreateFPToSI(LHS, Type::getInt32Ty(*TheContext));
				RHS = Builder->CreateFPToSI(RHS, Type::getInt32Ty(*TheContext));
			}
			Builder->CreateAnd(LHS, RHS);
			break;
		case O_OR:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				LHS = Builder->CreateFPToSI(LHS, Type::getInt32Ty(*TheContext));
				RHS = Builder->CreateFPToSI(RHS, Type::getInt32Ty(*TheContext));
			}
			Builder->CreateOr(LHS, RHS);
			break;
		case O_EQ:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				Value *v = Builder->CreateFCmp(CmpInst::Predicate::FCMP_OEQ, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			else {
				Value *v = Builder->CreateICmp(CmpInst::Predicate::ICMP_EQ, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			break;
		case O_NEQ:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				Value *v = Builder->CreateFCmp(CmpInst::Predicate::FCMP_ONE, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			else {
				Value *v = Builder->CreateICmp(CmpInst::Predicate::ICMP_NE, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			break;
		case O_GT:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				Value *v = Builder->CreateFCmp(CmpInst::Predicate::FCMP_OGT, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			else {
				Value *v = Builder->CreateICmp(CmpInst::Predicate::ICMP_SGT, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			break;
		case O_LT:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				Value *v = Builder->CreateFCmp(CmpInst::Predicate::FCMP_OLT, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			else {
				Value *v = Builder->CreateICmp(CmpInst::Predicate::ICMP_SLT, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			break;
		case O_GE:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				Value *v = Builder->CreateFCmp(CmpInst::Predicate::FCMP_OGE, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			else {
				Value *v = Builder->CreateICmp(CmpInst::Predicate::ICMP_SGE, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			break;
		case O_LE:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				Value *v = Builder->CreateFCmp(CmpInst::Predicate::FCMP_OLE, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			else {
				Value *v = Builder->CreateICmp(CmpInst::Predicate::ICMP_SLE, LHS, RHS);
				return Builder->CreateSExt(v, Type::getInt32Ty(*TheContext));
			}
			break;
		case O_PLUS:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				return Builder->CreateFAdd(LHS, RHS);
			}
			else {
				return Builder->CreateAdd(LHS, RHS);
			}
			break;
		case O_MINUS:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				RHS = Builder->CreateFNeg(RHS);
				return Builder->CreateFAdd(LHS, RHS);
			}
			else {
				RHS = Builder->CreateNeg(RHS);
				return Builder->CreateAdd(LHS, RHS);
			}
			break;
		case O_MULTIPLY:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				return Builder->CreateFMul(LHS, RHS);
			}
			else {
				return Builder->CreateMul(LHS, RHS);
			}
			break;
		case O_DIVIDE:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				return Builder->CreateFDiv(LHS, RHS);
			}
			else {
				return Builder->CreateSDiv(LHS, RHS);
			}
			break;
		}

	}

	if (typeid(*root) == typeid(ast_node_assg)) {
		// We encounter an assignment statement
		ast_node_assg *assg = dynamic_cast<ast_node_assg *>(root);
		ast_node_lvalue *lv = dynamic_cast<ast_node_lvalue *>(assg->left);
		Value *v = codegenHelper(assg->right);
		symbolTableEntry e;
		if (findintable(lv->id, e, tablestack)) {
			if (e.type.arraydim != 0) {
				Value *index = codegenHelper(lv->arrayind[0]);
				for (int i = 1; i < lv->arrayind.size(); i++) {
					Value *tmp = codegenHelper(lv->arrayind[i]);
					index = Builder->CreateMul(index, tmp);
				}
				auto zero = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
				Type *t = gettype(e.type);
				auto ptr = llvm::GetElementPtrInst::Create(t, e.mem, { zero, index }, "", Builder->GetInsertBlock());
				return Builder->CreateStore(v, ptr);
			}
			else
				return Builder->CreateStore(v,e.mem);
		}
	}

	if (typeid(*root) == typeid(ast_node_const)) {
		// We encounter an const statement
		ast_node_const *c = dynamic_cast<ast_node_const *>(root);
		if (c->type == T_INT) {
			return ConstantInt::get(*TheContext, APInt(32, c->data.i));
		}
		if (c->type == T_FLOAT) {
			return ConstantFP::get(*TheContext, APFloat(c->data.f));
		}
		if (c->type == T_CHAR) {
			return ConstantInt::get(*TheContext, APInt(8, c->data.c));
		}
	}
	return nullptr;
}