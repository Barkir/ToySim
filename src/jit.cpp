#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/IR/LLVMContext.h"

#include <iostream>

#include "errors.hpp"
#include "helper.hpp"
#include "commands_jit.hpp"


using namespace llvm;
using namespace llvm::orc;

ExitOnError ExitOnErr;

ThreadSafeModule createDemoModule() {
    auto Context = std::make_unique<LLVMContext>();
    auto M = std::make_unique<Module>("test", *Context);

    LLSPU SPU = {};
    Function *mainF = Function::Create(FunctionType::get(Type::getInt32Ty(*Context)), {}, false);
    ToyInstruction instr(352);
    lljitXOR(instr, Context, mainF, SPU);

}

int main(int argc, char **argv) {
    InitLLVM X(argc, argv);

    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    cl::ParseCommandLineOptions(argc, argv, "whatever");
    ExitOnErr.setBanner(std::string(argv[0]) + ": ");

    auto J = ExitOnErr(LLJITBuilder().create());
    auto M = createDemoModule();
    ExitOnErr(J->addIRModule(std::move(M)));

}
