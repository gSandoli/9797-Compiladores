#include "../ast.h"
#include "../chamada_funcao.h"
#include "../util/symboltable.h"
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

/*
 * Método para criar funções do LLVM com linkagem externa
 */
void createFunction(unique_ptr<Module> &module,
                    SymbolTable<Function> &functions, string const &name,
                    vector<Type *> const &args, Type *retType) {
  FunctionType *functionType = FunctionType::get(retType, args, false);
  Function *function = Function::Create(functionType, Function::ExternalLinkage,
                                        name, module.get());
  functions.push(name, function);
}

/*
 * Método que cria as funções LLVM da biblioteca padrão
 */
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

/*
 * Método principal para criação da representação intermediária e de código
 * executável
 */
Value *tradutor(unique_ptr<LLVMContext> &context,
                unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                Ast *root, string outputFileName,
                string intermediateCodeFilename,
                map<string, AllocaInst *> &namedValues) {

  // Inicialização dos targets para geração de código
  InitializeAllTargetInfos();
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmParsers();
  InitializeAllAsmPrinters();

  // Retorna o targetTriple da máquina atual, e configura o module para
  // utilizá-lo
  string targetTriple = getDefaultTargetTriple();
  module->setTargetTriple(targetTriple);
  string error;

  // Retorna o target desejado
  const Target *target = TargetRegistry::lookupTarget(targetTriple, error);
  if (!target) {
    errs() << error;
    return nullptr;
  }

  // Configurações para a máquina alvo.
  StringRef CPU = "generic";
  StringRef features = "";
  TargetOptions opt;
  Optional<Reloc::Model> RM = Optional<Reloc::Model>();
  TargetMachine *targetMachine =
      target->createTargetMachine(targetTriple, CPU, features, opt, RM);
  module->setDataLayout(targetMachine->createDataLayout());

  // Cria o prototipo da função main, do tipo void.
  FunctionType *mainProto = FunctionType::get(Type::getVoidTy(*context), false);
  Function *mainFunction = Function::Create(
      mainProto, GlobalValue::ExternalLinkage, "main", module.get());

  // Cria o bloco básico da função principal
  BasicBlock *block = BasicBlock::Create(*context, "entry", mainFunction);

  // Seta o entry point da main
  builder->SetInsertPoint(block);
  IRBuilder<> TmpB(&mainFunction->getEntryBlock(),
                   mainFunction->getEntryBlock().begin());

  // Cria as chamdas de funções da bilbioteca padrão
  SymbolTable<Function> functions;
  seedFunctions(functions, context, module);

  // Chama os métodos tradutor de toda a árvore
  root->tradutor(context, builder, module, functions, namedValues);

  // Cria o retorno da função main
  builder->CreateRetVoid();

  // Verifica o código gerado
  if (verifyFunction(*mainFunction, &errs())) {
    cerr << "Erro na geração de código." << endl;
    exit(0);
  }

  // Abre o descritor de arquivo destino
  error_code EC;
  raw_fd_ostream dest(outputFileName, EC, OF_None);

  if (EC) {
    errs() << "Não foi possível abrir o arquivo: " << EC.message();
    return nullptr;
  }

  // Cria o pass que vai gerar o object file
  legacy::PassManager pm;
  pm.add(createPrintModulePass(outs()));
  CodeGenFileType fileType = CGFT_ObjectFile;
  if (targetMachine->addPassesToEmitFile(pm, dest, nullptr, fileType)) {
    errs() << "TheTargetMachine não pode emitir um arquivo deste tipo";
    return nullptr;
  }

  // Escreve o arquivo .ll
  raw_fd_ostream destFonte(intermediateCodeFilename, EC, OF_Text);
  module->print(destFonte, nullptr);

  // Escreve o arquivo .o
  pm.run(*module);
  dest.flush();
  return nullptr;
}