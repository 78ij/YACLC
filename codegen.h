#ifndef CODEGEN_H
#define CODEGEN_H
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
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

using namespace llvm;

class CodeGen {
public:
	CodeGen(ast_node *_root) :root(_root) {
		TheContext = std::make_unique<LLVMContext>();
		Builder = std::make_unique<IRBuilder<> >(*TheContext);
		TheModule = std::make_unique<Module>("YACLC Module", *TheContext);

		auto TargetTriple = sys::getDefaultTargetTriple();
		std::string Error;
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
};



#endif