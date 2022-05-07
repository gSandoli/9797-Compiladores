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

using namespace llvm;
using namespace std;
using namespace A;

Function *createFunction(unique_ptr<Module> &module,
                         SymbolTable<Function> functions,
                         std::string const &name,
                         std::vector<Type *> const &args, Type *retType) {
  auto functionType = FunctionType::get(retType, args, false);
  auto function = Function::Create(functionType, Function::ExternalLinkage,
                                   name, module.get());
  functions.push(name, function);
  return function;
}

void seedFunctions(SymbolTable<Function> functions,
                   unique_ptr<LLVMContext> &context,
                   unique_ptr<Module> &module) {
  Type *doubleType{Type::getDoubleTy(*context)};
  Type *intType{Type::getInt64Ty(*context)};
  Type *voidType{Type::getVoidTy(*context)};
  Type *stringType{PointerType::getUnqual(Type::getInt8Ty(*context))};

  functions["print"] =
      createFunction(module, functions, "print", {stringType}, voidType);
  functions["printd"] =
      createFunction(module, functions, "printd", {intType}, voidType);
  functions["flush"] = createFunction(module, functions, "flush", {}, voidType);
  functions["getchar"] =
      createFunction(module, functions, "getchar_", {}, stringType);
  functions["ord"] =
      createFunction(module, functions, "ord", {stringType}, intType);
  functions["chr"] =
      createFunction(module, functions, "chr", {intType}, stringType);
  functions["size"] =
      createFunction(module, functions, "size", {stringType}, intType);
}

Value *tradutor(unique_ptr<LLVMContext> &context,
                unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                Ast *root, string outputFileName,
                string intermediateCodeFilename) {
  SymbolTable<Function> functions;

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

  auto targetTriple = sys::getDefaultTargetTriple();
  module->setTargetTriple(targetTriple);
  string error;
  auto target = TargetRegistry::lookupTarget(targetTriple, error);
  if (!target) {
    errs() << error;
    return nullptr;
  }
  auto CPU = "generic";
  auto features = "";
  TargetOptions opt;
  auto RM = Optional<Reloc::Model>();
  auto targetMachine =
      target->createTargetMachine(targetTriple, CPU, features, opt, RM);
  module->setDataLayout(targetMachine->createDataLayout());

  vector<Type *> args;
  auto mainProto = FunctionType::get(Type::getVoidTy(*context), args, false);
  auto mainFunction = Function::Create(mainProto, GlobalValue::ExternalLinkage,
                                       "main", module.get());
  staticLink.push_front(StructType::create(*context, "main"));
  vector<Type *> localVar;
  staticLink.front()->setBody(localVar);
  auto block = BasicBlock::Create(*context, "entry", mainFunction);
  seedFunctions(functions, *context, *module);
  builder->SetInsertPoint(block);
  IRBuilder<> TmpB(&mainFunction->getEntryBlock(),
                   mainFunction->getEntryBlock().begin());
  currentFrame = TmpB.CreateAlloca(staticLink.front(), nullptr, "mainframe");
  currentLevel = 0;

  Funcao *f = ((Funcao *)root);
  f->tradutor(context, builder, module);

  builder->CreateRetVoid();
  if (verifyFunction(*mainFunction, &errs())) {
    cerr << "Erro na geração de código." << endl;
    exit(0);
  }

  error_code EC;
  raw_fd_ostream dest(outputFileName, EC, sys::fs::OF_None);

  if (EC) {
    errs() << "Could not open file: " << EC.message();
    return nullptr;
  }

  CodeGenFileType fileType = CGFT_ObjectFile;

  if (targetMachine->addPassesToEmitFile(pm, dest, nullptr, fileType)) {
    errs() << "TheTargetMachine can't emit a file of this type";
    return nullptr;
  }

  raw_fd_ostream destFonte(intermediateCodeFilename, EC, sys::fs::OF_Text);
  module->print(destFonte, nullptr);

  pm.run(*module);
  dest.flush();

  cout << "Wrote " << outputFileName << endl;
  cout << "Wrote " << intermediateCodeFilename << endl;
  return nullptr;
}