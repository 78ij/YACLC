#include "codegen.h"

AllocaInst *CodeGen::CreateEntryBlockAlloca(Function *TheFunction,
	StringRef VarName, Type *t,int size) {
	IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
		TheFunction->getEntryBlock().begin());
	
	return TmpB.CreateAlloca(t, ConstantInt::get(Type::getInt32Ty(*TheContext),APInt(32,size,true)));
}


Value *CodeGen::tofloat(Value *a) {
	if (a->getType() == Type::getInt32Ty(*TheContext)) {
		return Builder->CreateSIToFP(a, Type::getFloatTy(*TheContext));
	}
	if (a->getType() == Type::getInt8Ty(*TheContext)) {
		return Builder->CreateSIToFP(a, Type::getFloatTy(*TheContext));
	}
	return a;
}
Value *CodeGen::toint(Value *a) {
	if (a->getType() == Type::getFloatTy(*TheContext)) {
		return Builder->CreateFPToSI(a, Type::getInt32Ty(*TheContext));
	}
	if (a->getType() == Type::getInt8Ty(*TheContext)) {
		return Builder->CreateSExt(a, Type::getInt32Ty(*TheContext));
	}
	return a;
}

Value *CodeGen::tochar(Value *a) {
	if (a->getType() == Type::getFloatTy(*TheContext)) {
		return Builder->CreateFPToSI(a, Type::getInt8Ty(*TheContext));
	}
	if (a->getType() == Type::getInt32Ty(*TheContext)) {
		return Builder->CreateTrunc(a, Type::getInt8Ty(*TheContext));
	}
	return a;
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
	/*for (auto &F : *TheModule)
		TheFPM->run(F);*/
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
	if (typeid(*root) == typeid(ast_node_control)) {
		//Perform Check: is control sequence in a loop?
		//Check all open scopes
		ast_node_control *ctrl = dynamic_cast<ast_node_control*>(root);
		int i;
		for (i = tablestack.size() - 1; i >= 0; i--) {
			if (tablestack[i].isloop == true) break;
		}
		if (ctrl->ctrltype == C_BREAK) {
			Builder->CreateBr(tablestack[i].next);
		}
		else {
			Builder->CreateBr(tablestack[i].cont);
		}
	}
	if (typeid(*root) == typeid(ast_node_bigbrac)) {
		// We are now entering a new scope
		// So create a new symbol table
		symbolTable newscope;
		newscope.scopeid = "Compound Statement";
		//newscope.level = level + 1;
		newscope.isloop = false;
		tablestack.push_back(newscope);
		for (auto node : dynamic_cast<ast_node_bigbrac *>(root)->body) {
			codegenHelper(node);
		}
		tablestack.pop_back();
	}
	if (typeid(*root) == typeid(ast_node_lvalue)) {
		// Encounter an lvalue
		// search it in open scope
		ast_node_lvalue *lv = dynamic_cast<ast_node_lvalue *>(root);
		symbolTableEntry e;
		if (findintable(lv->id, e, tablestack)) {
			parm_type temp;
			temp.arraydim = 0;
			temp.isarray = false;
			temp.type = e.type.type;
			Type *t = gettype(temp);
			if (e.type.arraydim != 0) {
				auto zero = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
				if (lv->arrayind.size() == 0) {
					Value *ptr;
					if (e.mem->getType()->isPointerTy() && e.mem->getType()->getPointerElementType()->isPointerTy()) {
						ptr = Builder->CreateLoad(e.mem);
						ptr = llvm::GetElementPtrInst::Create(t, ptr, { zero }, "", Builder->GetInsertBlock());
					}
					else {
						ptr = llvm::GetElementPtrInst::Create(t, e.mem, { zero }, "", Builder->GetInsertBlock());
					}
					return ptr;
				}
				Value *index = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
				for (int i = 0; i < lv->arrayind.size(); i++) {
					Value *tmp = codegenHelper(lv->arrayind[i]);
					int temp = 1;
					for (int j = i + 1; j < lv->arrayind.size(); j++) {
						temp *= e.type.arraysize[j];
					}
					Value *dims = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, temp, true));
					tmp = Builder->CreateMul(dims, tmp);
					index = Builder->CreateAdd(index, tmp);
				}
			
				Value *ptr;
				if (e.mem->getType()->isPointerTy() && e.mem->getType()->getPointerElementType()->isPointerTy()) {
					ptr = Builder->CreateLoad(e.mem);
					ptr = llvm::GetElementPtrInst::Create(t, ptr, { index }, "", Builder->GetInsertBlock());
				}
				else {
					ptr = llvm::GetElementPtrInst::Create(t,e.mem, { index }, "", Builder->GetInsertBlock());
				}
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
		if(st->el != nullptr)
			Builder->CreateCondBr(CondV, ThenBB, ElseBB);
		else {
			Builder->CreateCondBr(CondV, ThenBB, MergeBB);
		}
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
		ast_node_while *wi = dynamic_cast<ast_node_while *>(root);
		Function *TheFunction = Builder->GetInsertBlock()->getParent();
		BasicBlock *CondBB = BasicBlock::Create(*TheContext, "while cond", TheFunction);
		BasicBlock *LoopBB = BasicBlock::Create(*TheContext, "while loop", TheFunction);
		BasicBlock *AfterBB = BasicBlock::Create(*TheContext, "after while loop", TheFunction);
		symbolTable newscope;
		newscope.scopeid = "While Statement";
		newscope.isloop = true;

		
		newscope.next = AfterBB;
		newscope.cont = CondBB;
		tablestack.push_back(newscope);

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
		Function *TheFunction = Builder->GetInsertBlock()->getParent();
		BasicBlock *CondBB = BasicBlock::Create(*TheContext, "for cond", TheFunction);
		BasicBlock *BodyBB = BasicBlock::Create(*TheContext, "for body", TheFunction);
		BasicBlock *IterBB = BasicBlock::Create(*TheContext, "for iter", TheFunction);
		BasicBlock *AfterBB = BasicBlock::Create(*TheContext, "for after", TheFunction);
		symbolTable newscope;
		newscope.scopeid = "For Statement";
		newscope.isloop = true;
		newscope.cont = IterBB;
		newscope.next = AfterBB;
		tablestack.push_back(newscope);

		codegenHelper(fo->init);


		Builder->CreateBr(CondBB);
		Builder->SetInsertPoint(CondBB);
		Value *CondV;
		if (fo->cond != nullptr) {
			CondV = codegenHelper(fo->cond);
			if (CondV->getType() == Type::getFloatTy(*TheContext)) {
				CondV = Builder->CreateFPToSI(CondV, Type::getInt32Ty(*TheContext));
			}
			else if (CondV->getType() == Type::getInt8Ty(*TheContext)) {
				CondV = Builder->CreateSExt(CondV, Type::getInt32Ty(*TheContext));
			}
			CondV = Builder->CreateICmpNE(CondV, ConstantInt::get(*TheContext, APInt(32, 0, true)), "for cond");
			Builder->CreateCondBr(CondV, BodyBB, AfterBB);
		}
		else {
			Builder->CreateBr(BodyBB);
		}

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
		if (tr == Type::getFloatTy(*TheContext)) {
			if (retval->getType() != Type::getFloatTy(*TheContext))
				retval = Builder->CreateSIToFP(retval, Type::getFloatTy(*TheContext));
		}
		if (tr == Type::getInt32Ty(*TheContext)) {
			if (retval->getType() == Type::getFloatTy(*TheContext))
				retval = Builder->CreateFPToSI(retval, Type::getInt32Ty(*TheContext));
			if (retval->getType() == Type::getInt8Ty(*TheContext))
				retval = Builder->CreateSExt(retval, Type::getInt32Ty(*TheContext));
		}
		if (tr == Type::getInt8Ty(*TheContext)) {
			if (retval->getType() == Type::getFloatTy(*TheContext))
				retval = Builder->CreateFPToSI(retval, Type::getInt8Ty(*TheContext));
			if (retval->getType() == Type::getInt32Ty(*TheContext))
				retval = Builder->CreateTrunc(retval, Type::getInt8Ty(*TheContext));
		}
		Builder->CreateRet(retval);
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
				else if (t -> isArrayTy()) {

					ArgsV.push_back(V);
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
			Type *t = gettype(p);
			if (t->isArrayTy()) {
				args.push_back(PointerType::get(t->getArrayElementType(), 0));
			}
			else
				args.push_back(t);
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
			tp.arraydim = 0;
			Type *ret = gettype(tp);
			for (auto p : def->parms) {
				Type *t = gettype(p);
				if (t->isArrayTy()) {
					args.push_back(PointerType::get(t->getArrayElementType(),0));
				}else 
					args.push_back(t);
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
		BasicBlock *BB = BasicBlock::Create(*TheContext, def->id + " entry", F);
		Builder->SetInsertPoint(BB);
		// push back all the parameters into the symbol table
		for (int i = 0; i < def->parms.size(); i++) {
			Argument *arg = F->getArg(i);
			AllocaInst *Alloca = CreateEntryBlockAlloca(F, arg->getName(), arg->getType(),1);
			Builder->CreateStore(arg, Alloca);
			e.mem = Alloca;
			e.id = def->parms[i].ident;
			e.type = def->parms[i];
			e.isfunc = false;
			e.isproto = false;
			e.alias = "v_" + e.id;
			tablestack[tablestack.size() - 1].entrys.push_back(e);
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
		if (tablestack[tablestack.size() - 1].scopeid == "global") {
			for (auto v : var->vars) {
				parm_type tmp;
				tmp.type = var->type;
				tmp.arraydim = 0;
				Type *t = gettype(tmp);
				if (v.arraydim != 0) {
					int size = 1;
					for (int i = 0; i < v.arraydim; i++) {
						size *= v.arraysize[i];
					}
					t = ArrayType::get(t, size);
				}
				TheModule->getOrInsertGlobal(v.ident, t);
				GlobalVariable *gVar = TheModule->getNamedGlobal(v.ident);
				gVar->setLinkage(GlobalValue::CommonLinkage);
				gVar->setAlignment(4);
				if (t == Type::getInt32Ty(*TheContext)) {
					gVar->setInitializer(ConstantInt::get(*TheContext, APInt(32, 0)));
				}
				if (t == Type::getInt8Ty(*TheContext)) {
					gVar->setInitializer(ConstantInt::get(*TheContext, APInt(8, 0)));
				}
				if (t == Type::getFloatTy(*TheContext)) {
					gVar->setInitializer(ConstantFP::get(*TheContext, APFloat(0.f)));
				}
				else if (t->isArrayTy()) {
					gVar->setInitializer(ConstantAggregateZero::get(t));
				}
				e.id = v.ident;
				e.type = v;
				e.type.type = var->type;
				e.isfunc = false;
				e.isproto = false;
				e.mem = gVar;
				tablestack[tablestack.size() - 1].entrys.push_back(e);

			}
		}
		else {
			for (auto v : var->vars) {

				Function *TheFunction = Builder->GetInsertBlock()->getParent();
				parm_type tmp;
				tmp.type = var->type;
				tmp.arraydim = 0;
				Type *t = gettype(tmp);
				Value * mem;
				if (v.arraydim != 0) {
					int size = 1;
					for (int i = 0; i < v.arraydim; i++) {
						size *= v.arraysize[i];
					}
					ArrayType *t2 = ArrayType::get(t, size);
					mem = CreateEntryBlockAlloca(TheFunction, v.ident, t,size);

				}
				else {
					mem = CreateEntryBlockAlloca(TheFunction, v.ident, t,1);

				}
				e.id = v.ident;
				e.type = v;
				e.type.type = var->type;
				e.isfunc = false;
				e.isproto = false;
				e.mem = mem;
				tablestack[tablestack.size() - 1].entrys.push_back(e);

			}
		}
		
	}

	if (typeid(*root) == typeid(ast_node_unary)) {
		// We encounter an unary operation
		ast_node_unary *u = dynamic_cast<ast_node_unary *>(root);
		Value *V = codegenHelper(u->body);
		ast_node_lvalue *lv = dynamic_cast<ast_node_lvalue *>(u->body);
		Value *ptr;
		if (u->op == O_SELFPLUS || u->op == O_SELFMINUS) {

			symbolTableEntry e;
			if (findintable(lv->id, e, tablestack)) {
				if (e.type.arraydim != 0) {
					Value *index = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
					for (int i = 0; i < lv->arrayind.size(); i++) {
						Value *tmp = codegenHelper(lv->arrayind[i]);
						int temp = 1;
						for (int j = i + 1; j < lv->arrayind.size(); j++) {
							temp *= e.type.arraysize[j];
						}
						Value *dims = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, temp, true));
						tmp = Builder->CreateMul(dims, tmp);
						index = Builder->CreateAdd(index, tmp);
					}
					auto zero = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
					parm_type temp;
					temp.arraydim = 0;
					temp.isarray = false;
					temp.type = e.type.type;
					Type *t = gettype(temp);

					Value *ptr;
					if (e.mem->getType()->isPointerTy() && e.mem->getType()->getPointerElementType()->isPointerTy()) {
						ptr = Builder->CreateLoad(e.mem);
						ptr = llvm::GetElementPtrInst::Create(t, ptr, { index }, "", Builder->GetInsertBlock());
					}
					else {
						ptr = llvm::GetElementPtrInst::Create(t, e.mem, { index }, "", Builder->GetInsertBlock());
					}
					Value *ltmp;
					Value *rtmp;
					rtmp = Builder->CreateLoad(ptr);
					if (u->op == O_SELFPLUS) {
						ltmp = Builder->CreateAdd(rtmp, ConstantInt::get(Type::getInt32Ty(*TheContext), APInt(32, 1, true)));
						ltmp = Builder->CreateStore(ltmp, ptr);
					}
					if (u->op == O_SELFMINUS) {
						ltmp = Builder->CreateAdd(rtmp, ConstantInt::get(Type::getInt32Ty(*TheContext), APInt(32, -1, true)));
						ltmp = Builder->CreateStore(ltmp, ptr);
					}
					if(u->isright)
						return rtmp;
					else return ltmp;
				}
				else {
					Value *ltmp;
					Value *rtmp;
					rtmp = V;
					if (u->op == O_SELFPLUS) {
						ltmp = Builder->CreateAdd(rtmp, ConstantInt::get(Type::getInt32Ty(*TheContext), APInt(32, 1, true)));
						Builder->CreateStore(ltmp, e.mem);
					}
					if (u->op == O_SELFMINUS) {
						ltmp = Builder->CreateAdd(rtmp, ConstantInt::get(Type::getInt32Ty(*TheContext), APInt(32, -1, true)));
						Builder->CreateStore(ltmp, e.mem);
					}
					if (u->isright)
						return rtmp;
					else return ltmp;
				}
			}
		}
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
			return Builder->CreateAnd(LHS, RHS);
			break;
		case O_OR:
			if (LHS->getType() == Type::getFloatTy(*TheContext)) {
				LHS = Builder->CreateFPToSI(LHS, Type::getInt32Ty(*TheContext));
				RHS = Builder->CreateFPToSI(RHS, Type::getInt32Ty(*TheContext));
			}
			return Builder->CreateOr(LHS, RHS);
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
				Value *index = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
				for (int i = 0; i < lv->arrayind.size(); i++) {
					Value *tmp = codegenHelper(lv->arrayind[i]);
					int temp = 1;
					for (int j = i + 1; j < lv->arrayind.size(); j++) {
						temp *= e.type.arraysize[j];
					}
					Value *dims = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, temp, true));
					tmp = Builder->CreateMul(dims, tmp);
					index = Builder->CreateAdd(index, tmp);
				}
				auto zero = llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));
				parm_type temp;
				temp.arraydim = 0;
				temp.isarray = false;
				temp.type = e.type.type;
				Type *t = gettype(temp);

				Value *ptr;
				if (e.mem->getType()->isPointerTy() && e.mem->getType()->getPointerElementType()->isPointerTy()) {
					ptr = Builder->CreateLoad(e.mem);
					ptr = llvm::GetElementPtrInst::Create(t, ptr, { index }, "", Builder->GetInsertBlock());
				}
				else {
					ptr = llvm::GetElementPtrInst::Create(t, e.mem, { index }, "", Builder->GetInsertBlock());
				}
				if (ptr->getType()->getPointerElementType() == Type::getFloatTy(*TheContext)) {
					v = tofloat(v);
				}
				if (ptr->getType()->getPointerElementType() == Type::getInt32Ty(*TheContext)) {
					v = toint(v);
				}
				if (ptr->getType()->getPointerElementType() == Type::getInt8Ty(*TheContext)) {
					v = tochar(v);
				}
				Value *v1;
				if (assg->op == operations::O_EQ)
					return Builder->CreateStore(v, ptr);
				else {
					switch(assg->op) {
						case O_PLUS:
							v1 = Builder->CreateLoad(ptr);
							if (v->getType() == Type::getFloatTy(*TheContext))
								v1 = Builder->CreateFAdd(v, v1);
							else
								v1 = Builder->CreateAdd(v, v1);
							Builder->CreateStore(v1, ptr);
							break;
						case O_MINUS:
							v1 = Builder->CreateLoad(ptr);
							if (v->getType() == Type::getFloatTy(*TheContext))
								v1 = Builder->CreateFAdd(v, Builder->CreateFNeg(v1));
							else
								v1 = Builder->CreateAdd(v, Builder->CreateNeg(v1));
							Builder->CreateStore(v1, ptr);
							break;
						case O_MULTIPLY:
							v1 = Builder->CreateLoad(ptr);
							if (v->getType() == Type::getFloatTy(*TheContext))
								v1 = Builder->CreateFMul(v, v1);
							else
								v1 = Builder->CreateMul(v, v1);
							Builder->CreateStore(v1, ptr);
							break;
						case O_DIVIDE:
							v1 = Builder->CreateLoad(ptr);
							if (v->getType() == Type::getFloatTy(*TheContext))
								v1 = Builder->CreateFDiv(v, v1);
							else
								v1 = Builder->CreateSDiv(v, v1);
							Builder->CreateStore(v1, ptr);
							break;
					}
				}
			}
			else
				if (e.mem->getType()->getPointerElementType() == Type::getFloatTy(*TheContext)) {
					v = tofloat(v);
				}
				if (e.mem->getType()->getPointerElementType() == Type::getInt32Ty(*TheContext)) {
					v = toint(v);
				}
				if (e.mem->getType()->getPointerElementType() == Type::getInt8Ty(*TheContext)) {
					v = tochar(v);
				}
				if (assg->op == operations::O_EQ)
					return Builder->CreateStore(v, e.mem);
				else {
					Value *v1;
					switch (assg->op) {
					case O_PLUS:
						v1 = Builder->CreateLoad(e.mem);
						if (v->getType() == Type::getFloatTy(*TheContext))
							v1 = Builder->CreateFAdd(v, v1);
						else
							v1 = Builder->CreateAdd(v, v1);
						Builder->CreateStore(v1, e.mem);
						break;
					case O_MINUS:
						v1 = Builder->CreateLoad(e.mem);
						if (v->getType() == Type::getFloatTy(*TheContext))
							v1 = Builder->CreateFAdd(v, Builder->CreateFNeg(v1));
						else
							v1 = Builder->CreateAdd(v, Builder->CreateNeg(v1));
						Builder->CreateStore(v1, e.mem);
						break;
					case O_MULTIPLY:
						v1 = Builder->CreateLoad(e.mem);
						if (v->getType() == Type::getFloatTy(*TheContext))
							v1 = Builder->CreateFMul(v, v1);
						else
							v1 = Builder->CreateMul(v, v1);
						Builder->CreateStore(v1, e.mem);
						break;
					case O_DIVIDE:
						v1 = Builder->CreateLoad(e.mem);
						if (v->getType() == Type::getFloatTy(*TheContext))
							v1 = Builder->CreateFDiv(v, v1);
						else
							v1 = Builder->CreateSDiv(v, v1);
						Builder->CreateStore(v1, e.mem);
						break;
					}
				}
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