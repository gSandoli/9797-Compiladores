#include "../ast.h"
#include "../funcao.h"
#include "../util/symboltable.h"
#include <cstddef>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <system_error>

using namespace std;
using namespace A;
using namespace llvm;
using namespace sys;
using namespace fs;

void createFunction(unique_ptr<Module> &module,
                    SymbolTable<Function> &functions, string const &name,
                    vector<Type *> const &args, Type *retType) {
  FunctionType *functionType = FunctionType::get(retType, args, false);
  Function *function = Function::Create(functionType, Function::ExternalLinkage,
                                        name, module.get());
  functions.push(name, function);
}

void seedFunctions(SymbolTable<Function> &functions,
                   unique_ptr<LLVMContext> &context,
                   unique_ptr<Module> &module) {
  Type *doubleType{Type::getDoubleTy(*context)};
  Type *intType{Type::getInt64Ty(*context)};
  Type *voidType{Type::getVoidTy(*context)};
  Type *stringType{PointerType::getUnqual(Type::getInt8Ty(*context))};

  createFunction(module, functions, "imprimei", {intType}, voidType);
  createFunction(module, functions, "imprimer", {doubleType}, voidType);
  createFunction(module, functions, "imprimec", {stringType}, voidType);
  createFunction(module, functions, "emite", {}, voidType);
  createFunction(module, functions, "lc", {}, stringType);
  createFunction(module, functions, "li", {}, intType);
  createFunction(module, functions, "lr", {}, doubleType);
  createFunction(module, functions, "ordem", {stringType}, intType);
  createFunction(module, functions, "chr", {intType}, stringType);
  createFunction(module, functions, "tamanho", {stringType}, intType);
  createFunction(module, functions, "subcadeia", {stringType, intType, intType},
                 stringType);
  createFunction(module, functions, "concatene", {stringType, stringType},
                 stringType);
  createFunction(module, functions, "inverter", {intType}, intType);
  createFunction(module, functions, "termine", {intType}, voidType);
  createFunction(module, functions, "gere_inteiro", {}, intType);
  createFunction(module, functions, "gere_real", {}, doubleType);
}

Value *tradutor(unique_ptr<LLVMContext> &context,
                unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                Ast *root, string outputFileName,
                string intermediateCodeFilename) {

  deque<StructType *> staticLink;
  AllocaInst *currentFrame;
  size_t currentLevel = 0;

  legacy::PassManager pm;
  pm.add(createPrintModulePass(outs()));

  InitializeAllTargetInfos();
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmParsers();
  InitializeAllAsmPrinters();

  string targetTriple = getDefaultTargetTriple();
  module->setTargetTriple(targetTriple);
  string error;
  const Target *target = TargetRegistry::lookupTarget(targetTriple, error);
  if (!target) {
    errs() << error;
    return nullptr;
  }
  StringRef CPU = "generic";
  StringRef features = "";
  TargetOptions opt;
  Optional<Reloc::Model> RM = Optional<Reloc::Model>();
  TargetMachine *targetMachine =
      target->createTargetMachine(targetTriple, CPU, features, opt, RM);

  module->setDataLayout(targetMachine->createDataLayout());

  vector<Type *> args;
  FunctionType *mainProto =
      FunctionType::get(Type::getVoidTy(*context), args, false);
  Function *mainFunction = Function::Create(
      mainProto, GlobalValue::ExternalLinkage, "main", module.get());

  staticLink.push_front(StructType::create(*context, "main"));
  vector<Type *> localVar;
  staticLink.front()->setBody(localVar);
  BasicBlock *block = BasicBlock::Create(*context, "entry", mainFunction);
  SymbolTable<Function> functions;
  seedFunctions(functions, context, module);
  builder->SetInsertPoint(block);
  IRBuilder<> TmpB(&mainFunction->getEntryBlock(),
                   mainFunction->getEntryBlock().begin());
  currentFrame = TmpB.CreateAlloca(staticLink.front(), nullptr, "mainframe");
  currentLevel = 0;

  root->tradutor(context, builder, module, functions);

  builder->CreateRetVoid();
  if (verifyFunction(*mainFunction, &errs())) {
    cerr << "Erro na geração de código." << endl;
    exit(0);
  }

  error_code EC;
  raw_fd_ostream dest(outputFileName, EC, OF_None);

  if (EC) {
    errs() << "Não foi possível abrir o arquivo: " << EC.message();
    return nullptr;
  }

  CodeGenFileType fileType = CGFT_ObjectFile;

  if (targetMachine->addPassesToEmitFile(pm, dest, nullptr, fileType)) {
    errs() << "TheTargetMachine não pode emitir um arquivo deste tipo";
    return nullptr;
  }

  raw_fd_ostream destFonte(intermediateCodeFilename, EC, OF_Text);
  module->print(destFonte, nullptr);

  pm.run(*module);
  dest.flush();
  return nullptr;
}