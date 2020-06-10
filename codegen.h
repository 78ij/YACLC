#ifndef CODEGEN_H
#define CODEGEN_H

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <system_error>
#include <utility>
#include <vector>
#include "decl.h"
#include "semantic.h"


class CodeGen {
public:
	CodeGen(ast_node *_root) :root(_root) {
		TheContext = std::make_unique<LLVMContext>();
		Builder = std::make_unique<IRBuilder<> >(*TheContext);
		TheModule = std::make_unique<Module>("YACLC Module", *TheContext);

		auto TargetTriple = sys::getDefaultTargetTriple();
		std::string Error;
		InitializeNativeTarget();
		auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);
		if (!Target) {
			errs() << Error;
		}
		auto CPU = "generic";
		auto Features = "";
		TargetOptions opt;
		auto RM = Optional<Reloc::Model>();
		auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
		TheModule->setDataLayout(TargetMachine->createDataLayout());
		TheModule->setTargetTriple(TargetTriple);
		TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());

		// Promote allocas to registers.
		TheFPM->add(createPromoteMemoryToRegisterPass());
		// Do simple "peephole" optimizations and bit-twiddling optzns.
		TheFPM->add(createInstructionCombiningPass());
		// Reassociate expressions.
		TheFPM->add(createReassociatePass());
		// Eliminate Common SubExpressions.
		TheFPM->add(createGVNPass());
		// Simplify the control flow graph (deleting unreachable blocks, etc).
		TheFPM->add(createCFGSimplificationPass());
		
		TheFPM->doInitialization();
	}
	void genIR();
private:
	ast_node *root;
	std::unique_ptr<LLVMContext> TheContext;
	std::unique_ptr<IRBuilder<> > Builder;
	std::unique_ptr<Module> TheModule;
	std::unique_ptr<legacy::FunctionPassManager> TheFPM;
	vector<symbolTable> tablestack;
	Value *codegenHelper(ast_node *root);
	AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
		StringRef VarName, Type *t,int size);
	Type *gettype(parm_type p);
	Value *tofloat(Value *a);
	Value *toint(Value *a);
	Value *tochar(Value *a);
	Value *convert(Value *a, Value *b);
	bool typecmp(Type *a, Type *b);
};



#endif